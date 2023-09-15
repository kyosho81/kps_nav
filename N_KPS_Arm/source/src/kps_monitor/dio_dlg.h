#ifndef _DIO_DLG_20230220_H_
#define _DIO_DLG_20230220_H_

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
class dio_table;


class dio_dlg : public QDialog
{
	Q_OBJECT

public:

	dio_dlg( QWidget *parent = 0 );
	~dio_dlg();

	void init( map_scene* map_scene );
	void bind_lab_event( qt_eve::mouse_event::Slot_Lab event_slot );

private:

	QTimer *timer_;
	
	bool b_begin_;
	void do_timer(bool b_begin);

	map_scene* map_scene_;
	//map_view* map_view_;
	dio_table* dio_table_;

	       

	QPushButton* btn_load_;	
	QPushButton* btn_save_;
	QPushButton* btn_commit_;

	std::string str_file_;
	bool get_dio_bind();
	std::map<std::string, SDIO_NM_INDEX> m_dio_bind_;

private slots:

	void ChooseLoadFile( bool flag );
	void ChooseSaveFile( bool flag );
	void ChooseCommit( bool flag );

	void time_get_dio_data();
	
	
};

#endif//_DIO_DLG_20230220_H_