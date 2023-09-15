#ifndef _DATA_EDIT_DLG_20201116_H_
#define _DATA_EDIT_DLG_20201116_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>
#include "scene/mouse_event.h"
#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "meta_data/meta_data.h"
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


// typedef struct _SUpdatePara
// {
// 	std::string str_id_;
// 	std::string str_group_;
// 	std::string str_name_;
// 	std::string str_data_;
// 
// }SUpdatePara;

class data_edit_dlg : public QDialog
{
	Q_OBJECT

public:

	data_edit_dlg( QWidget *parent = 0 );
	~data_edit_dlg();

	void init(map_scene* map_sc);

	//void bind_lab_event( qt_eve::mouse_event::Slot_Lab event_slot );
	void init_timer();
	void stop_timer();

private:


	QWidget* create_para_wiget();
	int create_group_pro(QtTreePropertyBrowser *variantEditor);


	QTimer *timer_;
	QWidget *parent_;
	map_scene* map_sc_;

	bool split_id_data(std::string &str_type , std::string &str_id, std::string str_sig);


public slots:

	void time_event();
	void valueChanged(QtProperty *property, const QVariant &value);
	
	void slot_show_data(QString str);
	
	//para grid
private:
	QtVariantPropertyManager *variantManager_;
	QtEnumPropertyManager *enumManager_;
	QtBoolPropertyManager *boolManager_;

	QtVariantEditorFactory* variantFactory_;
	QtEnumEditorFactory* comboBoxFactory_;
	QtCheckBoxFactory* checkBoxFactory_;

	QtTreePropertyBrowser *variantEditor_;


	bool b_run_task_;
	QPushButton* btn_save_;	    //save to project
	QPushButton* btn_refresh_;	//refresh project
	QPushButton* btn_add_;	//add cargo type
	QPushButton* btn_del_;	//del cargo type

public slots:
	void ChooseAdd(bool flag);
	void ChooseDel(bool flag);
//private slots:

    void ChooseSave( bool flag );
// 	void ChooseExit(bool flag );

private:
	void show_node(int id);
	void show_edge(int id);
	void show_reflector(int id);
	void show_lab(int id);
	void show_rect(std::string str_id);
	void show_range(std::string str_id);
	void show_cargo_type(int id);
	void show_pallet_type(int id);
	void show_producer(int id);
	void show_consumer(int id);
	void show_processer(int id);
	void show_storage(int id);
	void show_charge(int id);
	void show_qrcode(int id);

	bool update_node(int id , std::string str_group, std::string str_name ,std::string str_data);
	bool update_edge(int id , std::string str_group, std::string str_name ,std::string str_data);
	bool update_reflector(int id , std::string str_group, std::string str_name ,std::string str_data);
	bool update_cargo_type(int id , std::string str_group, std::string str_name ,std::string str_data);
	bool update_pallet_type(int id , std::string str_group, std::string str_name ,std::string str_data);
	bool update_producer(int id , std::string str_group, std::string str_name ,std::string str_data);
	bool update_consumer(int id , std::string str_group, std::string str_name ,std::string str_data);
	bool update_processr(int id , std::string str_group, std::string str_name ,std::string str_data);
	bool update_storage(int id , std::string str_group, std::string str_name ,std::string str_data);	
	bool update_charge(int id , std::string str_group, std::string str_name ,std::string str_data);
	bool update_rect(std::string str_id , std::string str_group, std::string str_name ,std::string str_data);
	bool update_range(std::string str_id , std::string str_group, std::string str_name ,std::string str_data);
	bool update_qrcode(int id , std::string str_group, std::string str_name ,std::string str_data);

	std::string str_type_;
	std::string str_id_ ;

private:

	void clear_data();

	bool add_para( const std::string &group_name, SSMetaData &para);
	bool add_para_string(const std::string &group_name,const std::string &para_name,const std::string &para_value, bool b_read_only);
	bool add_para_int(const std::string &group_name,const std::string &para_name,const int &i_data,const int &i_min,const int &i_max, bool b_read_only);
	bool add_para_double(const std::string &group_name,const std::string &para_name,const double &d_data,const double &d_min,const double &d_max, bool b_read_only);
	bool add_cmb_enum( const std::string &group_name,const std::string &para_name,const int &e_data,std::vector<std::string> v_cmb, bool b_read_only  );
	bool add_bool(const std::string &group_name,const std::string &para_name,const bool &i_data , bool b_read_only );
	bool add_group(const std::string &group_name,const std::string &para_name, const std::string &para_value,std::vector<std::string> v_group, bool b_read_only );
	bool add_color(const std::string &group_name,const std::string &para_name, const std::string &para_value, bool b_read_only);
	

	//get QtProperty* from group name
	QtProperty* get_group(const std::string &group_name);
	void clear_group();
	std::map< std::string,QtProperty*> m_group_name;
	
	//get group name from QtProperty*(when valume change) 
	std::string get_group_pro(QtProperty* property);
	void add_pro_group(QtProperty* property, std::string str_group );
	std::map<QtProperty*, std::string> m_property_group_;

// 	//when bind data change ,should reflash data
// 	QtProperty* get_pro_by_gname(std::string str_group,std::string str_name);
// 	void add_group_name_pro(std::string str_group,std::string str_name,QtProperty* pro);
// 	std::map<std::string,QtProperty*> m_group_name_property_;

};

#endif//_DATA_EDIT_DLG_20201116_H_