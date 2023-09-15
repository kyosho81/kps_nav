
#include <QDebug>
#include "interpro_shared/sh_pool.hpp"
#include "robot/RobotStruct.h"
#include "interface/xml_rpc_client.h"
#include "interface/cfg.hpp"

#include "scene/map_view.h"
#include "scene/map_scene.h"
#include "scene/mouse_event.h"

#include "robot/Geometry.h"
#include "Comm/Comm.h"
#include "Comm/configs.h"

#include "msg_pump/msg_pump.hpp"
#include "laser_filter/laser_filter.h"
#include "laser_filter/laser_filter_ex.h"
#include "laser_filter/laser_filter_ex2.h"
#include "robot/robot_remote_para.h"

#include "property/qtpropertymanager.h"
#include "property/qtvariantproperty.h"
#include "property/qttreepropertybrowser.h"
#include "property/qteditorfactory.h"

#include "device/device_pool.h"
#include "scene/robot_item.h"
#include "scene/map_item.h"
#include "plot/Plot_Lib.h"
#include "reflected_pillar/reflected_pillar.h"
#include "project/project_manage.h"
#include "calib/calib_tools.h"
#include "shape_dlg.h"
#include "mapserver/MapServer.h"

#include "calib_dlg.h"

Calib_dlg::Calib_dlg( QWidget *parent):
th_show_laser_(1)
{
	init();
	//get_config();
	show_data(laser_para_,laser_type_);

	//ignore show data to save para
	connect(variantManager_, SIGNAL(valueChanged(QtProperty *, QVariant)),
		this, SLOT(valueChanged(QtProperty *, QVariant)));
// 	plot_ = new Plot();
// 	iinten_ = plot_->AddPlot("intensities",100);
// 	plot_->show();

	b_laser_ex_ = false;
	i_sub_laser_ = -1;
	i_sub_laser_ex_ = -1;
	i_sub_ref_ = -1;

	p_special_loc_base_ = 0;
	calib_tools_ = 0;

	SPOS_CONFIDENCE cpos;
	memset(&cpos,0,sizeof(SPOS_CONFIDENCE));
	th_pos_ = cpos;

	p_shape_dlg_ = 0;

	gmap_laser_inf_ = 0;

	th_save_laser_ex_ = false;
	i_safe_cnt_ = 0;
}

Calib_dlg::~Calib_dlg()
{
	
}
void Calib_dlg::bind_lab_event( qt_eve::mouse_event::Slot_Lab event_slot )
{
	map_scene_->bind_lab_event(event_slot);
}
void Calib_dlg::init(){

	i_8400_7200_720_ = 2;
	Config::getConfig("dev_r2000_8400",i_8400_7200_720_);
	std::cout<<"dev_r2000_8400:"<<i_8400_7200_720_<<std::endl;

	i_dev_wj712_7200_ = 0;
	i_dev_wj719_10800_ = 1;

	timer_ = 0;
	map_scene_ = 0;
	map_view_ = 0;

	variantManager_ = 0;
	enumManager_ = 0;
	boolManager_ = 0;

	item_laser_ip_ = 0;
	item_laser_type_ = 0;
	item_laser_reverse_ = 0;
	item_laser_start_angle_ = 0;
	item_laser_range_max_ = 0;
	item_laser_range_min_ = 0;
	item_laser_dx_ = 0;
	item_laser_dy_ = 0;
	item_laser_resolution_ = 0;

	item_robot_shape_ = 0;
	item_stop_in_shape_ = 0;
	item_stop_out_shape_ = 0;
	item_slow_shape_ = 0;
	item_ccw_shape_ = 0;
	item_cw_shape_ = 0;
	item_payload_egn1_ = 0;
	item_payload_egn2_ = 0;

	b_connection_ = false;
	
	str_robot_shape_ = "0.5,-0.4;0.5,0.4;-0.3:0.4,-0.3,-0.4;0.5,-0.4";
	str_stop_in_shape_ = "0.45,-0.35;0.45,0.35;-0.45,0.35;-0.45,-0.35;0.45,-0.35";
	str_stop_out_shape_ = "0.6,-0.4;0.6,0.4;-0.6,0.4;-0.6,-0.4;0.6,-0.4";
	str_slow_shape_ = "0.8,-0.39;0.8,0.39;-0.6,0.39;-0.6,-0.39;0.8,-0.39";
	str_ccw_shape_ = "0.6,-0.4;0.6,0.4;-0.6,0.4;-0.6,-0.4;0.6,-0.4";
	str_cw_shape_ = "0.6,-0.4;0.6,0.4;-0.6,0.4;-0.6,-0.4;0.6,-0.4";
	str_payload_egn1_ = "0.6,-0.4;0.6,0.4;-0.6,0.4;-0.6,-0.4;0.6,-0.4";
	str_payload_egn2_ = "0.6,-0.4;0.6,0.4;-0.6,0.4;-0.6,-0.4;0.6,-0.4";
	
	Config::getConfig("dev_robot_shape",str_robot_shape_);
	Config::getConfig("fix_obs_range_in",str_stop_in_shape_);
	Config::getConfig("fix_obs_range_out",str_stop_out_shape_);
	Config::getConfig("fix_obs_range_slow",str_slow_shape_);
	Config::getConfig("fix_obs_ccw",str_ccw_shape_);
	Config::getConfig("fix_obs_cw",str_cw_shape_);
	Config::getConfig("dev_payload_egn1",str_payload_egn1_);
	Config::getConfig("dev_payload_egn2",str_payload_egn2_);


	set_r2000_para();
	//set_pavo_para();
	f_r2000_start_angle_ = laser_para_.laser_start_angle_;
	f_wj712_start_angle_ = laser_para_.laser_start_angle_;

	map_scene_ = new map_scene();
	map_view_ = new map_view();
	map_view_->setScene(map_scene_);
	
	

	create_x_y_axle();
	create_laser_y();

	map_view_->zoom(25);
	map_view_->centerOn(0,0);

	QGridLayout* grid = new QGridLayout();

	grid->addWidget(create_para_wiget(),0,0,10,4);

	btn_connection_ = new QPushButton(tr("Connection"));
	btn_laser_ex_ = new QPushButton(tr("amcl_scan"));
	btn_calib_laser_ = new QPushButton(tr("Calib_laser_para"));
	btn_seg_laser_ = new QPushButton(tr("Preview"));
	btn_steering_ = new QPushButton(tr("Steering"));
	btn_show_shape_ = new QPushButton(tr("ShowShape"));
	btn_save_para_ = new QPushButton(tr("SavePara"));
	btn_show_lasermap_ = new QPushButton(tr("ShowLaserMap"));
	btn_save_laser_ex_ = new QPushButton(tr("SaveLaserEx"));
	btn_calib_ref_ = new QPushButton(tr("CalibRef"));

	connect(btn_connection_, SIGNAL(clicked(bool)), this, SLOT(ChooseConnection(bool)));
	connect(btn_laser_ex_, SIGNAL(clicked(bool)), this, SLOT(ChooseLaserEx(bool)));
	connect(btn_calib_laser_, SIGNAL(clicked(bool)), this, SLOT(ChooseCalibLaser(bool)));
	connect(btn_seg_laser_, SIGNAL(clicked(bool)), this, SLOT(ChooseSegLaser(bool)));
	connect(btn_steering_, SIGNAL(clicked(bool)), this, SLOT(ChooseSteering(bool)));
	connect(btn_show_shape_, SIGNAL(clicked(bool)), this, SLOT(ChooseShowShape(bool)));
	connect(btn_save_para_, SIGNAL(clicked(bool)), this, SLOT(ChooseSavePara(bool)));
	connect(btn_show_lasermap_, SIGNAL(clicked(bool)), this, SLOT(ChooseShowLasermap(bool)));
	
	connect(btn_save_laser_ex_, SIGNAL(clicked(bool)), this, SLOT(ChooseSaveLaserEx(bool)));
	connect(btn_calib_ref_, SIGNAL(clicked(bool)), this, SLOT(ChooseCalibRef(bool)));

	btn_laser_ex_->setText(tr("amcl_scan"));

	grid->addWidget(btn_connection_,13,0,1,1);
	grid->addWidget(btn_laser_ex_,13,1,1,1);
	grid->addWidget(btn_calib_laser_,14,0,1,1);
	grid->addWidget(btn_steering_,14,1,1,1);

	grid->addWidget(btn_show_shape_,15,0,1,1);
	grid->addWidget(btn_save_para_,15,1,1,1);

	grid->addWidget(btn_show_lasermap_,16,0,1,1);

	grid->addWidget(btn_save_laser_ex_,17,0,1,1);
	grid->addWidget(btn_calib_ref_,17,1,1,1);

	grid->setColumnMinimumWidth(0,80);

// 	QVBoxLayout* v1 = new QVBoxLayout();
// 	v1->addLayout(grid);
// 	QLabel *lab_nun = new QLabel(tr(""));
// 	v1->addWidget(lab_nun);
	

// 	QHBoxLayout* h1 = new QHBoxLayout();
// 	
// 	h1->addWidget(map_view_);
// 	h1->addLayout(v1);

//	setLayout(h1);
	QDialog* p_para_dlg = new QDialog();
	p_para_dlg->setLayout(grid);

	addWidget(map_view_);
	addWidget(p_para_dlg);
  	

}

void Calib_dlg::set_sick_lms()
{
	i_8400_7200_720_ = 2;

	laser_type_ = Laser_type::SICK_LMS;

	str_ip_ = "192.168.1.100";
	memset(laser_para_.ch_laser_ip_,0,500);
	memcpy(laser_para_.ch_laser_ip_,str_ip_.c_str(),str_ip_.length());


	laser_para_.reverse_ = false;
	laser_para_.laser_start_angle_ = Deg2Rad(-135);
	f_wj712_start_angle_ = laser_para_.laser_start_angle_;
	laser_para_.laser_resolution_ = Deg2Rad(0.5);

	laser_para_.laser_range_max_ = 20.0;
	laser_para_.laser_range_min_ = 0.05;
	laser_para_.laser_dx_ = 0.2;
	laser_para_.laser_dy_ = 0.0;
}

void Calib_dlg::set_r2000_para()
{
	laser_type_ = Laser_type::P_F_R2000;

	str_ip_ = "192.168.1.100";
	memset(laser_para_.ch_laser_ip_,0,500);
	memcpy(laser_para_.ch_laser_ip_,str_ip_.c_str(),str_ip_.length());

	
	Config::getConfig("dev_r2000_8400",i_8400_7200_720_);
	std::cout<<"dev_r2000_8400:"<<i_8400_7200_720_<<std::endl;

	laser_para_.reverse_ = false;
	if (i_8400_7200_720_ == 0){

		laser_para_.laser_start_angle_ = Deg2Rad(-173.57142);
		laser_para_.laser_resolution_ = Deg2Rad(0.642857);

	}else if (i_8400_7200_720_ == 1){

		laser_para_.laser_start_angle_ = Deg2Rad(-115.71428);
		laser_para_.laser_resolution_ = Deg2Rad(0.428571);

	}else if (i_8400_7200_720_ == 2){
		laser_para_.laser_start_angle_ = Deg2Rad(-135);
		laser_para_.laser_resolution_ = Deg2Rad(0.5);
	}else{
		laser_para_.laser_start_angle_ = Deg2Rad(-135);
		laser_para_.laser_resolution_ = Deg2Rad(0.5);
	}

	f_r2000_start_angle_ = laser_para_.laser_start_angle_;
	laser_para_.laser_range_max_ = 20.0;
	laser_para_.laser_range_min_ = 0.1;
	laser_para_.laser_dx_ = 0.2;
	laser_para_.laser_dy_ = 0.0;
	
}

void Calib_dlg::set_pavo_para()
{
	laser_type_ = Laser_type::PAVO_LS20;

	str_ip_ = "192.168.1.100";
	memset(laser_para_.ch_laser_ip_,0,500);
	memcpy(laser_para_.ch_laser_ip_,str_ip_.c_str(),str_ip_.length());

	laser_para_.reverse_ = false;
	laser_para_.laser_start_angle_ = Deg2Rad(-135);
	laser_para_.laser_range_max_ = 20.0;
	laser_para_.laser_range_min_ = 0.1;
	laser_para_.laser_dx_ = 0.2;
	laser_para_.laser_dy_ = 0.0;
	laser_para_.laser_resolution_ = Deg2Rad(0.48);
}

void Calib_dlg::set_wj712_para()
{
	laser_type_ = Laser_type::WJ_712;

	str_ip_ = "192.168.1.100";
	memset(laser_para_.ch_laser_ip_,0,500);
	memcpy(laser_para_.ch_laser_ip_,str_ip_.c_str(),str_ip_.length());


	Config::getConfig("dev_wj712_7200",i_dev_wj712_7200_);
	std::cout<<"dev_wj712_7200:"<<i_dev_wj712_7200_<<std::endl;

	laser_para_.reverse_ = false;
	laser_para_.laser_start_angle_ = Deg2Rad(-108);
	laser_para_.laser_resolution_ = Deg2Rad(0.4);

	f_wj712_start_angle_ = laser_para_.laser_start_angle_;

	laser_para_.laser_range_max_ = 70.0;
	laser_para_.laser_range_min_ = 0.01;
	laser_para_.laser_dx_ = 0.2;
	laser_para_.laser_dy_ = 0.0;
}

void Calib_dlg::set_wj719_para()
{
	laser_type_ = Laser_type::WJ_719;

	str_ip_ = "192.168.1.100";
	memset(laser_para_.ch_laser_ip_,0,500);
	memcpy(laser_para_.ch_laser_ip_,str_ip_.c_str(),str_ip_.length());

	Config::getConfig("dev_wj719_10800",i_dev_wj719_10800_);
	std::cout<<"dev_wj719_10800:"<<i_dev_wj719_10800_<<std::endl;

	laser_para_.reverse_ = false;
	laser_para_.laser_start_angle_ = Deg2Rad(-135);
	f_wj712_start_angle_ = laser_para_.laser_start_angle_;
	laser_para_.laser_resolution_ = Deg2Rad(0.5);

	laser_para_.laser_range_max_ = 40.0;
	laser_para_.laser_range_min_ = 0.05;
	laser_para_.laser_dx_ = 0.2;
	laser_para_.laser_dy_ = 0.0;
}

void Calib_dlg::set_pavo2_ls50h_para()
{
	laser_type_ = Laser_type::PAVO2_LS50H;

	str_ip_ = "192.168.1.100";
	memset(laser_para_.ch_laser_ip_,0,500);
	memcpy(laser_para_.ch_laser_ip_,str_ip_.c_str(),str_ip_.length());


	laser_para_.reverse_ = false;
	laser_para_.laser_start_angle_ = Deg2Rad(-129.6);
	f_r2000_start_angle_ = laser_para_.laser_start_angle_;
	laser_para_.laser_resolution_ = Deg2Rad(0.48); //slam angle resolution ,for every 6 step

	laser_para_.laser_range_max_ = 40.0;
	laser_para_.laser_range_min_ = 0.01;
	laser_para_.laser_dx_ = 0.2;
	laser_para_.laser_dy_ = 0.0;
}

void Calib_dlg::set_hins_le_para()
{
	laser_type_ = Laser_type::HINS_LE;

	str_ip_ = "192.168.1.100";
	memset(laser_para_.ch_laser_ip_,0,500);
	memcpy(laser_para_.ch_laser_ip_,str_ip_.c_str(),str_ip_.length());


	laser_para_.reverse_ = false;
	int laser_start_index = ( LASER_COUNT_EX2 - (LASER_COUNT - 1) * 28  ) / 2;
	laser_para_.laser_start_angle_ = Deg2Rad( - 180 + 360.0 / LASER_COUNT_EX2 * laser_start_index);// Deg2Rad(-136.5); 
	f_wj712_start_angle_ = laser_para_.laser_start_angle_;
	laser_para_.laser_resolution_ = Deg2Rad(360.0 / LASER_COUNT_EX2 * 28); //slam angle resolution ,for every 6 step

	laser_para_.laser_range_max_ = 60.0;
	laser_para_.laser_range_min_ = 0.01;
	laser_para_.laser_dx_ = 0.2;
	laser_para_.laser_dy_ = 0.0;
}
void Calib_dlg::shape_show(){

}
QWidget* Calib_dlg::create_para_wiget(){

	variantManager_ = new QtVariantPropertyManager();
	
	enumManager_ = new QtEnumPropertyManager();
	boolManager_ = new QtBoolPropertyManager();

	
	QtProperty *laser_para_group = variantManager_->addProperty(QtVariantPropertyManager::groupTypeId(),QLatin1String("Laser Para"));
	laser_para_group->setPropertyId(QLatin1String("Laser Para"));
	
	item_laser_type_ = variantManager_->addProperty(QtVariantPropertyManager::enumTypeId(), QString::fromStdString("dev_laser_type"));

	QStringList enumNames;
	enumNames << "SICK_LMS" << "SICK_TIM" << "HOKUYO" << "SAMTEC"<<"P_F_R2000"<<"PAVO_LS20"<<"wj_712"<<"wj_719"<<"wj_718mini"<<"PAVO2_LS50H"<<"HINS_LE";

	item_laser_type_->setAttribute(QLatin1String("enumNames"), enumNames);
	item_laser_type_->setValue(laser_type_);
	item_laser_type_->setAttribute(QLatin1String("readOnly"), true);
	laser_para_group->addSubProperty(item_laser_type_);
	

	item_laser_ip_ = variantManager_->addProperty(QVariant::String, QLatin1String("dev_laser_ip"));
	std::string str_ip = laser_para_.ch_laser_ip_;
	QString qs_ip = QString::fromStdString(str_ip);
	item_laser_ip_->setValue(qs_ip);
	laser_para_group->addSubProperty(item_laser_ip_);

	item_laser_reverse_ = boolManager_->addProperty("dev_laser_reverse");
	laser_para_group->addSubProperty(item_laser_reverse_);

	item_laser_start_angle_ = variantManager_->addProperty(QVariant::Double, QLatin1String("dev_laser_start_angle"));
	item_laser_start_angle_->setValue(-135.000);
	item_laser_start_angle_->setAttribute(QLatin1String("singleStep"), 0.01);
	item_laser_start_angle_->setAttribute(QLatin1String("decimals"), 3);
	laser_para_group->addSubProperty(item_laser_start_angle_);

	item_laser_dx_ = variantManager_->addProperty(QVariant::Double, QLatin1String("dev_laser_dx"));
	item_laser_dx_->setValue(0.000);
	item_laser_dx_->setAttribute(QLatin1String("singleStep"), 0.01);
	item_laser_dx_->setAttribute(QLatin1String("decimals"), 3);
	laser_para_group->addSubProperty(item_laser_dx_);

	item_laser_dy_ = variantManager_->addProperty(QVariant::Double, QLatin1String("dev_laser_dy"));
	item_laser_dy_->setValue(0.00);
	item_laser_dy_->setAttribute(QLatin1String("singleStep"), 0.01);
	item_laser_dy_->setAttribute(QLatin1String("decimals"), 2);
	laser_para_group->addSubProperty(item_laser_dy_);

	item_laser_resolution_ = variantManager_->addProperty(QVariant::Double, QLatin1String("dev_laser_resolution"));
	item_laser_resolution_->setValue(0.5);
	item_laser_resolution_->setAttribute(QLatin1String("singleStep"), 0.001);
	item_laser_resolution_->setAttribute(QLatin1String("decimals"), 5);
	laser_para_group->addSubProperty(item_laser_resolution_);

	item_laser_range_max_ = variantManager_->addProperty(QVariant::Double, QLatin1String("dev_laser_range_max"));
	item_laser_range_max_->setValue(20.00);
	item_laser_range_max_->setAttribute(QLatin1String("singleStep"), 0.01);
	item_laser_range_max_->setAttribute(QLatin1String("decimals"), 2);
	laser_para_group->addSubProperty(item_laser_range_max_);

	item_laser_range_min_ = variantManager_->addProperty(QVariant::Double, QLatin1String("dev_laser_range_min"));
	item_laser_range_min_->setValue(0.01);
	item_laser_range_min_->setAttribute(QLatin1String("singleStep"), 0.01);
	item_laser_range_min_->setAttribute(QLatin1String("decimals"), 2);
	laser_para_group->addSubProperty(item_laser_range_min_);

	QtProperty *calib_group = variantManager_->addProperty(QtVariantPropertyManager::groupTypeId(),QLatin1String("calibration"));

	item_calib_line_ = variantManager_->addProperty(QVariant::Double, QLatin1String("calib line"));
	item_calib_line_->setValue(3.0);
	item_calib_line_->setAttribute(QLatin1String("singleStep"), 0.01);
	item_calib_line_->setAttribute(QLatin1String("decimals"), 3);
	calib_group->addSubProperty(item_calib_line_);

	QtProperty *shape_group = variantManager_->addProperty(QtVariantPropertyManager::groupTypeId(),QLatin1String("shape"));
	item_robot_shape_ = variantManager_->addProperty(QVariant::String, QString::fromStdString("dev_robot_shape"));
	item_robot_shape_->setValue(QString::fromStdString(str_robot_shape_));
	v_shape_pro_.push_back(std::make_pair("dev_robot_shape" , item_robot_shape_)) ;
	shape_group->addSubProperty(item_robot_shape_);

	item_stop_in_shape_ = variantManager_->addProperty(QVariant::String, QString::fromStdString("fix_obs_range_in"));
	item_stop_in_shape_->setValue(QString::fromStdString(str_stop_in_shape_));
	v_shape_pro_.push_back(std::make_pair("fix_obs_range_in" , item_stop_in_shape_)) ;
	shape_group->addSubProperty(item_stop_in_shape_);

	item_stop_out_shape_ = variantManager_->addProperty(QVariant::String, QString::fromStdString("fix_obs_range_out"));
	item_stop_out_shape_->setValue(QString::fromStdString(str_stop_out_shape_));
	v_shape_pro_.push_back(std::make_pair("fix_obs_range_out" , item_stop_out_shape_)) ;
	shape_group->addSubProperty(item_stop_out_shape_);

	item_slow_shape_ = variantManager_->addProperty(QVariant::String, QString::fromStdString("fix_obs_range_slow"));
	item_slow_shape_->setValue(QString::fromStdString(str_slow_shape_));
	v_shape_pro_.push_back(std::make_pair("fix_obs_range_slow" , item_slow_shape_)) ;
	shape_group->addSubProperty(item_slow_shape_);

	item_ccw_shape_ = variantManager_->addProperty(QVariant::String, QString::fromStdString("fix_obs_range_ccw"));
	item_ccw_shape_->setValue(QString::fromStdString(str_ccw_shape_));
	v_shape_pro_.push_back(std::make_pair("fix_obs_range_ccw" , item_ccw_shape_)) ;
	shape_group->addSubProperty(item_ccw_shape_);

	item_cw_shape_ = variantManager_->addProperty(QVariant::String, QString::fromStdString("fix_obs_range_cw"));
	item_cw_shape_->setValue(QString::fromStdString(str_cw_shape_));
	v_shape_pro_.push_back(std::make_pair("fix_obs_range_cw" , item_cw_shape_)) ;
	shape_group->addSubProperty(item_cw_shape_);

	item_payload_egn1_ = variantManager_->addProperty(QVariant::String, QString::fromStdString("payload_egn1"));
	item_payload_egn1_->setValue(QString::fromStdString(str_payload_egn1_));
	v_shape_pro_.push_back(std::make_pair("payload_egn1" , item_payload_egn1_)) ;
	shape_group->addSubProperty(item_payload_egn1_);

	item_payload_egn2_ = variantManager_->addProperty(QVariant::String, QString::fromStdString("payload_egn2"));
	item_payload_egn2_->setValue(QString::fromStdString(str_payload_egn2_));
	v_shape_pro_.push_back(std::make_pair("payload_egn2" , item_payload_egn2_)) ;
	shape_group->addSubProperty(item_payload_egn2_);

	QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory();
	QtEnumEditorFactory *comboBoxFactory = new QtEnumEditorFactory();
	QtCheckBoxFactory *checkBoxFactory = new QtCheckBoxFactory();

	QtTreePropertyBrowser *variantEditor = new QtTreePropertyBrowser();
	
	variantEditor->setFactoryForManager(variantManager_, variantFactory);
	variantEditor->setFactoryForManager(enumManager_, comboBoxFactory);
	variantEditor->setFactoryForManager(boolManager_, checkBoxFactory);

	variantEditor->addProperty(laser_para_group);
	variantEditor->addProperty(calib_group);
	variantEditor->addProperty(shape_group);
	variantEditor->setPropertiesWithoutValueMarked(true);
	variantEditor->setRootIsDecorated(false);
	
	
	

	return (QWidget*)variantEditor;
}
void Calib_dlg::valueChanged(QtProperty *property, const QVariant &value)
{
	std::string str_name = property->propertyName().toStdString();
	std::string str_data = value.toString().toStdString();

	QVariant qv = ((QtVariantProperty*)property)->attributeValue("enumNames");
	QStringList enumNames = qv.toStringList();
	if (enumNames.size() > 0){
		int cmb_index = 0;
		cComm::ConvertToNum(cmb_index,str_data);
		if ( cmb_index < enumNames.size()){
			str_data = enumNames.takeAt(cmb_index).toStdString();
		}
	}

	if ( str_name == "calib line") {
		item_line_->setLine(value.toDouble(),-2,value.toDouble(),2);
	}else if(str_name == "dev_laser_type"){
		int itype = item_laser_type_->value().toInt();
		Laser_type laser_type = (Laser_type)(itype);
		str_laser_type_ = laser_type_cov(laser_type);
		str_data = str_laser_type_;

		switch(laser_type){
		case Laser_type::SICK_LMS:
			set_sick_lms();
			show_data(laser_para_,laser_type);

			break;
		case Laser_type::P_F_R2000:
			set_r2000_para();
			show_data(laser_para_,laser_type);

			break;
		case Laser_type::PAVO_LS20:
			set_pavo_para();
			show_data(laser_para_,laser_type);

			break;
		case Laser_type::WJ_712:
			set_wj712_para();
			show_data(laser_para_,laser_type);

			break;

		case Laser_type::WJ_719:
			set_wj719_para();
			show_data(laser_para_,laser_type);

			break;
		case Laser_type::WJ_718MINI:
			set_wj718mini_para();
			show_data(laser_para_,laser_type);

			break;
		case Laser_type::PAVO2_LS50H:
			set_pavo2_ls50h_para();
			show_data(laser_para_,laser_type);

			break;
		case Laser_type::HINS_LE:

			set_hins_le_para();
			show_data(laser_para_,laser_type);

			break;
		}
	}


	std::string str_code;
	RPC_CONFIG_CLIENT.get_whole_config( str_code, str_name);
	config_it cfg("default");
	cfg.decode(str_code);

	if ( cfg.get_type() =="string"){
		cfg.set_value(str_data);
		m_update_para_[str_name] = cfg.code();
	}else if (cfg.get_type() == typeid(int).name()){
		cfg.set_value(value.toInt());
		m_update_para_[str_name] = cfg.code();
	}else if (cfg.get_type() == typeid(float).name()){
		cfg.set_value(value.toFloat());
		m_update_para_[str_name] = cfg.code();
	}else if (cfg.get_type() == typeid(double).name()){
		cfg.set_value(value.toDouble());
		m_update_para_[str_name] = cfg.code();
	}else{

		std::cout<<"para_dlg::valueChanged value type err!"<<std::endl;
	}

	

}
void Calib_dlg::init_timer()
{

	if (!timer_)
	{
		timer_ = new QTimer(this);
		timer_->setInterval(100);
		connect(timer_, SIGNAL(timeout()), this, SLOT(update_sensor()));

		timer_->start();
	}
	
}

void Calib_dlg::stop_timer()
{
	if(timer_){
		timer_->stop();
		delete timer_;
		timer_ = 0;
	}

}

bool Calib_dlg::s_update_laser(const SLaser& laser)
{
	//th_show_laser_.put( laser );
	//std::cout<<"laser:"<<laser.stamp_<<std::endl;

	laser_filter l_filter;
	get_data(laser_para_,laser_type_);

	SLaser new_laser;
	memcpy(&new_laser,&laser,sizeof(SLaser));
	
	if (i_8400_7200_720_ < 2){
		new_laser.start_angle_ += laser_para_.laser_start_angle_ - f_r2000_start_angle_;
		//new_laser.start_angle_ = laser_para_.laser_start_angle_;
		new_laser.range_max_ = laser_para_.laser_range_max_;
		new_laser.range_min_ = laser_para_.laser_range_min_;
		new_laser.resolution_ = laser_para_.laser_resolution_;
	}else{
		new_laser.start_angle_ = laser_para_.laser_start_angle_;
		new_laser.range_max_ = laser_para_.laser_range_max_;
		new_laser.range_min_ = laser_para_.laser_range_min_;
		new_laser.resolution_ = laser_para_.laser_resolution_;
	}


	memset(new_laser.seg_,0,sizeof(U8)*LASER_COUNT);
	new_laser.used_ = 0;

	l_filter.init_laser_para(str_robot_shape_,new_laser,laser_para_.laser_dx_,laser_para_.laser_dy_);
	l_filter.filter_used(new_laser);
	get_robot_item()->set_laser_para(laser_para_);
	get_robot_item()->set_laser(new_laser);
	get_robot_item()->update();

	return true;
}

bool Calib_dlg::s_update_wj_laser(const SLaser& laser)
{
#if 0
	get_data(laser_para_,laser_type_);
	//SLaser new_laser;
	//memcpy(&new_laser,&laser,sizeof(SLaser));
	std::stringstream ss;
	ss<<"dev_laser_start_angle:"<<laser_para_.laser_start_angle_<<";";
	Singleton_Device_Pool::get_mutable_instance().set_dev_para("laser",ss.str());
	//memset(new_laser.seg_,0,sizeof(U8)*LASER_COUNT);
	//new_laser.used_ = 0;

// 	l_filter.init_laser_para(str_robot_shape_,new_laser,laser_para_.laser_dx_,laser_para_.laser_dy_);
// 	l_filter.filter_used(new_laser);
	get_robot_item()->set_laser_para(laser_para_);
	get_robot_item()->set_laser(laser);
	get_robot_item()->update();
#else
	get_data(laser_para_,laser_type_);
	SLaser new_laser;
	memcpy(&new_laser,&laser,sizeof(SLaser));
	new_laser.start_angle_ = laser.start_angle_ + laser_para_.laser_start_angle_ - f_wj712_start_angle_;

	laser_filter l_filter;
	l_filter.init_laser_para(str_robot_shape_,new_laser,laser_para_.laser_dx_,laser_para_.laser_dy_);
	l_filter.filter_used(new_laser);
	get_robot_item()->set_laser_para(laser_para_);
	get_robot_item()->set_laser(new_laser);
	//laser ref rot angle diff
	SReflector laser_ref = th_ref_();
	for ( int i = 0 ; i < laser_ref.used_ ; ++i ){
		SVec &pos = laser_ref.pos_[i];
		VecPosition vp(pos.x_,pos.y_);
		vp.rotate(Rad2Deg(laser_para_.laser_start_angle_ - f_wj712_start_angle_));
		pos.x_ = vp.getX();
		pos.y_ = vp.getY();
	}
	get_robot_item()->set_scan_reflector(laser_ref);
	get_robot_item()->update();
	
#endif
	return true;

}

bool Calib_dlg::s_update_pavo2_laser(const SLaser& laser)
{
	get_data(laser_para_,laser_type_);
	SLaser new_laser;
	memcpy(&new_laser,&laser,sizeof(SLaser));
	new_laser.start_angle_ = laser.start_angle_ + laser_para_.laser_start_angle_ - f_r2000_start_angle_;

	laser_filter l_filter;
	l_filter.init_laser_para(str_robot_shape_,new_laser,laser_para_.laser_dx_,laser_para_.laser_dy_);
	l_filter.filter_used(new_laser);
	get_robot_item()->set_laser_para(laser_para_);
	get_robot_item()->set_laser(new_laser);
	get_robot_item()->update();
	return true;

}

void Calib_dlg::create_x_y_axle()
{
	QGraphicsItem* qi = 0;
	QPen pen;
	pen.setColor(Qt::black);
	qi =map_scene_->addLine(-20,0,20,0,pen);
	qi->setZValue(0);
	qi =map_scene_->addLine(0,-20,0,20,pen);
	qi->setZValue(0);
	
	SPos arrow;
	arrow.x_ = 10;
	arrow.y_ = 0;
	arrow.th_ = 0;
	QPolygonF p3;
	get_triangle(p3,arrow);
	qi = map_scene_->addPolygon(p3,pen);
	qi->setZValue(0);

	arrow.x_ = 0;
	arrow.y_ = 10;
	arrow.th_ = M_PI/2;
	QPolygonF p31;
	get_triangle(p31,arrow);
	qi = map_scene_->addPolygon(p31,pen);
	qi->setZValue(0);
}

void Calib_dlg::create_laser_y()
{
	QPen pen;
	pen.setColor(Qt::blue);
	item_line_ = map_scene_->addLine(3,-2,3,2,pen);
	item_line_->setZValue(0);
}
void Calib_dlg::get_triangle( QPolygonF &p3, const SPos &pos){
	QPointF p;

	VecPosition phead(0.8,0,POLAR);
	phead.rotate(Rad2Deg(pos.th_));
	phead += VecPosition(pos.x_,pos.y_);
	p.setX(phead.getX());
	p.setY(phead.getY());
	p3<<p;

	VecPosition pleft(0.2,90,POLAR);
	pleft.rotate(Rad2Deg(pos.th_));
	pleft += VecPosition(pos.x_,pos.y_);
	p.setX(pleft.getX());
	p.setY(pleft.getY());
	p3<<p;

	VecPosition pright(0.2,-90,POLAR);
	pright.rotate(Rad2Deg(pos.th_));
	pright += VecPosition(pos.x_,pos.y_);
	p.setX(pright.getX());
	p.setY(pright.getY());
	p3<<p;

}

void Calib_dlg::update_sensor()
{

 	get_robot_item()->set_amcl_pos(th_pos_().pos_);
	SWorldLM wlm = th_wlm_();
  	VecPosition robot(wlm.landmark_in_robot_.x_,wlm.landmark_in_robot_.y_);
  	SLine2P ln;
  	ln.p1_.x_ = robot.getX();
  	ln.p1_.y_ = robot.getY();
  	robot += VecPosition(0.5,Rad2Deg(wlm.landmark_in_robot_.th_),POLAR);
  	ln.p2_.x_ = robot.getX();
  	ln.p2_.y_ = robot.getY();
  
  	get_robot_item()->set_sm_ori(ln);

	std::vector<SSteering> v_st;
	DATASERVER_XML_CLIENT.get_steering(v_st);

	auto it = v_st.begin();
	for ( ; it != v_st.end() ; ++it ){
		SSteering &st(*it);
		std::cout<<"id:"<<st.id_<<" pos_x:"<<st.pos_.x_<<" y:"<<st.pos_.y_<<" th:"<<st.pos_.th_<<std::endl;
		std::cout<<"max_a:"<<st.max_angle_<<" min_a:"<<st.min_angle_<<" zero_angle:"<<st.zero_angle_<<std::endl;
		std::cout<<"set angle:"<<st.set_angle_<<" set_speed:"<<st.set_speed_<<" cur_angle:"<<st.cur_angle_<<" cur_speed:"<<st.cur_speed_<<std::endl;
		std::cout<<"-----------"<<std::endl;
	}

	get_robot_item()->set_steering(v_st);
	get_robot_item()->update();
	//Singleton_XML_Client::get_mutable_instance().get_laser()
}
void Calib_dlg::get_config(){

}
void Calib_dlg::show_data(const SLaser_para &para,const Laser_type &laser_type)
{

	item_laser_type_->setValue(laser_type);

	std::string str_ip = laser_para_.ch_laser_ip_;
	item_laser_ip_->setValue(QLatin1String(str_ip.c_str()));

	boolManager_->setValue(item_laser_reverse_,laser_para_.reverse_);

	item_laser_start_angle_->setValue(Rad2Deg(para.laser_start_angle_));
	item_laser_range_max_->setValue(para.laser_range_max_);
	item_laser_range_min_->setValue(para.laser_range_min_);

	item_laser_dx_->setValue(para.laser_dx_);
	item_laser_dy_->setValue(para.laser_dy_);
	item_laser_resolution_->setValue(Rad2Deg( para.laser_resolution_));
}

void Calib_dlg::get_data(SLaser_para &para,Laser_type &laser_type)
{
	
 	int itype = item_laser_type_->value().toInt();
 	laser_type = (Laser_type)(itype);
 	
	str_ip_ = item_laser_ip_->value().toString().toStdString();
	memset(para.ch_laser_ip_,0,500);
	memcpy(para.ch_laser_ip_,str_ip_.c_str(),str_ip_.length());

	para.laser_start_angle_ = Deg2Rad( item_laser_start_angle_->value().toDouble());
	para.reverse_ = boolManager_->value(item_laser_reverse_);
	para.laser_dx_ = item_laser_dx_->value().toDouble();
	para.laser_dy_ = item_laser_dy_->value().toDouble();
	para.laser_range_max_ = item_laser_range_max_->value().toDouble();
	para.laser_range_min_ = item_laser_range_min_->value().toDouble();
	para.laser_resolution_ = Deg2Rad(item_laser_resolution_->value().toDouble());
}

std::string Calib_dlg::set_laser_para()
{
	Config::setConfig("dev_laser_ip",str_ip_);
	laser_para_.laser_start_angle_ = Rad2Deg(laser_para_.laser_start_angle_);
	Config::setConfig("dev_laser_start_angle",laser_para_.laser_start_angle_);
	laser_para_.laser_resolution_ = Rad2Deg(laser_para_.laser_resolution_);
	Config::setConfig("dev_laser_resolution",laser_para_.laser_resolution_);
	Config::setConfig("dev_laser_reverse",laser_para_.reverse_);
	Config::setConfig("dev_laser_dx",laser_para_.laser_dx_);
	Config::setConfig("dev_laser_dy",laser_para_.laser_dy_);
	Config::setConfig("dev_laser_range_max",laser_para_.laser_range_max_);
	Config::setConfig("dev_laser_range_min",laser_para_.laser_range_min_);

//  	std::stringstream ss;
//  	ss<<str_conn;
//  	ss<<"dev_laser_ip:"<<str_ip_<<";";
//  	ss<<"dev_laser_start_angle:"<<laser_para_.laser_start_angle_<<";";
//  	ss<<"dev_laser_resolution:"<<laser_para_.laser_resolution_<<";";
//  	ss<<"dev_laser_reverse:"<<laser_para_.reverse_<<";";
//  
//  	ss<<"dev_laser_dx:"<<laser_para_.laser_dx_<<";";
//  	ss<<"dev_laser_dy:"<<laser_para_.laser_dy_<<";";
//  	ss<<"dev_laser_range_max:"<<laser_para_.laser_range_max_<<";";
//  	ss<<"dev_laser_range_min:"<<laser_para_.laser_range_min_<<";";
// 
// 	return ss.str();
	return "";
}
std::string Calib_dlg::laser_type_cov(Laser_type type){
	std::string str_type = "sicklms";

	if ( type == SICK_LMS  )
	{
		str_type = "sicklms";
	}else if ( type == P_F_R2000  )
	{
		str_type = "P_F_R2000";
	}else if ( type == HOKUYO  )
	{
		str_type = "hokuyo";
	}else if ( type == SICK_TIM  )
	{
		str_type = "sicktim";
	}else if ( type == SAMTEC  )
	{
		str_type = "samtec";
	}else if ( type == PAVO_LS20  )
	{
		str_type = "pavo_ls20";
	}else if ( type == WJ_712  )
	{
		str_type = "wj_712";
	}else if ( type == WJ_719  )
	{
		str_type = "wj_719";
	}else if ( type == PAVO2_LS50H  )
	{
		str_type = "pavo2_ls50h";
	}else if ( type == HINS_LE  )
	{
		str_type = "hins_le";
	}else if ( type == SIM  )
	{
		str_type = "sim";
	}
	return str_type;
}
void Calib_dlg::ChooseConnection( bool flag )
{
	get_data(laser_para_,laser_type_);
	
	//i_8400_7200_720_ = 0;
	//i_dev_wj712_7200_ = 0;

	std::stringstream ss;
	ss<<"dev_b_name:laser;";
	if( laser_type_ == Laser_type::SICK_LMS ){
		ss<<"dev_b_ms_loop:40;";
		ss<<"dev_pub_laser_ex:0;";
	}else if( laser_type_ == Laser_type::P_F_R2000 ){
		//i_8400_7200_720_ = 0;
		ss<<"dev_b_ms_loop:100;";
		ss<<"dev_r2000_8400:"<<i_8400_7200_720_<<";";
		//ss<<";dev_pub_laser_ex:0;";
		if (b_laser_ex_){
			ss<<"dev_pub_amcl_ref:0;";
			ss<<"dev_pub_laser_ex:1;";
		}else{
			ss<<"dev_pub_amcl_ref:1;";
			ss<<"dev_pub_laser_ex:0;";
		}
	}else if ( laser_type_ == Laser_type::WJ_712 ){
		if (i_dev_wj712_7200_ == 0){
			// 0.1deg 3600
			ss<<"dev_b_ms_loop:59;";
			ss<<"dev_wj712_7200:0;";
		}else{
			// 0.05deg 7200
			ss<<"dev_b_ms_loop:120;";
			ss<<"dev_wj712_7200:1;";
		}
		
		if (b_laser_ex_){
			ss<<"dev_pub_amcl_ref:0;";
			ss<<"dev_pub_laser_ex:1;";
		}else{
			ss<<"dev_pub_amcl_ref:1;";
			ss<<"dev_pub_laser_ex:0;";
		}
	}else if ( laser_type_ == Laser_type::WJ_719 ){
		if (i_dev_wj719_10800_ == 0){
			// 0.1deg 3600
			ss<<"dev_b_ms_loop:33.3;";
			ss<<"dev_wj719_10800:0;";
		}else{
			// 0.0333333 deg 10800
			ss<<"dev_b_ms_loop:100;";
			ss<<"dev_wj719_10800:1;";
		}

		if (b_laser_ex_){
			ss<<"dev_pub_amcl_ref:0;";
			ss<<"dev_pub_laser_ex:1;";
		}else{
			ss<<"dev_pub_amcl_ref:1;";
			ss<<"dev_pub_laser_ex:0;";
		}
	}else if ( laser_type_ == Laser_type::WJ_718MINI ){
		ss<<"dev_b_ms_loop:40;";
		if (b_laser_ex_){
			ss<<"dev_pub_amcl_ref:0;";
			ss<<"dev_pub_laser_ex:1;";
		}else{
			ss<<"dev_pub_amcl_ref:1;";
			ss<<"dev_pub_laser_ex:0;";
		}
	}else if ( laser_type_ == Laser_type::PAVO2_LS50H ){

		ss<<"dev_b_ms_loop:40;";
		if (b_laser_ex_){
			ss<<"dev_pub_laser_ex:1;";
		}else{
			ss<<"dev_pub_laser_ex:0;";
		}
		
	}else if ( laser_type_ == Laser_type::HINS_LE ){

		ss<<"dev_b_ms_loop:100;";
		if (b_laser_ex_){
			ss<<"dev_pub_laser_ex:1;";
		}else{
			ss<<"dev_pub_laser_ex:0;";
		}

	}
	
	set_laser_para();
	//reflash para from config

	
	if (b_laser_ex_){

		//ss<<"dev_pub_amcl_ref:0;dev_pub_laser_ex_ref:1;";

		msg_pump::end_Sub(i_sub_laser_,SLaser());
		msg_pump::end_Sub(i_sub_laser_ex_,SLaser_Ex());
		boost::function<bool( const SLaser_Ex& laser )> fnc_laser_ex;
		if ( laser_type_ == Laser_type::WJ_712 ){
			fnc_laser_ex = boost::bind(&Calib_dlg::s_update_laser_ex2,this,_1);
			i_sub_laser_ex_ = msg_pump::sub_msg(PUB_LASER_EX,fnc_laser_ex);
		}else if ( laser_type_ == Laser_type::WJ_719 ){
			boost::function<bool( const SLaser_Ex2& laser2 )> fnc_laser_ex2;
			fnc_laser_ex2 = boost::bind(&Calib_dlg::s_update_laser_ex3,this,_1);
			i_sub_laser_ex_ = msg_pump::sub_msg(PUB_LASER_EX2,fnc_laser_ex2);
		}else if ( laser_type_ == Laser_type::WJ_718MINI ){
			fnc_laser_ex = boost::bind(&Calib_dlg::s_update_laser_ex4,this,_1);
			i_sub_laser_ex_ = msg_pump::sub_msg(PUB_LASER_EX,fnc_laser_ex);
		}else if ( laser_type_ == Laser_type::HINS_LE ){
			fnc_laser_ex = boost::bind(&Calib_dlg::s_update_laser_ex2,this,_1);
			i_sub_laser_ex_ = msg_pump::sub_msg(PUB_LASER_EX,fnc_laser_ex);
		}else if ( laser_type_ == Laser_type::PAVO2_LS50H ){
			fnc_laser_ex = boost::bind(&Calib_dlg::s_update_laser_ex2,this,_1);
			i_sub_laser_ex_ = msg_pump::sub_msg(PUB_LASER_EX,fnc_laser_ex);
		}else {
			fnc_laser_ex = boost::bind(&Calib_dlg::s_update_laser_ex,this,_1);
			i_sub_laser_ex_ = msg_pump::sub_msg(PUB_LASER_EX,fnc_laser_ex);
		}
	
	}else{
		//ss<<"dev_pub_amcl_ref:1;dev_pub_laser_ex_ref:0;";

		msg_pump::end_Sub(i_sub_laser_,SLaser());
		msg_pump::end_Sub(i_sub_laser_ex_,SLaser_Ex());
		boost::function<bool( const SLaser& laser )> fnc_laser;

		if ( laser_type_ == Laser_type::WJ_712 ){
			fnc_laser = boost::bind(&Calib_dlg::s_update_wj_laser,this,_1);
		}else if ( laser_type_ == Laser_type::WJ_719 ){
			fnc_laser = boost::bind(&Calib_dlg::s_update_wj_laser,this,_1);
		}if ( laser_type_ == Laser_type::WJ_718MINI ){
			fnc_laser = boost::bind(&Calib_dlg::s_update_wj_laser,this,_1);
//			i_sub_laser_ex_ = msg_pump::sub_msg(PUB_LASER_EX,fnc_laser);
// 			boost::function<bool( const SLaser_Ex& laser )> fnc_laser_ex;
// 			fnc_laser_ex = boost::bind(&Calib_dlg::s_update_laser_ex4,this,_1);
//			i_sub_laser_ex_ = msg_pump::sub_msg(PUB_LASER_EX,fnc_laser_ex);
			
		}else if ( laser_type_ == Laser_type::HINS_LE ){
			fnc_laser = boost::bind(&Calib_dlg::s_update_wj_laser,this,_1);
		}else if ( laser_type_ == Laser_type::PAVO2_LS50H ){
			fnc_laser = boost::bind(&Calib_dlg::s_update_pavo2_laser,this,_1);
		}else{
			fnc_laser = boost::bind(&Calib_dlg::s_update_laser,this,_1);
		}
		i_sub_laser_ = msg_pump::sub_msg(PUB_AMCL_LASER,fnc_laser);
		
	}
	msg_pump::end_Sub(i_sub_ref_,SReflector());
	boost::function<bool( const SReflector &laser_ref )> fnc_ref;
	fnc_ref = boost::bind(&Calib_dlg::s_update_ref,this,_1);
	i_sub_ref_ = msg_pump::sub_msg(PUB_REFLECTOR_LIST,fnc_ref);


	std::string str_conn = ss.str();

	Singleton_Device_Pool::get_mutable_instance().get_laser_para(true);

	if (!b_connection_){	
		Singleton_Device_Pool::get_mutable_instance().create_laser( laser_type_, str_conn );
	}else{
		Singleton_Device_Pool::get_mutable_instance().destruct_laser();
	}


	if (b_connection_)
	{
		btn_connection_->setText(tr("Connection"));
	}else{
		btn_connection_->setText(tr("DisConnection"));
	}
	b_connection_ = !b_connection_;
	
}
void Calib_dlg::show_loc_pos( SWorldLM wlm , SPOS_CONFIDENCE con_pos ){
	th_pos_ = con_pos;
	th_wlm_ = wlm;
	//	get_robot_item()->set_amcl_pos(pos);
// 	VecPosition robot(wlm.landmark_in_robot_.x_,wlm.landmark_in_robot_.y_);
// 	SLine2P ln;
// 	ln.p1_.x_ = robot.getX();
// 	ln.p1_.y_ = robot.getY();
// 	robot += VecPosition(0.5,Rad2Deg(wlm.landmark_in_robot_.th_),POLAR);
// 	ln.p2_.x_ = robot.getX();
// 	ln.p2_.y_ = robot.getY();
// 
// 	get_robot_item()->set_sm_ori(ln);
//	get_robot_item()->update();
}
void Calib_dlg::ChooseSegLaser( bool flag )
{
	return;

	SDelete(p_special_loc_base_);
	p_special_loc_base_ = (special_loc_base*) new laser_special_loc();
	p_special_loc_base_->init();
	((laser_special_loc*)p_special_loc_base_)->init_sensor_diff(laser_para_.laser_dx_,laser_para_.laser_dy_,0);
	SLEEP(1000);

	p_special_loc_base_->bind_landmark_world();
	p_special_loc_base_->bind_pub_pos(boost::bind(&Calib_dlg::show_loc_pos,this,_1,_2));
	p_special_loc_base_->fnc_show_laser_ = boost::bind( & Calib_dlg::show_laser_seg,this,_1);

	return;

	//if (b_laser_ex_){


// 		msg_pump::end_Sub(i_sub_laser_,SLaser());
// 		msg_pump::end_Sub(i_sub_laser_ex_,SLaser_Ex());
// 		boost::function<bool( const SLaser_Ex& laser )> fnc_laser_ex;
// 		fnc_laser_ex = boost::bind(&Calib_dlg::s_update_laser_ex,this,_1);
// 		i_sub_laser_ex_ = msg_pump::sub_msg(PUB_LASER_EX,fnc_laser_ex);
		

// 		boost::function<void( const SLaser_Ex& laser )> fnc_laser_ex;
// 		fnc_laser_ex = boost::bind(&Calib_dlg::s_update_laser_ex,this,_1);
// 		END_MSG_SH_POOL( SLaser(),"laser");
// 		END_MSG_SH_POOL(SLaser_Ex(),"laser_ex");
// 		SUB_MSG_SH_POOL("laser_ex",fnc_laser_ex);

//	}else{

// 		msg_pump::end_Sub(i_sub_laser_,SLaser());
// 		msg_pump::end_Sub(i_sub_laser_ex_,SLaser_Ex());
// 		boost::function<bool( const SLaser& laser )> fnc_laser;
// 		fnc_laser = boost::bind(&Calib_dlg::s_update_laser,this,_1);
// 		i_sub_laser_ = msg_pump::sub_msg(PUB_AMCL_LASER,fnc_laser);

		boost::function<bool( const SLaser& laser )> fnc_laser;
		fnc_laser = boost::bind(&Calib_dlg::show_laser_seg,this,_1);
		END_MSG_SH_POOL( SLaser,"laser_PLAYBACK");
		//END_MSG_SH_POOL( SLaser_Ex(),"laser_ex");
		SUB_MSG_SH_POOL( "laser_PLAYBACK",fnc_laser);

//	}

	return;

 	Singleton_Project_Manage::get_mutable_instance().open_pro(".//project//default6.pro");
 	Singleton_Reflected_Pillar::get_mutable_instance().init();
 
 	return;

// 	SLaser_Ex laser_ex;
// 	laser_filter_ex l_filter;
// 	
// 	l_filter.load("laser_ex.txt",laser_ex);
// 	l_filter.init_laser_para(laser_ex,0.2,0);
// 	//l_filter.filter_used(laser_ex);
// 	std::multimap<int, std::vector<SPos>> seg_list;
// 	//l_filter.make_seg( laser_ex.seg_, seg_list, laser_ex );
// 	l_filter.filter_intesity(seg_list,laser_ex);
// 
// 	show_laser_ex_seg(laser_ex);
// 	
// 	plot->show();
// 	int irange = plot->AddPlot("range",10000);
// 	int iinten = plot->AddPlot("intensities",10000);
// 
// 	for (int i = 0 ; i < 1000 ; ++i )
// 	{
// 		if (laser_ex.data_[i] < laser_ex.range_max_)
// 		{
// 			plot->AddPlotData(irange,i,laser_ex.data_[i]);
// 			plot->AddPlotData(iinten,i,(F32(laser_ex.intensities_[i])/ 2200* 20) + 5);
// 		}
// 		
// 		
// 	}
// 	//plot->AddPlotData(irange,)
// 
// 	plot->show();


//  	laser_filter l_filter;
//  	get_data(laser_para_,laser_type_);
//  
//  	SLaser new_laser;
//  	if(!th_show_laser_.get(new_laser)){
//  		return;
//  	}
//  	new_laser.start_angle_ = laser_para_.laser_start_angle_;
//  	new_laser.range_max_ = laser_para_.laser_range_max_;
//  	new_laser.range_min_ = laser_para_.laser_range_min_;
//  	new_laser.resolution_ = laser_para_.laser_resolution_;
//  
//  	memset(new_laser.seg_,0,sizeof(U8)*LASER_COUNT);
//  	new_laser.used_ = 0;
//  
//  	l_filter.init_laser_para(str_robot_shape_,new_laser,laser_para_.laser_dx_,laser_para_.laser_dy_);
//  	l_filter.filter_used(new_laser);
//  	get_robot_item()->set_laser_para(laser_para_);
//  	get_robot_item()->set_laser(new_laser);
//  	get_robot_item()->update();

	
}
void Calib_dlg::ChooseLaserEx( bool flag ){
	b_laser_ex_ = !b_laser_ex_;

	if (b_laser_ex_){
		btn_laser_ex_->setText(tr("ext_scan"));
	}else{
		btn_laser_ex_->setText(tr("amcl_scan"));
	}
}

robot_item* Calib_dlg::get_robot_item()
{
	std::vector<QGraphicsItem*> v_item;
	QGraphicsItem* qi = map_scene_->get_item(v_item,"robot");
	
	robot_item*  p_robot_item = static_cast<robot_item*>(qi);

	if (!p_robot_item)
	{
		p_robot_item = new robot_item();
		//SLaser_para laser_para = Singleton_remote_para::get_mutable_instance().get_laser_para();
		p_robot_item->set_laser_para(laser_para_);

// 		std::vector<SVec> v_robot_shape = Singleton_remote_para::get_mutable_instance().get_robot_shape();
// 		p_robot_item->set_robot_shape(v_robot_shape);
// 		std::vector<SVec> v_robot_shape = Singleton_remote_para::get_mutable_instance().get_robot_shape();
// 		p_robot_item->set_robot_shape(v_robot_shape);
		p_robot_item->setZValue(100);
		p_robot_item->setPos(0,0);
		map_scene_->add_item( "robot" , (QGraphicsItem*)p_robot_item);
	}
	
	
	return p_robot_item;
}

map_item* Calib_dlg::get_map_item()
{
	std::vector<QGraphicsItem*> v_item;
	QGraphicsItem* qi = map_scene_->get_item(v_item,MAP_ITEM);

	map_item*  p_map_item = static_cast<map_item*>(qi);

	if (!p_map_item)
	{
		p_map_item = new map_item();
		map_scene_->add_item( MAP_ITEM , (QGraphicsItem*)p_map_item);
	}

	return p_map_item;
}

bool Calib_dlg::s_update_laser_ex( const SLaser_Ex& laser_ex )
{
	laser_filter_ex l_filter;
	get_data(laser_para_,laser_type_);

	SLaser_Ex new_laser;
	new_laser.used_ray_ = LASER_COUNT_EX;

	memcpy(&new_laser,&laser_ex,sizeof(SLaser_Ex));


	F32 diff_angle = 0;
	if(laser_type_ == Laser_type::P_F_R2000){
		if (i_8400_7200_720_ == 0){
			diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-173.57142) ;
		}else if (i_8400_7200_720_ == 1){
			diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-115.71428) ;
		}else if (i_8400_7200_720_ == 2){
			diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-135) ;
		}else{
			diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-135) ;
		}

	}

	new_laser.start_angle_ = laser_ex.start_angle_ + diff_angle;
	new_laser.range_max_ = laser_para_.laser_range_max_;
	new_laser.range_min_ = laser_para_.laser_range_min_;
	//new_laser.resolution_ = laser_para_.laser_resolution_;
	new_laser.dx_ = laser_para_.laser_dx_;
	new_laser.dy_ = laser_para_.laser_dy_;

	memset(new_laser.seg_,0,sizeof(U8)*LASER_COUNT_EX);

	if (th_save_laser_ex_()){
		std::stringstream ss;
		ss<<"laser_ex_"<<i_safe_cnt_++<<".txt4";
		l_filter.save(ss.str(),new_laser);
		th_save_laser_ex_ = false;
	}

	l_filter.init_laser_para(str_robot_shape_,new_laser,new_laser.dx_,new_laser.dy_);
	l_filter.filter_used(new_laser);

	

	get_robot_item()->set_laser_para(laser_para_);
	get_robot_item()->set_laser(new_laser);

	std::multimap<int, std::vector<SPos>> seg_list;
	l_filter.filter_intesity(seg_list,new_laser);

	F32 angle = new_laser.start_angle_;
	SReflector laser_ref;
	memset(&laser_ref,0,sizeof(SReflector));
	std::multimap<int, std::vector<SPos>>::iterator it = seg_list.begin();
	for ( ; it !=  seg_list.end() ; ++it )
	{
		std::vector<SPos> &v(it->second);

		SVec vp;
		if (l_filter.curve_fit( vp, v ))
		{
			angle = new_laser.start_angle_ + new_laser.resolution_*vp.x_;
			laser_ref.id_[laser_ref.used_] = laser_ref.used_;
			laser_ref.pos_[laser_ref.used_].x_ = cos(angle)*vp.y_;
			laser_ref.pos_[laser_ref.used_].y_ = sin(angle)*vp.y_;
			laser_ref.used_++;
		}

	}
	


#if 0

	//int irange = plot_->AddPlot("range",100);

	std::vector<SVec> v_reflect_feature;
	std::multimap<int, std::vector<SPos>>::iterator it = seg_list.begin();
	for ( ; it !=  seg_list.end() ; ++it )
	{
		std::vector<SPos> &v(it->second);

		// 		std::vector<SPos>::iterator it2 = v.begin();
		// 		for ( ; it2 != v.end(); ++it2 )
		// 		{
		// 			int index = it2->x_;
		// 			plot_->AddPlotData(iinten_,index,it2->y_);
		// 		}

		SVec vp;
		if (l_filter.curve_fit( vp, v ))
		{
			v_reflect_feature.push_back(vp);
		}

	}
#endif

	laser_para_.laser_resolution_ = laser_ex.resolution_;

	get_robot_item()->set_scan_reflector(laser_ref);
	get_robot_item()->update();


	//exit(0);
	return true;

}

bool Calib_dlg::s_update_laser_ex2(const SLaser_Ex& laser_ex)
{
	laser_filter_ex l_filter;
	get_data(laser_para_,laser_type_);

	SLaser_Ex new_laser;
	new_laser.used_ray_ = LASER_COUNT_EX;

	memcpy(&new_laser,&laser_ex,sizeof(SLaser_Ex));
	F32 diff_angle = 0;
	if (laser_type_ == Laser_type::WJ_719){
		diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-108) ;
	}else if (laser_type_ == Laser_type::WJ_712){
		diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-108) ;
	}else if (laser_type_ == Laser_type::WJ_718MINI){
		diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-135) ;
		new_laser.used_ray_ = LASER_COUNT_EX_WJ3;
	}else if(laser_type_ == Laser_type::PAVO2_LS50H){
		diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-129.6) ;
	}else if(laser_type_ == Laser_type::P_F_R2000){
		if (i_8400_7200_720_ == 0){
			diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-173.57142) ;
		}else if (i_8400_7200_720_ == 1){
			diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-115.71428) ;
		}else if (i_8400_7200_720_ == 2){
			diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-135) ;
		}else{
			diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-135) ;
		}

	}
	
	new_laser.start_angle_ = laser_ex.start_angle_ + diff_angle;
	new_laser.range_max_ = laser_para_.laser_range_max_;
	new_laser.range_min_ = laser_para_.laser_range_min_;
	//new_laser.resolution_ = laser_para_.laser_resolution_;
	new_laser.dx_ = laser_para_.laser_dx_;
	new_laser.dy_ = laser_para_.laser_dy_;

	memset(new_laser.seg_,0,sizeof(U8)*LASER_COUNT_EX);
	


	l_filter.init_laser_para(str_robot_shape_,new_laser,new_laser.dx_,new_laser.dy_);
	l_filter.filter_used(new_laser);

	get_robot_item()->set_laser_para(laser_para_);
	get_robot_item()->set_laser(new_laser);

	std::multimap<int, std::vector<SPos>> seg_list;
	l_filter.filter_intesity_wj(seg_list,new_laser);
	
	F32 angle = new_laser.start_angle_;
	SReflector laser_ref;
	memset(&laser_ref,0,sizeof(SReflector));
	std::multimap<int, std::vector<SPos>>::iterator it = seg_list.begin();
	for ( ; it !=  seg_list.end() ; ++it )
	{
		std::vector<SPos> &v(it->second);

		SVec vp;
		if (l_filter.curve_fit( vp, v ))
		{
			angle = new_laser.start_angle_ + new_laser.resolution_*vp.x_;
			laser_ref.id_[laser_ref.used_] = laser_ref.used_;
			laser_ref.pos_[laser_ref.used_].x_ = cos(angle)*vp.y_;
			laser_ref.pos_[laser_ref.used_].y_ = sin(angle)*vp.y_;
			laser_ref.used_++;
		}

	}
	if (th_save_laser_ex_()){
		std::stringstream ss;
		ss<<"laser_ex_"<<i_safe_cnt_++<<".txt";
		l_filter.save(ss.str(),new_laser);
		th_save_laser_ex_ = false;
	}
	

#if 0

	//int irange = plot_->AddPlot("range",100);

	std::vector<SVec> v_reflect_feature;
	std::multimap<int, std::vector<SPos>>::iterator it = seg_list.begin();
	for ( ; it !=  seg_list.end() ; ++it )
	{
		std::vector<SPos> &v(it->second);

		// 		std::vector<SPos>::iterator it2 = v.begin();
		// 		for ( ; it2 != v.end(); ++it2 )
		// 		{
		// 			int index = it2->x_;
		// 			plot_->AddPlotData(iinten_,index,it2->y_);
		// 		}

		SVec vp;
		if (l_filter.curve_fit( vp, v ))
		{
			v_reflect_feature.push_back(vp);
		}

	}
#endif
	laser_para_.laser_resolution_ = laser_ex.resolution_;
	
	get_robot_item()->set_scan_reflector(laser_ref);
	get_robot_item()->update();

	
	//exit(0);
	return true;
}

bool Calib_dlg::s_update_ref(const SReflector &laser_ref)
{
	th_ref_ = laser_ref;
	return true;
}

bool Calib_dlg::show_laser_ex_seg( const SLaser_Ex& laser_ex )
{
	
	//l_filter.save("laser_ex.txt",new_laser);
	get_robot_item()->set_laser_para(laser_para_);
	get_robot_item()->set_laser(laser_ex);
	get_robot_item()->update();
	//exit(0);
	return true;
}

bool Calib_dlg::show_laser_seg(const SLaser& laser)
{
	laser_filter l_filter;
	get_data(laser_para_,laser_type_);

	SLaser new_laser;
	memcpy(&new_laser,&laser,sizeof(SLaser));

	if (i_8400_7200_720_ < 2){
		new_laser.start_angle_ += laser_para_.laser_start_angle_ - f_r2000_start_angle_;
		//new_laser.start_angle_ = laser_para_.laser_start_angle_;
		new_laser.range_max_ = laser_para_.laser_range_max_;
		new_laser.range_min_ = laser_para_.laser_range_min_;
		new_laser.resolution_ = laser_para_.laser_resolution_;
	}else{
		new_laser.start_angle_ = laser_para_.laser_start_angle_;
		new_laser.range_max_ = laser_para_.laser_range_max_;
		new_laser.range_min_ = laser_para_.laser_range_min_;
		new_laser.resolution_ = laser_para_.laser_resolution_;
	}


	memset(new_laser.seg_,0,sizeof(U8)*LASER_COUNT);
	new_laser.used_ = 0;

	l_filter.init_laser_para(str_robot_shape_,new_laser,laser_para_.laser_dx_,laser_para_.laser_dy_);
	l_filter.filter_used(new_laser);
	l_filter.segment_used(new_laser);
	std::vector<SLine2P> ln;
	l_filter.get_line(ln,2,0,5);
	get_robot_item()->set_line(ln);
	get_robot_item()->set_laser_para(laser_para_);
	get_robot_item()->set_laser_seg(new_laser);
	//get_robot_item()->set_laser(l_filter.laserxy_);
	get_robot_item()->update();

	return true;
}

void Calib_dlg::ChooseSteering( bool flag )
{
	if(timer_){
		stop_timer();
	}else{
		init_timer();
	}

		


	
}

void Calib_dlg::ChooseShowShape( bool flag )
{
	if (!p_shape_dlg_){
		p_shape_dlg_ = new shape_dlg(); 
		p_shape_dlg_->setMinimumWidth(400);
		p_shape_dlg_->setMinimumHeight(100);
		//p_shape_dlg_->setModal(false);
		p_shape_dlg_->set_shape_list(v_shape_pro_);

		robot_item* p_robot = get_robot_item();
		p_shape_dlg_->bind_show( boost::bind(&robot_item::set_shape,p_robot,_1,_2) );
		p_shape_dlg_->exec();
	}else{
		p_shape_dlg_->exec();
	}
	
	//pDlg->setModal(true);
	
	

	QtVariantProperty* p_item = 0;
	p_shape_dlg_->get_sel_shape(p_item);
	

	if (p_item){
		std::string str_nm = p_item->propertyName().toStdString();
		std::string str_shape = p_item->value().toString().toStdString();
	}
	
}

void Calib_dlg::ChooseSavePara(bool flag)
{
	std::map< std::string, std::string >::iterator it = m_update_para_.begin();
	for (; it != m_update_para_.end() ; ++it ){

		RPC_CONFIG_CLIENT.set_whole_config(it->first,it->second);
	}
	if (m_update_para_.size()){
		RPC_CONFIG_CLIENT.save();
	}
	
}

void Calib_dlg::ChooseShowLasermap(bool flag)
{

	if(!gmap_laser_inf_){
		gmap_laser_inf_ = CREATE_SHARED_GMAP(SHARED_GLOBAL_LASER_INF_MAP);
	}
	map_item*  p_map_item = get_map_item();

	if (p_map_item)
	{
		p_map_item->set_map(gmap_laser_inf_);
	}

}
void Calib_dlg::ChooseSaveLaserEx( bool flag )
{
	th_save_laser_ex_ = true;

}
void Calib_dlg::filter_r2000(std::string str_file){

	laser_filter_ex l_filter;
	get_data(laser_para_,laser_type_);

	SLaser_Ex new_laser;
	memset(&new_laser,0,sizeof(SLaser_Ex));
	l_filter.load(str_file,new_laser);

	memset(new_laser.seg_,0,sizeof(U8)*LASER_COUNT_EX);
	new_laser.used_ray_ = LASER_COUNT_EX;

	//s_update_laser_ex2(new_laser);
	l_filter.init_laser_para(str_robot_shape_,new_laser,new_laser.dx_,new_laser.dy_);
	l_filter.filter_used(new_laser);

	get_robot_item()->set_laser_para(laser_para_);
	get_robot_item()->set_laser(new_laser);


	std::multimap<int, std::vector<SPos>> seg_list;
	l_filter.filter_intesity(seg_list,new_laser);

	F32 angle = new_laser.start_angle_;
	SReflector laser_ref;
	memset(&laser_ref,0,sizeof(SReflector));
	std::multimap<int, std::vector<SPos>>::iterator it = seg_list.begin();
	for ( ; it !=  seg_list.end() ; ++it )
	{
		std::vector<SPos> &v(it->second);

		SVec vp;
		if (l_filter.curve_fit( vp, v ))
		{
			angle = new_laser.start_angle_ + new_laser.resolution_*vp.x_;
			laser_ref.id_[laser_ref.used_] = laser_ref.used_;
			laser_ref.pos_[laser_ref.used_].x_ = cos(angle)*vp.y_;
			laser_ref.pos_[laser_ref.used_].y_ = sin(angle)*vp.y_;
			laser_ref.used_++;
		}

	}

	get_robot_item()->set_scan_reflector(laser_ref);
	get_robot_item()->update();
	//pub_ref(laser_ref);
}
void Calib_dlg::filter_wj712(std::string str_file){
	
	laser_filter_ex l_filter;
	get_data(laser_para_,laser_type_);

	SLaser_Ex new_laser;
	memset(&new_laser,0,sizeof(SLaser_Ex));
	l_filter.load(str_file,new_laser);

	memset(new_laser.seg_,0,sizeof(U8)*LASER_COUNT_EX);
	new_laser.used_ray_ = 7200;

	//s_update_laser_ex2(new_laser);
	l_filter.init_laser_para(str_robot_shape_,new_laser,new_laser.dx_,new_laser.dy_);
	l_filter.filter_used(new_laser);

	get_robot_item()->set_laser_para(laser_para_);
	get_robot_item()->set_laser(new_laser);


	std::multimap<int, std::vector<SPos>> seg_list;
	l_filter.filter_intesity_wj(seg_list,new_laser);

	F32 angle = new_laser.start_angle_;
	SReflector laser_ref;
	memset(&laser_ref,0,sizeof(SReflector));
	std::multimap<int, std::vector<SPos>>::iterator it = seg_list.begin();
	for ( ; it !=  seg_list.end() ; ++it )
	{
		std::vector<SPos> &v(it->second);

		SVec vp;
		if (l_filter.curve_fit( vp, v ))
		{
			angle = new_laser.start_angle_ + new_laser.resolution_*vp.x_;
			laser_ref.id_[laser_ref.used_] = laser_ref.used_;
			laser_ref.pos_[laser_ref.used_].x_ = cos(angle)*vp.y_;
			laser_ref.pos_[laser_ref.used_].y_ = sin(angle)*vp.y_;
			laser_ref.used_++;
		}

	}
	
	get_robot_item()->set_scan_reflector(laser_ref);
	get_robot_item()->update();
	//pub_ref(laser_ref);
}

void Calib_dlg::ChooseCalibRef( bool flag )
{
	std::string file_name = ".//";

	QString dir = QFileDialog::getOpenFileName(NULL,tr("Open File"),
		file_name.c_str(),
		"file (*.txt *.txt2 *.txt3 *.txt4)");
	std::string path = dir.toStdString();
	std::string str_type = cComm::Get_FileType(path);
	if (str_type == "txt4"){
		filter_r2000(path);
	}else if (str_type == "txt"){
		filter_wj712(path);
	}else if (str_type == "txt2"){
		filter_wj719(path);
	}else if (str_type == "txt3"){
		filter_wj718mini(path);
	}
	

}

bool Calib_dlg::s_update_laser_ex3( const SLaser_Ex2& laser_ex2 )
{
	laser_filter_ex2 l_filter2;
	get_data(laser_para_,laser_type_);

	SLaser_Ex2 new_laser2;
	memcpy(&new_laser2,&laser_ex2,sizeof(SLaser_Ex2));
	F32 diff_angle = 0;
	if (laser_type_ == Laser_type::WJ_719){
		diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-135) ;
	}

	new_laser2.start_angle_ = laser_ex2.start_angle_ + diff_angle;
	new_laser2.range_max_ = laser_para_.laser_range_max_;
	new_laser2.range_min_ = laser_para_.laser_range_min_;
	//new_laser.resolution_ = laser_para_.laser_resolution_;
	new_laser2.dx_ = laser_para_.laser_dx_;
	new_laser2.dy_ = laser_para_.laser_dy_;

	memset(new_laser2.seg_,0,sizeof(U8)*LASER_COUNT_EX2);
	new_laser2.used_ray_ = LASER_COUNT_EX2;


	l_filter2.init_laser_para(str_robot_shape_,new_laser2,new_laser2.dx_,new_laser2.dy_);
	l_filter2.filter_used(new_laser2);

	get_robot_item()->set_laser_para(laser_para_);
	get_robot_item()->set_laser(new_laser2);

	std::multimap<int, std::vector<SPos>> seg_list;
	l_filter2.filter_intesity_wj2(seg_list,new_laser2);

	F32 angle = new_laser2.start_angle_;
	SReflector laser_ref;
	memset(&laser_ref,0,sizeof(SReflector));
	std::multimap<int, std::vector<SPos>>::iterator it = seg_list.begin();
	for ( ; it !=  seg_list.end() ; ++it )
	{
		std::vector<SPos> &v(it->second);

		SVec vp;
		if (l_filter2.curve_fit( vp, v ))
		{
			angle = new_laser2.start_angle_ + new_laser2.resolution_*vp.x_;
			laser_ref.id_[laser_ref.used_] = laser_ref.used_;
			laser_ref.pos_[laser_ref.used_].x_ = cos(angle)*vp.y_;
			laser_ref.pos_[laser_ref.used_].y_ = sin(angle)*vp.y_;
			laser_ref.used_++;
		}

	}
	if (th_save_laser_ex_()){
		std::stringstream ss;
		ss<<"laser_ex_"<<i_safe_cnt_++<<".txt2";
		l_filter2.save(ss.str(),new_laser2);
		th_save_laser_ex_ = false;
	}


#if 0

	//int irange = plot_->AddPlot("range",100);

	std::vector<SVec> v_reflect_feature;
	std::multimap<int, std::vector<SPos>>::iterator it = seg_list.begin();
	for ( ; it !=  seg_list.end() ; ++it )
	{
		std::vector<SPos> &v(it->second);

		// 		std::vector<SPos>::iterator it2 = v.begin();
		// 		for ( ; it2 != v.end(); ++it2 )
		// 		{
		// 			int index = it2->x_;
		// 			plot_->AddPlotData(iinten_,index,it2->y_);
		// 		}

		SVec vp;
		if (l_filter.curve_fit( vp, v ))
		{
			v_reflect_feature.push_back(vp);
		}

	}
#endif
	laser_para_.laser_resolution_ = laser_ex2.resolution_;

	get_robot_item()->set_scan_reflector(laser_ref);
	get_robot_item()->update();


	//exit(0);
	return true;
}

void Calib_dlg::filter_wj719( std::string str_file )
{
	laser_filter_ex2 l_filter2;
	get_data(laser_para_,laser_type_);

	SLaser_Ex2 new_laser2;
	memset(&new_laser2,0,sizeof(SLaser_Ex2));
	l_filter2.load(str_file,new_laser2);

	memset(new_laser2.seg_,0,sizeof(U8)*LASER_COUNT_EX2);
	new_laser2.used_ray_ = LASER_COUNT_EX2;

	//s_update_laser_ex2(new_laser);
	l_filter2.init_laser_para(str_robot_shape_,new_laser2,new_laser2.dx_,new_laser2.dy_);
	l_filter2.filter_used(new_laser2);

	get_robot_item()->set_laser_para(laser_para_);
	get_robot_item()->set_laser(new_laser2);


	std::multimap<int, std::vector<SPos>> seg_list;
	l_filter2.filter_intesity_wj2(seg_list,new_laser2);

	F32 angle = new_laser2.start_angle_;
	SReflector laser_ref;
	memset(&laser_ref,0,sizeof(SReflector));
	std::multimap<int, std::vector<SPos>>::iterator it = seg_list.begin();
	for ( ; it !=  seg_list.end() ; ++it )
	{
		std::vector<SPos> &v(it->second);

		SVec vp;
		if (l_filter2.curve_fit( vp, v ))
		{
			angle = new_laser2.start_angle_ + new_laser2.resolution_*vp.x_;
			laser_ref.id_[laser_ref.used_] = laser_ref.used_;
			laser_ref.pos_[laser_ref.used_].x_ = cos(angle)*vp.y_;
			laser_ref.pos_[laser_ref.used_].y_ = sin(angle)*vp.y_;
			laser_ref.used_++;
		}

	}

	get_robot_item()->set_scan_reflector(laser_ref);
	get_robot_item()->update();
}

void Calib_dlg::set_wj718mini_para()
{
	laser_type_ = Laser_type::WJ_718MINI;

	str_ip_ = "192.168.1.100";
	memset(laser_para_.ch_laser_ip_,0,500);
	memcpy(laser_para_.ch_laser_ip_,str_ip_.c_str(),str_ip_.length());

	laser_para_.reverse_ = false;
	laser_para_.laser_start_angle_ = Deg2Rad(-135);
	f_wj712_start_angle_ = laser_para_.laser_start_angle_;
	laser_para_.laser_resolution_ = Deg2Rad(0.5);

	laser_para_.laser_range_max_ = 30.0;
	laser_para_.laser_range_min_ = 0.05;
	laser_para_.laser_dx_ = 0.2;
	laser_para_.laser_dy_ = 0.0;
}

void Calib_dlg::ChooseCalibLaser( bool flag )
{
	F32 dx = 0 ; 
	F32 da = 0 ;

	if (!calib_tools_){
		calib_tools_ = new calib_tools();
		F32 f_wall = item_calib_line_->value().toDouble();
		calib_tools_->init(f_wall);
		calib_tools_->bind_pub_laser(boost::bind( & Calib_dlg::show_laser_seg,this,_1));
	}else{

		calib_tools_->stop_get_diff(dx,da);
		SDelete(calib_tools_);

		laser_para_.laser_start_angle_ = laser_para_.laser_start_angle_ + Deg2Rad(da);
		laser_para_.laser_dx_ = laser_para_.laser_dx_ + dx;
		show_data(laser_para_,laser_type_);
	}

}

bool Calib_dlg::s_update_laser_ex4( const SLaser_Ex& laser_ex )
{
	laser_filter_ex l_filter;
	get_data(laser_para_,laser_type_);

	SLaser_Ex new_laser;
	memcpy(&new_laser,&laser_ex,sizeof(SLaser_Ex));
	new_laser.used_ray_ = LASER_COUNT_EX_WJ3;

	F32 diff_angle = 0;
	if (laser_type_ == Laser_type::WJ_719){
		diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-108) ;
	}else if (laser_type_ == Laser_type::WJ_712){
		diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-108) ;
	}else if (laser_type_ == Laser_type::WJ_718MINI){
		diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-135) ;
		new_laser.used_ray_ = LASER_COUNT_EX_WJ3;
	}else if(laser_type_ == Laser_type::PAVO2_LS50H){
		diff_angle = laser_para_.laser_start_angle_ - Deg2Rad(-129.6) ;
	}

	new_laser.start_angle_ = laser_ex.start_angle_ + diff_angle;
	new_laser.range_max_ = laser_para_.laser_range_max_;
	new_laser.range_min_ = laser_para_.laser_range_min_;
	//new_laser.resolution_ = laser_para_.laser_resolution_;
	new_laser.dx_ = laser_para_.laser_dx_;
	new_laser.dy_ = laser_para_.laser_dy_;

	memset(new_laser.seg_,0,sizeof(U8)*LASER_COUNT_EX);



	l_filter.init_laser_para(str_robot_shape_,new_laser,new_laser.dx_,new_laser.dy_);
	l_filter.filter_used(new_laser);

	get_robot_item()->set_laser_para(laser_para_);
	get_robot_item()->set_laser(new_laser);

	std::multimap<int, std::vector<SPos>> seg_list;
	l_filter.filter_intesity_wj3(seg_list,new_laser);

	F32 angle = new_laser.start_angle_;
	SReflector laser_ref;
	memset(&laser_ref,0,sizeof(SReflector));
	std::multimap<int, std::vector<SPos>>::iterator it = seg_list.begin();
	for ( ; it !=  seg_list.end() ; ++it )
	{
		std::vector<SPos> &v(it->second);

		SVec vp;
		if (l_filter.curve_fit( vp, v ))
		{
			angle = new_laser.start_angle_ + new_laser.resolution_*vp.x_;
			laser_ref.id_[laser_ref.used_] = laser_ref.used_;
			laser_ref.pos_[laser_ref.used_].x_ = cos(angle)*vp.y_;
			laser_ref.pos_[laser_ref.used_].y_ = sin(angle)*vp.y_;
			laser_ref.used_++;
		}

	}
	
	if (th_save_laser_ex_()){
		std::stringstream ss;
		ss<<"laser_ex_"<<i_safe_cnt_++<<".txt3";
		l_filter.save(ss.str(),new_laser);
		th_save_laser_ex_ = false;
	}

	get_robot_item()->set_scan_reflector(laser_ref);
	get_robot_item()->update();


	//exit(0);
	return true;
	
}

void Calib_dlg::filter_wj718mini( std::string str_file )
{
	laser_filter_ex l_filter;
	get_data(laser_para_,laser_type_);

	SLaser_Ex new_laser;
	memset(&new_laser,0,sizeof(SLaser_Ex));
	l_filter.load(str_file,new_laser);

	memset(new_laser.seg_,0,sizeof(U8)*LASER_COUNT_EX);
	new_laser.used_ray_ = LASER_COUNT_EX_WJ3;

	//s_update_laser_ex2(new_laser);
	l_filter.init_laser_para(str_robot_shape_,new_laser,new_laser.dx_,new_laser.dy_);
	l_filter.filter_used(new_laser);

	get_robot_item()->set_laser_para(laser_para_);
	get_robot_item()->set_laser(new_laser);


	std::multimap<int, std::vector<SPos>> seg_list;
	l_filter.filter_intesity_wj3(seg_list,new_laser);

	F32 angle = new_laser.start_angle_;
	SReflector laser_ref;
	memset(&laser_ref,0,sizeof(SReflector));
	std::multimap<int, std::vector<SPos>>::iterator it = seg_list.begin();
	for ( ; it !=  seg_list.end() ; ++it )
	{
		std::vector<SPos> &v(it->second);

		SVec vp;
		if (l_filter.curve_fit( vp, v ))
		{
			angle = new_laser.start_angle_ + new_laser.resolution_*vp.x_;
			laser_ref.id_[laser_ref.used_] = laser_ref.used_;
			laser_ref.pos_[laser_ref.used_].x_ = cos(angle)*vp.y_;
			laser_ref.pos_[laser_ref.used_].y_ = sin(angle)*vp.y_;
			laser_ref.used_++;
		}

	}

	get_robot_item()->set_scan_reflector(laser_ref);
	get_robot_item()->update();
}


