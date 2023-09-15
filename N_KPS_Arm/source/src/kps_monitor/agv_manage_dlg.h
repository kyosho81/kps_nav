#ifndef _AGV_MANAGE_MONITOR_DLG_H_
#define _AGV_MANAGE_MONITOR_DLG_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "dispatching/traffic_control.h"
#endif

class map_scene;
class agv_item;
class agv_manage_table;



class agv_manage_dlg : public QDialog
{
	Q_OBJECT

public:

	agv_manage_dlg( QWidget *parent = 0 );
	~agv_manage_dlg();

	void init( map_scene* map_scene );

	void init_timer();


	public slots:
		void updateTimerEvent();


	void ChooseSearch( bool flag );
	void ChooseLock( bool flag );
	void ChooseSetInit( bool flag );
	void ChooseSetOffline( bool flag );


	void ChooseSimFast( bool flag );
	void ChooseSimSlow( bool flag );

	void remove_agv();
	

private:
	QTimer *timer_;
	agv_manage_table* table_;

	QPushButton* btn_search_;
	QPushButton* btn_lock_;
	QPushButton* btn_set_init_;
	QPushButton* btn_set_offline_;

	QPushButton* btn_sim_fast_;
	QPushButton* btn_sim_low_;
	QLineEdit* qedit_speed_;
	int i_speed_;
	int i_heart_beat_;


private:

	map_scene* map_scene_;

	void update_agv_item( std::map<int,agv_show_data> &show_data);
	
	bool check_agv_show(  std::map<int,int> &m_online );
	bool get_agv_item( agv_item* &p_agv_item , const int &id );
	std::map<int,agv_item* > m_agv_item_;


};

#endif//_AGV_MANAGE_MONITOR_DLG_H_