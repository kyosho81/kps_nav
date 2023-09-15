#ifndef _STRATEGY_DLG_20191014_H_
#define _STRATEGY_DLG_20191014_H_

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
class strategy_table;


class strategy_dlg : public QDialog
{
	Q_OBJECT

public:

	strategy_dlg( QWidget *parent = 0 );
	~strategy_dlg();

	void init( map_scene* map_scene );
	void bind_lab_event( qt_eve::mouse_event::Slot_Lab event_slot );

private:
	QTimer *timer_;
	
	void init_timer();

	map_scene* map_scene_;
	//map_view* map_view_;
	strategy_table* strategy_table_;

	       
	QPushButton* btn_new_;	
	QPushButton* btn_del_;

	QPushButton* btn_load_;	
	QPushButton* btn_save_;
	QPushButton* btn_commit_;

	std::string str_file_;

private slots:
	void ChooseNew( bool flag );
	void ChooseDel( bool flag );

	void ChooseLoadFile( bool flag );
	void ChooseSaveFile( bool flag );
	void ChooseCommit( bool flag );

	void time_accepte_order();
	
	
};

#endif//_STRATEGY_DLG_20191014_H_