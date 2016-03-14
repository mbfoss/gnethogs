#include "gettext.h"
#include "MainWindow.h"
#include "PendingUpdates.h"
#include <iostream>
#include <sstream>

class RefPtr;
template<typename T>
static std::shared_ptr<T> 
loadWiget(Glib::RefPtr<Gtk::Builder>& builder, const char* name)
{
	T* ptr = nullptr;
    builder->get_widget(name, ptr);
    assert(ptr);
	return std::shared_ptr<T>(ptr);
}


MainWindow::MainWindow()
{
}

MainWindow::~MainWindow()
{
}

bool MainWindow::onTimer()
{
	if( PendingUpdates::getNetHogsMonitorStatus() == NETHOGS_STATUS_FAILURE)
	{
		char const* fail_msg = _("Failed to access network device(s).");
		std::ostringstream oss;
		oss << "<span foreground=\"red\">" << fail_msg << "</span>";
		m_p_label_sent_bytes->set_markup(oss.str());
		
		return false; //stops the timer
	} 
	
	PendingUpdates::Update update;
	while(PendingUpdates::getRowUpdate(update))
	{
		//update row data map and list store
		auto it = m_rows_data.lower_bound(update.record.record_id);
		bool const existing = (it != m_rows_data.end() && it->first == update.record.record_id);
		
		if( update.action == NETHOGS_APP_ACTION_REMOVE )
		{
			if( existing )
			{
				m_list_store->erase(it->second.list_item_it);
				m_rows_data.erase(update.record.record_id);
			}
		}
		else
		{
			Gtk::ListStore::iterator ls_it;
			if( existing )
			{
				ls_it = it->second.list_item_it;
			}
			else
			{ 
				ls_it = m_list_store->append();
				it = m_rows_data.insert(it, std::make_pair(update.record.record_id, RowData(ls_it)));
				//set fixed fields
				(*ls_it)[m_tree_data.pid ] = update.record.pid;
				(*ls_it)[m_tree_data.name] = getFileName(update.record.name);
				(*ls_it)[m_tree_data.path] = update.record.name;
			}

			//updte other fields
			(*ls_it)[m_tree_data.device_name] = update.record.device_name;
			(*ls_it)[m_tree_data.uid   	    ] = update.record.pid?gtUserName(update.record.uid):"";
			(*ls_it)[m_tree_data.sent_bytes ] = update.record.sent_bytes;
			(*ls_it)[m_tree_data.recv_bytes ] = update.record.recv_bytes;
			(*ls_it)[m_tree_data.sent_kbs   ] = update.record.sent_kbs;
			(*ls_it)[m_tree_data.recv_kbs	] = update.record.recv_kbs;

			//update total stats
			m_total_data.sent_bytes += (update.record.sent_bytes - it->second.sent_bytes);
			m_total_data.recv_bytes += (update.record.recv_bytes - it->second.recv_bytes);			

			//save stat data
			it->second.sent_bytes = update.record.sent_bytes;
			it->second.recv_bytes = update.record.recv_bytes;
			it->second.sent_kbs   = update.record.sent_kbs;
			it->second.recv_kbs	  = update.record.recv_kbs;
		}
	}

	//update total stats
	m_total_data.sent_kbs = 0;
	m_total_data.recv_kbs = 0;
	for(auto const& v : m_rows_data)
	{
		m_total_data.sent_kbs += v.second.sent_kbs;
		m_total_data.recv_kbs += v.second.recv_kbs;
	}
	
	char buffer[30];
	
	snprintf(buffer, sizeof(buffer), "Sent: %s", formatByteCount(m_total_data.sent_bytes).c_str());
	m_p_label_sent_bytes->set_label(buffer);
	
	snprintf(buffer, sizeof(buffer), "Received: %s", formatByteCount(m_total_data.recv_bytes).c_str());
	m_p_label_recv_bytes->set_label(buffer);

	snprintf(buffer, sizeof(buffer), "Outbound: %s", formatBandwidth(m_total_data.sent_kbs).c_str());
	m_p_label_sent_kbs->set_label(buffer);

	snprintf(buffer, sizeof(buffer), "Inbound: %s", formatBandwidth(m_total_data.recv_kbs).c_str());
	m_p_label_recv_kbs->set_label(buffer);

	return true;
}

void MainWindow::onLoaded()
{
	if( !m_timer_connection.connected() )
	{
		m_timer_connection = Glib::signal_timeout().connect_seconds(sigc::bind(&MainWindow::onTimer, this), 1);
	}
}

bool MainWindow::onClosed(GdkEventAny*)
{
	m_timer_connection.disconnect();
	return false;
}

void MainWindow::run(Glib::RefPtr<Gtk::Application> app)
{   
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();

	builder->add_from_resource("/nethogs_gui/window.glade");
	builder->add_from_resource("/nethogs_gui/headerbar.ui");
	
	
	//get widgets
	m_window = loadWiget<Gtk::ApplicationWindow>(builder, "main_window");
	m_p_label_sent_bytes = loadWiget<Gtk::Label>(builder, "label_stat_sent");
	m_p_label_recv_bytes = loadWiget<Gtk::Label>(builder, "label_stat_recv");
	m_p_label_sent_kbs   = loadWiget<Gtk::Label>(builder, "label_stat_sent_bw");
	m_p_label_recv_kbs   = loadWiget<Gtk::Label>(builder, "label_stat_recv_bw");
	
	std::shared_ptr<Gtk::TreeView>  tree_view = loadWiget<Gtk::TreeView>(builder, "treeview");
	std::shared_ptr<Gtk::HeaderBar> pheaderbar = loadWiget<Gtk::HeaderBar>(builder, "headerbar");
		
	//set title bar
	m_window->set_titlebar(*pheaderbar);
		
	//Create the Tree model
	 m_list_store = m_tree_data.createListStore(); 
	 assert(m_list_store);
	tree_view->set_model(m_list_store);
	m_tree_data.setTreeColumns(tree_view.get());
	
	//Connect signals
	m_window->signal_realize().connect(std::bind(&MainWindow::onLoaded, this));
	m_window->signal_delete_event().connect(sigc::mem_fun(this,&MainWindow::onClosed));
	m_window->signal_show().connect(sigc::mem_fun(this,&MainWindow::onShow));
	
	//add actions
	app->add_action("about", sigc::mem_fun(this,&MainWindow::onAction_About));
	app->add_action("quit",  sigc::mem_fun(this,&MainWindow::onAction_Quit));
		
	app->run(*m_window);
}

void MainWindow::onShow()
{		
}

void MainWindow::onAction_About()
{
	Gtk::AboutDialog dlg;

	dlg.set_transient_for(*m_window);
	dlg.set_program_name(PACKAGE_NAME);
	dlg.set_version(PACKAGE_VERSION);
	dlg.set_logo_icon_name("gnethogs"),
	dlg.set_comments(_("Per-application bandwidth usage statistics."));
	dlg.set_authors({"<a href=\"mailto:mbfoss@fastmail.com\">Mohamed Boussaffa</a>"});
	dlg.set_license(_("This program comes with ABSOLUTELY NO WARRANTY." "\n"
					 "See the GNU General Public License, version 2 or later for details."));
	dlg.run();
}

void MainWindow::onAction_Quit()
{
	m_window->close();
}
