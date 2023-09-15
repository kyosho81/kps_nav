#ifndef _CALIB_DLG_20191014_H_
#define _CALIB_DLG_20191014_H_

#include <QTimer>
#include <QPolygonF>

#include <QtGui>
#include <QDialog>
#include <QSplitter>

#ifndef Q_MOC_RUN 
#include "boost/unordered/unordered_map.hpp"
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "scene/mouse_event.h"
#include "sub_map_loc/laser_special_loc.h"
#endif


class map_scene;
class map_view;
class QtProperty;
class QtVariantProperty;
class QtVariantPropertyManager;
class QtEnumPropertyManager;
class QtBoolPropertyManager;
class robot_item;
class special_loc_base;
class calib_tools;
class shape_dlg;
class map_item;
class GridMap;

class Plot;

class Calib_dlg : public QSplitter
{
	Q_OBJECT

public:

	Calib_dlg( QWidget *parent = 0 );
	~Calib_dlg();


	void bind_lab_event( qt_eve::mouse_event::Slot_Lab event_slot );
	void init_timer();
	void stop_timer();
	
	bool s_update_laser( const SLaser& laser );
	bool s_update_wj_laser( const SLaser& laser );
	bool s_update_pavo2_laser( const SLaser& laser );
	bool s_update_laser_ex( const SLaser_Ex& laser_ex );
	bool s_update_laser_ex2( const SLaser_Ex& laser_ex );
	bool s_update_laser_ex3( const SLaser_Ex2& laser_ex2 );
	bool s_update_laser_ex4( const SLaser_Ex& laser_ex );
	bool s_update_ref( const SReflector &laser_ref );

	bool show_laser_ex_seg( const SLaser_Ex& laser_ex );
	bool show_laser_seg( const SLaser& laser );

private:

	void init();
	void set_sick_lms();
	void set_r2000_para();
	void set_pavo_para();
	void set_wj712_para();
	void set_wj718mini_para();
	void set_wj719_para();
	void set_pavo2_ls50h_para();
	void set_hins_le_para();

	QWidget* create_para_wiget();
	
	void create_x_y_axle();
	void create_laser_y();

	void get_triangle( QPolygonF &p3, const SPos &pos);
	QTimer *timer_;

	map_scene* map_scene_;
	map_view* map_view_;

	SBuffer<SLaser> th_show_laser_;

	THSafe<SPOS_CONFIDENCE> th_pos_;
	THSafe<SWorldLM> th_wlm_;
	THSafe<bool> th_save_laser_ex_;
	THSafe<SReflector> th_ref_;

	int i_safe_cnt_;
public slots:
	
	void update_sensor();
	void valueChanged(QtProperty *property, const QVariant &value);
	//para grid
private:
	QtVariantPropertyManager *variantManager_;
	QtEnumPropertyManager *enumManager_;
	QtBoolPropertyManager *boolManager_;

	QtVariantProperty* item_laser_type_;
	QtVariantProperty* item_laser_ip_;
	QtProperty* item_laser_reverse_;
	QtVariantProperty* item_laser_start_angle_;
	QtVariantProperty* item_laser_range_max_;
	QtVariantProperty* item_laser_range_min_;
	QtVariantProperty* item_laser_dx_;
	QtVariantProperty* item_laser_dy_;
	QtVariantProperty* item_laser_resolution_;

	QtVariantProperty* item_calib_line_;

	QtVariantProperty* item_robot_shape_;
	QtVariantProperty* item_stop_in_shape_;
	QtVariantProperty* item_stop_out_shape_;
	QtVariantProperty* item_slow_shape_;
	QtVariantProperty* item_ccw_shape_;
	QtVariantProperty* item_cw_shape_;
	QtVariantProperty* item_payload_egn1_;
	QtVariantProperty* item_payload_egn2_;
	
	std::string str_laser_type_;
	std::string str_robot_shape_;
	
	std::string str_stop_in_shape_;
	std::string str_stop_out_shape_;
	std::string str_slow_shape_;
	std::string str_ccw_shape_;
	std::string str_cw_shape_;
	
	std::string str_payload_egn1_;
	std::string str_payload_egn2_;


	QPushButton* btn_connection_;	    //test connection
	QPushButton* btn_laser_ex_;	
	QPushButton* btn_calib_laser_;  //calib laser para
	QPushButton* btn_seg_laser_;	//over
	QPushButton* btn_steering_;
	QPushButton* btn_show_shape_;

	QPushButton* btn_save_para_;

	QPushButton* btn_show_lasermap_;
	QPushButton* btn_save_laser_ex_;
	QPushButton* btn_calib_ref_;

	robot_item* get_robot_item();
	map_item* get_map_item();

	shape_dlg* p_shape_dlg_;
	GridMap* gmap_laser_inf_;

	std::map< std::string, std::string > m_update_para_;

private slots:
	
	void ChooseConnection( bool flag );
	void ChooseLaserEx( bool flag );
	void ChooseCalibLaser(bool flag );
	void ChooseSegLaser(bool flag );

	void ChooseSteering(bool flag);

	void ChooseShowShape(bool flag );
	void ChooseSavePara(bool flag );

	void ChooseShowLasermap(bool flag );
	void ChooseSaveLaserEx(bool flag );
	void ChooseCalibRef(bool flag );

	void filter_r2000(std::string str_file);
	void filter_wj712(std::string str_file);
	void filter_wj719(std::string str_file);
	void filter_wj718mini(std::string str_file);

private:
	bool b_connection_;
	void show_data(const SLaser_para &para,const Laser_type &laser_type);
	void get_data(SLaser_para &para,Laser_type &laser_type);
	std::string set_laser_para();

	std::string laser_type_cov(Laser_type type);
	void get_config();
	void show_loc_pos( SWorldLM wlm , SPOS_CONFIDENCE con_pos );
	void shape_show();
	
	SLaser_para laser_para_;
	Laser_type laser_type_;
	std::string str_ip_;
	
	QGraphicsLineItem* item_line_;
	
	Plot* plot_;
	int iinten_;

	int i_8400_7200_720_;
	F32 f_r2000_start_angle_;

private:
	bool b_laser_ex_;
	int i_sub_laser_;
	int i_sub_laser_ex_;
	int i_sub_ref_;
	//sm local
private:
	special_loc_base* p_special_loc_base_;

private:
	calib_tools* calib_tools_;

private:
	int i_dev_wj712_7200_;
	int i_dev_wj719_10800_;
	F32 f_wj712_start_angle_;

private:
	std::vector<std::pair<std::string,QtVariantProperty*>> v_shape_pro_;
};

#endif//_CALIB_DLG_20191014_H_