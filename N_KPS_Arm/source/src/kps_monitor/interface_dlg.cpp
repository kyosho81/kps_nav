
#include <QDebug>
#include "interpro_shared/sh_pool.hpp"
#include "robot/RobotStruct.h"
#include "interface/xml_rpc_client.h"

#include "scene/map_view.h"
#include "scene/map_scene.h"
#include "scene/mouse_event.h"
#include "scene/map_item.h"
#include "scene/agv_item.h"

#include "robot/Geometry.h"
#include "Comm/Comm.h"
#include "dispatching/traffic_control.h"
#include "mapserver/MapServer.h"

#include "protobuf_msg/state_machine_factory.h"
#include "role_table.h"
#include "dispatching/order_factory.h"
#include "dispatching/task_factory.h"
#include "dispatching/manual_order.h"
#include "dispatching/manual_para_def.h"
#include "interface_model.h"

#include "interface_table.h"
#include "manual_table.h"

#include "interface_dlg.h"

interface_dlg::interface_dlg( QWidget *parent)
{
	timer_ = 0;

	interface_table_ = 0;
}

interface_dlg::~interface_dlg()
{
	
}
void interface_dlg::bind_lab_event( qt_eve::mouse_event::Slot_Lab event_slot )
{
	map_scene_->bind_lab_event(event_slot);
}

void interface_dlg::init_timer()
{
	if (!timer_){
		timer_ = new QTimer(this);
		timer_->setInterval(1000);
		connect(timer_, SIGNAL(timeout()), this, SLOT(time_show_manual()));
		timer_->start();
	}else{
		timer_->stop();
		SDelete(timer_);
	}
	

	
}

void interface_dlg::init( map_scene* map_scene ){

	assert(map_scene);
	map_scene_ = map_scene;

	
//	map_view_->zoom(25);
//	map_view_->centerOn(0,0);
// 
 	QGridLayout* grid = new QGridLayout();
// 
// 	//grid->addWidget(create_para_wiget(),0,0);
// 
 	btn_new_order_ = new QPushButton(tr("New")); 
	connect(btn_new_order_, SIGNAL(clicked(bool)), this, SLOT(ChooseNewOrder(bool)));
 
	btn_del_order_ = new QPushButton(tr("Del")); 
	connect(btn_del_order_, SIGNAL(clicked(bool)), this, SLOT(ChooseDelOrder(bool)));

	btn_create_cmd_ = new QPushButton(tr("Create_CMD")); 
	connect(btn_create_cmd_, SIGNAL(clicked(bool)), this, SLOT(ChooseCreateCMD(bool)));

	btn_commit_ = new QPushButton(tr("Commit")); 
	connect(btn_commit_, SIGNAL(clicked(bool)), this, SLOT(ChooseCommit(bool)));


	interface_table_ = new interface_table();
	manual_table_ = new manual_table();

 	grid->addWidget(interface_table_,0,0,3,10);
// 	grid->addWidget(order_run_table_,4,0,3,10);
// 	grid->addWidget(order_his_table_,7,0,6,10);
  	grid->addWidget(btn_new_order_,14,0,1,1);
	grid->addWidget(btn_del_order_,14,1,1,1);
	grid->addWidget(btn_create_cmd_,14,2,1,1);
	grid->addWidget(btn_commit_,14,3,1,1);
	grid->addWidget(manual_table_,15,0,1,10);
// 	QVBoxLayout* v1 = new QVBoxLayout();
// 
// 	v1->addWidget(role_table_);
// 	v1->addWidget(order_run_table_);
// 	v1->addWidget(order_his_table_);
// 
// 	v1->addLayout(grid);

	setLayout(grid);
	
	init_timer();

}

void interface_dlg::time_show_manual()
{
	std::map<std::string ,manual_order*> m_manual_order_run;
	MANUAL_ORDER_FACTORY.get_manual_order(m_manual_order_run);
	manual_table_->show_manual_order(m_manual_order_run);
}

void interface_dlg::ChooseNewOrder( bool flag )
{
 	//manual_order* p_manual_order = new manual_order();
	std::map<std::string,std::string> m_para;
	m_para[MANUAL_ORDER_ID] = cTimerDiff::get_now();
	m_para[MANUAL_ORDER_FROM_ROLE] = PRODUCER_ITEM;
	m_para[MANUAL_ORDER_FROM_ROLE_ID] = cComm::ConvertToString(0);
	m_para[MANUAL_ORDER_TO_ROLE] = CONSUMER_ITEM;
	m_para[MANUAL_ORDER_TO_ROLE_ID] = cComm::ConvertToString(0);
	m_para[MANUAL_ORDER_AGV_GP_ID] = cComm::ConvertToString(1);
	m_para[MANUAL_ORDER_TIME] = cTimerDiff::get_now_ms() ;

	manual_order* p_manual = MANUAL_ORDER_FACTORY.new_manual_order(m_para);

	m_manual_order_tb_.insert(std::make_pair(p_manual->str_order_id_,p_manual));

	interface_table_->show_manual_order(m_manual_order_tb_);
}

void interface_dlg::ChooseDelOrder( bool flag )
{
	std::vector<std::string> v_del = interface_table_->del_sel_order();
	auto it = v_del.begin();
	for ( ; it != v_del.end() ; ++it ){
		m_manual_order_tb_.erase(*it);
	}
}

void interface_dlg::ChooseCreateCMD( bool flag )
{

}

void interface_dlg::ChooseCommit( bool flag )
{
	QVector<QStringList> qv_data = interface_table_->get_data();
	

	foreach (QStringList row, qv_data) {
		
		std::string str_id = row.at(COL_ORDER_ID).toStdString();
		
		auto it = m_manual_order_tb_.find(str_id);
		if ( it != m_manual_order_tb_.end() ){
			
			manual_order* p_manual = it->second;
			assert(p_manual->str_order_id_ == str_id) ;

			p_manual->str_from_role_ = row.at(COL_FROM_ROLE).toStdString();
			p_manual->str_from_role_gp_id_ = row.at(COL_FROM_ROLE_ID).toStdString();
			p_manual->str_to_role_ = row.at(COL_TO_ROLE).toStdString();
			p_manual->str_to_role_gp_id_ = row.at(COL_TO_ROLE_ID).toStdString();
			p_manual->str_agv_gp_id_ = row.at(COL_TO_AGV_ID).toStdString();
			p_manual->str_order_time_ = row.at(COL_ORDER_TIME).toStdString();
		}
		
	}
	
	
	
	std::vector<std::string> v_del = interface_table_->sel_order();
	auto it = v_del.begin();
	for ( ; it != v_del.end() ; ++it ){

		auto it2 = m_manual_order_tb_.find(*it);
		manual_order* p_manual = it2->second;
		p_manual->state_ = manual_order::MANUAL_COMMIT;
		MANUAL_ORDER_FACTORY.insert_manual_order(it2->second);
		
		m_manual_order_tb_.erase(*it);
	}

	interface_table_->show_manual_order(m_manual_order_tb_);

// 	std::map<std::string ,manual_order*> m_manual_order_run;
// 	MANUAL_ORDER_FACTORY.get_manual_order(m_manual_order_run);
// 	manual_table_->show_manual_order(m_manual_order_run);
}
