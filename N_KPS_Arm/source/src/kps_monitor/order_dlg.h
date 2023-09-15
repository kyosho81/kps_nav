#ifndef _ORDER_DLG_20191014_H_
#define _ORDER_DLG_20191014_H_

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
class order_table;

class order_dlg : public QDialog
{
	Q_OBJECT

public:

	order_dlg( QWidget *parent = 0 );
	~order_dlg();

	void init( map_scene* map_scene );
	void bind_lab_event( qt_eve::mouse_event::Slot_Lab event_slot );

private:
	QTimer *timer_;
	
	void init_timer();

	map_scene* map_scene_;
	//map_view* map_view_;
	role_table* role_table_;
	order_table* order_run_table_;
	order_table* order_his_table_;
	       
	bool b_accepte_order_;
	QPushButton* btn_accepte_order_;	
	QRadioButton* btn_run_order_;
	QRadioButton* btn_his_order_;
	bool b_run_hist_;


	int i_scene_show_cnt_;

private slots:
	void ChooseRunHis( bool flag );
	void ChooseAccepteOrder( bool flag );
	void time_accepte_order();
	

};

#endif//_ORDER_DLG_20191014_H_