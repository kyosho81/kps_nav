#include <string>

#include "plot/Plot_Lib.h"

#include "dev_monitor_dlg.h"
#include "action_monitor_dlg.h"

#include "Comm/Comm.h"
#include "interface/xml_rpc_client.h"
#include "interface/cfg.hpp"
#include "interface/rpc_config_client.h"
#include "scene/map_view.h"
#include "scene/map_scene.h"
#include "action.h"
#include "item_collection.h"
#include "robot/robot_remote_para.h"
#include "protobuf_msg/protobuf_bag.h"
#include "protobuf_msg/protobuf_bag_ex.h"
#include "calib_dlg.h"
#include "trans_dev/trans_dev.h"
#include "Comm/PortDef.h"
#include "log/Log4cppArm.hpp"
#include "interface/rpc_config_server.h"
#include "ip_list_dlg.h"
//#include "scene/CustomButton.h"
#include "interpro_shared/sh_pool.hpp"
#include "mapserver/map_def.h"
#include "robot/msg_def.h"
#include "project/task_manage.h"
#include "project/task_rpc_client.h"
#include "mapserver/MapServer.h"
#include "agv_manage_dlg.h"
#include "dispatching/agv_manage.h"
#include "data_manage_dlg.h"
#include "order_dlg.h"
#include "interface_dlg.h"
#include "strategy_dlg.h"
#include "manual_ctl_dlg.h"
#include "dio_dlg.h"
#include "task_flow_dlg.h"
#include "dispatching/task_flow_factory.h"

#include "kps_main_win.h"


kps_main_win::kps_main_win( bool b_init_core, bool b_agvs, QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),mubuf_log_(2500)
{
	b_agvs_ = b_agvs;

	buttonGroup_ = 0;
	menu_widget_ = 0;
	dev_widget_ = 0;
	calib_widget_ = 0;
	project_widget_ = 0;
	tcontrol_widget_ = 0;

	menu_dock_ = 0;
	dev_dock_ = 0;
	calib_dock_ = 0;
	action_dock_ = 0;
	agv_manage_dock_ = 0;
	dio_dock_ = 0;
	order_dock_ = 0;
	interface_dock_ = 0;
	strategy_dock_ = 0;
	data_manage_dock_ = 0;
	task_flow_dock_ = 0;

	lab_status_ = 0;
	lab_confidence_ = 0;
	process_bar_ = 0;
	b_show_pro_ = false;

	timer_id_ = 0;
	b_show_log_ = false;

	rpc_config_server_ = 0;
	map_scene_ = 0;
	map_view_ = 0;
	//th_check_priority_ = false;

	//slot_print_log("");
	create_rpc(b_init_core);

	item_ = new item_collection();
	item_->init(this);

	action_ = new action_collection();
	action_->init(this,item_);
	
	calib_dlg_ = 0;
	action_dlg_ = 0;
	agv_manage_dlg_ = 0;
	dio_dlg_ = 0;
	data_manage_dlg_ = 0;
	order_dlg_ = 0;
	interface_dlg_ = 0;
	strategy_dlg_ = 0;

	

	CreateMenuDock();
	//CreateDevMonitorDock();
	if (!b_agvs_){
		CreateCalibrationDock();
		CreateDataDock();
		CreateMapMonitorDock();

		CreateTaskFlowDock();
		
	}else{
		CreateMapMonitorDock();
		CreateDataDock();
		CreateTaskFlowDock();
		CreateOrderDock();
		CreateInterfaceDock();
		CreateStrategyDock();
	}

	
	
	//CreateTaskMinitorDock();

	

	CreateLogDock();
	//

	

	create_status_bar();
	create_confidence_bar();
	create_process_bar();
	
	Singleton_ProtoBuf_Bag::get_mutable_instance().bind_process_bar(boost::bind(&kps_main_win::show_process,this,_1));
	Singleton_ProtoBuf_Bag_ex::get_mutable_instance().bind_process_bar(boost::bind(&kps_main_win::show_process,this,_1));
	SProcess_Bar pro_tmp;
	memset(&pro_tmp,0,sizeof(SProcess_Bar));
	ths_process_bar_ = pro_tmp;
	
	//sub playback log
	//PUB_PIPE_LOG
	SUB_PIPE_SH_POOL(PUB_LOG_PLAYBACK,boost::bind(&kps_main_win::update_pipe_log_playback,this,_1,_2,_3));

	

	run_timer();

	
}

kps_main_win::~kps_main_win()
{
	AGV_MANAGE.destruct();
}
map_scene* kps_main_win::get_scene()
{
	return map_scene_;
}
map_view* kps_main_win::get_view()
{
	return map_view_;
}
bool kps_main_win::Reg_sh_map(std::string sh_name,U32 dsize){
	if (!block_shared_pool::Reg_sh_range(sh_name,dsize))
	{
		return false;
	}
	if (!locker_shared_pool::reg_locker(sh_name + "_lock"))
	{
		return false;
	}

	return true;
};
void kps_main_win::create_rpc( bool b_init_core ){

	

	b_online_ = false;
	bool ok = true;
	para_ip_ = "127.0.0.1";
	//std::string para_ip_ = "192.168.1.99";
	//std::string para_ip_ = "106.12.90.152";
// 	QString qstr_ip = QInputDialog::getText(this, tr("Connect to robot ?"),
// 		tr("AGV ip:"), QLineEdit::Normal,
// 	//	tr("192.168.1.146"), &ok);
// 	tr("127.0.0.1"), &ok);
// 	//tr("192.168.1.99"), &ok);
// 	//tr("106.12.90.152"), &ok);
// 	if (ok && !qstr_ip.isEmpty()){
//	para_ip_ = qstr_ip.toStdString();
	
	ip_list_dlg *pDlg = new ip_list_dlg(); 
	pDlg->setModal(true); 
	//pDlg->set_map_list(v_map_list);
	pDlg->exec();

	pDlg->get_sel_file(para_ip_);

	SDelete(pDlg);
	if (cComm::Check_ip(para_ip_)){
	
		
		msg_shared_pool::init(std::string("kps_monitor"),b_init_core);
		pipe_shared_pool::init(std::string("kps_monitor"),b_init_core);
		block_shared_pool::init(std::string("kps_monitor"),b_init_core);
		locker_shared_pool::init(std::string("kps_monitor"),b_init_core);
		pub_view_data::init(std::string("kps_monitor"));

		b_online_ = true;
		
		SDelete(rpc_config_server_);

		RPC_CONFIG_CLIENT.init(para_ip_);

		TASK_XML_CLIENT.init(para_ip_);

	}else{
		
		b_online_ = false;

		rpc_config_server_ = new rpc_config_server();
		rpc_config_server_->init();

		//agv schedule sim
		if(b_init_core){

			msg_shared_pool::init(std::string("kps_monitor"),true);
			pipe_shared_pool::init(std::string("kps_monitor"),true);
			block_shared_pool::init(std::string("kps_monitor"),true);
			locker_shared_pool::init(std::string("kps_monitor"),true);

			Reg_sh_map(SHARED_AMCL_MAP,GLOBAL_MAP_SIZE);
			Reg_sh_map(SHARED_GLOBAL_INF_MAP,GLOBAL_MAP_SIZE);
			Reg_sh_map(SHARED_LASER_INF_MAP,LOCAL_MAP_SIZE);
			Reg_sh_map(SHARED_GLOBAL_LASER_INF_MAP,GLOBAL_MAP_SIZE);
			Reg_sh_map(SHARED_GLOBAL_PROHIBIT_INF_MAP,GLOBAL_MAP_SIZE);

			Reg_sh_map(SHARED_PROHIBIT_MAP,GLOBAL_MAP_SIZE);

			std::cout<<"init core!!!do agv schedule sim!!"<<std::endl;
		}else{

			msg_shared_pool::init(std::string("kps_monitor"));
			pipe_shared_pool::init(std::string("kps_monitor"));
			block_shared_pool::init(std::string("kps_monitor"));
			locker_shared_pool::init(std::string("kps_monitor"));
			pub_view_data::init(std::string("kps_monitor"));

			std::cout<<"do agv schedule sim without init core!!"<<std::endl;
		}

		RPC_CONFIG_CLIENT.init("127.0.0.1");
	}
	CREATE_MEM_GMAP("mem_show_map");
	CREATE_SHARED_GMAP(SHARED_AMCL_MAP);
	CREATE_SHARED_GMAP(SHARED_GLOBAL_PROHIBIT_INF_MAP);

	AGV_MANAGE.init();
	//TASK_MANAGE.init();

	char* argv[1];
	argv[0] = "kps_monitor";
	REG_POOL(argv);


	if (b_online_)
	{
		DATASERVER_XML_CLIENT.init(para_ip_,RPC_DATA_SER_PORT);
		connect_log_server();
		
	}
	Singleton_remote_para::get_mutable_instance().init();
}
void kps_main_win::CreateMenuDock()
{

	buttonGroup_ = new QButtonGroup(this);
	buttonGroup_->setExclusive(false);
	connect(buttonGroup_, SIGNAL(buttonClicked(int)),
		this, SLOT(buttonGroupClicked(int)));

// 	QPushButton* btu_device_status = new QPushButton();
// 	btu_device_status->setText(tr("Device\nstatus"));
// 	btu_device_status->setFixedSize(50,50);
// 	//btu_device_status->setFont(QFont("SansSerif", 24, QFont::Normal));
// 	buttonGroup_->addButton(btu_device_status, MTYPE::DEV_STA);
	
	
	QPushButton* btu_map = new QPushButton();
	btu_map->setText(tr("Mapping"));
	btu_map->setFixedSize(50,50);
	//btu_map->setFont(QFont("SansSerif", 24, QFont::Normal));
	buttonGroup_->addButton(btu_map, MTYPE::MAPPING);


	QPushButton* btu_reflector = new QPushButton();
	btu_reflector->setText(tr("Ref"));
	btu_reflector->setFixedSize(50,50);
	//btu_log_bag->setFont(QFont("SansSerif", 24, QFont::Normal));
	buttonGroup_->addButton(btu_reflector, MTYPE::REFLECTOR);

	QPushButton* btu_location = new QPushButton();
	btu_location->setText(tr("Loc"));
	btu_location->setFixedSize(50,50);
	//btu_location->setFont(QFont("SansSerif", 24, QFont::Normal));
	buttonGroup_->addButton(btu_location, MTYPE::LOCATION);

	QPushButton* btu_loop_closure = new QPushButton();
	btu_loop_closure->setText(tr("Loop\nClosure"));
	btu_loop_closure->setFixedSize(50,50);
	//btu_task->setFont(QFont("SansSerif", 24, QFont::Normal));
	buttonGroup_->addButton(btu_loop_closure, MTYPE::LOOP_CLOSURE);

	QPushButton* btu_log_bag = new QPushButton();
	btu_log_bag->setText(tr("Log"));
	btu_log_bag->setFixedSize(50,50);
	//btu_log_bag->setFont(QFont("SansSerif", 24, QFont::Normal));
	buttonGroup_->addButton(btu_log_bag, MTYPE::LOG_BAG);

	QPushButton* btu_project = new QPushButton();
	btu_project->setText(tr("Projcet"));
	btu_project->setFixedSize(50,50);
	//btu_task->setFont(QFont("SansSerif", 24, QFont::Normal));
	buttonGroup_->addButton(btu_project, MTYPE::PROJECT);


// 	QPushButton* btu_calib = new QPushButton();
// 	btu_calib->setText(tr("Calib"));
// 	btu_calib->setFixedSize(50,50);
// 	//btu_task->setFont(QFont("SansSerif", 24, QFont::Normal));
// 	buttonGroup_->addButton(btu_calib, MTYPE::CALIB);

	

	QPushButton* btu_init = new QPushButton();
	btu_init->setText(tr("Init"));
	btu_init->setFixedSize(50,50);
	//btu_task->setFont(QFont("SansSerif", 24, QFont::Normal));
	buttonGroup_->addButton(btu_init, MTYPE::INIT);

 	QPushButton* btu_tools = new QPushButton();
 	btu_tools->setText(tr("Tools"));
 	btu_tools->setFixedSize(50,50);
 	//btu_task->setFont(QFont("SansSerif", 24, QFont::Normal));
 	buttonGroup_->addButton(btu_tools, MTYPE::TOOLS);
	
	QVBoxLayout *layout = new QVBoxLayout;
	//layout->addWidget(btu_device_status);
	layout->addWidget(btu_map);
	layout->addWidget(btu_reflector);
	layout->addWidget(btu_location);
	layout->addWidget(btu_log_bag);
	layout->addWidget(btu_project);
	
	//layout->addWidget(btu_calib);
	//layout->addWidget(btu_loop_closure);
	//layout->addWidget(btu_init);
	layout->addWidget(btu_tools);
	layout->setAlignment(Qt::AlignTop);
	//layout->addWidget(new QLabel("Pointer"), 1, 0, Qt::AlignHCenter);

	
	/*layout->setMargin(0);
	layout->setSpacing(0);*/

	
	menu_widget_ = new QWidget;
	menu_widget_->setLayout(layout);

	menu_dock_ = new QDockWidget( tr("Menu"),this);
	menu_dock_->setFeatures(QDockWidget::NoDockWidgetFeatures);
//	menu_dock_->setAllowedAreas(Qt::AllDockWidgetAreas );
	menu_dock_->setWidget(menu_widget_);//
	menu_dock_->setMaximumWidth(60);
	addDockWidget(Qt::LeftDockWidgetArea, menu_dock_);

}
void kps_main_win::CreateDevMonitorDock()
{
	Dev_monitor_dlg* t_dlg = new Dev_monitor_dlg(this);
	t_dlg->init_timer();
	QHBoxLayout* t_layout = new QHBoxLayout();
	t_layout->addWidget(t_dlg);
	dev_widget_ = new QWidget;
	dev_widget_->setLayout(t_layout);

	dev_dock_ = new QDockWidget(tr("DevMonitor"),this);
	dev_dock_->setAllowedAreas(Qt::RightDockWidgetArea );
	dev_dock_->setWidget(dev_widget_);

	addDockWidget(Qt::RightDockWidgetArea, dev_dock_);
	//tabifiedDockWidgets(dev_dock_);
}

void kps_main_win::CreateMapMonitorDock()
{
	
	

	map_scene_ = new map_scene(this);
	map_scene_->bind_lab_event(boost::bind(&kps_main_win::show_status_bar,this,_1));
	map_scene_->bind_local_event(boost::bind(&item_collection::set_robot_est,item_,_1 ));
	map_scene_->bind_range_event(boost::bind(&item_collection::set_range_pos,item_,_1));
	map_scene_->bind_range_event(boost::bind(&action_collection::set_range_pos,action_,_1));
	map_scene_->bind_reflector_event(boost::bind(&item_collection::set_reflector_pos,item_,_1));
	map_scene_->bind_node_event(boost::bind(&item_collection::set_node_pos,item_,_1));
	map_scene_->bind_edge_event(boost::bind(&item_collection::link_edge_pos,item_,_1));
	map_scene_->bind_producer_event(boost::bind(&item_collection::set_producer_pos,item_,_1));
	map_scene_->bind_consumer_event(boost::bind(&item_collection::set_consumer_pos,item_,_1));
	map_scene_->bind_processer_event(boost::bind(&item_collection::set_processer_pos,item_,_1));
	map_scene_->bind_storage_event(boost::bind(&item_collection::set_storage_pos,item_,_1));
	map_scene_->bind_charge_event(boost::bind(&item_collection::set_charge_pos,item_,_1));
	map_scene_->bind_sel_event(boost::bind(&item_collection::multi_sel,item_,_1));
	map_scene_->bind_rect_event(boost::bind(&item_collection::set_rect_pos,item_,_1));
	map_scene_->bind_qrcod_event(boost::bind(&item_collection::set_qrcode_pos,item_,_1));

	map_dock_ = new QDockWidget(tr("Map"),this);
	//create map view
	QDialog* mv_dlg = new QDialog();
	manual_ctl_dlg* mc_dlg = new manual_ctl_dlg();
	mc_dlg->init();
	action_->bind_show_mv(boost::bind(&manual_ctl_dlg::show_btn,mc_dlg));

	map_view_ = new map_view();
	map_view_->setScene(map_scene_);
	if (data_manage_dlg_){
		data_manage_dlg_->init(map_scene_);
	}
	

	QPushButton* btn_cw_ = new QPushButton(tr("import"));
	QGridLayout* grid = new QGridLayout();
	grid->addWidget(map_view_,0,0,100,100);
	grid->addWidget(mc_dlg,2,0,6,2);
	mv_dlg->setLayout(grid);

	map_dock_->setWidget(mv_dlg);
	map_dock_->setAllowedAreas(Qt::RightDockWidgetArea);
	addDockWidget(Qt::RightDockWidgetArea, map_dock_);

	//map_dock_->hide();
	item_->show_map_rect();

	if (!b_agvs_){
		tabifyDockWidget(calib_dock_,map_dock_);
	}

	//CustomButton* cb = new CustomButton();
	//QGraphicsProxyWidget *pProxy = map_scene_->addWidget(cb);
	//pProxy->setFlag(QGraphicsItem::ItemIgnoresTransformations); 
}

void kps_main_win::CreateCalibrationDock()
{
 	calib_dlg_ = new Calib_dlg(this);
 	//calib_dlg_->init_timer();
	calib_dlg_->bind_lab_event(boost::bind(&kps_main_win::show_status_bar,this,_1));

 	QHBoxLayout* t_layout = new QHBoxLayout();
 	t_layout->addWidget(calib_dlg_);
 	calib_widget_ = new QWidget;
 	calib_widget_->setLayout(t_layout);


	calib_dock_ = new QDockWidget(tr("Calib"),this);
	calib_dock_->setAllowedAreas(Qt::RightDockWidgetArea );
	calib_dock_->setWidget(calib_widget_);

	
	addDockWidget(Qt::RightDockWidgetArea, calib_dock_);

	//tabifiedDockWidgets(calib_dock_);
	
}

void kps_main_win::CreateActionTrayDock()
{

}

void kps_main_win::buttonGroupClicked(int type){

	QList<QAbstractButton *> buttons = buttonGroup_->buttons();
	foreach (QAbstractButton *button, buttons) {
		if (buttonGroup_->button(type) != button)
			button->setChecked(false);
	}
	switch((MTYPE)type){
		// 		case QtType::ITEM_TASK_LIST:
// 	case MTYPE::DEV_STA:
// 		sel_dev_dock();
// 		action_->clear_all_menu();
// 		action_->sel_file_acton();
// 		std::cout<<"select dev status menu!"<<std::endl;
// 		break;
	case MTYPE::MAPPING:
		action_->clear_all_menu();
		//action_->sel_file_acton();
		action_->sel_map_acton();

		std::cout<<"select mapping menu!"<<std::endl;
		break;
	case MTYPE::LOCATION:
		action_->clear_all_menu();
		action_->sel_location();
		action_->sel_show_log();
	
		break;
	case MTYPE::LOG_BAG:
		action_->clear_all_menu();
		action_->sel_log_bag();

		break;
	case MTYPE::REFLECTOR:
		action_->clear_all_menu();
		action_->sel_reflector();

		break;
	case MTYPE::PROJECT:
		action_->clear_all_menu();
		action_->sel_project();

		break;
	case MTYPE::CALIB:
		action_->clear_all_menu();
		action_->sel_calib();

		break;
	case MTYPE::LOOP_CLOSURE:
		action_->clear_all_menu();
		action_->sel_loop_closure();

		break;
	case MTYPE::INIT:
		action_->clear_all_menu();
		action_->sel_init();

		break;
	case MTYPE::TOOLS:
		action_->clear_all_menu();
		action_->sel_tools();
		action_->sel_move();
		action_->sel_show_log();
		break;
	default:
		break;
	}
	
}

void kps_main_win::create_status_bar()
{
	lab_status_ = new QLabel; 
	lab_status_->setMinimumSize(lab_status_->sizeHint()); 
	lab_status_->setAlignment(Qt::AlignLeft); 
	lab_status_->setObjectName("lab_status");

	statusBar()->addWidget(lab_status_,Qt::AlignLeft);
}
void kps_main_win::create_process_bar(){

	process_bar_ = new QProgressBar(this);
	process_bar_->setVisible(false);
	//empty_lab for separate
	QLabel *empty_lab = new QLabel;
	statusBar()->addWidget(empty_lab);

	statusBar()->addWidget(process_bar_,Qt::AlignRight);
}

void kps_main_win::show_status_bar(std::string str_msg)
{
	//std::string str_msg;
	QString qstr( str_msg.c_str() );
	lab_status_->setText(qstr);
}
void kps_main_win::show_confidence_bar( const SAMCL_CONFIDENCE &ac )
{
	
	if( ac.b_amcl_confidence_ ){
		QPalette pa;
		pa.setColor(QPalette::WindowText,Qt::green);
		//pa.setColor(QPalette::Background,Qt::gray);
		lab_confidence_->setPalette(pa);
	}else{
		QPalette pa;
		pa.setColor(QPalette::WindowText,Qt::red);
		//pa.setColor(QPalette::Background,Qt::gray);
		lab_confidence_->setPalette(pa);
	}
	std::stringstream ss;
	ss<<"ac:"<<ac.amcl_confidence_;

	QString qstr( ss.str().c_str() );
	lab_confidence_->setText(qstr);
}
void kps_main_win::show_rconfidence_bar( const SPOS_CONFIDENCE &ac )
{

	if( ac.confidence_.b_amcl_confidence_ ){
		QPalette pa;
		pa.setColor(QPalette::WindowText,Qt::green);
		//pa.setColor(QPalette::Background,Qt::gray);
		lab_confidence_->setPalette(pa);
	}else{
		QPalette pa;
		pa.setColor(QPalette::WindowText,Qt::red);
		//pa.setColor(QPalette::Background,Qt::gray);
		lab_confidence_->setPalette(pa);
	}
	std::stringstream ss;
	ss<<"[ac:"<<ac.confidence_.amcl_confidence_ <<"]";

	QString qstr( ss.str().c_str() );
	lab_confidence_->setText(qstr);
}
void kps_main_win::CreateLogDock()
{
	log_browser_ = new QTextBrowser();
	QDockWidget *log_dock = new QDockWidget(tr("Console"), this);
	log_browser_->document()->setMaximumBlockCount(500);
	log_browser_->document()->setIndentWidth(0);
	log_dock->setWidget(log_browser_);

	addDockWidget(Qt::BottomDockWidgetArea, log_dock);
	log_dock->setMaximumHeight(200);
	log_dock->setMinimumHeight(100);
	log_dock->maximumHeight();
	//tabifiedDockWidgets(log_dock);


	Dev_monitor_dlg* t_dlg = new Dev_monitor_dlg(this);
	t_dlg->init_timer();
	QHBoxLayout* t_layout = new QHBoxLayout();
	t_layout->addWidget(t_dlg);
	dev_widget_ = new QWidget;
	dev_widget_->setLayout(t_layout);

	dev_dock_ = new QDockWidget(tr("DevMonitor"),this);
	dev_dock_->setAllowedAreas(Qt::BottomDockWidgetArea );
	dev_dock_->setWidget(dev_widget_);
	addDockWidget(Qt::BottomDockWidgetArea, dev_dock_);


	action_dlg_ = new action_monitor_dlg(this);

	action_dock_ = new QDockWidget(tr("ActionMonitor"),this);
	action_dock_->setAllowedAreas(Qt::BottomDockWidgetArea );
	action_dock_->setWidget(action_dlg_);
	addDockWidget(Qt::BottomDockWidgetArea, action_dock_);


	dio_dlg_ = new dio_dlg(this);
	dio_dlg_->init(map_scene_);
	dio_dock_= new QDockWidget(tr("DioMonitor"),this);
	dio_dock_->setAllowedAreas(Qt::BottomDockWidgetArea );
	dio_dock_->setWidget(dio_dlg_);
	addDockWidget(Qt::BottomDockWidgetArea, dio_dock_);

	if (b_agvs_){



		agv_manage_dlg_ = new agv_manage_dlg(this);
		agv_manage_dlg_->init(map_scene_);

		agv_manage_dock_= new QDockWidget(tr("AgvManage"),this);
		agv_manage_dock_->setAllowedAreas(Qt::BottomDockWidgetArea );
		agv_manage_dock_->setWidget(agv_manage_dlg_);

		tabifyDockWidget(dev_dock_,log_dock);
		tabifyDockWidget(log_dock,action_dock_);
		tabifyDockWidget(action_dock_,dio_dock_);
		tabifyDockWidget(dio_dock_,agv_manage_dock_);
	}else{
		tabifyDockWidget(dev_dock_,log_dock);
		tabifyDockWidget(log_dock,action_dock_);
		tabifyDockWidget(action_dock_,dio_dock_);
	}
	
	dev_dock_->raise();
}
void kps_main_win::slot_print_log(std::string str)
{
// 	if ( log_browser_->document()->blockCount() > 500 )
// 	{
// 		log_browser_->clear();
// 	}

	//QDateTime current_date_time =QDateTime::currentDateTime();
	//QString current_date =current_date_time.toString("yyyy-MM-dd-hh:mm:ss:zzz");
	//log_browser_->append(current_date);
	log_browser_->append(QString::fromStdString(str));
	//log_browser_->moveCursor(QTextCursor::End);
	
}

void kps_main_win::connect_log_server()
{
	cConnPara conn_para;
	conn_para.m_iType = cConnPara::NETWORK;
	conn_para.m_nNetType = cConnPara::TCPCLIENT;
	conn_para.m_nRemoteIP = para_ip_;
	conn_para.m_nRemotePort = LOG_MONITOR_PORT;

	tcp_log_client_ = cTransferDevice::GetInstance(conn_para);
	pt_log_.size_controller().resize(1);
	pt_log_.schedule(boost::bind(&kps_main_win::th_log_client,this));
}
bool kps_main_win::merge_data(std::string &str,char* p_data,const int &ilen){
	// 3 status
	// 1: <head insert
	// 2: >end merge
	// 3: mid data
	str = "";

	if (ilen < 1)
	{
		return false;
	}
	if (p_data[0] == CH_LOG_HEAD)
	{
		//whole body
		if (p_data[ilen - 1] == CH_LOG_TAIL) //62 '>'
		{
			cComm::Char2String(str,(U8*)(p_data));
			str_merge_str_ = "";
			return true;
		}else{//only head
			std::string str_tmp;
			cComm::Char2String(str_tmp,(U8*)(p_data));
			str_merge_str_ += str_tmp;
			str = str_merge_str_;
			return false;
		}
		//only tail
	}else if(p_data[ilen - 1] == CH_LOG_TAIL){
		std::string str_tmp;
		cComm::Char2String(str_tmp,(U8*)(p_data));
		str = str_merge_str_ + str_tmp;
		str_merge_str_ = "";
		return true;
	}else{//only body
		std::string str_tmp;
		cComm::Char2String(str_tmp,(U8*)(p_data));
		str_merge_str_ += str_tmp;
		return false;
	}

}
void kps_main_win::th_log_client()
{
	th_log_run_ = 1;
	char* p_data = new char[MAX_TCP_LOG_DATA_SIZE];
	memset(p_data,0,MAX_TCP_LOG_DATA_SIZE);
	int ilen = 0;
	std::string str;
	int itime = 0;


	while(th_log_run_() == 1){

		if (tcp_log_client_ && tcp_log_client_->m_Status.IsOpen())
		{
			tcp_log_client_->ReadData((U8*)p_data,ilen,-1,0);
			if ( (ilen > 0 ) && (ilen < MAX_TCP_LOG_DATA_SIZE))
			{
				if (b_show_log_)
				{
					if (merge_data(str,p_data,ilen))
					{
						std::vector<std::string> v_res;
						cComm::SplitString(str,">",v_res);

						std::vector<std::string>::iterator it = v_res.begin();
						for ( ; it != v_res.end() ; ++it){

							
							//int err=sscanf((*it).c_str(),"<%d %s %s |%s %s|: %s",&itime,ch_1,ch_2,ch_pri,ch_pro,ch_m);
// 							if (err  != 1)
// 							{
// 								
// 							}
							mubuf_log_.put(*it);
						}


					}
					
				}
				memset(p_data,0,MAX_TCP_LOG_DATA_SIZE);
				SLEEP(20);
			}else{
				SLEEP(100);
			}
			
			
		}else{

			SLEEP(500);
			std::cout<<"tcp_log_client connection err!"<<std::endl;
		}
	}
}

void kps_main_win::show_log()
{
	if (!b_show_log_)
	{
		return;
	}
	std::string str;
	while ( mubuf_log_.size() > 0)
	{
		mubuf_log_.get(str);
		//pro_priority_filter(str);
		slot_print_log(str);
	}
}

void kps_main_win::set_show_log()
{
	b_show_log_ = !b_show_log_;
}

void kps_main_win::clear_show_log()
{
	log_browser_->clear();
}

void kps_main_win::timerEvent( QTimerEvent *event )
{
	item_->time_event(b_online_);
	

	

	SAMCL_ENTROPY ae;
	if(Singleton_XML_Client::get_mutable_instance().get_amcl_entropy(ae)){
		show_entropy_bar(ae);
	}

	if (item_->v_ref_conf_.size() > 0 ){
		show_rconfidence_bar(item_->v_ref_conf_[0]);
		item_->v_ref_conf_.clear();
	}else{
		SAMCL_CONFIDENCE ac;
		if(Singleton_XML_Client::get_mutable_instance().get_amcl_confidence(ac)){
			show_confidence_bar(ac);
		}
	}

	SProcess_Bar pro_bar;
	// 	if(Singleton_XML_Client::get_mutable_instance().do_get_process_bar(pro_bar,"")){
	// 		//std::cout<<"process bar:"<<pro_bar.name_<<" icurrent:"<<pro_bar.current_step_<<" imax:"<<pro_bar.max_step_<<std::endl;
	// 	}else{
	// 		pro_bar = ths_process_bar_();
	// 	}
	pro_bar = ths_process_bar_();
	std::string str_nm = pro_bar.name_;
	show_process(str_nm,pro_bar.current_step_,pro_bar.max_step_);

	show_log();

	//show_action();
}
void kps_main_win::run_timer()
{
	if (!timer_id_)
		timer_id_ = startTimer(1000/10);
}

void kps_main_win::stop_timer()
{
	if (timer_id_ != 0)
	{
		killTimer(timer_id_);
		timer_id_ = 0;
	}
}

void kps_main_win::show_process(const std::string &str_nm,const int &icount ,const int &itotal){

	if(itotal == 0){
		process_bar_->setMaximum(itotal);  
		process_bar_->setValue(icount); 
		process_bar_->setVisible(false);
		return;
	}
	std::stringstream ss;
	ss<<str_nm<<":%p%";
	QString qs = QString::fromStdString(ss.str());

	process_bar_->setFormat(qs);
	process_bar_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);  
	process_bar_->setVisible(true);
	if ( icount < itotal)
	{
		process_bar_->setMinimum(0);  
		process_bar_->setMaximum(itotal);  
		process_bar_->setValue(icount);  
		process_bar_->setVisible(true);
		b_show_pro_ = true;

	}else{
		process_bar_->setMaximum(itotal);  
		process_bar_->setValue(icount); 

		if(b_show_pro_){
			QMessageBox *tips = new QMessageBox(QMessageBox::NoIcon,"ProcessBar",QString::fromStdString(str_nm),QMessageBox::Ok | QMessageBox::Default,0);

			tips->show();
			b_show_pro_ = false;
		}
		process_bar_->setVisible(false);
	}
}

void kps_main_win::show_process(SProcess_Bar pro_bar)
{
	ths_process_bar_ = pro_bar;
}


void kps_main_win::create_confidence_bar()
{
	lab_entropy_ = new QLabel; 
	lab_entropy_->setMinimumSize(lab_entropy_->sizeHint()); 
	lab_entropy_->setAlignment(Qt::AlignLeft); 
	lab_entropy_->setObjectName(tr("lab_entropy"));

	statusBar()->addWidget(lab_entropy_,Qt::AlignLeft);

	lab_confidence_ = new QLabel; 
	lab_confidence_->setMinimumSize(lab_confidence_->sizeHint()); 
	lab_confidence_->setAlignment(Qt::AlignLeft); 
	lab_confidence_->setObjectName(tr("lab_confidence"));

	statusBar()->addWidget(lab_confidence_,Qt::AlignLeft);

	
	
}

void kps_main_win::show_entropy_bar(const SAMCL_ENTROPY &ae)
{
	if( ae.b_amcl_entropy_ ){
		QPalette pa;
		pa.setColor(QPalette::WindowText,Qt::green);
		//pa.setColor(QPalette::Background,Qt::gray);
		lab_entropy_->setPalette(pa);
	}else{
		QPalette pa;
		pa.setColor(QPalette::WindowText,Qt::red);
		//pa.setColor(QPalette::Background,Qt::gray);
		lab_entropy_->setPalette(pa);
	}
	std::stringstream ss;
	ss<<"ae:"<<ae.amcl_entropy_;

	QString qstr( ss.str().c_str() );
	lab_entropy_->setText(qstr);
}

std::string kps_main_win::get_ip()
{
	return para_ip_;
}

void kps_main_win::remove_agv()
{
	if (agv_manage_dlg_){
		agv_manage_dlg_->remove_agv();
	}
	
}

void kps_main_win::clear_show_bag()
{
	item_->clear_bag_item();
}

bool kps_main_win::update_pipe_log_playback( std::string name,U8* data,U32 len )
{
	std::string str_log;
	cComm::Char2String(str_log,data);
	mubuf_log_.put(str_log);
	return true;
}

void kps_main_win::show_action()
{
	std::vector<task_feadback> v_feadback;
 	TASK_XML_CLIENT.get_feadback(-1,v_feadback);
	get_action()->set_tfb(v_feadback);

	return ;
 	std::vector<task_feadback>::iterator it = v_feadback.begin();
 	for ( ; it != v_feadback.end() ; ++it ){
 		task_feadback &tfb(*it);
 		std::cout<<"tfb id:"<<tfb.get_task_id()<<" sta:"<<tfb.get_status()<<" strsta:"<<tfb.get_str_status()<<std::endl;
 	}
}

action_monitor_dlg* kps_main_win::get_action()
{
	return action_dlg_;
}

void kps_main_win::CreateDataDock()
{

	data_manage_dlg_ = new data_manage_dlg(this);
	if (map_scene_){
		data_manage_dlg_->init(map_scene_);
	}
	

	data_manage_dock_ = new QDockWidget(tr("DataManage"),this);
	data_manage_dock_->setAllowedAreas(Qt::RightDockWidgetArea );
	data_manage_dock_->setWidget(data_manage_dlg_);


	addDockWidget(Qt::RightDockWidgetArea, data_manage_dock_);
	if (!b_agvs_){
		splitDockWidget(calib_dock_,data_manage_dock_,Qt::Horizontal);
	}else{
		splitDockWidget(map_dock_,data_manage_dock_,Qt::Horizontal);
	}
	
	//tabifyDockWidget(task_flow_dock_,data_manage_dock_);
}

void kps_main_win::CreateOrderDock()
{
	order_dlg_ = new order_dlg();
	order_dlg_->init(map_scene_);
	//order_dlg_->bind_lab_event(boost::bind(&kps_main_win::show_status_bar,this,_1));

// 	QHBoxLayout* t_layout = new QHBoxLayout();
// 	t_layout->addWidget(order_dlg_);
// 	tcontrol_widget_ = new QWidget;
// 	tcontrol_widget_->setLayout(t_layout);


	order_dock_ = new QDockWidget(tr("Order"),this);
	order_dock_->setAllowedAreas(Qt::RightDockWidgetArea );
	order_dock_->setWidget(order_dlg_);

	

 	addDockWidget(Qt::RightDockWidgetArea, order_dock_);
 	//splitDockWidget(task_flow_dock_,order_dock_,Qt::Horizontal);
 	tabifyDockWidget(task_flow_dock_,order_dock_);
	
}
void kps_main_win::CreateInterfaceDock()
{
	interface_dlg_ = new interface_dlg();
	interface_dlg_->init(map_scene_);

	interface_dock_ = new QDockWidget(tr("interface"),this);
	interface_dock_->setAllowedAreas(Qt::RightDockWidgetArea );
	interface_dock_->setWidget(interface_dlg_);

	addDockWidget(Qt::RightDockWidgetArea, interface_dock_);
	tabifyDockWidget(order_dock_,interface_dock_);
}
void kps_main_win::CreateStrategyDock()
{
	strategy_dlg_ = new strategy_dlg();
	strategy_dlg_->init(map_scene_);

	strategy_dock_ = new QDockWidget(tr("strategy"),this);
	strategy_dock_->setAllowedAreas(Qt::RightDockWidgetArea );
	strategy_dock_->setWidget(strategy_dlg_);

	addDockWidget(Qt::RightDockWidgetArea, strategy_dock_);
	tabifyDockWidget(interface_dock_,strategy_dock_);
}

void kps_main_win::CreateTaskFlowDock()
{
	task_flow_dlg_ = new task_flow_dlg(this);
	task_flow_dlg_->init(map_scene_);

	task_flow_dock_ = new QDockWidget(tr("task_flow"),this);
	task_flow_dock_->setAllowedAreas(Qt::RightDockWidgetArea );
	task_flow_dock_->setWidget(task_flow_dlg_);


	addDockWidget(Qt::RightDockWidgetArea, task_flow_dock_);
	//splitDockWidget(map_dock_,task_flow_dock_,Qt::Horizontal);
	tabifyDockWidget(map_dock_,task_flow_dock_);
}

// void kps_main_win::set_check_priority(bool b_check){
// 	th_check_priority_ = b_check;
// }
// void kps_main_win::pro_priority_filter(std::string &str)
// {
// 
// 	if( !th_check_priority_() ){
// 		return;
// 	}
// 
// 	int ipriority = log4cpp::Priority::INFO;
// 	std::string str_pro_nm = "";
// 	std::vector<std::string> v_res1;
// 	cComm::SplitString( str,"|",v_res1);
// 	if (v_res1.size() > 2)
// 	{
// 		std::vector<std::string> v_res2;
// 		cComm::SplitString( v_res1[1]," ",v_res2);
// 		if (v_res2.size() > 1)
// 		{
// 			if (fnc_show_priority_)
// 			{
// 				fnc_show_priority_(v_res2[1],v_res2[0]);
// 			}
// 			
// 		}
// 	}
// }

// void kps_main_win::bind_show_priority(boost::function<void(const std::string &str_pro_nm, const std::string &str_priority)> fnc)
// {
// 	fnc_show_priority_ = fnc;
// }

// {
// 	HANDLE handle;
// 	WORD wOldColorAttrs, wAttributes;
// 	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
// 	handle = GetStdHandle(STD_OUTPUT_HANDLE);
// 	GetConsoleScreenBufferInfo(handle, &csbiInfo);
// 	wOldColorAttrs = csbiInfo.wAttributes;
// 	switch (color)
// 	{
// 	case red:
// 		wAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
// 		break;
// 	case green:
// 		wAttributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
// 		break;
// 	case blue:
// 		wAttributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
// 		break;
// 	case white:
// 		wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
// 		break;
// 	case yellow:
// 		wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
// 		break;
// 	case purple:
// 		wAttributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
// 		break;
// 	default:
// 		wAttributes = wOldColorAttrs;
// 		break;
// 	}
// 	SetConsoleTextAttribute(handle, wAttributes);
// 
// 	memset(buff_, 0, Buff_SIZE);
// 	if (fmt == nullptr)
// 	{
// 		sprintf_s(buff_, Buff_SIZE, "log_warning_color: fmt is NULL");
// 	}
// 	else
// 	{
// 		va_list args;
// 		va_start(args, fmt);
// 		_vsnprintf_s(buff_, Buff_SIZE, Buff_SIZE, fmt, args);
// 		va_end(args);
// 	}
// 
// 	if (log_initialized_)
// 	{
// 		BOOST_LOG_SEV(lg, warning) << buff_;
// 	}
// 	else
// 	{
// 		std::cout << buff_ << std::endl;
// 	}
// 	print_sink_signal_(buff_, color);
// 
// 	SetConsoleTextAttribute(handle, wOldColorAttrs);
// }



