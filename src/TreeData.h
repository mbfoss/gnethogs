#ifndef TREE_MODEL_H
#define TREE_MODEL_H

#include <gtkmm.h>
#include <list>
#include "Tools.h"

//Tree model columns
class TreeData
{
public:
	TreeData()
	{ 

	}
	
	Glib::RefPtr<Gtk::ListStore> createListStore()
	{
		Gtk::TreeModel::ColumnRecord column_record;
		column_record.add(name);
		column_record.add(device_name);
		column_record.add(uid);
		column_record.add(pid);
		column_record.add(sent_bytes);
		column_record.add(recv_bytes);
		column_record.add(sent_kbs);
		column_record.add(recv_kbs);
		column_record.add(path);		
		return Gtk::ListStore::create(column_record);
	}
	

	static void pid_CellDataFun(Gtk::CellRenderer* renderer, 
								const Gtk::TreeModel::iterator& iter, 
								int model_column)
	{
		Gtk::CellRendererText* p_text_renderer = dynamic_cast<Gtk::CellRendererText*>(renderer);
		if(iter)
		{
			//Get the value from the model.
			Gtk::TreeModel::Row row = *iter;
			int32_t value = 0;
			row.get_value(model_column, value);
			if( !value )
			{
				p_text_renderer->property_text() = "";
			}
		}
	}
	
	static void byteCount_CellDataFun(Gtk::CellRenderer* renderer, 
									  const Gtk::TreeModel::iterator& iter, 
									  int model_column)
	{
		Gtk::CellRendererText* p_text_renderer = dynamic_cast<Gtk::CellRendererText*>(renderer);
		if(iter)
		{
			//Get the value from the model.
			Gtk::TreeModel::Row row = *iter;
			uint32_t value = 0;
			row.get_value(model_column, value);
			//Show the text representation in the view:
			p_text_renderer->property_text() = formatByteCount(value).c_str();
		}
	}	
	
	static void bandwidth_CellDataFun(Gtk::CellRenderer* renderer, 
									  const Gtk::TreeModel::iterator& iter, 
									  int model_column)
	{
		Gtk::CellRendererText* p_text_renderer = dynamic_cast<Gtk::CellRendererText*>(renderer);
		if(iter)
		{
			//Get the value from the model.
			Gtk::TreeModel::Row row = *iter;
			float value = 0;
			row.get_value(model_column, value);
			//Show the text representation in the view:
			p_text_renderer->property_text() = formatBandwidth(value).c_str();
		}
	}		
	
	void setTreeColumns(Gtk::TreeView* tree_view)
	{
		using namespace std::placeholders;
		
		Gtk::TreeView::Column* pcolumn = 0;
		int col = 0;
				
		tree_view->append_column(_("Name"), name);
		tree_view->append_column(_("Device"), device_name);
		tree_view->append_column(_("User"), uid);
		
		tree_view->append_column(_("Process ID"), pid);
		col = tree_view->get_n_columns() - 1;
		pcolumn = tree_view->get_column(col);
		pcolumn->set_cell_data_func(*pcolumn->get_cells().at(0),
			std::bind(&pid_CellDataFun, _1, _2, col));
		
		tree_view->append_column(_("Sent"), sent_bytes);
		col = tree_view->get_n_columns() - 1;
		pcolumn = tree_view->get_column(col);
		pcolumn->set_cell_data_func(*pcolumn->get_cells().at(0),
			std::bind(&byteCount_CellDataFun, _1, _2, col));
		
		tree_view->append_column(_("Received"), recv_bytes);
		col = tree_view->get_n_columns() - 1;
		pcolumn = tree_view->get_column(col);
		pcolumn->set_cell_data_func(*pcolumn->get_cells().at(0),
			std::bind(&byteCount_CellDataFun, _1, _2, col));

		tree_view->append_column(_("Outboud"), sent_kbs);
		col = tree_view->get_n_columns() - 1;
		pcolumn = tree_view->get_column(col);
		pcolumn->set_cell_data_func(*pcolumn->get_cells().at(0),
			std::bind(&bandwidth_CellDataFun, _1, _2, col));		
		
		tree_view->append_column(_("Inbound"), recv_kbs);
		col = tree_view->get_n_columns() - 1;
		pcolumn = tree_view->get_column(col);
		pcolumn->set_cell_data_func(*pcolumn->get_cells().at(0),
			std::bind(&bandwidth_CellDataFun, _1, _2, col));	
				
		tree_view->set_tooltip_column(tree_view->get_n_columns() );

		for(int pos = 0; pos < tree_view->get_n_columns(); ++pos)
		{
			Gtk::TreeView::Column* pcolumn = tree_view->get_column(pos);
			pcolumn->set_sort_column(pos);
		}	
	}
		
	Gtk::TreeModelColumn<Glib::ustring> name;
	Gtk::TreeModelColumn<Glib::ustring> device_name;
	Gtk::TreeModelColumn<Glib::ustring> uid;
	Gtk::TreeModelColumn<int32_t> 		pid;
	Gtk::TreeModelColumn<uint32_t> 		sent_bytes;
	Gtk::TreeModelColumn<uint32_t> 		recv_bytes;
	Gtk::TreeModelColumn<float>	 		sent_kbs;
	Gtk::TreeModelColumn<float> 		recv_kbs;
	Gtk::TreeModelColumn<Glib::ustring> path;
};

#endif
