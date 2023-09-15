#ifndef _PARA_DLG_20201116_H_
#define _PARA_DLG_20201116_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>
#include "scene/mouse_event.h"
#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#endif


class map_scene;
class map_view;
class QtProperty;
class QtVariantProperty;
class QtVariantPropertyManager;
class QtEnumPropertyManager;
class QtBoolPropertyManager;
class QtTreePropertyBrowser;
class QtVariantEditorFactory;
class QtEnumEditorFactory;
class QtCheckBoxFactory;

class robot_item;
class config_it;

class Plot;

class para_dlg : public QDialog
{
	Q_OBJECT

public:

	para_dlg( QWidget *parent = 0 );
	~para_dlg();

	void init();

	void bind_lab_event( qt_eve::mouse_event::Slot_Lab event_slot );
	void init_timer();
	void stop_timer();
	
	bool s_update_laser( const SLaser& laser );
	bool s_update_laser_ex( const SLaser_Ex& laser_ex );

	bool show_laser_ex_seg( const SLaser_Ex& laser_ex );

private:

	


	QWidget* create_para_wiget();
	int create_group_pro(QtTreePropertyBrowser *variantEditor);
	
	void create_x_y_axle();
	void create_laser_y();

	void get_triangle( QPolygonF &p3, const SPos &pos);
	QTimer *timer_;

	map_scene* map_scene_;
	map_view* map_view_;

	SBuffer<SLaser> th_show_laser_;

public slots:

	void update_sensor();
	void valueChanged(QtProperty *property, const QVariant &value);
	//para grid
private:
	QtVariantPropertyManager *variantManager_;
	QtEnumPropertyManager *enumManager_;
	QtBoolPropertyManager *boolManager_;

	QtVariantEditorFactory* variantFactory_;
	QtEnumEditorFactory* comboBoxFactory_;
	QtCheckBoxFactory* checkBoxFactory_;

	QtTreePropertyBrowser *variantEditor_;

	QPushButton* btn_upload_;	    //upload from robot
	QPushButton* btn_download_;	    //download to robot

	QPushButton* btn_import_;	    //import from file
	QPushButton* btn_export_;	    //export to file

	QPushButton* btn_save_;	    //download to robot
	QPushButton* btn_exit_;	    //exit without save

	robot_item* get_robot_item();

private slots:
	
	void ChooseUpload( bool flag );
	void ChooseDownload(bool flag );

	void ChooseImport( bool flag );
	void ChooseExport(bool flag );

	void ChooseSave( bool flag );
	void ChooseExit(bool flag );

private:
	bool b_connection_;


	void get_config();
	

	
	QGraphicsLineItem* item_line_;

	Plot* plot_;
	int iinten_;

private:
	
	bool load_para();
	void clear_para();

	bool add_para( config_it* c_para);
	bool add_para_string(const std::string &group_name,const std::string &para_name,const std::string &para_value);
	bool add_para_int(const std::string &group_name,const std::string &para_name,const int &i_data,const int &i_min,const int &i_max);
	bool add_para_double(const std::string &group_name,const std::string &para_name,const double &d_data,const double &d_min,const double &d_max);

	QtProperty* get_group(const std::string &group_name);

	bool add_para_map(const std::string &para_name,QtProperty* pro);
	std::string get_type(const std::string str_name);

	std::map< std::string,QtProperty*> m_group_name;
	std::map< std::string,QtProperty*> m_name_value;
	std::map< std::string,std::string> m_name_type;

	std::map< std::string, std::string > m_update;
};

#endif//_PARA_DLG_20201116_H_