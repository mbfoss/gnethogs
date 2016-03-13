#include "PendingUpdates.h"
#include <string.h>

std::mutex PendingUpdates::m_mutex;
PendingUpdates::RowUpdatesMap PendingUpdates::m_row_updates_map;
int PendingUpdates::m_nethogs_monitor_status = NETHOGS_STATUS_OK;

void PendingUpdates::setRowUpdate(int action, NethogsMonitorRecord const* record)
{
	if( action == NETHOGS_APP_ACTION_REMOVE || record->sent_bytes || record->recv_bytes )
	{
		//save the update for GUI use
		std::lock_guard<std::mutex> lock(m_mutex);
		Update update;
		memset(&update, 0, sizeof(update));
		update.action = action;
		update.record_id = record->record_id;
		update.record = ((action == NETHOGS_APP_ACTION_REMOVE)? nullptr : record);
		m_row_updates_map[record->record_id] = update;
	}	
}

bool PendingUpdates::getRowUpdate(PendingUpdates::Update& update)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if( m_row_updates_map.empty() )
		return false;
	update = m_row_updates_map.begin()->second;
	m_row_updates_map.erase(m_row_updates_map.begin());
	return true;
}

void PendingUpdates::setNetHogsMonitorStatus(int status) 
{ 
	std::lock_guard<std::mutex> lock(m_mutex);
	m_nethogs_monitor_status = status; 
}

int PendingUpdates::getNetHogsMonitorStatus()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_nethogs_monitor_status;
}
