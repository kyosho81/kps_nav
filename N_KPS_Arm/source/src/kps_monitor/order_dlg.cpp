
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
#include "order_table.h"

#include "order_dlg.h"

order_dlg::order_dlg( QWidget *parent)
{
	timer_ = 0;
	b_accepte_order_ = true;

	role_table_ = 0 ;
	i_scene_show_cnt_ = 0;
}

order_dlg::~order_dlg()
{
	
}
void order_dlg::bind_lab_event( qt_eve::mouse_event::Slot_Lab event_slot )
{
	map_scene_->bind_lab_event(event_slot);
}

void order_dlg::init_timer()
{
	if (!timer_){
		timer_ = new QTimer(this);
		timer_->setInterval(100);
		connect(timer_, SIGNAL(timeout()), this, SLOT(time_accepte_order()));
		timer_->start();
	}else{
		timer_->stop();
		SDelete(timer_);
	}
	

	
}

void order_dlg::init( map_scene* map_scene ){

	assert(map_scene);
	map_scene_ = map_scene;

	role_table_ = new role_table(this);
	order_run_table_ = new order_table(this);
//	order_his_table_ = new order_table(this);
//	map_view_->zoom(25);
//	map_view_->centerOn(0,0);
//	
	
	QSplitter *pSplitter = new QSplitter(Qt::Orientation::Vertical, this);

 	QGridLayout* grid = new QGridLayout();


	pSplitter->addWidget(role_table_);
	pSplitter->addWidget(order_run_table_);

	b_run_hist_ = true;
	
	btn_run_order_ = new QRadioButton(tr("run_order"));
	btn_his_order_ = new QRadioButton(tr("history_order"));
 	btn_accepte_order_ = new QPushButton(tr("RefuseOrder")); 
	btn_run_order_->setChecked(true);

	connect(btn_run_order_,SIGNAL(toggled(bool)),this,SLOT(ChooseRunHis(bool)));
	//connect(btn_his_order_,SIGNAL(toggled(bool)),this,SLOT(ChooseRunHis(bool)));
	connect(btn_accepte_order_, SIGNAL(clicked(bool)), this, SLOT(ChooseAccepteOrder(bool)));

	//grid->addWidget(role_table_,0,0,3,10);
	//grid->addWidget(order_run_table_,4,0,3,10);
	grid->addWidget(pSplitter,0,0,13,10);

 	grid->addWidget(btn_run_order_,14,0,1,1);
 	grid->addWidget(btn_his_order_,14,1,1,1);
  	grid->addWidget(btn_accepte_order_,14,2,1,8);
// 	QHBoxLayout *pHBox = new QHBoxLayout(this);
// 	pHBox->addWidget(btn_run_order_);
// 	pHBox->addWidget(btn_his_order_);
// 	pHBox->addWidget(btn_accepte_order_);

	
	
 	
// 	QVBoxLayout* v1 = new QVBoxLayout();
// 	v1->addWidget(pSplitter);
// 	v1->addWidget(btn_run_order_);
// 	v1->addWidget(btn_his_order_);
// 	v1->addWidget(btn_accepte_order_);
// 
// 	v1->addWidget(role_table_);
// 	v1->addWidget(order_run_table_);
// 	v1->addWidget(order_his_table_);
// 
// 	v1->addLayout(grid);

	setLayout(grid);

	init_timer();

}

// void order_dlg::ChooseConnection( bool flag )
// {
// 	//init_timer();
// 	return ;
	//create_test_body_on_path_both();
// 	
// 	create_test_body_on_path_circle();
// 	
// 	TRAFFIC_CONTROL.set_data(m_agv_status_,m_agv_info_,m_run_path_,m_robot_shape_);
// 	TRAFFIC_CONTROL.do_traffic_control();
// 
// 	update_agv_item(TRAFFIC_CONTROL.get_agv_raw_show() );
// 	show_map(TRAFFIC_CONTROL.get_global_map() );
//}

void order_dlg::time_accepte_order()
{
	std::multimap< std::string, protobuf_base*> mm_roles;
	SM_FACTORY.run_sm(mm_roles);
	
	
	if (b_run_hist_){
		std::list<order_schedule*> run_order = TASK_FACTORY.get_run_order();
		order_run_table_->show_order_list(run_order);
	}else{
		std::list<order_schedule*> hist_order = TASK_FACTORY.get_his_order();
		order_run_table_->show_order_list(hist_order);
	}
	
	//order_his_table_->show_order_list(hist_order);

	role_table_->show_role_list(mm_roles);

	if (i_scene_show_cnt_ == 0){
		map_scene_->update_item();
		i_scene_show_cnt_ = 5;
	}else{
		i_scene_show_cnt_--;
	}
 	
}

void order_dlg::ChooseRunHis(bool flag)
{
	if (btn_run_order_->isChecked()){
		b_run_hist_ = true;
		return;
	}
	if (btn_his_order_->isChecked()){
		b_run_hist_ = false;
		return;
	}
}

void order_dlg::ChooseAccepteOrder( bool flag )
{
	b_accepte_order_ = !b_accepte_order_;
 	if ( b_accepte_order_ ){

 		btn_accepte_order_->setText(tr("RefuseOrder"));
 	}else{
 		btn_accepte_order_->setText(tr("AcceptOrder"));
 	}
 	
	init_timer();
}

// 
// 
// void order_dlg::init_test_data()
// {
// 	
// 	SVec vp;
// 	vp.x_ = 0.5 ;
// 	vp.y_ = 0.3;
// 	v_shape_.push_back(vp);
// 	vp.x_ = -0.4 ;
// 	vp.y_ = 0.3;
// 	v_shape_.push_back(vp);
// 	vp.x_ = -0.4 ;
// 	vp.y_ = -0.3;
// 	v_shape_.push_back(vp);
// 	vp.x_ = 0.5 ;
// 	vp.y_ = -0.3;
// 	v_shape_.push_back(vp);
// 	vp.x_ = 0.5 ;
// 	vp.y_ = 0.3;
// 	v_shape_.push_back(vp);
// 
// 	m_agv_status_.clear();
// 	m_agv_info_.clear();
// 	m_run_path_.clear();
// 	m_robot_shape_.clear();
// }
// 
// void order_dlg::create_test_data(int id, SPos pos_f, SPos pos_m , SPos pos_t)
// {
// 	m_robot_shape_[id] = v_shape_;
// 
// 	SAGV_Info ai;
// 	memset(&ai,0,sizeof(SAGV_Info));
// 	ai.id_ = id;
// 	m_agv_status_[id] = ai;
// 
// 
// 	SRobot_Inf ri;
// 	memset(&ri,0,sizeof(SRobot_Inf));
// 	m_agv_info_[id] = ri;
// 	m_agv_info_[id].amcl_pos_ = pos_f;
// 
// 	m_robot_shape_[id] = v_shape_;
// 
// 	std::list<SPathData> suro_path;
// 	SPathData sd;
// 	memset(&sd,0,sizeof(SPathData));
// 	sd.tn_from_.x_ = pos_f.x_ ; 
// 	sd.tn_from_.y_ = pos_f.y_ ; 
// 	sd.tn_to_.x_ = pos_m.x_ ; 
// 	sd.tn_to_.y_ = pos_m.y_ ; 
// 	suro_path.push_back(sd);
// 	sd.tn_from_.x_ = pos_m.x_ ;
// 	sd.tn_from_.y_ = pos_m.y_ ; 
// 	sd.tn_to_.x_ = pos_t.x_ ; 
// 	sd.tn_to_.y_ = pos_t.y_ ; 
// 	suro_path.push_back(sd);
// 
// 	m_run_path_[id] = suro_path;
// 
// }
// 
// void order_dlg::create_test_body_on_path_both()
// {
// 	init_test_data();
// 	SPos pos_f;
// 	SPos pos_m;
// 	SPos pos_t;
// 	pos_f.x_ = 0;
// 	pos_f.y_ = 0;
// 	pos_f.th_ = Deg2Rad(0);
// 	pos_m.x_ = 5;
// 	pos_m.y_ = 0;
// 	pos_t.x_ = 5;
// 	pos_t.y_ = 3;
// 	create_test_data(1,pos_f,pos_m,pos_t);
// 
// 	pos_f.x_ = 3;
// 	pos_f.y_ = 0;
// 	pos_f.th_ = Deg2Rad(0);
// 	pos_m.x_ = -1;
// 	pos_m.y_ = 0;
// 	pos_t.x_ = -1;
// 	pos_t.y_ = 2;
// 	create_test_data(2,pos_f,pos_m,pos_t);
// }
// 
// void order_dlg::create_test_path_on_path()
// {
// 	init_test_data();
// 	SPos pos_f;
// 	SPos pos_m;
// 	SPos pos_t;
// 	pos_f.x_ = 0;
// 	pos_f.y_ = 0;
// 	pos_f.th_ = Deg2Rad(0);
// 	pos_m.x_ = 5;
// 	pos_m.y_ = 0;
// 	pos_t.x_ = 5;
// 	pos_t.y_ = 3;
// 	create_test_data(1,pos_f,pos_m,pos_t);
// 
// 	pos_f.x_ = 3;
// 	pos_f.y_ = -2;
// 	pos_f.th_ = Deg2Rad(0);
// 	pos_m.x_ = 3;
// 	pos_m.y_ = 4;
// 	pos_t.x_ = 6;
// 	pos_t.y_ = 4;
// 	create_test_data(2,pos_f,pos_m,pos_t);
// }
// 
// 
// void order_dlg::create_test_body_on_path_circle()
// {
// 	init_test_data();
// 	SPos pos_f;
// 	SPos pos_m;
// 	SPos pos_t;
// 	pos_f.x_ = 0;
// 	pos_f.y_ = 0;
// 	pos_f.th_ = Deg2Rad(0);
// 	pos_m.x_ = 3;
// 	pos_m.y_ = 0;
// 	pos_t.x_ = 3;
// 	pos_t.y_ = 1;
// 	create_test_data(1,pos_f,pos_m,pos_t);
// 
// 	pos_f.x_ = 3;
// 	pos_f.y_ = 1;
// 	pos_f.th_ = Deg2Rad(0);
// 	pos_m.x_ = 0;
// 	pos_m.y_ = 1;
// 	pos_t.x_ = 0;
// 	pos_t.y_ = 0;
// 	create_test_data(2,pos_f,pos_m,pos_t);
// }
