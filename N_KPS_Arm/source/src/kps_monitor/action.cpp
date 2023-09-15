#include <iostream>

#include <QtGui>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QObject>
#include <QMessageBox>
#include <QGraphicsItem>

#include "flirt/sensorstream/CarmenLog.h"
#include "flirt/sensorstream/LogSensorStream.h"
#include "flirt/sensorstream/SensorStream.h"
#include "flirt/feature/CurvatureDetector.h"

#include "Comm/Comm.h"
#include "Comm/Rand.hpp"
#include "Comm/TimerDiff.h"
#include "Comm/Laser2LaserEx.hpp"

#include "kps_main_win.h"
#include "mapserver/map_def.h"
#include "mapserver/MapServer.h"

#include "interface/xml_rpc_client.h"
#include "interface/cfg.hpp"
#include "interface/rpc_config_client.h"
#include "file_list_dlg.h"
#include "item_collection.h"
#include "scene/map_scene.h"
#include "slam/map_server.h"
#include "project/project_manage.h"
#include "scene/QTypeDefine.h"
#include "scene/reflector_item.h"
#include "scene/lab_item.h"
#include "scene/node_item.h"
#include "scene/edge_item.h"
#include "scene/range_item.h"
#include "scene/producer_item.h"
#include "scene/consumer_item.h"
#include "scene/processer_item.h"
#include "scene/storage_item.h"
#include "scene/charge_item.h"
#include "reflected_pillar/reflected_pillar_mapping.h"
#include "action_monitor_dlg.h"

#include "loop_closure/2dlaser_loop_closure.h"
#include "log_priority_dlg.h"
#include "para_dlg.h"

#include "device/device_para.h"
#include "device/device_pool.h"
#include "project/task_manage.h"
#include "project/project_manage.h"
#include "project/task_rpc_client.h"
#include "auto_cover.h"
#include "path_search_dlg.h"
#include "dynamic_loc/dynamic_loc.h"

#include "action.h"

action_collection::action_collection()
{
	str_user_ = MENU_USER_ROOT;

	m_event_ = 0;
	
	main_win_ = 0;
	main_menuBar_ = 0;
	main_Toolbar_ = 0;

	map_menu_ = 0;
	begin_mapping_ = 0;
	end_mapping_ = 0;
	begin_bag_mapping_ = 0;
	end_bag_mapping_ = 0;
	show_mapping_ = 0;
	save_mapping_ = 0;
	arm_mapping_ = 0;
	b_arm_mapping_ = false;

	file_menu_ = 0;
	open_map_ = 0;
	upload_map_ = 0;
	download_map_ = 0;
	download_map_file_ = 0;
	save_map_ = 0;
	save_onboard_map_ = 0;
	set_onboard_map_ = 0;
	

	location_menu_ = 0;
	show_laser_ = 0;
	show_particles_ = 0;
	locate_ = 0;
	auto_locate_ = 0;

	
	b_locate_ = false;
	b_auto_locate_ = false;

	reflector_menu_ = 0;
	open_reflector_ = 0;
	save_reflector_ = 0;
	upload_reflector_ = 0;
	download_reflector_ = 0;

	show_ex_reflector_ = 0;
	add_reflector_ = 0;
	del_item_ = 0;
	log_bag_ex_begin_ = 0;
	log_bag_ex_end_ = 0;
	reflector_mapping_ = 0;
	reflector_gmapping_ = 0;
	reflector_modify_ = 0;
	reflector_g2o_ = 0;
	
	b_add_reflector_ = false;

	log_bag_menu_ = 0;
	log_bag_begin_ = 0;
	log_bag_end_ = 0;
	log_bag_play_ = 0;
	log_bag_play_stop_ = 0;
	log_bag_continue_ = 0;
	log_bag_gmapping_ = 0;
	log_bag_upload_ = 0;
	log_bag_suro_debug_ = 0;
	log_bag_play_back = 0;
	log_bag_ex_play_ = 0 ;
	log_bag_dynamic_key_ = 0;
	log_bag_clear_ = 0;

	move_menu_ = 0;
	move_ccw_ = 0;
	move_cw_ = 0;
	move_front_ = 0;
	move_back_ = 0;
	move_stop_ = 0;
	move_left_ = 0;
	move_right_ = 0;
	move_ori_ = 0;
	move_show_ = 0;
	//file_menuBar_ = 0;

	calib_menu_ = 0;
	laser_cross_ = 0;

	loop_closure_menu_ = 0;
	mathc_one_ = 0;
	load_refscan_ = 0;

	show_log_menu_ = 0;
	show_log_ = 0;
	clear_log_ = 0;
	set_priority_ = 0;
	set_para_ = 0;

	init_menu_ = 0;
	para_init_ = 0;
	auto_init_ = 0;

	tools_menu_ = 0;
	zoom_in_ = 0;
	zoom_out_ = 0;
	search_path_ = 0;
	dy_location_ = 0;
	scan_match_ = 0;
	add_qr_code_ = 0;

	path_search_dlg_ = 0;
	

	open_project_ = 0;
	save_project_ = 0;

	download_project_ = 0;
	upload_project_ = 0;
	set_onboard_project_ = 0 ;

	
	
	select_ = 0;
	align_ = 0;
	rect_ = 0;
	range_ = 0;

	node_ = 0;
	edge_ = 0 ;
	rand_edge_ = 0 ;
	del_node_edge_ = 0;

	wander_ = 0;
	auto_cover_ = 0;
	producer_ = 0;
	consumer_ = 0;
	processer_ = 0;
	processer_ = 0;
	storage_ = 0;
	charge_ = 0;

	b_wander_run_ = false;
	b_rect_ = false;
	b_range_ = false;
	b_add_node_ = false;
	b_add_edge_ = false;
	b_add_producer_ = false;
	b_add_consumer_ = false;
	b_add_processer_ = false;
	b_add_storage_ = false;	
	b_add_charge_ = false;
	b_add_qrcode_ = false;

	p_lc_ = 0;
	p_psm_node_ = 0;
	i_current_index_ = 0;

	pro_path_ = ".//project//";

	ref_mapping_ = 0;
}

action_collection::~action_collection()
{

}

void action_collection::init( kps_main_win* main_win ,item_collection* item )
{
	main_win_ = main_win;
	item_ = item;
	
	act_permission_.init();
	create_menu();
	
	main_win_->setMenuBar(main_menuBar_);
	main_win_->addToolBar(main_Toolbar_);

	SPubDevStatus dev;
	Singleton_XML_Client::get_mutable_instance().get_dev_status(dev,Comm_Dev_Id::ID_MAP_SERVER);
	if (dev.dev_status_.status_ == eMAP_STATUS::MAP_IDLE)
	{
		arm_mapping_->setIconText(QString("Mapping(Run)"));
		b_arm_mapping_ = false;
	}else{
		arm_mapping_->setIconText(QString("Mapping(Stop)"));
		b_arm_mapping_ = true;
	}

	wander_->setIconText(QString("Wander (Run)"));

	play_back_bag_.init_normal();
	play_back_bag_ex_.init_normal_r();

	
}

void action_collection::load_menu(std::string str_group, QMenu* p_menu)
{
	std::list<std::pair<QAction*,int>> l_avail_permission;

	act_permission_.get_menu_available(str_group,str_user_,l_avail_permission);

	std::list<std::pair<QAction*,int>>::iterator it = l_avail_permission.begin();
	for ( ; it != l_avail_permission.end() ; ++it ){
		
		QAction* p_action = it->first;
		
		int i_permission = it->second;
		if (i_permission){
			p_action->setEnabled(true);
		}else{
			p_action->setEnabled(false);
		}
		
		p_menu->addAction(p_action);
		main_Toolbar_->addAction(p_action);
	}
}

void action_collection::create_menu(){

	main_menuBar_ = new QMenuBar( main_win_);

	create_toolbar();

	create_file_action();
	create_map_action();
	create_locate_action();
	create_log_bag_action();
	create_reflector_action();
	create_move_action();
	create_project_action();
	create_calib_action();
	create_loop_closure_action();
	create_show_log();
	create_init_action();
	create_tools_action();

	clear_all_menu();
	sel_map_acton();
	sel_show_log();
}

bool action_collection::set_CursorShape(qt_eve::mouse_event::MU_TYPE mt)
{
	set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_NONE);
	QApplication::restoreOverrideCursor();

	int i_bit = m_event_ & (1<<mt);

	if (m_event_ & (1<<qt_eve::mouse_event::MU_TYPE::MU_ADD_EDGE)){
		foreach (QGraphicsItem *item, main_win_->get_scene()->items()) 
		{
			item->setAcceptedMouseButtons(Qt::LeftButton);
		}
	}
	
	m_event_ = 0;

	if (i_bit){
		m_event_ &= ~(1<<mt);
		return false;
	}else{
		m_event_ |= (1<<mt);
		return true;
	}

}

void action_collection::create_toolbar(){

	main_Toolbar_ = new QToolBar(tr("ToolBar"),main_win_);
	main_Toolbar_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void action_collection::create_map_action()
{
	map_menu_ = main_menuBar_->addMenu(tr("&Mapping"));
	

	begin_mapping_ = new QAction(QIcon("images/import.png"),tr("&Begin Mapping"), main_win_);
	begin_mapping_->setShortcut(tr("Ctrl+B"));
	begin_mapping_->setStatusTip(tr("Begin Mapping"));
	connect(begin_mapping_, SIGNAL(triggered()),this, SLOT(do_begin_mapping()));

 	//map_menu_->addAction(begin_mapping_);
 	//main_Toolbar_->addAction(begin_mapping_);


	end_mapping_ = new QAction(QIcon("images/import.png"),tr("&End Mapping"), main_win_);
	end_mapping_->setShortcut(tr("Ctrl+E"));
	end_mapping_->setStatusTip(tr("End Mapping"));
	connect(end_mapping_, SIGNAL(triggered()),this, SLOT(do_end_mapping()));

 	//map_menu_->addAction(end_mapping_);
 	//main_Toolbar_->addAction(end_mapping_);

	begin_bag_mapping_ = new QAction(QIcon("images/import.png"),tr("Begin&Mapping bag"), main_win_);
	begin_bag_mapping_->setShortcut(tr("Ctrl+M"));
	begin_bag_mapping_->setStatusTip(tr("Begin Mapping bag"));
	connect(begin_bag_mapping_, SIGNAL(triggered()),this, SLOT(do_begin_bag_mapping()));
	
	end_bag_mapping_ = new QAction(QIcon("images/import.png"),tr("End&Mapping bag"), main_win_);
	end_bag_mapping_->setShortcut(tr("Ctrl+M"));
	end_bag_mapping_->setStatusTip(tr("End Mapping bag"));
	connect(end_bag_mapping_, SIGNAL(triggered()),this, SLOT(do_end_bag_mapping()));
// 	map_menu_->addAction(bag_mapping_);
// 	main_Toolbar_->addAction(bag_mapping_);


	show_mapping_ = new QAction(QIcon("images/import.png"),tr("Sho&w Mapping"), main_win_);
	show_mapping_->setShortcut(tr("Ctrl+W"));
	show_mapping_->setStatusTip(tr("Show Mapping"));
	connect(show_mapping_, SIGNAL(triggered()),this, SLOT(do_show_mapping()));

// 	map_menu_->addAction(show_mapping_);
// 	main_Toolbar_->addAction(show_mapping_);
	save_mapping_ = new QAction(QIcon("images/import.png"),tr("&Save Mapping"), main_win_);
	save_mapping_->setShortcut(tr("Ctrl+W"));
	save_mapping_->setStatusTip(tr("Save Mapping"));
	connect(save_mapping_, SIGNAL(triggered()),this, SLOT(do_save_mapping()));
	
	arm_mapping_= new QAction(QIcon("images/import.png"),tr("&Mapping(Run)"), main_win_);
	arm_mapping_->setShortcut(tr("Ctrl+W"));
	arm_mapping_->setStatusTip(tr("Mapping"));
	connect(arm_mapping_, SIGNAL(triggered()),this, SLOT(do_arm_mapping()));
	connect(this,SIGNAL(sig_show_mapping_str(QString)),SLOT(slot_show_mapping_str(QString))); 
	
	//bind_mapping_event( boost::bind( &action_collection::show_mapping_icon ,this) );
}
void action_collection::create_file_action()
{
	file_menu_ = main_menuBar_->addMenu(tr("&File"));

	
	open_map_ = new QAction(QIcon("images/import.png"),tr("&Open Map"), main_win_);
	open_map_->setShortcut(tr("Ctrl+D"));
	open_map_->setStatusTip(tr("Open Map"));
	connect(open_map_, SIGNAL(triggered()),this, SLOT(do_open_map()));
	act_permission_.set_menu(MENU_ACT_GP_MAP,MENU_ACT_OPEN_MAP,open_map_);

	upload_map_ = new QAction(QIcon("images/import.png"),tr("&upLoad Map"), main_win_);
	upload_map_->setShortcut(tr("Ctrl+U"));
	upload_map_->setStatusTip(tr("upLoad Map"));
	connect(upload_map_, SIGNAL(triggered()),this, SLOT(do_upload_map_separate()));
	act_permission_.set_menu(MENU_ACT_GP_MAP,MENU_ACT_UPLOAD_MAP,upload_map_);
	act_permission_.set_menu(MENU_ACT_GP_REF,MENU_ACT_REFBAG_LOGEX_UPLOAD,upload_map_);

	download_map_ = new QAction(QIcon("images/import.png"),tr("&downLoad Map"), main_win_);
	download_map_->setShortcut(tr("Ctrl+D"));
	download_map_->setStatusTip(tr("downLoad Map"));
	connect(download_map_, SIGNAL(triggered()),this, SLOT(do_download_map()));
	act_permission_.set_menu(MENU_ACT_GP_MAP,MENU_ACT_DOWNLOAD_MAP,download_map_);

	download_map_file_ = new QAction(QIcon("images/import.png"),tr("&downLoad Map file"), main_win_);
	download_map_file_->setShortcut(tr("Ctrl+D"));
	download_map_file_->setStatusTip(tr("downLoad Map file"));
	connect(download_map_file_, SIGNAL(triggered()),this, SLOT(do_download_map_file()));
	act_permission_.set_menu(MENU_ACT_GP_MAP,MENU_ACT_DOWNLOAD_MAP_FILE,download_map_file_);

	save_map_ = new QAction(QIcon("images/import.png"),tr("&Save Map"), main_win_);
	save_map_->setShortcut(tr("Ctrl+S"));
	save_map_->setStatusTip(tr("Save Map"));
	connect(save_map_, SIGNAL(triggered()),this, SLOT(do_save_map()));
	act_permission_.set_menu(MENU_ACT_GP_MAP,MENU_ACT_SAVEMAP,save_map_);

	
	save_onboard_map_ = new QAction(QIcon("images/import.png"),tr("&Save onboard Map"), main_win_);
	save_onboard_map_->setShortcut(tr("Ctrl+R"));
	save_onboard_map_->setStatusTip(tr("Save onboard Map"));
	connect(save_onboard_map_, SIGNAL(triggered()),this, SLOT(do_save_onboard_map()));
	act_permission_.set_menu(MENU_ACT_GP_MAP,MENU_ACT_SAVE_ONBOARD_MAP,save_onboard_map_);

	set_onboard_map_ = new QAction(QIcon("images/import.png"),tr("&Set onboard Map"), main_win_);
	set_onboard_map_->setShortcut(tr("Ctrl+R"));
	set_onboard_map_->setStatusTip(tr("Set onboard Map"));
	connect(set_onboard_map_, SIGNAL(triggered()),this, SLOT(do_set_onboard_map()));
	act_permission_.set_menu(MENU_ACT_GP_MAP,MENU_ACT_SET_ONBOARD_MAP,set_onboard_map_);

	
// 	file_menuBar_ = new QMenuBar(0);
//	file_menu_ = new QMenu(file_menuBar_);
//	file_menu_->addAction("a");
}

void action_collection::create_locate_action()
{
	location_menu_ = main_menuBar_->addMenu(tr("&Location"));


	show_laser_= new QAction(QIcon("images/import.png"),tr("ShowLaser"), main_win_);
	show_laser_->setShortcut(tr("Ctrl+A"));
	show_laser_->setStatusTip(tr("ShowLaser"));
	connect(show_laser_, SIGNAL(triggered()),this, SLOT(do_show_laser()));
	act_permission_.set_menu(MENU_ACT_GP_LOC,MENU_ACT_SHOW_LASER,show_laser_);

	show_particles_= new QAction(QIcon("images/import.png"),tr("ShowParticles"), main_win_);
	show_particles_->setShortcut(tr("Ctrl+A"));
	show_particles_->setStatusTip(tr("ShowParticles"));
	connect(show_particles_, SIGNAL(triggered()),this, SLOT(do_show_particles()));
	act_permission_.set_menu(MENU_ACT_GP_LOC,MENU_ACT_SHOW_PARTICLES,show_particles_);

	locate_ = new QAction(QIcon("images/import.png"),tr("Loc&ate"), main_win_);
	locate_->setShortcut(tr("Ctrl+A"));
	locate_->setStatusTip(tr("Locate"));
	connect(locate_, SIGNAL(triggered()),this, SLOT(do_locate()));
	act_permission_.set_menu(MENU_ACT_GP_LOC,MENU_ACT_LOCATE,locate_);

	auto_locate_ = new QAction(QIcon("images/import.png"),tr("Auto&Locate"), main_win_);
	auto_locate_->setShortcut(tr("Alt+A"));
	auto_locate_->setStatusTip(tr("AutoLocate"));
	connect(auto_locate_, SIGNAL(triggered()),this, SLOT(do_auto_locate()));
	act_permission_.set_menu(MENU_ACT_GP_LOC,MENU_ACT_AUTO_LOCATE,auto_locate_);
	
}
void action_collection::sel_map_acton()
{
#if 0
	file_menu_->addAction(arm_mapping_);
	main_Toolbar_->addAction(arm_mapping_);


 	map_menu_->addAction(log_bag_upload_);
 	main_Toolbar_->addAction(log_bag_upload_);
 
 	map_menu_->addAction(log_bag_gmapping_);
 	main_Toolbar_->addAction(log_bag_gmapping_);

	
//	main_Toolbar_->addSeparator();


// 	map_menu_->addAction(begin_mapping_);
// 	main_Toolbar_->addAction(begin_mapping_);
// 	map_menu_->addAction(end_mapping_);
// 	main_Toolbar_->addAction(end_mapping_);
// 	map_menu_->addAction(save_mapping_);
// 	main_Toolbar_->addAction(save_mapping_);

// 	main_Toolbar_->addSeparator();
// 
// 	map_menu_->addAction(begin_bag_mapping_);
// 	main_Toolbar_->addAction(begin_bag_mapping_);
// 	map_menu_->addAction(end_bag_mapping_);
// 	main_Toolbar_->addAction(end_bag_mapping_);
// 
// 	main_Toolbar_->addSeparator();
// 
// 	map_menu_->addAction(save_mapping_);
// 	main_Toolbar_->addAction(save_mapping_);
// 	map_menu_->addAction(show_mapping_);
// 	main_Toolbar_->addAction(show_mapping_);

#endif

	load_menu(MENU_ACT_GP_MAP,map_menu_);
	main_Toolbar_->addSeparator();
	load_menu(MENU_ACT_GP_GMAPPING,map_menu_);

	main_menuBar_->addMenu(map_menu_);

	main_Toolbar_->addSeparator();
	
}

void action_collection::sel_file_acton()
{

	file_menu_->addAction(open_map_);
	main_Toolbar_->addAction(open_map_);

	file_menu_->addAction(upload_map_);
	main_Toolbar_->addAction(upload_map_);

	file_menu_->addAction(download_map_);
	main_Toolbar_->addAction(download_map_);

	file_menu_->addAction(download_map_file_);
	main_Toolbar_->addAction(download_map_file_);

	file_menu_->addAction(save_map_);
	main_Toolbar_->addAction(save_map_);
// 
// 	file_menu_->addAction(save_onboard_map_);
// 	main_Toolbar_->addAction(save_onboard_map_);
// 
 	file_menu_->addAction(set_onboard_map_);
 	main_Toolbar_->addAction(set_onboard_map_);
// 
// 	main_Toolbar_->addSeparator();
// 
// 	file_menu_->addAction(open_project_);
// 	main_Toolbar_->addAction(open_project_);
// 
// 	file_menu_->addAction(save_project_);
// 	main_Toolbar_->addAction(save_project_);
	

	main_menuBar_->addMenu(file_menu_);

	main_Toolbar_->addSeparator();
}
void action_collection::sel_location()
{
	load_menu(MENU_ACT_GP_LOC,location_menu_);

	main_menuBar_->addMenu(location_menu_);

	main_Toolbar_->addSeparator();
}
void action_collection::sel_log_bag()
{
#if 0
 	log_bag_menu_->addAction(log_bag_begin_);
 	main_Toolbar_->addAction(log_bag_begin_);
 
 	log_bag_menu_->addAction(log_bag_end_);
 	main_Toolbar_->addAction(log_bag_end_);

	main_Toolbar_->addSeparator();
 	log_bag_menu_->addAction(log_bag_play_);
 	main_Toolbar_->addAction(log_bag_play_);
 
 	log_bag_menu_->addAction(log_bag_play_stop_);
 	main_Toolbar_->addAction(log_bag_play_stop_);
 
 	log_bag_menu_->addAction(log_bag_continue_);
 	main_Toolbar_->addAction(log_bag_continue_);

	main_Toolbar_->addSeparator();

	

	log_bag_menu_->addAction(log_bag_play_back);
	main_Toolbar_->addAction(log_bag_play_back);

	log_bag_menu_->addAction(log_bag_ex_play_);
	main_Toolbar_->addAction(log_bag_ex_play_);

	log_bag_menu_->addAction(log_bag_dynamic_key_);
	main_Toolbar_->addAction(log_bag_dynamic_key_);

	log_bag_menu_->addAction(log_bag_suro_debug_);
	main_Toolbar_->addAction(log_bag_suro_debug_);

	log_bag_menu_->addAction(log_bag_clear_);
	main_Toolbar_->addAction(log_bag_clear_);
#endif
	load_menu(MENU_ACT_GP_BAG,log_bag_menu_);

	main_menuBar_->addMenu(log_bag_menu_);

	main_Toolbar_->addSeparator();
}

void action_collection::sel_reflector()
{
	

//	reflector_menu_->addAction(log_bag_clear_);
//	main_Toolbar_->addAction(log_bag_clear_);

	load_menu(MENU_ACT_GP_REF,reflector_menu_);
	main_Toolbar_->addSeparator();
	load_menu(MENU_ACT_GP_REFBAG,reflector_menu_);

	main_menuBar_->addMenu(reflector_menu_);

	main_Toolbar_->addSeparator();
}

void action_collection::sel_move()
{
	load_menu(MENU_ACT_GP_MOVE,move_menu_);

	main_menuBar_->addMenu(move_menu_);

	main_Toolbar_->addSeparator();
}
void action_collection::sel_project()
{
	
	load_menu(MENU_ACT_PRO_FILE,project_menu_);
	main_Toolbar_->addSeparator();
	load_menu(MENU_ACT_PRO_TOPOL,project_menu_);
	main_Toolbar_->addSeparator();
	load_menu(MENU_ACT_PRO_TOOLS,project_menu_);
// 	main_Toolbar_->addSeparator();
// 	load_menu(MENU_ACT_PRO_TOPOL,project_menu_);
	main_Toolbar_->addSeparator();
	load_menu(MENU_ACT_PRO_ROLE,project_menu_);


	main_menuBar_->addMenu(project_menu_);

	main_Toolbar_->addSeparator();
}
void action_collection::sel_calib()
{
	calib_menu_->addAction(laser_cross_);
	main_Toolbar_->addAction(laser_cross_);

	main_menuBar_->addMenu(calib_menu_);

	main_Toolbar_->addSeparator();
}
void action_collection::sel_loop_closure()
{
	loop_closure_menu_->addAction(load_refscan_);
	main_Toolbar_->addAction(load_refscan_);

	loop_closure_menu_->addAction(mathc_one_);
	main_Toolbar_->addAction(mathc_one_);

	main_menuBar_->addMenu(loop_closure_menu_);

	main_Toolbar_->addSeparator();
}

void action_collection::sel_show_log()
{
	show_log_menu_->addAction(show_log_);
	main_Toolbar_->addAction(show_log_);

	show_log_menu_->addAction(clear_log_);
	main_Toolbar_->addAction(clear_log_);

	show_log_menu_->addAction(set_priority_);
	main_Toolbar_->addAction(set_priority_);

	show_log_menu_->addAction(set_para_);
	main_Toolbar_->addAction(set_para_);

	main_menuBar_->addMenu(show_log_menu_);

	main_Toolbar_->addSeparator();
}
void action_collection::sel_init(){

	init_menu_->addAction(para_init_);
	main_Toolbar_->addAction(para_init_);

// 	show_log_menu_->addAction(auto_init_);
// 	main_Toolbar_->addAction(auto_init_);

	main_menuBar_->addMenu(init_menu_);

	main_Toolbar_->addSeparator();
}

void action_collection::sel_tools()
{

	load_menu(MENU_ACT_GP_TOOLS,tools_menu_);

	main_menuBar_->addMenu(tools_menu_);

	main_Toolbar_->addSeparator();
}

void action_collection::clear_all_menu()
{
	map_menu_->removeAction(arm_mapping_);
	map_menu_->removeAction(begin_mapping_);
	map_menu_->removeAction(end_mapping_);
	map_menu_->removeAction(begin_bag_mapping_);
	map_menu_->removeAction(end_bag_mapping_);
	map_menu_->removeAction(show_mapping_);
	map_menu_->removeAction(save_mapping_);
	map_menu_->removeAction(log_bag_gmapping_);
	map_menu_->removeAction(log_bag_upload_);
	

	file_menu_->removeAction(open_map_);
	file_menu_->removeAction(upload_map_);
	file_menu_->removeAction(download_map_);
	file_menu_->removeAction(download_map_file_);
	file_menu_->removeAction(save_map_);
	file_menu_->removeAction(save_onboard_map_);
	file_menu_->removeAction(set_onboard_map_);


	location_menu_->removeAction(show_laser_);
	location_menu_->removeAction(show_particles_);
	location_menu_->removeAction(locate_);
	location_menu_->removeAction(auto_locate_);

	reflector_menu_->removeAction(open_reflector_);
	reflector_menu_->removeAction(save_reflector_);
	reflector_menu_->removeAction(upload_reflector_);
	reflector_menu_->removeAction(download_reflector_);
	reflector_menu_->removeAction(show_ex_reflector_);
	reflector_menu_->removeAction(add_reflector_);
	reflector_menu_->removeAction(del_item_);
	reflector_menu_->removeAction(log_bag_ex_begin_);
	reflector_menu_->removeAction(log_bag_ex_end_);
	reflector_menu_->removeAction(reflector_mapping_);
	reflector_menu_->removeAction(reflector_gmapping_);
	reflector_menu_->removeAction(reflector_modify_);
	reflector_menu_->removeAction(reflector_g2o_);

 	log_bag_menu_->removeAction(log_bag_begin_);
 	log_bag_menu_->removeAction(log_bag_end_);
	/////////////////
 	log_bag_menu_->removeAction(log_bag_play_);
 	log_bag_menu_->removeAction(log_bag_play_stop_);
 	log_bag_menu_->removeAction(log_bag_continue_);
	log_bag_menu_->removeAction(log_bag_play_back);
	log_bag_menu_->removeAction(log_bag_ex_play_);
	log_bag_menu_->removeAction(log_bag_dynamic_key_);
	log_bag_menu_->removeAction(log_bag_suro_debug_);

	log_bag_menu_->removeAction(log_bag_clear_);

	move_menu_->removeAction(move_ccw_);
	move_menu_->removeAction(move_cw_);
	move_menu_->removeAction(move_front_);
	move_menu_->removeAction(move_back_);
	move_menu_->removeAction(move_stop_);
	move_menu_->removeAction(move_left_);
	move_menu_->removeAction(move_right_);
	move_menu_->removeAction(move_ori_);

	project_menu_->removeAction(open_project_);
	project_menu_->removeAction(save_project_);
	project_menu_->removeAction(download_project_);
	project_menu_->removeAction(upload_project_);
	project_menu_->removeAction(set_onboard_project_);

	project_menu_->removeAction(select_);
	project_menu_->removeAction(align_);
	project_menu_->removeAction(range_);
	project_menu_->removeAction(rect_);

	project_menu_->removeAction(node_);
	project_menu_->removeAction(edge_);
	project_menu_->removeAction(rand_edge_);
	project_menu_->removeAction(del_node_edge_);
	

	project_menu_->removeAction(producer_);
	project_menu_->removeAction(consumer_);
	project_menu_->removeAction(processer_);
	project_menu_->removeAction(storage_);
	project_menu_->removeAction(charge_);
	
	project_menu_->removeAction(wander_);
	project_menu_->removeAction(auto_cover_);

	calib_menu_->removeAction(laser_cross_);
	loop_closure_menu_->removeAction(load_refscan_);
	loop_closure_menu_->removeAction(mathc_one_);

	show_log_menu_->removeAction(show_log_);
	show_log_menu_->removeAction(clear_log_);
	show_log_menu_->removeAction(set_priority_);
	show_log_menu_->removeAction(set_para_);

	init_menu_->removeAction(para_init_);
	init_menu_->removeAction(auto_init_);

	tools_menu_->removeAction(zoom_in_);
	tools_menu_->removeAction(zoom_out_);
	tools_menu_->removeAction(search_path_);
	tools_menu_->removeAction(dy_location_);
	tools_menu_->removeAction(scan_match_);
	tools_menu_->removeAction(add_qr_code_);
	tools_menu_->removeAction(exp_qr_code_);

	main_Toolbar_->clear();
	main_menuBar_->clear();
}

void action_collection::do_begin_mapping()
{
	
	Singleton_XML_Client::get_mutable_instance().do_begin_gmapping();
	std::cout<<"action:do_begin_mapping"<<std::endl;
	
}

void action_collection::do_end_mapping()
{
	
	Singleton_XML_Client::get_mutable_instance().do_stop_gmapping();
	std::cout<<"action:do_end_mapping"<<std::endl;
}

void action_collection::do_begin_bag_mapping()
{
	//1 begin mapping
	std::cout<<"action:bag play back"<<std::endl;
	Singleton_XML_Client::get_mutable_instance().do_begin_bag_mapping();
	
	//2 begin play back
	std::cout<<"action:do_begin_bag_mapping"<<std::endl;
	std::vector<std::string> v_bag_list;
	Singleton_XML_Client::get_mutable_instance().get_file_list(v_bag_list,".//pro_log//");

	file_list_dlg *pDlg = new file_list_dlg(); 
	pDlg->setModal(true); 
	pDlg->set_file_list(v_bag_list);
	pDlg->exec();
	std::string str_file = "";
	pDlg->get_sel_file(str_file);

	SDelete(pDlg);
	Singleton_XML_Client::get_mutable_instance().do_play_back_log(str_file);
	
	std::cout<<"action:do_begin_bag_mapping"<<std::endl;

	int ires = Singleton_XML_Client::get_mutable_instance().do_continue_play_log();
	std::cout<<"action:do_log_bag_play_continue over current index:"<<ires<<std::endl;
}
// 	std::cout<<"action:do_bag_mapping"<<std::endl;
// 	std::vector<std::string> v_bag_list;
// 	Singleton_XML_Client::get_mutable_instance().get_file_list(v_bag_list,".//map_log//");
// 	
// 	file_list_dlg *pDlg = new file_list_dlg(); 
// 	pDlg->setModal(true); 
// 	pDlg->set_file_list(v_bag_list);
// 	pDlg->exec();
// 	std::string str_file = "";
// 	pDlg->get_sel_file(str_file);
// 
// 	SDelete(pDlg);
// 
// 	Singleton_XML_Client::get_mutable_instance().do_bag_mapping(str_file);
void action_collection::do_end_bag_mapping()
{
	Singleton_XML_Client::get_mutable_instance().do_end_play_back_log();
	std::cout<<"action:do_log_bag_play_stop over"<<std::endl;

	Singleton_XML_Client::get_mutable_instance().do_end_bag_mapping();
	std::cout<<"action:do_end_bag_mapping"<<std::endl;
}
void action_collection::do_save_mapping()
{
	bool ok = true;
	std::stringstream ss;
	ss<<cTimerDiff::get_file_now()<<".maproto";
	QString qstr_map_name = QString::fromStdString(ss.str());
	qstr_map_name = QInputDialog::getText(main_win_, tr("Save mapping?"),
		tr("map name:"), QLineEdit::Normal,
		qstr_map_name, &ok);

	if (ok && !qstr_map_name.isEmpty()){
		Singleton_XML_Client::get_mutable_instance().do_save_gmapping(qstr_map_name.toStdString());
		std::cout<<"action:do_save_mapping name:"<<qstr_map_name.toStdString()<<std::endl;
	}else{
		std::cout<<"action: cancel do_save_mapping"<<std::endl;
	}
	
}
void action_collection::do_show_mapping()
{
	

	//Singleton_XML_Client::get_mutable_instance().do_show_gmapping();
	
	std::vector<int> v_data;
	Singleton_XML_Client::get_mutable_instance().get_map( v_data, SHARED_AMCL_MAP);
	item_->show_map_item(v_data);
	std::cout<<"action:do_show_mapping"<<std::endl;
}
void action_collection::do_open_map()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	std::string map_name = ".//map//";

	QString dir = QFileDialog::getOpenFileName(NULL,tr("Open Map"),
		map_name.c_str(),
		"maps (*.pgm *.maproto *.maprotoex)");
	std::string path = dir.toStdString();

	if (!item_->open_map(path)){
		QMessageBox::warning(0, tr("Error"), tr("do_open_map Err!"));
	}
	

	//main_win_->sel_map_dock();
	std::cout<<"action:do_open_map over"<<path<<std::endl;

	QApplication::restoreOverrideCursor();
}

void action_collection::th_bag_mapping(std::string bag_path,std::string path){

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	
	map_server g_ms;
	g_ms.init();
	g_ms.bind_show_bag(boost::bind(&item_collection::add_bag_item,item_,_1));
	g_ms.begin_bag_gmapping();
	g_ms.do_bag_mapping(bag_path);
	g_ms.stop_bag_gmapping();
	

	g_ms.save_gmapping_map(path);
	SLEEP(1000);
	g_ms.wait_save_map_over();

	QApplication::restoreOverrideCursor();

// 	QMessageBox *tips = new QMessageBox(QMessageBox::NoIcon,"bag_mapping_on_pc","Successful",QMessageBox::Ok | QMessageBox::Default,0);
// 	tips->exec();
// 	std::cout<<"------------do_bag_mapping_onpc()-----------"<<std::endl;
}
void action_collection::do_bag_mapping_onpc(){
	
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	std::string str_bag_name = ".//pro_log//";

	QString dir = QFileDialog::getOpenFileName(NULL,tr("Proto Bag On pc!"),
		str_bag_name.c_str(),
		"bag (*.proto)");
	std::string path = dir.toStdString();
	//path = cComm::Get_FileName(path) + ".proto";
	
	if (cComm::FileExist(path))
	{
		//std::string str_map_name = cComm::Get_FileName(path);
		std::string str_map_name = cComm::Get_FileName(path);

#if 0
		QMessageBox *tips = new QMessageBox(QMessageBox::Question,tr("map type")," Yes>> save '.maproto' map No>> save '.pgm' map",QMessageBox::Yes | QMessageBox::No,0);
		if (tips->exec() == QMessageBox::Yes){
			str_map_name = ".//map//"+ str_map_name + ".maproto";
		}else{
			str_map_name = ".//map//"+ str_map_name + ".pgm";
		}
#endif
		str_map_name = ".//map//"+ str_map_name + ".pgm";
		
		item_->clear_bag_item();

		boost::thread th(boost::bind(&action_collection::th_bag_mapping,this,path,str_map_name));
	}else{
		QMessageBox::warning(0, tr("Error"), tr("File path is not exist!"));
	}
	
	
// 	QMessageBox msg;
// 	msg.setWindowTitle(tr("bag_mapping_on_pc"));
// 	msg.setText(tr("open new map file yes or not?"));
// 	//msg.setStyleSheet("color:rgb(220, 0, 0);font: 14pt");
// 	msg.setIcon(QMessageBox::Information);
// 	msg.addButton(tr("yes"),QMessageBox::ActionRole);
// 	msg.addButton(tr("no"),QMessageBox::ActionRole);
// 	if(msg.exec() == 0){
// 		do_open_map();
// 	}
	QApplication::restoreOverrideCursor();

	QMessageBox::information(0, tr("Over"), tr("Action Done!"));
}

void action_collection::do_upload_map()
{
	
#if 0
	std::vector<std::string> v_map_list;
	Singleton_XML_Client::get_mutable_instance().get_file_list(v_map_list,".//map//");

	file_list_dlg *pDlg = new file_list_dlg(); 
	pDlg->setModal(true); 
	pDlg->set_map_list(v_map_list);
	pDlg->exec();
	std::string str_file = "";
	pDlg->get_sel_file(str_file);

	SDelete(pDlg);
#endif
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	//if(Singleton_XML_Client::get_mutable_instance().do_load_map(str_file)){

		std::vector<int> v_data;
		Singleton_XML_Client::get_mutable_instance().get_map( v_data, SHARED_AMCL_MAP);
		item_->show_map_item(v_data);
#if 0
		std::cout<<"action:do_load_map ok:"<<str_file<<std::endl;

		///////////////////syn upload landmark map////////////////
		str_file = ".//map//" + cComm::Get_FileName(str_file) + ".lm";
		//---------set upload file name
		bool ok = true;
		QString qstr_log_name = QString::fromStdString(str_file);
		qstr_log_name = QInputDialog::getText(main_win_, tr("Save upload file ?"),
			tr("landmark file:"), QLineEdit::Normal,
			qstr_log_name, &ok);


		if (ok && !qstr_log_name.isEmpty()){

			QMessageBox *tips = 0;
			if (!Singleton_XML_Client::get_mutable_instance().get_remote_file(str_file ,qstr_log_name.toStdString()) )
			{
				tips = new QMessageBox(QMessageBox::Warning,tr("landmark_upload"),tr("landmark_upload Err!"),QMessageBox::Ok ,0);
				tips->exec();
				SDelete(tips);
			}else{
				
			}
			

		}
#endif

// 	}else{
// 		std::cout<<"action:do_load_map err:"<<str_file<<std::endl;
// 	}
	
	QApplication::restoreOverrideCursor();

	QMessageBox::information(0, tr("Over"), tr("Action Done!"));

}

void action_collection::do_upload_map_separate()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	//if(Singleton_XML_Client::get_mutable_instance().do_load_map(str_file)){

	std::vector<int> v_data;
	Singleton_XML_Client::get_mutable_instance().get_map_separate( v_data, SHARED_AMCL_MAP);
	item_->show_map_item(v_data);

#if 0
	std::cout<<"action:do_load_map ok:"<<str_file<<std::endl;

	///////////////////syn upload landmark map////////////////
	str_file = ".//map//" + cComm::Get_FileName(str_file) + ".lm";
	//---------set upload file name
	bool ok = true;
	QString qstr_log_name = QString::fromStdString(str_file);
	qstr_log_name = QInputDialog::getText(main_win_, tr("Save upload file ?"),
		tr("landmark file:"), QLineEdit::Normal,
		qstr_log_name, &ok);


	if (ok && !qstr_log_name.isEmpty()){

		QMessageBox *tips = 0;
		if (!Singleton_XML_Client::get_mutable_instance().get_remote_file(str_file ,qstr_log_name.toStdString()) )
		{
			tips = new QMessageBox(QMessageBox::Warning,tr("landmark_upload"),tr("landmark_upload Err!"),QMessageBox::Ok ,0);
			tips->exec();
			SDelete(tips);
		}else{

		}


	}
#endif


	QApplication::restoreOverrideCursor();

	QMessageBox::information(0, tr("Over"), tr("Action Done!"));
}

void action_collection::do_download_map()
{	
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	std::vector<int> v_data;
	
	item_->download_map(v_data);

	Singleton_XML_Client::get_mutable_instance().set_map(v_data);

	std::cout<<"action:do_download_map over:"<<std::endl;

	QApplication::restoreOverrideCursor();
}
void action_collection::do_download_map_file()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	std::string map_name = ".//map//";

	QString dir = QFileDialog::getOpenFileName(NULL,tr("Open Map"),
		map_name.c_str(),
		"maps (*.pgm *.yaml *.maproto)");
	std::string path = dir.toStdString();
	
	std::string str_map_path = ".//map//";
	Config::getConfig("map_path",str_map_path);

	std::string str_arm_file = str_map_path + cComm::Get_FileName(path) + "." + cComm::Get_FileType(path);
	Singleton_XML_Client::get_mutable_instance().do_download_file(path,str_arm_file);

	if (cComm::Get_FileType(path) == "pgm"){
		str_arm_file = str_map_path + cComm::Get_FileName(path) + ".yaml";
		path = cComm::Get_FilePath(path) + cComm::Get_FileName(path) + ".yaml";
		Singleton_XML_Client::get_mutable_instance().do_download_file(path,str_arm_file);
	}

	QApplication::restoreOverrideCursor();

	QMessageBox::information(0, tr("Over"), tr("Action Done!"));
}
void action_collection::do_save_onboard_map()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	QString qmap_name = QFileDialog::getOpenFileName(NULL,tr("Save map"),
		".//map//kps.pgm",
		"Images(*.pgm)");
	if ( qmap_name.length() < 1)
	{
		QMessageBox::warning(0, tr("Error"), tr("Please enter map name!! exp: kps.pgm"));
		return;
	}
	std::string map_name = qmap_name.toStdString();
	Singleton_XML_Client::get_mutable_instance().do_save_onboard_map(map_name);

	std::cout<<"action:do_save_onboard_map over:"<<map_name<<std::endl;

	QApplication::restoreOverrideCursor();
}

void action_collection::do_save_map(){

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));


	std::stringstream ss;
	ss<<"..//map//"<<cTimerDiff::get_file_now()<<".pgm";
	QString qstr_map_name = QString::fromStdString(ss.str());

	QString qmap_name = QFileDialog::getSaveFileName(NULL,tr("Save map"),
		qstr_map_name,
		"Images(*.pgm)");
	if ( qmap_name.length() < 1)
	{
		QMessageBox::warning(0, tr("Error"), tr("Please enter map name!! exp: kps.pgm"));
		return;
	}
	std::string map_name = qmap_name.toStdString();
	item_->save_map(map_name);

	std::cout<<"action:do_save_map over:"<<map_name<<std::endl;

	QApplication::restoreOverrideCursor();

	QMessageBox::information(0, tr("Over"), tr("Action Done!"));

}

void action_collection::do_set_onboard_map()
{

	

	std::vector<std::string> v_map_list;
	Singleton_XML_Client::get_mutable_instance().get_file_list(v_map_list,".//map//");

	file_list_dlg *pDlg = new file_list_dlg(); 
	pDlg->setModal(true); 
	pDlg->set_map_list(v_map_list);
	pDlg->exec();
	std::string str_file = "";
	pDlg->get_sel_file(str_file);

	SDelete(pDlg);

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	if(Singleton_XML_Client::get_mutable_instance().do_set_onboard_map(str_file)){

		std::cout<<"action:do_load_map ok:"<<str_file<<std::endl;
	}else{
		std::cout<<"action:do_load_map err:"<<str_file<<std::endl;
	}

	QApplication::restoreOverrideCursor();

	QMessageBox::information(0, tr("Over"), tr("Action Done!"));
}



void action_collection::do_show_log(){
	main_win_->set_show_log();
	std::cout<<"action:do_show_log over:"<<std::endl;
}

void action_collection::do_clear_log()
{
	main_win_->clear_show_log();
	std::cout<<"action:do_clear_log over:"<<std::endl;
}



void action_collection::show_map_date( const std::vector<int> &v_data )
{
	item_->show_map_item(v_data);
}
void action_collection::do_show_laser()
{
	item_->show_laser();
	std::cout<<"action:do_show_laser :"<<std::endl;
}
void action_collection::do_show_particles()
{
	item_->show_particles();
	std::cout<<"action:do_show_particles :"<<std::endl;
}

void action_collection::do_locate()
{
	b_locate_ = set_CursorShape(qt_eve::mouse_event::MU_TYPE::MU_LOCATE);
	if(b_locate_){
		set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_LOCATE);
		QApplication::setOverrideCursor(QCursor(Qt::CrossCursor));
	}else{
		set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_NONE);
		QApplication::restoreOverrideCursor();
	}

}

void action_collection::do_auto_locate()
{
	b_auto_locate_ = set_CursorShape(qt_eve::mouse_event::MU_TYPE::MU_AUTO_LOC);

	if(!b_auto_locate_){
		

		boost::thread th(boost::bind(&action_collection::th_loop_closure,this));
		
	}else{

		Singleton_XML_Client::get_mutable_instance().do_set_loop_clusure_cmd("stop");

		
	}

}
void action_collection::th_loop_closure(){
	
	QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));
	Singleton_XML_Client::get_mutable_instance().do_set_loop_clusure_cmd("locate");

	SLoopCLosurePos cpos;

	while(b_auto_locate_){

		if( Singleton_XML_Client::get_mutable_instance().get_loop_closure_pos(cpos) ){
			break;

		}
		SLEEP(200);
	}

	//auto_locate_ == true means get cpos from robot
	//auto_locate_ == false  force stop
	if (b_auto_locate_ ){
		SPos est_pos;
		est_pos.x_ = cpos.pos_.x_;
		est_pos.y_ = cpos.pos_.y_;
		est_pos.th_ = cpos.pos_.th_;
		if ( cpos.confidence_  > 0 ){
			if(!Singleton_XML_Client::get_mutable_instance().set_est_pos(est_pos)){
				//QMessageBox::warning(0, tr("Error"), "Please set correct robot pos");
			}
		}else{
			std::cout<<"confidence err:"<<cpos.confidence_<<std::endl;
		}
		
		
	}
	b_auto_locate_ = false;
	QApplication::restoreOverrideCursor();
}
void action_collection::do_show_ex_reflector()
{
	item_->show_ex_reflector();
}

void action_collection::do_add_reflector()
{
	if(!b_add_reflector_){
		set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_ADD_REFECTOR);
		QApplication::setOverrideCursor(QCursor(Qt::CrossCursor));
	}else{
		set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_NONE);
		QApplication::restoreOverrideCursor();
	}
	b_add_reflector_ = !b_add_reflector_;
}
void action_collection::do_del_ref(){

	
	foreach (QGraphicsItem *item, main_win_->get_scene()->selectedItems()) {
		if (  QtType::ITEM_REFLECTOR == item->type() )
		{

			reflector_item* ref =  qgraphicsitem_cast<reflector_item *>(item);
			//Singleton_Project_Manage::get_mutable_instance().remove_reflector(Singleton_Project_Manage::get_mutable_instance().get_current_project_nm(),ref->get_id());
			PRO_MANAGE.remove_reflector(CURRENT_PRO,ref->get_id());
			main_win_->get_scene()->del_item(ref);

		}else if( QtType::ITEM_LAB == item->type() ){

			lab_item* lab =  qgraphicsitem_cast<lab_item *>(item);
			PRO_MANAGE.remove_lab(CURRENT_PRO,lab->get_id());
			main_win_->get_scene()->del_item(lab);
			//Singleton_Project_Manage::get_mutable_instance().remove_lab(Singleton_Project_Manage::get_mutable_instance().get_current_project_nm(),lab->get_id());

			
		}
	}
	std::cout<<"del reflector over!!"<<std::endl;
}

void action_collection::do_log_ex_begin()
{
	bool ok = true;
	std::stringstream ss;
	ss<<cTimerDiff::get_file_now()<<".protoex";
	QString qstr_log_name = QString::fromStdString(ss.str());
	qstr_log_name = QInputDialog::getText(main_win_, tr("Save proto ex?"),
		tr("Log file:"), QLineEdit::Normal,
		qstr_log_name, &ok);

	if (ok && !qstr_log_name.isEmpty()){

		Singleton_XML_Client::get_mutable_instance().do_begin_log_ex(qstr_log_name.toStdString());
		std::cout<<"action:do_log_ex_begin over:"<<qstr_log_name.toStdString()<<std::endl;
	}else{
		std::cout<<"action:do_log_ex_begin cancel"<<std::endl;
	}




}

void action_collection::do_log_ex_end()
{
	Singleton_XML_Client::get_mutable_instance().do_end_log_ex();
	QMessageBox *tips = new QMessageBox(QMessageBox::NoIcon,tr("do_log_ex_end"),tr("Successful"),QMessageBox::Ok | QMessageBox::Default,0);
	tips->exec();
	SDelete(tips);
	std::cout<<"action:do_log_ex_end over:"<<std::endl;

}

void action_collection::do_ref_mapping()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	std::string str_bag_name = ".//pro_log//";


	QString dir = QFileDialog::getOpenFileName(NULL,tr("protoex On pc!"),
		str_bag_name.c_str(),
		"bagex (*.protoex)");
	std::string path = dir.toStdString();
	path = cComm::Get_FileName(path) + ".protoex";

	if (cComm::FileExist(str_bag_name + path))
	{
		boost::thread th(boost::bind(&action_collection::th_ref_mapping,this,str_bag_name + path));
	}else{
		QMessageBox::warning(0, tr("Error"), tr("File path is not exist!"));
	}

	QApplication::restoreOverrideCursor();

}

void action_collection::th_ref_mapping(std::string path)
{

	item_->clear_bag_item();

	reflected_pillar_mapping ref_mapping;
	ref_mapping.init();
	ref_mapping.bind_show_bag(boost::bind(&item_collection::add_bag_ex_item,item_,_1));
	ref_mapping.mapping(path);

	
	//std::vector<SVec> reflector_list;
	//ref_mapping.get_mapping_reflector(reflector_list);
	//item_->show_reflector_list(reflector_list,true);
}

void action_collection::do_ref_modify()
{
	item_->clear_bag_item();
	item_->clear_mapping_reflector();

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	std::string str_bag_name = ".//pro_log//";


	QString dir = QFileDialog::getOpenFileName(NULL,tr("protoex On pc!"),
		str_bag_name.c_str(),
		"gmapex (*.gmapex)");
	std::string path = dir.toStdString();
	path = cComm::Get_FileName(path) + ".gmapex";

	str_path_gmap_ = str_bag_name + path;

	if (cComm::FileExist(str_bag_name + path))
	{
		boost::thread th(boost::bind(&action_collection::th_ref_modify,this,str_bag_name + path));

		

	}else{
		QMessageBox::warning(0, tr("Error"), tr("File path is not exist!"));
		QMessageBox::warning(0, tr("Error"), tr("Do 1-RefGMap first?"));
	}

	QApplication::restoreOverrideCursor();

	

}

void action_collection::th_ref_modify(std::string path)
{

	reflected_pillar_mapping* p_ref = (reflected_pillar_mapping*)ref_mapping_;

	if (!ref_mapping_){
		p_ref = new reflected_pillar_mapping();
		ref_mapping_ = (void*)p_ref;
	}
	

	p_ref->init();
 	p_ref->bind_show_bag(boost::bind(&item_collection::add_bag_ex_item,item_,_1));
	p_ref->bind_map_reflector(boost::bind(&item_collection::add_mapping_reflector,item_,_1,_2,_3,_4));
 	p_ref->modify_bag_ex(path);
}

void action_collection::set_mouse_event( const qt_eve::mouse_event::MU_TYPE &type )
{
	if (main_win_)
	{
		main_win_->get_scene()->set_mouse_event(type);
	}
	
}

void action_collection::create_log_bag_action()
{
	log_bag_menu_ = main_menuBar_->addMenu(tr("Log&Bag"));

	log_bag_begin_ = new QAction(QIcon("images/import.png"),tr("LogBa&gBegin"), main_win_);
	log_bag_begin_->setShortcut(tr("Ctrl+G"));
	log_bag_begin_->setStatusTip(tr("LogBagBegin"));
	connect(log_bag_begin_, SIGNAL(triggered()),this, SLOT(do_log_bag_begin()));
	act_permission_.set_menu(MENU_ACT_GP_GMAPPING,MENU_ACT_GP_LOG_BAGIN,log_bag_begin_);

	log_bag_end_ = new QAction(QIcon("images/import.png"),tr("LogBag&End"), main_win_);
	log_bag_end_->setShortcut(tr("Ctrl+E"));
	log_bag_end_->setStatusTip(tr("LogBagEnd"));
	connect(log_bag_end_, SIGNAL(triggered()),this, SLOT(do_log_bag_end()));
	act_permission_.set_menu(MENU_ACT_GP_GMAPPING,MENU_ACT_GP_LOG_END,log_bag_end_);

	log_bag_play_ = new QAction(QIcon("images/import.png"),tr("LogBag&Play"), main_win_);
	log_bag_play_->setShortcut(tr("Ctrl+P"));
	log_bag_play_->setStatusTip(tr("LogBagPlay"));
	connect(log_bag_play_, SIGNAL(triggered()),this, SLOT(do_log_bag_play()));

	log_bag_play_stop_ = new QAction(QIcon("images/import.png"),tr("LogBag&PlayStop"), main_win_);
	log_bag_play_stop_->setShortcut(tr("Ctrl+T"));
	log_bag_play_stop_->setStatusTip(tr("LogBagPlayStop"));
	connect(log_bag_play_stop_, SIGNAL(triggered()),this, SLOT(do_log_bag_play_stop()));

	log_bag_continue_ = new QAction(QIcon("images/import.png"),tr("LogBag&PlayContinue"), main_win_);
	log_bag_continue_->setShortcut(tr("Ctrl+C"));
	log_bag_continue_->setStatusTip(tr("LogBagPlayContinue"));
	connect(log_bag_continue_, SIGNAL(triggered()),this, SLOT(do_log_bag_play_continue()));

	log_bag_upload_ = new QAction(QIcon("images/import.png"),tr("LogBag&UpLoad"), main_win_);
	log_bag_upload_->setShortcut(tr("Ctrl+G"));
	log_bag_upload_->setStatusTip(tr("LogBagUpLoad"));
	connect(log_bag_upload_, SIGNAL(triggered()),this, SLOT(do_log_upload()));
	act_permission_.set_menu(MENU_ACT_GP_GMAPPING,MENU_ACT_GP_UPLOAD_BAG,log_bag_upload_);
	act_permission_.set_menu(MENU_ACT_GP_REFBAG,MENU_ACT_REFBAG_LOGEX_UPLOAD,log_bag_upload_);
	act_permission_.set_menu(MENU_ACT_GP_BAG,MENU_ACT_BAG_UPLOAD,log_bag_upload_);

	log_bag_gmapping_ = new QAction(QIcon("images/import.png"),tr("LogBag&Gmapping"), main_win_);
	log_bag_gmapping_->setShortcut(tr("Ctrl+G"));
	log_bag_gmapping_->setStatusTip(tr("LogBagGmapping"));
	connect(log_bag_gmapping_, SIGNAL(triggered()),this, SLOT(do_bag_mapping_onpc()));
	act_permission_.set_menu(MENU_ACT_GP_GMAPPING,MENU_ACT_GP_BAG_GMAPPING,log_bag_gmapping_);

	log_bag_suro_debug_=  new QAction(QIcon("images/import.png"),tr("LogBag&SuroDebug"), main_win_);
	log_bag_suro_debug_->setShortcut(tr("F3"));
	log_bag_suro_debug_->setStatusTip(tr("LogBagSuroDebug"));
	//connect(log_bag_suro_debug_, SIGNAL(triggered()),this, SLOT(do_log_bag_flirt_debug()));
	connect(log_bag_suro_debug_, SIGNAL(triggered()),this, SLOT(do_log_bag_suro_debug()));

	log_bag_play_back=  new QAction(QIcon("images/import.png"),tr("LogBag&PlayPc"), main_win_);
	log_bag_play_back->setShortcut(tr("F1"));
	log_bag_play_back->setStatusTip(tr("LogBagPlay"));
	connect(log_bag_play_back, SIGNAL(triggered()),this, SLOT(do_log_bag_play_onpc()));
	act_permission_.set_menu(MENU_ACT_GP_BAG,MENU_ACT_BAG_PLABBACK,log_bag_play_back);

	log_bag_ex_play_ = new QAction(QIcon("images/import.png"),tr("LogBagEx&Play"), main_win_);
	log_bag_ex_play_->setShortcut(tr("F2"));
	log_bag_ex_play_->setStatusTip(tr("LogBagExPlay"));
	connect(log_bag_ex_play_, SIGNAL(triggered()),this, SLOT(do_log_ex_play_onpc()));
	act_permission_.set_menu(MENU_ACT_GP_BAG,MENU_ACT_BAG_PLABBACK_EX,log_bag_ex_play_);

	log_bag_dynamic_key_=  new QAction(QIcon("images/import.png"),tr("LogDynamicKeyFrame"), main_win_);
	log_bag_dynamic_key_->setShortcut(tr("F3"));
	log_bag_dynamic_key_->setStatusTip(tr("LogDynamicKeyFrame"));
	connect(log_bag_dynamic_key_, SIGNAL(triggered()),this, SLOT(do_log_keyframe_onpc()));
	act_permission_.set_menu(MENU_ACT_GP_BAG,MENU_ACT_BAG_DYNAMIC_FRAME,log_bag_dynamic_key_);

	log_bag_clear_ = new QAction(QIcon("images/import.png"),tr("ClearBagShow"), main_win_);
	log_bag_clear_->setShortcut(tr("F12"));
	log_bag_clear_->setStatusTip(tr("ClearBagShow"));
	connect(log_bag_clear_, SIGNAL(triggered()),this, SLOT(do_clear_bag_show()));
	act_permission_.set_menu(MENU_ACT_GP_GMAPPING,MENU_ACT_GP_BAG_CLEARBG,log_bag_clear_);
	act_permission_.set_menu(MENU_ACT_GP_REFBAG,MENU_ACT_REFBAG_LOGEX_CLEARBG,log_bag_clear_);
	act_permission_.set_menu(MENU_ACT_GP_BAG,MENU_ACT_BAG_CLEARBG,log_bag_clear_);
}

void action_collection::do_log_bag_begin()
{
	bool ok = true;
	std::stringstream ss;
	ss<<cTimerDiff::get_file_now()<<".proto";
	QString qstr_log_name = QString::fromStdString(ss.str());
	qstr_log_name = QInputDialog::getText(main_win_, tr("Save proto log?"),
		tr("Log file:"), QLineEdit::Normal,
		qstr_log_name, &ok);

	if (ok && !qstr_log_name.isEmpty()){

		Singleton_XML_Client::get_mutable_instance().do_begin_log(qstr_log_name.toStdString());
		std::cout<<"action:do_log_bag_begin over:"<<qstr_log_name.toStdString()<<std::endl;
	}else{
		std::cout<<"action:do_log_bag_begin cancel"<<std::endl;
	}

	

	
}

void action_collection::do_log_bag_end()
{
	Singleton_XML_Client::get_mutable_instance().do_end_log();
	QMessageBox *tips = new QMessageBox(QMessageBox::NoIcon,tr("do_log_bag_end"),tr("Successful"),QMessageBox::Ok | QMessageBox::Default,0);
	tips->exec();

	std::cout<<"action:do_log_bag_end over:"<<std::endl;

}

void action_collection::do_log_bag_play()
{
	std::cout<<"action:do_log_bag_play"<<std::endl;
	std::vector<std::string> v_bag_list;
	Singleton_XML_Client::get_mutable_instance().get_file_list(v_bag_list,".//pro_log//");

	file_list_dlg *pDlg = new file_list_dlg(); 
	pDlg->setModal(true); 
	pDlg->set_file_list(v_bag_list);
	pDlg->exec();
	std::string str_file = "";
	pDlg->get_sel_file(str_file);

	SDelete(pDlg);

	Singleton_XML_Client::get_mutable_instance().do_play_back_log(str_file);

	std::cout<<"action:do_log_bag_play over:"<<std::endl;
}

void action_collection::do_log_bag_play_stop()
{
	Singleton_XML_Client::get_mutable_instance().do_end_play_back_log();
	std::cout<<"action:do_log_bag_play_stop over"<<std::endl;
}
void action_collection::do_log_bag_play_continue()
{
	int ires = Singleton_XML_Client::get_mutable_instance().do_continue_play_log();
	std::cout<<"action:do_log_bag_play_continue over current index:"<<ires<<std::endl;
}

void action_collection::do_log_upload()
{
	std::cout<<"action:do_log_bag_play"<<std::endl;
	std::vector<std::string> v_bag_list;
	Singleton_XML_Client::get_mutable_instance().get_file_list(v_bag_list,".//pro_log//");

	file_list_dlg *pDlg = new file_list_dlg(); 
	pDlg->setModal(true); 
	pDlg->set_file_list(v_bag_list);
	pDlg->exec();
	std::string str_file = "";
	pDlg->get_sel_file(str_file);

	SDelete(pDlg);

	str_file = ".//pro_log//" + str_file;
	//---------set upload file name
	bool ok = true;
	QString qstr_log_name = QString::fromStdString(str_file);
	qstr_log_name = QInputDialog::getText(main_win_, tr("Save upload file ?"),
		tr("Log file:"), QLineEdit::Normal,
		qstr_log_name, &ok);

	
	if (ok && !qstr_log_name.isEmpty()){

		QMessageBox *tips = 0;
		if (!Singleton_XML_Client::get_mutable_instance().get_remote_file(str_file ,qstr_log_name.toStdString()) )
		{
			tips = new QMessageBox(QMessageBox::Warning,"Bag_upload","Bag_upload Err!",QMessageBox::Ok ,0);

		}else{
			tips = new QMessageBox(QMessageBox::NoIcon,"Bag_upload","Bag_upload Over!",QMessageBox::Ok ,0);
		}
		tips->exec();
		SDelete(tips);
	}
	
}

void action_collection::do_log_bag_play_onpc()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	SPUB_BAG pbag;

	if ( bag_path_.empty() )
	{
		std::string str_bag_name = ".//pro_log//";

		QString dir = QFileDialog::getOpenFileName(NULL,tr("Proto Bag On pc!"),
			str_bag_name.c_str(),
			"bag (*.proto;*.maproto)");
		std::string path = dir.toStdString();
		//path = cComm::Get_FileName(path) + ".proto";
		if (cComm::Get_FileType(path) == "maproto"){
			b_laser_diff_ = false;
		}else{
			b_laser_diff_ = true;
		}
		bag_path_ =  path;

		if (cComm::FileExist(bag_path_))
		{
			
			play_back_bag_.open_file_normal(bag_path_);
			item_->clear_bag_item();
		}else{
			QMessageBox::warning(0, tr("Error"), tr("File path is not exist!"));
		}
	}else{
		if (play_back_bag_.get_one_normal(pbag))
		{
			if(!b_laser_diff_){
				pbag.laser_para_.laser_dx_ = 0;
				pbag.laser_para_.laser_dy_ = 0;
			}
			item_->add_bag_item(pbag);

		}else{
			QMessageBox::warning(0, tr("Error"), tr("File end!"));
			bag_path_ = "";
		}
	}


	QApplication::restoreOverrideCursor();

}


void action_collection::do_log_bag_suro_debug()
{
	//
	SBAG bag;
	SPUB_BAG pub_bag;
	memset(&pub_bag,0,sizeof(SPUB_BAG));
	pub_bag.laser_para_.laser_dx_ = 0.0;
	//pub_bag.laser_para_.laser_dx_ = 0.604;
	pub_bag.laser_para_.laser_dy_ = 0;
	std::string str_shape = "0.7,-0.38;0.7,0.38;-0.48,0.38;-0.48,-0.38;0.7,-0.38";
	memcpy(pub_bag.robot_shape_,str_shape.c_str(),str_shape.length());
	
	if (bag_path_.length() < 1)
	{
		//std::string file_name = "..//..//../debug_data//";
		std::string file_name = ".//map_log//";
		QString dir = QFileDialog::getOpenFileName(NULL,tr("Open Bag"),
			file_name.c_str(),
			"bags (*.bag;*.frame)");
		bag_path_ = dir.toStdString();
		
		item_->clear_bag_item();
	}
	//for (int i = 0 ; i < 150 ; ++i )
	{
		if( bag_.load_Bag(bag_path_,bag,false,true)){
			pub_bag.laser_para_.laser_range_max_ = bag.laser.range_max_;
			pub_bag.laser_para_.laser_range_min_ = bag.laser.range_min_;
			pub_bag.laser_para_.laser_resolution_ = bag.laser.resolution_;
			pub_bag.laser_para_.laser_start_angle_ = bag.laser.start_angle_;
			pub_bag.laser_para_.laser_dx_ = bag_.laser_dx_;
			pub_bag.laser_para_.laser_dy_ = bag_.laser_dy_;

			pub_bag.laser_ = bag.laser;
			pub_bag.odom_ = bag.odom;
			pub_bag.amcl_pos_ = bag.amcl_pos;

			//memset(pub_bag.laser_.seg_,255,sizeof(U8)*LASER_COUNT);
			//pub_bag.laser_.used_ = LASER_COUNT;

			item_->add_bag_item(pub_bag);
		}else{
			bag_path_ = "";
		}
	}
	

	


}
void action_collection::do_log_bag_flirt_debug()
{
	//
	SBAG bag;
	SPUB_BAG pub_bag;
	memset(&pub_bag,0,sizeof(SPUB_BAG));
	pub_bag.laser_para_.laser_dx_ = 0;
	pub_bag.laser_para_.laser_dy_ = 0;
	std::string str_shape = "0.7,-0.38;0.7,0.38;-0.48,0.38;-0.48,-0.38;0.7,-0.38";
	memcpy(pub_bag.robot_shape_,str_shape.c_str(),str_shape.length());


	static LogSensorStream* p_sensorReference = 0;
	static CarmenLogWriter* writer = 0;
	static CarmenLogReader* reader = 0;

	if (bag_path_.length() < 1)
	{
		std::string file_name = ".//data//";
		QString dir = QFileDialog::getOpenFileName(NULL,tr("Open log"),
			file_name.c_str(),
			"log (*.log)");
		bag_path_ = dir.toStdString();

		item_->clear_bag_item();

		SDelete(writer);
		SDelete(reader);
		SDelete(p_sensorReference);
	}

	
#if 1
	//static std::vector< std::vector<InterestPoint *> > m_pointsReference;
	//static std::vector< OrientedPoint2D > m_posesReference;
	static int index;
	if (!p_sensorReference)
	{
		
		writer = new CarmenLogWriter;
		reader = new CarmenLogReader;

		p_sensorReference = new LogSensorStream(reader, writer);

		p_sensorReference->load(bag_path_);


		p_sensorReference->seek(0,END);
		unsigned int end = p_sensorReference->tell();
		p_sensorReference->seek(0,BEGIN);


		//m_pointsReference.resize(end + 1);
		//m_posesReference.resize(end + 1);

		index = 0;

	}
	while ( !p_sensorReference->end() )
	{
		p_sensorReference->seek(500);
		const LaserReading* lreadReference = dynamic_cast<const LaserReading*>(p_sensorReference->next());
		if (lreadReference){
			//m_detector->detect(*lreadReference, m_pointsReference[i]);
			//m_posesReference[i] = lreadReference->getLaserPose();
			bag.laser.range_max_ = lreadReference->getMaxRange();
			bag.laser.range_min_ = 0.01;
			bag.laser.used_ = lreadReference->getRho().size();
			bag.laser.start_angle_ = lreadReference->getPhi()[0];
			bag.laser.resolution_ = lreadReference->getPhi()[1] - lreadReference->getPhi()[0];
			bag.laser.stamp_ = index++;

			for (int i = 0 ; i < bag.laser.used_ ; ++i)
			{
				bag.laser.data_[i] = lreadReference->getRho()[i];
				bag.laser.seg_[i] = 255;
			}
			OrientedPoint2D pos = lreadReference->getLaserPose();

			pub_bag.laser_para_.laser_range_max_ = bag.laser.range_max_;
			pub_bag.laser_para_.laser_range_min_ = bag.laser.range_min_;
			pub_bag.laser_para_.laser_resolution_ = bag.laser.resolution_;
			pub_bag.laser_para_.laser_start_angle_ = bag.laser.start_angle_;

			pub_bag.amcl_pos_.x_ = pos.x;
			pub_bag.amcl_pos_.y_ = pos.y;
			pub_bag.amcl_pos_.th_ = pos.theta;
			
			pub_bag.odom_.x_ = pos.x;
			pub_bag.odom_.y_ = pos.y;
			pub_bag.odom_.th_ = pos.theta;
			pub_bag.odom_.vx_ = 0;
			pub_bag.odom_.vy_ = 0;
			pub_bag.odom_.vw_ = 0;

			pub_bag.laser_ = bag.laser;

			//item_->add_bag_item(pub_bag);
			item_->show_bag_item(pub_bag);
	
		}else{
			bag_path_ = "";
		}
	}
	//else{
		bag_path_ = "";
	//}
#endif
// 	for (int i = 0 ; i < 10 ; ++i )
// 	{
// 		if( bag_.load_Bag(bag_path_,bag)){
// 			pub_bag.laser_para_.laser_range_max_ = bag.laser.range_max_;
// 			pub_bag.laser_para_.laser_range_min_ = bag.laser.range_min_;
// 			pub_bag.laser_para_.laser_resolution_ = bag.laser.resolution_;
// 			pub_bag.laser_para_.laser_start_angle_ = bag.laser.start_angle_;
// 
// 			pub_bag.laser_ = bag.laser;
// 			pub_bag.odom_ = bag.odom;
// 			pub_bag.amcl_pos_ = bag.amcl_pos;
// 
// 			memset(pub_bag.laser_.seg_,255,sizeof(U8)*LASER_COUNT);
// 			pub_bag.laser_.used_ = LASER_COUNT;
// 
// 			item_->add_bag_item(pub_bag);
// 		}else{
// 			bag_path_ = "";
// 		}
// 	}





}

void action_collection::create_reflector_action()
{
	reflector_menu_ = main_menuBar_->addMenu(tr("Reflector"));

	open_reflector_ = new QAction(QIcon("images/import.png"),tr("OpenReflector"), main_win_);
	open_reflector_->setShortcut(tr("Ctrl+o"));
	open_reflector_->setStatusTip(tr("OpenReflector"));
	connect(open_reflector_, SIGNAL(triggered()),this, SLOT(do_open_reflector()));
	act_permission_.set_menu(MENU_ACT_GP_REF,MENU_ACT_REFLECTOR_OPEN,open_reflector_);

	save_reflector_ = new QAction(QIcon("images/import.png"),tr("SaveReflector"), main_win_);
	save_reflector_->setShortcut(tr("Ctrl+o"));
	save_reflector_->setStatusTip(tr("SaveReflector"));
	connect(save_reflector_, SIGNAL(triggered()),this, SLOT(do_save_reflector()));
	act_permission_.set_menu(MENU_ACT_GP_REF,MENU_ACT_REFLECTOR_SAVE,save_reflector_);
	

	upload_reflector_ = new QAction(QIcon("images/import.png"),tr("upLoadReflector"), main_win_);
	upload_reflector_->setShortcut(tr("Ctrl+o"));
	upload_reflector_->setStatusTip(tr("upLoadReflector"));
	connect(upload_reflector_, SIGNAL(triggered()),this, SLOT(do_upload_reflector()));
	act_permission_.set_menu(MENU_ACT_GP_REF,MENU_ACT_REFLECTOR_UPLOAD,upload_reflector_);


	download_reflector_ = new QAction(QIcon("images/import.png"),tr("downLoadReflector"), main_win_);
	download_reflector_->setShortcut(tr("Ctrl+o"));
	download_reflector_->setStatusTip(tr("downLoadReflector"));
	connect(download_reflector_, SIGNAL(triggered()),this, SLOT(do_download_reflector()));
	act_permission_.set_menu(MENU_ACT_GP_REF,MENU_ACT_REFLECTOR_DOWNLOAD,download_reflector_);



	show_ex_reflector_ = new QAction(QIcon("images/import.png"),tr("Sh&owExReflector"), main_win_);
	show_ex_reflector_->setShortcut(tr("Ctrl+o"));
	show_ex_reflector_->setStatusTip(tr("ShowExReflector"));
	connect(show_ex_reflector_, SIGNAL(triggered()),this, SLOT(do_show_ex_reflector()));
	act_permission_.set_menu(MENU_ACT_GP_TOOLS,MENU_ACT_TOOLS_SHOW_EX_REF,show_ex_reflector_);


	add_reflector_ = new QAction(QIcon("images/import.png"),tr("&AddReflector"), main_win_);
	add_reflector_->setShortcut(tr("Ctrl+R"));
	add_reflector_->setStatusTip(tr("AddReflector"));
	connect(add_reflector_, SIGNAL(triggered()),this, SLOT(do_add_reflector()));
	act_permission_.set_menu(MENU_ACT_GP_REF,MENU_ACT_REFLECTOR_ADD,add_reflector_);


	del_item_ = new QAction(QIcon("images/delete.png"),tr("D&el"), main_win_);
	del_item_->setShortcut(QKeySequence::Delete);
	del_item_->setStatusTip(tr("DelRef"));
	connect(del_item_, SIGNAL(triggered()),this, SLOT(do_del_ref()));
	act_permission_.set_menu(MENU_ACT_GP_REF,MENU_ACT_REFLECTOR_DEL,del_item_);

	///////////////////////////////////
	//bag ex log
	log_bag_ex_begin_ = new QAction(QIcon("images/delete.png"),tr("LogExBegin"), main_win_);
	log_bag_ex_begin_->setShortcut(tr("LogExBegin"));
	log_bag_ex_begin_->setStatusTip(tr("LogExBegin"));
	connect(log_bag_ex_begin_, SIGNAL(triggered()),this, SLOT(do_log_ex_begin()));
	act_permission_.set_menu(MENU_ACT_GP_REFBAG,MENU_ACT_REFBAG_LOGEX_BEGIN,log_bag_ex_begin_);


	log_bag_ex_end_ = new QAction(QIcon("images/delete.png"),tr("LogExStop"), main_win_);
	log_bag_ex_end_->setShortcut(tr("LogExStop"));
	log_bag_ex_end_->setStatusTip(tr("LogExStop"));
	connect(log_bag_ex_end_, SIGNAL(triggered()),this, SLOT(do_log_ex_end()));
	act_permission_.set_menu(MENU_ACT_GP_REFBAG,MENU_ACT_REFBAG_LOGEX_STOP,log_bag_ex_end_);
	
	reflector_mapping_ = new QAction(QIcon("images/delete.png"),tr("RefMapping"), main_win_);
	reflector_mapping_->setShortcut(tr("RefMapping"));
	reflector_mapping_->setStatusTip(tr("RefMapping"));
	connect(reflector_mapping_, SIGNAL(triggered()),this, SLOT(do_ref_mapping()));
	act_permission_.set_menu(MENU_ACT_GP_REFBAG,MENU_ACT_REFBAG_LOGEX_MAPPING,reflector_mapping_);


	reflector_gmapping_ = new QAction(QIcon("images/delete.png"),tr("1-RefGMap"), main_win_);
	reflector_gmapping_->setShortcut(tr("RefGMap"));
	reflector_gmapping_->setStatusTip(tr("RefGMap"));
	connect(reflector_gmapping_, SIGNAL(triggered()),this, SLOT(do_ref_gmapping()));
	act_permission_.set_menu(MENU_ACT_GP_REFBAG,MENU_ACT_REFBAG_LOGEX_GMAP,reflector_gmapping_);


	reflector_modify_ = new QAction(QIcon("images/delete.png"),tr("2-Modify"), main_win_);
	reflector_modify_->setShortcut(tr("RefModify"));
	reflector_modify_->setStatusTip(tr("RefModify"));
	connect(reflector_modify_, SIGNAL(triggered()),this, SLOT(do_ref_modify()));
	act_permission_.set_menu(MENU_ACT_GP_REFBAG,MENU_ACT_REFBAG_LOGEX_MODIFY,reflector_modify_);


	reflector_g2o_ = new QAction(QIcon("images/delete.png"),tr("3-RefG2O"), main_win_);
	reflector_g2o_->setShortcut(tr("RefG2O"));
	reflector_g2o_->setStatusTip(tr("RefG2O"));
	connect(reflector_g2o_, SIGNAL(triggered()),this, SLOT(do_ref_g2o()));
	act_permission_.set_menu(MENU_ACT_GP_REFBAG,MENU_ACT_REFBAG_LOGEX_G2O,reflector_g2o_);

}
// 
// void action_collection::del_all_reflect_items()
// {
// 	foreach (QGraphicsItem *item, main_win_->get_scene()->items()) {
// 		if (  QtType::ITEM_REFLECTOR == item->type() )
// 		{
// 
// 			reflector_item* ref =  qgraphicsitem_cast<reflector_item *>(item);
// 			//Singleton_Project_Manage::get_mutable_instance().remove_reflector(Singleton_Project_Manage::get_mutable_instance().get_current_project_nm(),ref->get_id());
// 			PRO_MANAGE.remove_reflector(CURRENT_PRO,ref->get_id());
// 			main_win_->get_scene()->del_item(ref);
// 
// 		}
// 	}
// }

void action_collection::create_move_action()
{
	move_menu_ = main_menuBar_->addMenu(tr("&Move"));

	move_ccw_ = new QAction(QIcon("images/import.png"),tr("Rot&Left"), main_win_);
	move_ccw_->setShortcut(tr("Ctrl+R"));
	move_ccw_->setStatusTip(tr("RotLeft"));
	connect(move_ccw_, SIGNAL(triggered()),this, SLOT(do_rot_left()));
	act_permission_.set_menu(MENU_ACT_GP_MOVE,MENU_ACT_MV_CCW,move_ccw_);

	move_cw_ = new QAction(QIcon("images/import.png"),tr("Rot&Right"), main_win_);
	move_cw_->setShortcut(tr("Ctrl+L"));
	move_cw_->setStatusTip(tr("RotRight"));
	connect(move_cw_, SIGNAL(triggered()),this, SLOT(do_rot_right()));
	act_permission_.set_menu(MENU_ACT_GP_MOVE,MENU_ACT_MV_CW,move_cw_);

	move_front_ = new QAction(QIcon("images/import.png"),tr("Go&Front"), main_win_);
	move_front_->setShortcut(tr("Ctrl+F"));
	move_front_->setStatusTip(tr("GoFront"));
	connect(move_front_, SIGNAL(triggered()),this, SLOT(do_move_front()));
	act_permission_.set_menu(MENU_ACT_GP_MOVE,MENU_ACT_MV_FRONT,move_front_);

	move_back_ = new QAction(QIcon("images/import.png"),tr("Go&Back"), main_win_);
	move_back_->setShortcut(tr("Ctrl+B"));
	move_back_->setStatusTip(tr("GoBack"));
	connect(move_back_, SIGNAL(triggered()),this, SLOT(do_move_back()));
	act_permission_.set_menu(MENU_ACT_GP_MOVE,MENU_ACT_MV_BACK,move_back_);

	move_stop_ = new QAction(QIcon("images/import.png"),tr("Go&Stop"), main_win_);
	move_stop_->setShortcut(tr("Ctrl+P"));
	move_stop_->setStatusTip(tr("GoStop"));
	connect(move_stop_, SIGNAL(triggered()),this, SLOT(do_move_stop()));
	act_permission_.set_menu(MENU_ACT_GP_MOVE,MENU_ACT_MV_STOP,move_stop_);
	

	move_left_ = new QAction(QIcon("images/import.png"),tr("Go&Left"), main_win_);
	move_left_->setShortcut(tr("Ctrl+L"));
	move_left_->setStatusTip(tr("GotLeft"));
	connect(move_left_, SIGNAL(triggered()),this, SLOT(do_move_left()));
	act_permission_.set_menu(MENU_ACT_GP_MOVE,MENU_ACT_MV_LEFT,move_left_);

	move_right_ = new QAction(QIcon("images/import.png"),tr("Go&Right"), main_win_);
	move_right_->setShortcut(tr("Ctrl+R"));
	move_right_->setStatusTip(tr("GoRight"));
	connect(move_right_, SIGNAL(triggered()),this, SLOT(do_move_right()));
	act_permission_.set_menu(MENU_ACT_GP_MOVE,MENU_ACT_MV_RIGHT,move_right_);

	move_ori_ = new QAction(QIcon("images/import.png"),tr("Universal"), main_win_);
	move_ori_->setShortcut(tr("Ctrl+P"));
	move_ori_->setStatusTip(tr("orientation"));
	connect(move_ori_, SIGNAL(triggered()),this, SLOT(do_move_universal()));
	act_permission_.set_menu(MENU_ACT_GP_MOVE,MENU_ACT_MV_ORI,move_ori_);

	move_show_ = new QAction(QIcon("images/import.png"),tr("hide"), main_win_);
	move_show_->setShortcut(tr("Ctrl+P"));
	move_show_->setStatusTip(tr("hide"));
	connect(move_show_, SIGNAL(triggered()),this, SLOT(do_move_show()));
	act_permission_.set_menu(MENU_ACT_GP_MOVE,MENU_ACT_MV_SHOW,move_show_);

	
}

void action_collection::do_rot_left()
{
	Singleton_XML_Client::get_mutable_instance().do_cmd_speed("rot_left 0.1");
	std::cout<<"action:do_rot_left over:"<<std::endl;
}

void action_collection::do_rot_right()
{
	Singleton_XML_Client::get_mutable_instance().do_cmd_speed("rot_right 0.1");
	std::cout<<"action:do_rot_right over:"<<std::endl;
}


void action_collection::do_move_front()
{
	Singleton_XML_Client::get_mutable_instance().do_cmd_speed("front 0.3");
	std::cout<<"action:do_move_front over:"<<std::endl;

}

void action_collection::do_move_back()
{
	Singleton_XML_Client::get_mutable_instance().do_cmd_speed("back 0.15");
	std::cout<<"action:do_move_back over:"<<std::endl;
}

void action_collection::do_move_stop()
{
	Singleton_XML_Client::get_mutable_instance().do_cmd_speed("stop");
	std::cout<<"action:do_move_stop over:"<<std::endl;
}

void action_collection::do_move_left()
{
	Singleton_XML_Client::get_mutable_instance().do_cmd_speed("dir 90 0.1");
	std::cout<<"action:do_move_left over:"<<std::endl;
}

void action_collection::do_move_right()
{
	Singleton_XML_Client::get_mutable_instance().do_cmd_speed("dir -90 0.1");
	std::cout<<"action:do_move_right over:"<<std::endl;
}
void action_collection::do_move_universal()
{
	bool ok = false;
	double dir =  QInputDialog::getDouble(0 ,tr("universal"),tr("direction angle(deg)"), 0.00, -180, 180, 1, &ok);

}

void action_collection::do_move_show()
{
	if (fnc_show_mv_){
		bool b_show = fnc_show_mv_();
		if (b_show){
			move_show_->setText(tr("hide"));
		}else{
			move_show_->setText(tr("show"));
		}
	}
	
	
}

void action_collection::create_calib_action()
{
	calib_menu_ = main_menuBar_->addMenu(tr("Calib"));

	laser_cross_ = new QAction(QIcon("images/import.png"),tr("Cross"), main_win_);
	laser_cross_->setShortcut(tr("Ctrl+N"));
	laser_cross_->setStatusTip(tr("Cross"));
	connect(laser_cross_, SIGNAL(triggered()),this, SLOT(do_show_laser_cross()));
}
void action_collection::do_show_laser_cross()
{

}
bool action_collection::get_process_bar( SProcess_Bar &pro_bar )
{
	bool bres = Singleton_XML_Client::get_mutable_instance().do_get_process_bar(pro_bar,"");
	std::cout<<"action:get_process_bar over:"<<std::endl;
	return bres;
}



void action_collection::create_project_action()
{
	project_menu_ = main_menuBar_->addMenu(tr("Project"));

	open_project_ = new QAction(QIcon("images/import.png"),tr("Open &Project"), main_win_);
	open_project_->setShortcut(tr("Ctrl+P"));
	open_project_->setStatusTip(tr("Open Project"));
	connect(open_project_, SIGNAL(triggered()),this, SLOT(do_open_project()));
	act_permission_.set_menu(MENU_ACT_PRO_FILE,MENU_ACT_PROFILE_OPEN,open_project_);


	save_project_ = new QAction(QIcon("images/import.png"),tr("Save &Project"), main_win_);
	save_project_->setShortcut(tr("Ctrl+T"));
	save_project_->setStatusTip(tr("Save Project"));
	connect(save_project_, SIGNAL(triggered()),this, SLOT(do_save_project()));
	act_permission_.set_menu(MENU_ACT_PRO_FILE,MENU_ACT_PROFILE_SAVE,save_project_);

	download_project_ = new QAction(QIcon("images/import.png"),tr("DownloadProject"), main_win_);
	download_project_->setShortcut(tr("Ctrl+N"));
	download_project_->setStatusTip(tr("DownloadProject"));
	connect(download_project_, SIGNAL(triggered()),this, SLOT(do_download_project()));
	act_permission_.set_menu(MENU_ACT_PRO_FILE,MENU_ACT_PROFILE_DOWNLOAD,download_project_);

	upload_project_ = new QAction(QIcon("images/import.png"),tr("UploadProject"), main_win_);
	upload_project_->setShortcut(tr("Ctrl+N"));
	upload_project_->setStatusTip(tr("UploadProject"));
	connect(upload_project_, SIGNAL(triggered()),this, SLOT(do_upload_project()));
	act_permission_.set_menu(MENU_ACT_PRO_FILE,MENU_ACT_PROFILE_UPLOAD,upload_project_);

	set_onboard_project_ = new QAction(QIcon("images/import.png"),tr("SetOnboardProj"), main_win_);
	set_onboard_project_->setShortcut(tr("Ctrl+N"));
	set_onboard_project_->setStatusTip(tr("SetOnboardProj"));
	connect(set_onboard_project_, SIGNAL(triggered()),this, SLOT(do_set_onboard_project()));
	act_permission_.set_menu(MENU_ACT_PRO_FILE,MENU_ACT_PROFILE_SET_ONBOARD,set_onboard_project_);
	
	//////////////
	select_ = new QAction(QIcon("images/import.png"),tr("Select"), main_win_);
	select_->setShortcut(tr("Ctrl+N"));
	select_->setStatusTip(tr("Select"));
	connect(select_, SIGNAL(triggered()),this, SLOT(do_select()));
	act_permission_.set_menu(MENU_ACT_PRO_TOOLS,MENU_ACT_PROTOOLS_SELECT,select_);
	act_permission_.set_menu(MENU_ACT_GP_REF,MENU_ACT_REFLECTOR_SELECT,select_);

	align_ = new QAction(QIcon("images/import.png"),tr("Align"), main_win_);
	align_->setShortcut(tr("Ctrl+N"));
	align_->setStatusTip(tr("Align"));
	connect(align_, SIGNAL(triggered()),this, SLOT(do_align()));
	act_permission_.set_menu(MENU_ACT_PRO_TOOLS,MENU_ACT_PROTOOLS_ALIGN,align_);

	del_node_edge_ = new QAction(QIcon("images/import.png"),tr("Del"), main_win_);
	del_node_edge_->setShortcut(QKeySequence::Delete);
	del_node_edge_->setStatusTip(tr("Del"));
	connect(del_node_edge_, SIGNAL(triggered()),this, SLOT(do_del_node_edge()));
	act_permission_.set_menu(MENU_ACT_PRO_TOOLS,MENU_ACT_PROTOOLS_DEL,del_node_edge_);
	////////////

	node_ = new QAction(QIcon("images/import.png"),tr("Node"), main_win_);
	node_->setShortcut(tr("Ctrl+N"));
	node_->setStatusTip(tr("Node"));
	connect(node_, SIGNAL(triggered()),this, SLOT(do_node()));
	act_permission_.set_menu(MENU_ACT_PRO_TOPOL,MENU_ACT_PROTOPO_NODE,node_);

	edge_ = new QAction(QIcon("images/import.png"),tr("Edge"), main_win_);
	edge_->setShortcut(tr("Ctrl+N"));
	edge_->setStatusTip(tr("Edge"));
	connect(edge_, SIGNAL(triggered()),this, SLOT(do_edge()));
	act_permission_.set_menu(MENU_ACT_PRO_TOPOL,MENU_ACT_PROTOPO_EDGE,edge_);

	rand_edge_ = new QAction(QIcon("images/import.png"),tr("RandEdge"), main_win_);
	rand_edge_->setShortcut(tr("Ctrl+N"));
	rand_edge_->setStatusTip(tr("RandEdge"));
	connect(rand_edge_, SIGNAL(triggered()),this, SLOT(do_rand_edge()));
	act_permission_.set_menu(MENU_ACT_PRO_TOPOL,MENU_ACT_PROTOPO_RAND_EDGE,rand_edge_);


	range_ = new QAction(QIcon("images/import.png"),tr("Range"), main_win_);
	range_->setShortcut(tr("Ctrl+N"));
	range_->setStatusTip(tr("Range"));
	connect(range_, SIGNAL(triggered()),this, SLOT(do_range()));
	act_permission_.set_menu(MENU_ACT_PRO_TOPOL,MENU_ACT_PROTOPO_RANGE,range_);


	rect_ = new QAction(QIcon("images/import.png"),tr("Rect"), main_win_);
	rect_->setShortcut(tr("Ctrl+N"));
	rect_->setStatusTip(tr("Rect"));
	connect(rect_, SIGNAL(triggered()),this, SLOT(do_rect()));
	act_permission_.set_menu(MENU_ACT_PRO_TOPOL,MENU_ACT_PROTOPO_RECT,rect_);

	
	wander_ = new QAction(QIcon("images/import.png"),tr("Wander"), main_win_);
	wander_->setShortcut(tr("Ctrl+N"));
	wander_->setStatusTip(tr("Wander"));
	connect(wander_, SIGNAL(triggered()),this, SLOT(do_wander()));

	connect(this,SIGNAL(sig_show_wander_str(QString)),SLOT(slot_show_wander_str(QString))); 
	act_permission_.set_menu(MENU_ACT_PRO_SINGLE,MENU_ACT_PROSINGLE_WANDER,wander_);

	auto_cover_ = new QAction(QIcon("images/import.png"),tr("AtCov"), main_win_);
	auto_cover_->setShortcut(tr("Ctrl+o"));
	auto_cover_->setStatusTip(tr("AtCov"));
	connect(auto_cover_, SIGNAL(triggered()),this, SLOT(do_auto_cover()));
	act_permission_.set_menu(MENU_ACT_PRO_SINGLE,MENU_ACT_PROSINGLE_AUTO_COV,auto_cover_);

	//show producer
	producer_ = new QAction(QIcon("images/import.png"),tr("Producer"), main_win_);
	producer_->setShortcut(tr("Ctrl+o"));
	producer_->setStatusTip(tr("Producer"));
	connect(producer_, SIGNAL(triggered()),this, SLOT(do_producer()));
	act_permission_.set_menu(MENU_ACT_PRO_ROLE,MENU_ACT_PROROLE_PRODUCER,producer_);

	consumer_ = new QAction(QIcon("images/import.png"),tr("Consumer"), main_win_);
	consumer_->setShortcut(tr("Ctrl+o"));
	consumer_->setStatusTip(tr("Consumer"));
	connect(consumer_, SIGNAL(triggered()),this, SLOT(do_consumer()));
	act_permission_.set_menu(MENU_ACT_PRO_ROLE,MENU_ACT_PROROLE_CONSUMER,consumer_);

	processer_ = new QAction(QIcon("images/import.png"),tr("Processer"), main_win_);
	processer_->setShortcut(tr("Ctrl+o"));
	processer_->setStatusTip(tr("Processer"));
	connect(processer_, SIGNAL(triggered()),this, SLOT(do_processer()));
	act_permission_.set_menu(MENU_ACT_PRO_ROLE,MENU_ACT_PROROLE_PROCESSER,processer_);

	storage_ = new QAction(QIcon("images/import.png"),tr("Storage"), main_win_);
	storage_->setShortcut(tr("Ctrl+o"));
	storage_->setStatusTip(tr("Storage"));
	connect(storage_, SIGNAL(triggered()),this, SLOT(do_storage()));
	act_permission_.set_menu(MENU_ACT_PRO_ROLE,MENU_ACT_PROROLE_STORAGE,storage_);

	charge_ = new QAction(QIcon("images/import.png"),tr("charge"), main_win_);
	charge_->setShortcut(tr("Ctrl+o"));
	charge_->setStatusTip(tr("charge"));
	connect(charge_, SIGNAL(triggered()),this, SLOT(do_charge()));
	act_permission_.set_menu(MENU_ACT_PRO_ROLE,MENU_ACT_PROROLE_CHARGE,charge_);
}


void action_collection::do_range()
{
	b_range_ = set_CursorShape(qt_eve::mouse_event::MU_TYPE::MU_RANGE);
	if (b_range_)
	{
		QApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));
		set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_RANGE);
	}else{
		QApplication::restoreOverrideCursor();
		item_->range_clear();
	}
// 	else{
// 		set_mouse_event(mouse_event::MU_TYPE::MU_NONE);
// 	}
	
}

void action_collection::do_rect()
{
	b_rect_ = set_CursorShape(qt_eve::mouse_event::MU_TYPE::MU_RECT);
	if (b_rect_)
	{
		set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_RECT);
		QApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
	}
	else{
		// 		set_mouse_event(mouse_event::MU_TYPE::MU_NONE);
		QApplication::restoreOverrideCursor();
	}
}

void action_collection::do_download_project()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	std::string project_name = pro_path_;

	QString dir = QFileDialog::getOpenFileName(NULL,"Select Project",
		project_name.c_str(),
		"projects (*.pro)");
	std::string path = dir.toStdString();

	std::string str_arm_file = pro_path_ + cComm::Get_FileName(path) + "." + cComm::Get_FileType(path);
	DATASERVER_XML_CLIENT.do_download_file(path,str_arm_file);

	QApplication::restoreOverrideCursor();

	QMessageBox::information(0, tr("Over"), tr("Action Done!"));

}

void action_collection::do_upload_project()
{
	std::vector<std::string> vfiles;
	DATASERVER_XML_CLIENT.get_file_list(vfiles,pro_path_);

	file_list_dlg *pDlg = new file_list_dlg(); 
	pDlg->setModal(true); 
	pDlg->set_file_type("pro");
	pDlg->set_file_list(vfiles);
	pDlg->exec();
	std::string sel_project_nm = "";
	pDlg->get_sel_file(sel_project_nm);

	SDelete(pDlg);

	sel_project_nm = pro_path_ + sel_project_nm;
	//---------set upload file name
	bool ok = true;
	QString qstr_log_name = QString::fromStdString(sel_project_nm);
	qstr_log_name = QInputDialog::getText(main_win_, tr("Save upload file ?"),
		tr("Project file:"), QLineEdit::Normal,
		qstr_log_name, &ok);


	if (ok && !qstr_log_name.isEmpty()){

		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

		QMessageBox *tips = 0;
		if (!DATASERVER_XML_CLIENT.get_remote_file(sel_project_nm ,qstr_log_name.toStdString()) )
		{
			tips = new QMessageBox(QMessageBox::Warning,"Project upload","Project upload Err!",QMessageBox::Ok ,0);

		}else{
			tips = new QMessageBox(QMessageBox::NoIcon,"Project upload","Project upload Over!",QMessageBox::Ok ,0);
		}
		tips->exec();
		SDelete(tips);
	}

	std::cout<<"action:do_upload_project over:"<<std::endl;
	QApplication::restoreOverrideCursor();

	QMessageBox::information(0, tr("Over"), tr("Action Done!"));
}

void action_collection::do_set_onboard_project()
{
	std::vector<std::string> vfiles;
	DATASERVER_XML_CLIENT.get_file_list(vfiles,pro_path_);

	file_list_dlg *pDlg = new file_list_dlg(); 
	pDlg->setModal(true); 
	pDlg->set_file_type("pro");
	pDlg->set_file_list(vfiles);
	pDlg->exec();
	std::string sel_project_nm = "";
	pDlg->get_sel_file(sel_project_nm);

	SDelete(pDlg);

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	
	QApplication::restoreOverrideCursor();
	if(TASK_XML_CLIENT.set_onboard_project(sel_project_nm)){
		std::cout<<"action:do_set_pro_map over:"<<std::endl;
		QMessageBox::information(0, tr("Over"), tr("Action Done!"));
	}else{
		std::cout<<"action:do_set_pro_map error:"<<std::endl;
		QMessageBox::warning (0, tr("Error"), tr("Action Error!"));
	}

	

	
}

void action_collection::do_wander()
{

	
	if (!b_wander_run_){
		b_wander_run_ = true;
		wander_->setIconText(QString("Wander (Begin...)"));

		SPos robot_pos;
		memset(&robot_pos,0,sizeof(SPos));
		//DATASERVER_XML_CLIENT.get_robot_pos(robot_pos);

		boost::thread th(boost::bind(&action_collection::th_wander,this));
	}else{
		wander_->setIconText(QString("Wander (Stopping)"));
		b_wander_run_ = false;
	}
	
	
}
void action_collection::do_auto_cover(){

	if ( !PRO_MANAGE.pro_map_setup(CURRENT_PRO) ){
		QMessageBox *tips = new QMessageBox(QMessageBox::Question,"Project map"," Set project map first ?",QMessageBox::Yes | QMessageBox::No,0);
		if (tips->exec() == QMessageBox::Yes){

			std::string map_name = ".//map//";
			RPC_CONFIG_CLIENT.get_config(map_name,"dev_map_path");

			QString dir = QFileDialog::getOpenFileName(NULL,"Open Map",
				map_name.c_str(),
				"maps (*.pgm *.maproto *.maprotoex)");
			std::string path = dir.toStdString();

			item_->open_map(path);

			PRO_MANAGE.set_map(CURRENT_PRO,item_->get_map());

		}
		SDelete(tips);
	}

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	GridMap* p_map = PRO_MANAGE.get_raw_map(CURRENT_PRO);


	GridMap* map_global_tmp = CREATE_MEM_GMAP("map_global_tmp");
	MAP_SERVER.clone( p_map->Get_name(),map_global_tmp->Get_name());
	

	F32 amcl_map_inf = 0.1;
	Config::getConfig("loc_amcl_map_inf",amcl_map_inf);
	MAP_SERVER.fast_inflation( amcl_map_inf,map_global_tmp->Get_name() );
	map_global_tmp->check_border();

	std::vector<std::vector<Sxy>> v_all_range;
	PRO_MANAGE.get_all_range(CURRENT_PRO,v_all_range);
	AUTO_COVER.init(map_global_tmp,v_all_range);

	std::vector<std::vector<SOdomSpeed>> v_block_path;
	SPos pos;
	memset(&pos,0,sizeof(SPos));
	pos.x_ = 2.4;
	pos.y_ = 1.2;
	AUTO_COVER.get_path(v_block_path,pos);
	std::vector<segment_inline> seg_line = AUTO_COVER.get_seg_ln();
	std::vector<Sxy> border_list = AUTO_COVER.get_show_list();
	item_->show_map_item(border_list);
	int i_node_id = 0;
	int i_edge_id = 0;
	std::vector<segment_inline>::iterator it = seg_line.begin();
	for ( ; it != seg_line.end() ; ++it ){
		segment_inline &sl(*it);
// 		std::vector<SSegment>::iterator it = sl.from_to_list_.begin();
// 		for ( ; it != sl.from_to_list_.end() ; ++it){
// 			node_item* node_f = item_->get_new_node_item(i_node_id++,it->p1_.getX(),it->p1_.getY());
// 			node_item* node_t = item_->get_new_node_item(i_node_id++,it->p2_.getX(),it->p2_.getY());
// 			item_->get_new_edge(i_edge_id,node_f,node_t);
// 		}
		break;
	}
	//project* cur_pro = PRO_MANAGE.get_pro(CURRENT_PRO);
}

void action_collection::do_producer()
{
	b_add_producer_ = set_CursorShape(qt_eve::mouse_event::MU_TYPE::MU_ADD_PRODUCER);
	if (b_add_producer_)
	{
		set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_ADD_PRODUCER);
		QApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
	}
	else{
		// 		set_mouse_event(mouse_event::MU_TYPE::MU_NONE);
		QApplication::restoreOverrideCursor();
	}
}

void action_collection::do_consumer()
{
	b_add_consumer_ = set_CursorShape(qt_eve::mouse_event::MU_TYPE::MU_ADD_CONSUMER);
	if (b_add_consumer_)
	{
		set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_ADD_CONSUMER);
		QApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
	}
	else{
		// 		set_mouse_event(mouse_event::MU_TYPE::MU_NONE);
		QApplication::restoreOverrideCursor();
	}
}

void action_collection::do_processer()
{
	b_add_processer_ = set_CursorShape(qt_eve::mouse_event::MU_TYPE::MU_ADD_PROCESSER);
	if (b_add_processer_)
	{
		set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_ADD_PROCESSER);
		QApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
	}
	else{
		// 		set_mouse_event(mouse_event::MU_TYPE::MU_NONE);
		QApplication::restoreOverrideCursor();
	}
}

void action_collection::do_open_project()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	std::string map_name = pro_path_;

	QString dir = QFileDialog::getOpenFileName(NULL,"Open Project",
		map_name.c_str(),
		"projects (*.pro)");
	std::string path = dir.toStdString();

	if (path.length() > 0)
	{
		if (cComm::Get_FileType(path) == "pro"){
			if(!PRO_MANAGE.open_pro(path)){
				QMessageBox::warning(0, tr("Error"), "Please select correct project name!! exp: default.pro");
			}
		}

	}
	
	load_pro_item();

	//main_win_->sel_map_dock();
	std::cout<<"action:do_open_project over"<<path<<std::endl;

	QApplication::restoreOverrideCursor();

}

void action_collection::do_save_project()
{
	

	std::string str_def_project_nm = CURRENT_PRO;

	QString qmap_name = QFileDialog::getSaveFileName(NULL,"Save project",
		QString::fromStdString(str_def_project_nm),
		"Projects(*.pro)");
	if ( (qmap_name.length() < 1) && ( cComm::Get_FileType( qmap_name.toStdString()) == "pro"))
	{
		QMessageBox::warning(0, tr("Error"), "Please enter project name!! exp: default.pro");
		return;
	}
	std::string pro_name = qmap_name.toStdString();
	//item_->save_map(map_name);
	if (pro_name.length() < 1){
		return;
	}

	if ( !PRO_MANAGE.pro_map_setup(CURRENT_PRO) ){
		QMessageBox *tips = new QMessageBox(QMessageBox::Question,"Project map"," Set project map first ?",QMessageBox::Yes | QMessageBox::No,0);
		if (tips->exec() == QMessageBox::Yes){

			std::string map_name = ".//map//";
			RPC_CONFIG_CLIENT.get_config(map_name,"dev_map_path");

			QString dir = QFileDialog::getOpenFileName(NULL,"Open Map",
				map_name.c_str(),
				"maps (*.pgm *.maproto *.maprotoex)");
			std::string path = dir.toStdString();

			item_->open_map(path);

			PRO_MANAGE.set_map(CURRENT_PRO,item_->get_map());
			
		}
		SDelete(tips);
	}

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	PRO_MANAGE.save_pro(pro_name);

	std::cout<<"action:do_save_project over:"<<pro_name<<std::endl;

	QApplication::restoreOverrideCursor();


}
void action_collection::do_select()
{
	b_select_ = set_CursorShape(qt_eve::mouse_event::MU_TYPE::MU_SEL);
	if (b_select_)
	{
		set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_SEL);
		QApplication::setOverrideCursor(QCursor(Qt::CrossCursor));
	}
	else{

		QApplication::restoreOverrideCursor();
	}
}

void action_collection::do_align()
{
	item_->align_node();
}
void action_collection::do_node()
{
	b_add_node_ = set_CursorShape(qt_eve::mouse_event::MU_TYPE::MU_ADD_NODE);
	if (b_add_node_)
	{
		set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_ADD_NODE);
		QApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
	}
 	else{
// 		set_mouse_event(mouse_event::MU_TYPE::MU_NONE);
 		QApplication::restoreOverrideCursor();
 	}
	
}
void action_collection::do_edge()
{
	
	b_add_edge_ = set_CursorShape(qt_eve::mouse_event::MU_TYPE::MU_ADD_EDGE);
	if (b_add_edge_){
		set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_ADD_EDGE);
		foreach (QGraphicsItem *item, main_win_->get_scene()->items()) 
		{
			item->setAcceptedMouseButtons(Qt::NoButton);
		}
		QApplication::setOverrideCursor(QCursor(Qt::CrossCursor));
	}else{
		

		foreach (QGraphicsItem *item, main_win_->get_scene()->items()) 
		{
			item->setAcceptedMouseButtons(Qt::LeftButton);
		}

		QApplication::restoreOverrideCursor();
	}
	
	
// 	b_add_edge_ = !b_add_edge_;
// 	if (b_add_edge_)
// 	{
// 		
// 		set_mouse_event(mouse_event::MU_TYPE::MU_EDGE);
// 	}else{
// 		set_mouse_event(mouse_event::MU_TYPE::MU_NONE);
// 	}
}
void action_collection::do_rand_edge()
{

	set_CursorShape(qt_eve::mouse_event::MU_TYPE::MU_RAND_EDGE);
	foreach (QGraphicsItem *item, main_win_->get_scene()->items()) 
	{
		if (item->type() == QtType::ITEM_NODE){
			item->setSelected(true);
		}
	}
	item_->rand_edge();
}

void action_collection::do_del_node_edge()
{


	set_CursorShape(qt_eve::mouse_event::MU_TYPE::MU_NONE);

	foreach (QGraphicsItem *item, main_win_->get_scene()->selectedItems()) {

		if (item->type() == QtType::ITEM_NODE ){

			node_item* p_node =  qgraphicsitem_cast<node_item *>(item);
			QList<QGraphicsItem*> edge_list = p_node->get_edge_list();
			for ( int i = 0 ; i < edge_list.size() ; ++i ){
				edge_item* p_edge =  qgraphicsitem_cast<edge_item*>(edge_list.at(i));
				if ( p_edge->sourceNode() == p_node ){
					p_edge->destNode()->removeEdge(p_edge);
				}
				if ( p_edge->destNode() == p_node ){
					p_edge->sourceNode()->removeEdge(p_edge);
				}
				PRO_MANAGE.remove_edge(CURRENT_PRO,p_edge->get_id());
				main_win_->get_scene()->del_item((QGraphicsItem*)p_edge);
			}

			PRO_MANAGE.remove_node(CURRENT_PRO,p_node->get_id());
			main_win_->get_scene()->del_item((QGraphicsItem*)p_node);
		}else if (item->type() == QtType::ITEM_EDGE){
			edge_item* p_edge =  qgraphicsitem_cast<edge_item *>(item);
			p_edge->sourceNode()->removeEdge(p_edge);
			p_edge->destNode()->removeEdge(p_edge);
			PRO_MANAGE.remove_edge(CURRENT_PRO,p_edge->get_id());
			main_win_->get_scene()->del_item((QGraphicsItem*)p_edge);
		}else if (item->type() == QtType::ITEM_RANGE ){
			range_item* p_range =  qgraphicsitem_cast<range_item *>(item);
			PRO_MANAGE.remove_range(CURRENT_PRO,p_range->get_name());
			main_win_->get_scene()->del_item((QGraphicsItem*)p_range);
		}else if (item->type() == QtType::ITEM_PRODUCER ){
			producer_item* p_producer =  qgraphicsitem_cast<producer_item *>(item);
			PRO_MANAGE.remove_producer(CURRENT_PRO,p_producer->get_id());
			main_win_->get_scene()->del_item((QGraphicsItem*)p_producer);
		}else if (item->type() == QtType::ITEM_CONSUMER ){
			consumer_item* p_consumer =  qgraphicsitem_cast<consumer_item *>(item);
			PRO_MANAGE.remove_consumer(CURRENT_PRO,p_consumer->get_id());
			main_win_->get_scene()->del_item((QGraphicsItem*)p_consumer);
		}else if (item->type() == QtType::ITEM_PROCESSER ){
			processer_item* p_processer =  qgraphicsitem_cast<processer_item *>(item);
			PRO_MANAGE.remove_processer(CURRENT_PRO,p_processer->get_id());
			main_win_->get_scene()->del_item((QGraphicsItem*)p_processer);
		}else if (item->type() == QtType::ITEM_STORAGE ){
			storage_item* p_storage =  qgraphicsitem_cast<storage_item *>(item);
			PRO_MANAGE.remove_storage(CURRENT_PRO,p_storage->get_id());
			main_win_->get_scene()->del_item((QGraphicsItem*)p_storage);
		}else if (item->type() == QtType::ITEM_CHARGE ){
			charge_item* p_charge =  qgraphicsitem_cast<charge_item *>(item);
			PRO_MANAGE.remove_charge(CURRENT_PRO,p_charge->get_id());
			main_win_->get_scene()->del_item((QGraphicsItem*)p_charge);
		}
	}
}

void action_collection::set_range_pos( qt_eve::mouse_event::SRange_ev event )
{
	if ( event.show_set_ == qt_eve::mouse_event::_SRange_ev::RA_NONE)
	{
		b_range_ = false;
	}
}

void action_collection::bind_show_mv(boost::function<bool(void)> fnc)
{
	fnc_show_mv_ = fnc;
}

void action_collection::create_loop_closure_action()
{
	loop_closure_menu_ = main_menuBar_->addMenu(("Loop_Closure"));

	
	load_refscan_ = new QAction(QIcon("images/import.png"),tr("Load_ref"), main_win_);
	load_refscan_->setShortcut(tr("Ctrl+N"));
	load_refscan_->setStatusTip(tr("Load_ref"));
	connect(load_refscan_, SIGNAL(triggered()),this, SLOT(do_load_ref()));

	mathc_one_ = new QAction(QIcon("images/import.png"),tr("Match_one"), main_win_);
	mathc_one_->setShortcut(tr("F3"));
	mathc_one_->setStatusTip(tr("Match_one"));
	connect(mathc_one_, SIGNAL(triggered()),this, SLOT(do_match_one_scan()));
}

void action_collection::do_load_ref()
{
	std::string file_name = ".//data//";
	QString dir = QFileDialog::getOpenFileName(NULL,"Open log",
		file_name.c_str(),
		"log (*.log;*.proto;*.frame)");
	bag_path_ = dir.toStdString();
	if ( !cComm::FileExist(bag_path_))
	{
		return;
	}

	item_->clear_bag_item();

	i_current_index_ = 0;

	SDelete(p_lc_);

	p_lc_ = new laser2d_loop_closure;
	p_lc_->init_filter();
	int i_size = p_lc_->load(bag_path_,true);
	p_lc_->reset();
}

void action_collection::do_match_one_scan()
{

	item_->clear_bag_item();

	SPUB_BAG pub_bag;

#if 1

	
// 	while ( !lc.end())
// 	{
// 		LaserReading* lreadReference = dynamic_cast<LaserReading*>(lc.next());
// 		conver_laserRead2pubBag(pub_bag , lreadReference);
// 		//item_->add_bag_item(pub_bag);
// 		item_->show_bag_item(pub_bag);
// 	}
	std::cout<<"match index:"<<i_current_index_<<std::endl;
	if(!p_lc_->seek(i_current_index_++)){
		std::cout<<"end of data!"<<std::endl;
		return;
	}
	LaserReading* lreadReference = dynamic_cast<LaserReading*>(p_lc_->current());
#else
	CarmenLogWriter* m_writer_ = new CarmenLogWriter;
	CarmenLogReader* m_reader_ = new CarmenLogReader;
	LogSensorStream* m_sensorReference_ = new LogSensorStream(m_reader_,m_writer_);

	m_sensorReference_->load(bag_path_);

	m_sensorReference_->seek(500);

	LaserReading* lreadReference = dynamic_cast<LaserReading*>(m_sensorReference_->current());
	conver_laserRead2pubBag(pub_bag , lreadReference);
	item_->show_bag_item(pub_bag);

	return;
#endif
	std::vector<SMatch_res> v_res;
	p_lc_->match(v_res,lreadReference);

	std::vector<SMatch_res>::iterator it = v_res.begin();
	for ( ; it != v_res.end() ; ++it )
	{
		SMatch_res &res(*it);
		conver_laserRead2pubBag(pub_bag , res.lreadReference_);
		item_->show_bag_item(pub_bag);
	}
	std::vector<STriangle> v_probability_pos;
	SPos robot_pos;
	if ( p_lc_->filter_pos( robot_pos, v_probability_pos,v_res))
	{

	}

	item_->show_particle_item(v_probability_pos);
	std::cout<<"do_match_one_scan!"<<std::endl;
}

void action_collection::conver_laserRead2pubBag( SPUB_BAG &pub_bag,LaserReading* lreadReference )
{
	if (!lreadReference){
		return;
	}

	memset(&pub_bag,0,sizeof(SPUB_BAG));
	
	std::string str_shape = "0.7,-0.38;0.7,0.38;-0.48,0.38;-0.48,-0.38;0.7,-0.38";
	memcpy(pub_bag.robot_shape_,str_shape.c_str(),str_shape.length());

		
	OrientedPoint2D pos = lreadReference->getLaserPose();

	pub_bag.laser_para_.reverse_ = false;
	pub_bag.laser_para_.laser_dx_ = 0;
	pub_bag.laser_para_.laser_dy_ = 0;
	pub_bag.laser_para_.laser_range_max_ = lreadReference->getMaxRange();
	pub_bag.laser_para_.laser_range_min_ = 0.01;
	pub_bag.laser_para_.laser_resolution_ = lreadReference->getPhi()[1] - lreadReference->getPhi()[0];;
	pub_bag.laser_para_.laser_start_angle_ = lreadReference->getPhi()[0];

	pub_bag.laser_.range_max_ = pub_bag.laser_para_.laser_range_max_;
	pub_bag.laser_.range_min_ = pub_bag.laser_para_.laser_range_min_;
	pub_bag.laser_.resolution_ = pub_bag.laser_para_.laser_resolution_;
	pub_bag.laser_.start_angle_ = pub_bag.laser_para_.laser_resolution_;
	pub_bag.laser_.used_ = lreadReference->getRho().size();
	pub_bag.laser_.stamp_ = lreadReference->m_index;
	for (int i = 0 ; i < pub_bag.laser_.used_ ; ++i)
	{
		pub_bag.laser_.data_[i] = lreadReference->getRho()[i];
		pub_bag.laser_.seg_[i] = 255;
	}

	pub_bag.amcl_pos_.x_ = pos.x;
	pub_bag.amcl_pos_.y_ = pos.y;
	pub_bag.amcl_pos_.th_ = pos.theta;

	pub_bag.odom_.x_ = pos.x;
	pub_bag.odom_.y_ = pos.y;
	pub_bag.odom_.th_ = pos.theta;
	pub_bag.odom_.vx_ = 0;
	pub_bag.odom_.vy_ = 0;
	pub_bag.odom_.vw_ = 0;

}

void action_collection::create_show_log()
{
	show_log_menu_ = main_menuBar_->addMenu(tr("Logs"));
	
	show_log_ = new QAction(QIcon("images/import.png"),tr("ShowLog"), main_win_);
	show_log_->setShortcut(tr("F3"));
	show_log_->setStatusTip(tr("ShowLog"));
	connect(show_log_, SIGNAL(triggered()),this, SLOT(do_show_log()));

	clear_log_ = new QAction(QIcon("images/import.png"),tr("ClearLog"), main_win_);
	clear_log_->setShortcut(tr("F4"));
	clear_log_->setStatusTip(tr("ClearLog"));
	connect(clear_log_, SIGNAL(triggered()),this, SLOT(do_clear_log()));


	
	set_priority_ = new QAction(QIcon("images/import.png"),tr("Set_priority"), main_win_);
	set_priority_->setShortcut(tr("F3"));
	set_priority_->setStatusTip(tr("Set_priority"));
	connect(set_priority_, SIGNAL(triggered()),this, SLOT(do_set_priority()));

	set_para_ = new QAction(QIcon("images/import.png"),tr("Set_para"), main_win_);
	set_para_->setShortcut(tr("F3"));
	set_para_->setStatusTip(tr("Set_para"));
	connect(set_para_, SIGNAL(triggered()),this, SLOT(do_set_para()));
}

void action_collection::do_arm_mapping()
{
	if(!b_arm_mapping_){

		arm_mapping_->setIconText(tr("Mapping(Begin...)"));

		b_arm_mapping_ = true;

		bool ok = true;
		std::stringstream ss;
		ss<<cTimerDiff::get_file_now()<<".maproto";
		QString qstr_map_name = QString::fromStdString(ss.str());
		qstr_map_name = QInputDialog::getText(main_win_, tr("Save Map?"),
			tr("map name:"), QLineEdit::Normal,
			qstr_map_name, &ok);

		if (ok && !qstr_map_name.isEmpty()){
			boost::thread th(boost::bind(&action_collection::th_arm_mapping,this,qstr_map_name.toStdString()));
			std::cout<<"action:do_arm_mapping name:"<<qstr_map_name.toStdString()<<std::endl;
		}else{
			std::cout<<"action: cancel do_arm_mapping"<<std::endl;
		}

		

	}else{

		Singleton_XML_Client::get_mutable_instance().do_stop_gmapping();
		arm_mapping_->setIconText(tr("Mapping(Run)"));

		b_arm_mapping_ = false;

	}
}

void action_collection::th_arm_mapping(std::string str_map_name)
{

	QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));
	
	Singleton_XML_Client::get_mutable_instance().do_begin_gmapping();

	char pro[] = {'/' , '-' , '\\' , '\|' ,'*'};
	
	int index = 0;
	int i_size = sizeof(pro);

	/////////step 1 wait for mapserver begin mapping
	while(b_arm_mapping_){

		SPubDevStatus dev;
		Singleton_XML_Client::get_mutable_instance().get_dev_status(dev,Comm_Dev_Id::ID_MAP_SERVER);
		if (dev.dev_status_.status_ == eMAP_STATUS::MAP_RUN_MAPPING)
		{
			break;
		}
		///////////////////gui show/////////////////
		index = ++index % i_size ;
		std::stringstream ss;
		ss<<"Mapping(Begin: "<<pro[index]<<" )";
	
		emit sig_show_mapping_str(QString::fromStdString(ss.str()));
		SLEEP(100);
	}

	/////////step 2 wait for gui end mapping
	while(b_arm_mapping_){

		///////////////////gui show/////////////////
		index = ++index % i_size ;
		std::stringstream ss;
		ss<<"Mapping(Run: "<<pro[index]<<" )";

		emit sig_show_mapping_str(QString::fromStdString(ss.str()));
		SLEEP(100);
	}
	Singleton_XML_Client::get_mutable_instance().do_stop_gmapping();
	
	
	/////////step 3 wait for mapserver end mapping
	for (int i = 0 ; i < 1000 ; ++i ){

		SPubDevStatus dev;
		Singleton_XML_Client::get_mutable_instance().get_dev_status(dev,Comm_Dev_Id::ID_MAP_SERVER);

		if (dev.dev_status_.status_ == eMAP_STATUS::MAP_IDLE)
		{
			break;
		}

		///////////////////gui show/////////////////
		index = ++index % i_size ;
		std::stringstream ss;
		ss<<"Mapping(Stopping: "<<pro[index]<<" )";

		emit sig_show_mapping_str(QString::fromStdString(ss.str()));
		SLEEP(100);
	}

	/////////step 4 wait for mapserver saving map
	std::stringstream ss;
// 	ss<<cTimerDiff::get_now()<<".maproto";
// 	std::string str_map_name = ss.str();
	Singleton_XML_Client::get_mutable_instance().do_save_gmapping(str_map_name);
	emit sig_show_mapping_str(QString::fromStdString("Mapping (save...)"));
	
	for (int i = 0 ; i < 1000 ; ++i ){

		SPubDevStatus dev;
		Singleton_XML_Client::get_mutable_instance().get_dev_status(dev,Comm_Dev_Id::ID_MAP_SERVER);

		if ( (dev.dev_status_.status_ == eMAP_STATUS::MAP_IDLE) && (dev.dev_status_.err_code_ > 0))
		{
			break;
		}

		
		SLEEP(100);
	}

	emit sig_show_mapping_str(QString::fromStdString("Mapping (Setting...)"));

	Singleton_XML_Client::get_mutable_instance().do_set_onboard_map(str_map_name);

	emit sig_show_mapping_str(QString::fromStdString("Mapping (Run)"));

	QApplication::restoreOverrideCursor();

}

void action_collection::slot_show_mapping_str(QString str)
{
	arm_mapping_->setIconText(str);
}
void action_collection::slot_show_wander_str(QString str)
{
	wander_->setIconText(str);
}
void action_collection::do_set_priority()
{
	log_priority_dlg *pDlg = new log_priority_dlg(); 
	pDlg->setModal(true); 
	pDlg->init(main_win_->get_ip());
	//main_win_->set_check_priority(true);
	
	//main_win_->bind_show_priority( boost::bind(&log_priority_dlg::set_pro_nm_priority,pDlg,_1,_2) );
	
	pDlg->exec();

	//main_win_->set_check_priority(false);

	SDelete(pDlg);
}
void action_collection::do_set_para(){
	
	para_dlg *pDlg = new para_dlg(); 
	pDlg->setModal(true); 
	pDlg->init();
	//main_win_->set_check_priority(true);

	//main_win_->bind_show_priority( boost::bind(&log_priority_dlg::set_pro_nm_priority,pDlg,_1,_2) );

	pDlg->exec();

	//main_win_->set_check_priority(false);

	SDelete(pDlg);
}
void action_collection::do_log_ex_play_onpc()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	SPUB_BAG_EX pbag_ex;
	SPUB_BAG pbag;
	if ( bag_path_.empty() )
	{
		std::string str_bag_name = ".//map//";

		QString dir = QFileDialog::getOpenFileName(NULL,"Proto Bag ex On pc!",
			str_bag_name.c_str(),
			"bagex (*.maprotoex)");
		std::string path = dir.toStdString();
		//path = cComm::Get_FileName(path) + ".proto";

		bag_path_ =  path;

		if (cComm::FileExist(bag_path_))
		{
			
			play_back_bag_ex_.open_file_normal(bag_path_);
			item_->clear_bag_item();
		}else{
			QMessageBox::warning(0, tr("Error"), "File path is not exist!");
		}
	}else{
		if (play_back_bag_ex_.get_one_normal(pbag_ex))
		{
			//PubBagEx2PubBag(pbag,pbag_ex);

			item_->add_bag_ex_item(pbag_ex);
		}else{
			QMessageBox::warning(0, tr("Error"), "File end!");
			bag_path_ = "";
			
		}
	}


	QApplication::restoreOverrideCursor();

}

void action_collection::do_log_keyframe_onpc()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	SPUB_BAG pbag;

	if ( bag_path_.empty() )
	{
		std::string str_path = ".//map//";
		Config::getConfig("dev_map_path",str_path);

		std::string str_map_nm = "default.pgm";
		Config::getConfig("dev_map_name",str_map_nm);

		str_map_nm = cComm::Get_FileName(str_map_nm);

		str_path = str_path + str_map_nm ;

		QString dir = QFileDialog::getOpenFileName(NULL,"Key frame Bag On pc!",
			str_path.c_str(),
			"bag (*.proto;)");
		std::string path = dir.toStdString();
		//path = cComm::Get_FileName(path) + ".proto";
		
		bag_path_ =  path;

		if (cComm::FileExist(bag_path_))
		{

			play_back_bag_.open_file_normal(bag_path_);
			item_->clear_bag_item();
		}else{
			QMessageBox::warning(0, tr("Error"), "File path is not exist!");
		}
	}else{
		if (play_back_bag_.get_one_normal(pbag))
		{
			
			item_->add_key_item(pbag,false);

		}else{
			QMessageBox::warning(0, tr("Error"), "File end!");
			bag_path_ = "";
		}
	}


	QApplication::restoreOverrideCursor();
}

void action_collection::do_open_reflector()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	
	std::string str_bag_name = ".//map//";
	Config::getConfig("dev_map_path",str_bag_name);

	QString dir = QFileDialog::getOpenFileName(NULL,"reflector On pc!",
		str_bag_name.c_str(),
		"landmark (*.lm)");
	std::string path = dir.toStdString();
		//path = cComm::Get_FileName(path) + ".proto";

	if (cComm::FileExist(path))
	{
		std::vector<SReflectorPos> v_ref_pos;
		//reflected_pillar_loc ref_loc;
		//ref_loc.load_reflected_map(v_ref_pos,path);
		//ref_loc.init(v_ref_pos);

 		PRO_MANAGE.load_reflector(CURRENT_PRO,path);
		project* pro = PRO_MANAGE.get_pro(CURRENT_PRO);
 		pro->get_reflector_all(v_ref_pos);
		//ref_mapping.get_mapping_reflector(reflector_list);
		item_->show_reflector_list(v_ref_pos);

	}else{
		QMessageBox::warning(0, tr("Error"), "File path is not exist!");
	}

	QApplication::restoreOverrideCursor();
}
void action_collection::do_save_reflector()
{
	
	
	bool ok = true;
	std::stringstream ss;
	
	std::string str_bag_name = ".//map//";
	Config::getConfig("dev_map_path",str_bag_name);

	std::string ref_map_name = Singleton_Project_Manage::get_mutable_instance().get_current_project_nm();
	if (cComm::Get_FileType(ref_map_name) == "lm")
	{
		ss<<str_bag_name<<cComm::Get_FileName(ref_map_name)<<".lm";
	}else{
		ss<<str_bag_name<<cTimerDiff::get_file_now()<<".lm";
	}

	QString qstr_map_name = QString::fromStdString(ss.str());
	qstr_map_name = QInputDialog::getText(main_win_, tr("Save reflector map?"),
		tr("ml map name:"), QLineEdit::Normal,
		qstr_map_name, &ok);

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	if (ok && !qstr_map_name.isEmpty()){
		//Singleton_XML_Client::get_mutable_instance().do_save_gmapping(qstr_map_name.toStdString());
		std::string str_path_map = qstr_map_name.toStdString();

		Singleton_Project_Manage::get_mutable_instance().save_reflector_map(Singleton_Project_Manage::get_mutable_instance().get_current_project_nm() , str_path_map);
		std::cout<<"action:do_save_reflector name:"<<str_path_map<<std::endl;
	}else{
		std::cout<<"action: cancel do_save_reflector"<<std::endl;
	}
	
	QApplication::restoreOverrideCursor();
}
void action_collection::do_upload_reflector()
{
	std::cout<<"action:do_upload_reflector"<<std::endl;
	std::vector<std::string> v_bag_list;
	Singleton_XML_Client::get_mutable_instance().get_file_list(v_bag_list,".//map//");

	file_list_dlg *pDlg = new file_list_dlg(); 
	pDlg->setModal(true);
	pDlg->set_file_type("lm");
	pDlg->set_file_list(v_bag_list);
	pDlg->exec();
	std::string str_file = "";
	pDlg->get_sel_file(str_file);

	SDelete(pDlg);

	str_file = ".//map//" + str_file;
	//---------set upload file name
	bool ok = true;
	QString qstr_log_name = QString::fromStdString(str_file);
	qstr_log_name = QInputDialog::getText(main_win_, tr("Save upload file ?"),
		tr("landmark file:"), QLineEdit::Normal,
		qstr_log_name, &ok);


	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	if (ok && !qstr_log_name.isEmpty()){

		QMessageBox *tips = 0;
		if (!Singleton_XML_Client::get_mutable_instance().get_remote_file(str_file ,qstr_log_name.toStdString()) )
		{
			tips = new QMessageBox(QMessageBox::Warning,"landmark_upload","landmark_upload Err!",QMessageBox::Ok ,0);

		}else{
			tips = new QMessageBox(QMessageBox::NoIcon,"landmark_upload","landmark_upload Over!",QMessageBox::Ok ,0);
		}
		tips->exec();
		SDelete(tips);
	}
	QApplication::restoreOverrideCursor();
}

void action_collection::do_download_reflector()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	std::string map_name = ".//map//";

	QString dir = QFileDialog::getOpenFileName(NULL,"Open Map",
		map_name.c_str(),
		"landmark (*.lm)");
	std::string path = dir.toStdString();

	std::string str_arm_file = ".//map//" + cComm::Get_FileName(path) + "." + cComm::Get_FileType(path);
	Singleton_XML_Client::get_mutable_instance().do_download_file(path,str_arm_file);

	QApplication::restoreOverrideCursor();
}

void action_collection::do_clear_bag_show()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	main_win_->clear_show_bag();

	QApplication::restoreOverrideCursor();
}

void action_collection::create_init_action()
{
	init_menu_ = main_menuBar_->addMenu(("Init"));

	para_init_ = new QAction(QIcon("images/import.png"),tr("ParaInit"), main_win_);
	para_init_->setShortcut(tr("F0"));
	para_init_->setStatusTip(tr("ParaInit"));
	connect(para_init_, SIGNAL(triggered()),this, SLOT(do_para_init()));

	auto_init_ = new QAction(QIcon("images/import.png"),tr("AutoInit"), main_win_);
	auto_init_->setShortcut(tr("F112"));
	auto_init_->setStatusTip(tr("AutoInit"));
	connect(auto_init_, SIGNAL(triggered()),this, SLOT(do_auto_init()));
}

void action_collection::do_para_init()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	std::string str_map;
	Config::getConfig("dev_map_name",str_map);
	
	std::string str_value;
	Config::getConfig("dev_para_init_p1",str_value);
	std::vector<std::string> vres;
	cComm::SplitString(str_value,";",vres);


	SPos est_pos;
	if (vres.size() > 2){
		
		
		memset(&est_pos,0,sizeof(SPos));

		cComm::ConvertToNum(est_pos.x_, vres[0]);
		cComm::ConvertToNum(est_pos.y_, vres[1]);
		cComm::ConvertToNum(est_pos.th_, vres[2]);
		est_pos.th_ = Deg2Rad(est_pos.th_);
		
		
	}

	if(Singleton_XML_Client::get_mutable_instance().do_set_onboard_map(str_map)){

		std::cout<<"action:do_load_map ok:"<<str_map<<std::endl;

		if(!Singleton_XML_Client::get_mutable_instance().set_est_pos(est_pos)){
			QMessageBox::warning(0, tr("Error"), tr("Please set correct robot pos or set map first!!"));
		}

	}else{
		std::cout<<"action:do_load_map err:"<<str_value<<std::endl;
	}

	QApplication::restoreOverrideCursor();
}

void action_collection::do_auto_init()
{

}


void action_collection::create_tools_action()
{
	tools_menu_ = main_menuBar_->addMenu(tr("Tools"));


	//zoom_in_ = new QAction(QIcon("images/import.png"),tr("ZoomIn"), main_win_);
	//zoom_in_->setShortcut(tr("="));
	//zoom_in_->setStatusTip(tr("ZoomIn"));
	//connect(zoom_in_, SIGNAL(triggered()),this, SLOT(do_zoom_in()));

	//zoom_out_ = new QAction(QIcon("images/import.png"),tr("ZoomOut"), main_win_);
	//zoom_out_->setShortcut(tr("-"));
	//zoom_out_->setStatusTip(tr("ZoomOut"));
	//connect(zoom_out_, SIGNAL(triggered()),this, SLOT(do_zoom_out()));

	search_path_ = new QAction(QIcon("images/import.png"),tr("SearchPath"), main_win_);
	search_path_->setShortcut(tr("Ctrl+F"));
	search_path_->setStatusTip(tr("SearchPath"));
	connect(search_path_, SIGNAL(triggered()),this, SLOT(do_search_path()));
	act_permission_.set_menu(MENU_ACT_GP_TOOLS,MENU_ACT_TOOLS_SEARCH_PATH,search_path_);
	

	dy_location_ = new QAction(QIcon("images/import.png"),tr("dynamic_loc"), main_win_);
	dy_location_->setShortcut(tr("Ctrl+F"));
	dy_location_->setStatusTip(tr("dynamic_loc"));
	connect(dy_location_, SIGNAL(triggered()),this, SLOT(do_dynamic_loc()));
	act_permission_.set_menu(MENU_ACT_GP_TOOLS,MENU_ACT_TOOLS_DYNAMIC_LOC,dy_location_);

	scan_match_ = new QAction(QIcon("images/import.png"),tr("scan_match"), main_win_);
	scan_match_->setShortcut(tr("Ctrl+F"));
	scan_match_->setStatusTip(tr("scan_match"));
	connect(scan_match_, SIGNAL(triggered()),this, SLOT(do_scan_match()));
	act_permission_.set_menu(MENU_ACT_GP_TOOLS,MENU_ACT_TOOLS_SCAN_MATCH,scan_match_);


	add_qr_code_ = new QAction(QIcon("images/import.png"),tr("AddQrCode"), main_win_);
	add_qr_code_->setShortcut(tr("Ctrl+F"));
	add_qr_code_->setStatusTip(tr("AddQrCode"));
	connect(add_qr_code_, SIGNAL(triggered()),this, SLOT(do_add_qrcode()));
	act_permission_.set_menu(MENU_ACT_GP_TOOLS,MENU_ACT_TOOLS_ADD_QRCODE,add_qr_code_);

	
	exp_qr_code_ = new QAction(QIcon("images/import.png"),tr("ExpQrCode"), main_win_);
	exp_qr_code_->setShortcut(tr("Ctrl+F"));
	exp_qr_code_->setStatusTip(tr("ExpQrCode"));
	connect(exp_qr_code_, SIGNAL(triggered()),this, SLOT(do_exp_qrcode()));
	act_permission_.set_menu(MENU_ACT_GP_TOOLS,MENU_ACT_TOOLS_EXP_QRCODE,exp_qr_code_);

	imp_qr_code_ = new QAction(QIcon("images/import.png"),tr("ImpQrCode"), main_win_);
	imp_qr_code_->setShortcut(tr("Ctrl+F"));
	imp_qr_code_->setStatusTip(tr("ImpQrCode"));
	connect(imp_qr_code_, SIGNAL(triggered()),this, SLOT(do_imp_qrcode()));
	act_permission_.set_menu(MENU_ACT_GP_TOOLS,MENU_ACT_TOOLS_IMP_QRCODE,imp_qr_code_);
}
void action_collection::do_zoom_in(){
	std::cout<<"action_collection::do_zoom_in"<<std::endl;
}
void action_collection::do_zoom_out(){
	std::cout<<"action_collection::do_zoom_out"<<std::endl;
}
void action_collection::do_search_path()
{
	std::cout<<"action_collection::do_search_path"<<std::endl;

	if (!path_search_dlg_){
		path_search_dlg_ = new path_search_dlg();
		//path_search_dlg_->setModal(true); 
		path_search_dlg_->init();
		path_search_dlg_->exec();
	}else{
		path_search_dlg_->show();
	}
	 
	//
	


//	SDelete(pDlg);
}

void action_collection::load_pro_item()
{
	main_win_->remove_agv();
	item_->remove_all_item();
	GridMap* p_map = PRO_MANAGE.get_raw_map(CURRENT_PRO);
	item_->set_map(p_map);

	//show node
	protobuf_node* p_node = 0;
	p_node = PRO_MANAGE.get_next_node("",-1);

	while(p_node){
		SPos p;
		p_node->get_pos(p);
		item_->get_new_node_item(p_node->get_id(),p.x_,p.y_);
		p_node = PRO_MANAGE.get_next_node("",p_node->get_id());

	}
	//show edge
	protobuf_edge* p_edge = 0;
	p_edge = PRO_MANAGE.get_next_edge("",-1);

	while(p_edge){

		item_->get_new_edge(p_edge->get_id(),p_edge->get_nsrc_id(),p_edge->get_ndst_id());
		item_->set_ori_dir(p_edge->get_id(),p_edge->forward(),p_edge->backward(),p_edge->leftshift(),p_edge->rightshift());
		
		p_edge = PRO_MANAGE.get_next_edge("",p_edge->get_id());
	}



	std::vector<protobuf_reflector*> reflector_list;
	PRO_MANAGE.get_reflector("",reflector_list);
	std::vector<protobuf_reflector*>::iterator it = reflector_list.begin();
	for ( ; it !=  reflector_list.end() ; ++it)
	{
		F32 fx = 0;
		F32 fy = 0;
		(*it)->get_pos(fx,fy);
		reflector_item* p_reflector_item = item_->get_new_reflector_item(fx,fy);
		p_reflector_item->set_id((*it)->get_id());

		lab_item* p_lab_item = item_->get_new_lab_item(fx,fy);
		p_lab_item->set_id((*it)->get_id());
	}


	protobuf_lab* p_lab = 0;
	p_lab = Singleton_Project_Manage::get_mutable_instance().get_next_lab("",-1);

	while(p_lab){

		SVec vp;
		p_lab->get_pos(vp.x_,vp.y_);


		lab_item* p_item_lab = item_->get_new_lab_item(vp.x_,vp.y_);
		p_item_lab->set_id(p_lab->get_id());
		p_item_lab->set_lab(p_lab->get_lab());
		p_item_lab->setVisible(p_lab->get_show());

		p_lab = Singleton_Project_Manage::get_mutable_instance().get_next_lab("",p_lab->get_id());
	}

	protobuf_range* p_range = 0;
	p_range = Singleton_Project_Manage::get_mutable_instance().get_next_range("","");

	while(p_range){

		SVec vp;
		SPos pos = p_range->get_start_pos();

		std::vector<Sxy> v_list;
		p_range->get_range(v_list);

		range_item*  p_range_item = item_->get_new_range_item(p_range->get_name());
		p_range_item->setPos(pos.x_,pos.y_);
		p_range_item->add_point(v_list);

		p_range = Singleton_Project_Manage::get_mutable_instance().get_next_range("",p_range->get_name());
	}

	//show producer
	protobuf_producer* p_producer = 0;
	p_producer = Singleton_Project_Manage::get_mutable_instance().get_next_producer("",-1);

	while(p_producer){

 		SPos pos;
		p_producer->get_pos(pos);

		producer_item* p_producer_item = item_->get_new_producer_item(p_producer->get_id(),pos.x_,pos.y_);

		p_producer = Singleton_Project_Manage::get_mutable_instance().get_next_producer("",p_producer->get_id());
	}

	//show consumer
	protobuf_consumer* p_consumer = 0;
	p_consumer = Singleton_Project_Manage::get_mutable_instance().get_next_consumer("",-1);

	while(p_consumer){

		SPos pos;
		p_consumer->get_pos(pos);

		consumer_item* p_consumer_item = item_->get_new_consumer_item(p_consumer->get_id(),pos.x_,pos.y_);

		p_consumer = Singleton_Project_Manage::get_mutable_instance().get_next_consumer("",p_consumer->get_id());
	}

	//show processer
	protobuf_processer* p_processer = 0;
	p_processer = Singleton_Project_Manage::get_mutable_instance().get_next_processer("",-1);

	while(p_processer){

		SPos pos;
		p_processer->get_pos(pos);

		processer_item* p_processer_item = item_->get_new_processer_item(p_processer->get_id(),pos.x_,pos.y_);

		p_processer = Singleton_Project_Manage::get_mutable_instance().get_next_processer("",p_processer->get_id());
	}

	//show storage
	protobuf_storage* p_storage = 0;
	p_storage = Singleton_Project_Manage::get_mutable_instance().get_next_storage("",-1);

	while(p_storage){

		SPos pos;
		p_storage->get_pos(pos);

		storage_item* p_storage_item = item_->get_new_storage_item(p_storage->get_id(),pos.x_,pos.y_);

		p_storage = Singleton_Project_Manage::get_mutable_instance().get_next_storage("",p_storage->get_id());
	}

	//show charge
	protobuf_charge* p_charge = 0;
	p_charge = Singleton_Project_Manage::get_mutable_instance().get_next_charge("",-1);

	while(p_charge){

		SPos pos;
		p_charge->get_pos(pos);

		charge_item* p_charge_item = item_->get_new_charge_item(p_charge->get_id(),pos.x_,pos.y_);

		p_charge = Singleton_Project_Manage::get_mutable_instance().get_next_charge("",p_charge->get_id());
	}
}
void action_collection::th_wander()
{
	QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));


	char pro[] = {'/' , '-' , '\\' , '\|' ,'*'};

	int index = 0;
	int i_size = sizeof(pro);

	int i_rand_path_id = -1;

	/////////step 1 wait for mapserver begin mapping
	while(b_wander_run_){
		
		if (i_rand_path_id < 0){ 

 			SPos robot_pos;
 			memset(&robot_pos,0,sizeof(SPos));
// 			DATASERVER_XML_CLIENT.get_robot_pos(robot_pos);

			i_rand_path_id = TASK_XML_CLIENT.create_rand_path(robot_pos);
			if (i_rand_path_id < 0){
				std::cout<<"create_rand_path err!"<<std::endl;
			}
	
		}else{
			
			std::vector<task_feadback> ftb;
			TASK_XML_CLIENT.get_feadback(-1,ftb);
			main_win_->get_action()->set_tfb(ftb);

			std::vector<task_feadback>::iterator it = ftb.begin();
			for ( ; it != ftb.end() ; ++it ){
				task_feadback &fb(*it);
				if (fb.get_task_id() == i_rand_path_id){
					if (fb.get_status() == STASK_STA::TASK_DONE){
						i_rand_path_id = -1;
					}
				}
			}
	
	
		}
		
// 		if( TASK_MANAGE.do_task_list() < 1){
// 			b_wander_run_ = false;
// 		}
		///////////////////gui show/////////////////
		index = ++index % i_size ;
		std::stringstream ss;
		ss<<"Wander (Run: "<<pro[index]<<" )";

		emit sig_show_wander_str(QString::fromStdString(ss.str()));
		SLEEP(200);
	}

	emit sig_show_wander_str(QString::fromStdString("Wander (Over)"));

	QApplication::restoreOverrideCursor();
}
void action_collection::do_storage()
{
	b_add_storage_ = set_CursorShape(qt_eve::mouse_event::MU_TYPE::MU_ADD_STORAGE);
	if (b_add_storage_)
	{
		set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_ADD_STORAGE);
		QApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
	}
	else{
		// 		set_mouse_event(mouse_event::MU_TYPE::MU_NONE);
		QApplication::restoreOverrideCursor();
	}
}

void action_collection::do_charge()
{
	b_add_charge_ = set_CursorShape(qt_eve::mouse_event::MU_TYPE::MU_ADD_CHARGE);
	if (b_add_charge_)
	{
		set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_ADD_CHARGE);
		QApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
	}
	else{
		// 		set_mouse_event(mouse_event::MU_TYPE::MU_NONE);
		QApplication::restoreOverrideCursor();
	}
}

void action_collection::th_ref_gmapping( std::string path )
{
	SDelete(ref_mapping_);

	reflected_pillar_mapping* p_ref = new reflected_pillar_mapping();
	ref_mapping_ = (void*)p_ref;

	p_ref->init();
	p_ref->bind_show_bag(boost::bind(&item_collection::add_bag_ex_item,item_,_1));
	p_ref->bind_map_bag(boost::bind(&item_collection::add_mapping_item,item_,_1));
	p_ref->bind_clear_bag_item(boost::bind(&item_collection::clear_bag_item_thread,item_));
	p_ref->gmapping_bag_ex(path);
}

void action_collection::do_ref_gmapping()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	item_->clear_bag_item();

	std::string str_bag_name = ".//pro_log//";

	QString dir = QFileDialog::getOpenFileName(NULL,"protoex On pc!",
		str_bag_name.c_str(),
		"bagex (*.protoex)");
	std::string path = dir.toStdString();
	path = cComm::Get_FileName(path) + ".protoex";

	if (cComm::FileExist(str_bag_name + path))
	{
		boost::thread th(boost::bind(&action_collection::th_ref_gmapping,this,str_bag_name + path));
	}else{
		QMessageBox::warning(0, tr("Error"), tr("File path is not exist!"));
	}

	QApplication::restoreOverrideCursor();
}

void action_collection::do_ref_g2o()
{
	if (!cComm::FileExist(str_path_gmap_)){
		return;
	}

	if (!ref_mapping_){
		QMessageBox::warning(0, tr("Error"), "Do 2-Modify first!");
		return;
	}
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	item_->clear_bag_item();


	boost::thread th(boost::bind(&action_collection::th_ref_g2o,this,str_path_gmap_));
	

	QApplication::restoreOverrideCursor();
}

void action_collection::th_ref_g2o( std::string path )
{
	

	reflected_pillar_mapping* p_ref = (reflected_pillar_mapping*)ref_mapping_;
// 	ref_mapping_.init();
 	p_ref->bind_show_bag(boost::bind(&item_collection::add_bag_ex_item,item_,_1));
 	p_ref->g2omapping_bag_ex(path);
	item_->clear_mapping_reflector();
}

void action_collection::do_dynamic_loc()
{

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	SPUB_BAG pbag;

	if ( bag_path_.empty() )
	{
		std::string str_bag_name = ".//pro_log//";

		QString dir = QFileDialog::getOpenFileName(NULL,"Proto Bag On pc!",
			str_bag_name.c_str(),
			"bag (*.proto;*.maproto)");
		std::string path = dir.toStdString();
		//path = cComm::Get_FileName(path) + ".proto";
		if (cComm::Get_FileType(path) == "maproto"){
			b_laser_diff_ = false;
		}else{
			b_laser_diff_ = true;
		}
		bag_path_ =  path;

		if (cComm::FileExist(bag_path_))
		{

			play_back_bag_.open_file_normal(bag_path_);

			p_dy_ = new dynamic_loc();
			p_dy_->init(true);

			item_->clear_bag_item();
		}else{
			QMessageBox::warning(0, tr("Error"), "File path is not exist!");
		}
	}else{
		if (play_back_bag_.get_one_normal(pbag))
		{
			if(!b_laser_diff_){
				pbag.laser_para_.laser_dx_ = 0;
				pbag.laser_para_.laser_dy_ = 0;
				
			}
			p_dy_->set_laser_para(pbag.laser_para_,pbag.robot_shape_);
				
			p_dy_->updata_used_laser(pbag.laser_);
			p_dy_->update_amcl_pos(pbag.amcl_pos_);
			p_dy_->updata_amcl_conf(amcl_conf_);
			if (!p_dy_->update_odom(pbag.odom_)){
				QMessageBox::warning(0, tr("Error"), "File end!");
				bag_path_ = "";
				SDelete(p_dy_);
			}else{
				pbag.odom_.x_ = p_dy_->final_pos_.x_;
				pbag.odom_.y_ = p_dy_->final_pos_.y_;
				pbag.odom_.th_ = p_dy_->final_pos_.th_;
				//item_->add_bag_item(pbag);
			}
			
			
			//

		}else{
			QMessageBox::warning(0, tr("Error"), "File end!");
			bag_path_ = "";
			SDelete(p_dy_);
		}
	}

	
	QApplication::restoreOverrideCursor();
}

void action_collection::do_scan_match()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	SPUB_BAG pbag;

	SLaser cur_laser;
	SPos cur_pos;
	SLaser ref_laser;
	SPos ref_pos;
	SPos odom_diff;

	if ( bag_path_.empty() )
	{
		std::string str_bag_name = ".//map//";

		QString dir = QFileDialog::getOpenFileName(NULL,"Proto scan On pc!",
			str_bag_name.c_str(),
			"bag (*.proto)");
		std::string path = dir.toStdString();
		//path = cComm::Get_FileName(path) + ".proto";
		
		bag_path_ =  path;
		

		if (cComm::FileExist(bag_path_))
		{

			play_back_bag_.open_file_normal(bag_path_);

			SDelete(p_psm_node_);
			p_psm_node_ = new PSMNode();
			play_back_bag_.get_one_normal(pbag);
			cur_laser  = pbag.laser_;
			cur_pos = pbag.amcl_pos_;
			play_back_bag_.get_one_normal(pbag);
			ref_laser  = pbag.laser_;
			ref_pos = pbag.amcl_pos_;

			odom_diff = cComm::cal_diff(cur_pos , ref_pos);

			p_psm_node_->show_optimize(odom_diff,ref_laser,cur_laser,true);

			item_->clear_bag_item();
		}else{
			QMessageBox::warning(0, tr("Error"), "File path is not exist!");
		}
	}else{
		
		p_psm_node_->show_optimize(odom_diff,ref_laser,cur_laser,false);

	}
// 		QMessageBox::warning(0, tr("Error"), "File end!");
// 		bag_path_ = "";
			//SDelete(p_dy_);


	QApplication::restoreOverrideCursor();
}

void action_collection::do_add_qrcode()
{
	
	SQrCode qr_code;
	if (DATASERVER_XML_CLIENT.get_qr_code(qr_code)){
		item_->add_qrcode_pos(qr_code);
	}else{

		if(!b_add_qrcode_){
			set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_ADD_QRCOD);
			QApplication::setOverrideCursor(QCursor(Qt::CrossCursor));
		}else{
			set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_NONE);
			QApplication::restoreOverrideCursor();
		}
		b_add_qrcode_ = !b_add_qrcode_;

	}

	

	

	//QApplication::restoreOverrideCursor();

}

void action_collection::do_exp_qrcode()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_NONE);
	

	bool ok = true;
	std::stringstream ss;

	std::string str_map_path = ".//map//";
	Config::getConfig("dev_map_path",str_map_path);

	std::string qr_map_name = Singleton_Project_Manage::get_mutable_instance().get_current_project_nm();
	if (cComm::Get_FileType(qr_map_name) == "lm")
	{
		ss<<str_map_path<<cComm::Get_FileName(qr_map_name)<<".qr";
	}else{
		ss<<str_map_path<<cTimerDiff::get_file_now()<<".qr";
	}

	QString qstr_map_name = QString::fromStdString(ss.str());
	qstr_map_name = QInputDialog::getText(main_win_, tr("Save qr map?"),
		tr("qr map name:"), QLineEdit::Normal,
		qstr_map_name, &ok);

	if (ok && !qstr_map_name.isEmpty()){
		//Singleton_XML_Client::get_mutable_instance().do_save_gmapping(qstr_map_name.toStdString());
		std::string str_path_map = qstr_map_name.toStdString();

		Singleton_Project_Manage::get_mutable_instance().save_qr_map(Singleton_Project_Manage::get_mutable_instance().get_current_project_nm() , str_path_map);
		std::cout<<"action:do_save_qrcode name:"<<str_path_map<<std::endl;
	}else{
		std::cout<<"action: cancel do_save_qrcode"<<std::endl;
	}

	QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
}

void action_collection::do_imp_qrcode()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	set_mouse_event(qt_eve::mouse_event::MU_TYPE::MU_NONE);
	
	std::string str_bag_name = ".//map//";
	Config::getConfig("dev_map_path",str_bag_name);

	QString dir = QFileDialog::getOpenFileName(NULL,"qrcode On pc!",
		str_bag_name.c_str(),
		"qrcode (*.qr)");
	std::string path = dir.toStdString();

	if (cComm::FileExist(path))
	{
		std::vector<SReflectorPos> v_ref_pos;
		//reflected_pillar_loc ref_loc;
		//ref_loc.load_reflected_map(v_ref_pos,path);
		//ref_loc.init(v_ref_pos);

		PRO_MANAGE.load_qr_map(CURRENT_PRO,path);
		project* pro = PRO_MANAGE.get_pro(CURRENT_PRO);
		std::vector<SQrCode> v_qr_code;
		pro->get_qr_all(v_qr_code);
		//ref_mapping.get_mapping_reflector(reflector_list);
		item_->show_qr_list(v_qr_code);

	}else{
		QMessageBox::warning(0, tr("Error"), "File path is not exist!");
	}

	QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
}



































