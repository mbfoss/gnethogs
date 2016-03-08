#include "../config.h"
#include <libintl.h>
#define _(String) gettext (String)

#include "MainWindow.h"
#include <gtkmm.h>
#include <iostream>

extern GResource *app_get_resource (void);

int nethogs_monitor_status = 0;

std::mutex row_updates_map_mutex;
std::map<int, NethogsMonitorUpdate> row_updates_map;

//ASYNC CALLBACK BY NETHOGS MONITOR
static void onNethogsUpdate(NethogsMonitorUpdate const* update)
{
	if( update->action == NETHOGS_APP_ACTION_REMOVE ||
		update->sent_bytes || update->recv_bytes )
	{
		//save the update for GUI use
		std::lock_guard<std::mutex> lock(row_updates_map_mutex);
		row_updates_map[update->pid] = *update;
	}
}

static void onAppStartup(Glib::RefPtr<Gtk::Application> & app)
{
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
	builder->add_from_resource("/nethogs_gui/appmenu.ui");	
	//set app menu
	auto appmenu = Glib::RefPtr<Gio::MenuModel>::cast_dynamic(builder->get_object("appmenu"));
	app->set_app_menu(appmenu);	
}

int main(int argc, char* argv[])
{	
    setlocale (LC_ALL, "");
    textdomain (PACKAGE);
	bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);
	
	//create app
    Glib::RefPtr<Gtk::Application> app = 
		Gtk::Application::create(argc, argv, "io.github.mb-gh.nethogs_gui");

	nethogsmonitor_register_callback(&onNethogsUpdate);
	nethogs_monitor_status = nethogsmonitor_start();
	 	 
	MainWindow w;

	app->signal_startup().connect(std::bind(&onAppStartup, std::ref(app)));	
	
	w.run(app);
	
	nethogsmonitor_stop();	
		
    return 0;
}
