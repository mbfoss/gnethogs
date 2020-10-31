#include "gettext.h"
#include "MainWindow.h"
#include "PendingUpdates.h"
#include <gtkmm.h>
#include <iostream>
#include <thread>

extern GResource *app_get_resource (void);

//CALLBACK BY NETHOGS MONITOR
static void onNethogsUpdate(int action, NethogsMonitorRecord const* update)
{
	PendingUpdates::setRowUpdate(action, *update);
}

static void nethogsMonitorThreadProc()
{
	const int status = nethogsmonitor_loop(&onNethogsUpdate, NULL, 1000);
	PendingUpdates::setNetHogsMonitorStatus(status);
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
   Gtk::Main kit(argc, argv);
	
    setlocale (LC_ALL, "");
    textdomain (PACKAGE);
	bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);
	
	//create app
    Glib::RefPtr<Gtk::Application> app = 
		Gtk::Application::create(argc, argv, "io.github.mb-gh.nethogs_gui");

	std::thread nethogs_monitor_thread(&nethogsMonitorThreadProc);
	 	 
	MainWindow w;

	app->signal_startup().connect(std::bind(&onAppStartup, std::ref(app)));	
	
	w.run(app);
	
	nethogsmonitor_breakloop();	
	nethogs_monitor_thread.join();
		
    return 0;
}
