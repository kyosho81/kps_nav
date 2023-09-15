#ifndef _INTERFACE_DLG_20191014_H_
#define _INTERFACE_DLG_20191014_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>

#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "scene/mouse_event.h"

#endif

class map_scene;
class map_view;
class map_item;
class agv_item;
class traffic_agv_data;
class role_table;
class interface_table;
class manual_order;
class manual_table;

class interface_dlg : public QDialog
{
	Q_OBJECT

public:

	interface_dlg( QWidget *parent = 0 );
	~interface_dlg();

	void init( map_scene* map_scene );
	void bind_lab_event( qt_eve::mouse_event::Slot_Lab event_slot );

private:
	QTimer *timer_;
	
	void init_timer();

	map_scene* map_scene_;
	//map_view* map_view_;

	       
	
	QPushButton* btn_new_order_;	
	QPushButton* btn_del_order_;
	QPushButton* btn_create_cmd_;
	QPushButton* btn_commit_;

	interface_table* interface_table_;
	manual_table* manual_table_;

	std::map<std::string ,manual_order*> m_manual_order_tb_;

private slots:
	void ChooseNewOrder( bool flag );
	void ChooseDelOrder( bool flag );
	void ChooseCreateCMD( bool flag );
	void ChooseCommit( bool flag );

	void time_show_manual();
	

};

#endif//_INTERFACE_DLG_20191014_H_