
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
#include "strategy_table.h"
#include "strategy_model.h"

#include "strategy_dlg.h"

strategy_dlg::strategy_dlg( QWidget *parent)
{
	timer_ = 0;

	str_file_ = ".//cfg//strategy.txt";
	strategy_table_ = 0 ;
}

strategy_dlg::~strategy_dlg()
{
	
}
void strategy_dlg::bind_lab_event( qt_eve::mouse_event::Slot_Lab event_slot )
{
	map_scene_->bind_lab_event(event_slot);
}

void strategy_dlg::init_timer()
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

void strategy_dlg::init( map_scene* map_scene ){

	assert(map_scene);
	map_scene_ = map_scene;

	strategy_table_ = new strategy_table(this);

	STRATEGY_FACTORY.load_file(str_file_);
	strategy_table_->show_strategy( STRATEGY_FACTORY.get_schedule_list() );
	
//	map_view_->zoom(25);
//	map_view_->centerOn(0,0);
// 
 	QGridLayout* grid = new QGridLayout();
// 
// 	//grid->addWidget(create_para_wiget(),0,0);
// 
	btn_new_ = new QPushButton(tr("New")); 
	connect(btn_new_, SIGNAL(clicked(bool)), this, SLOT(ChooseNew(bool)));
	btn_del_ = new QPushButton(tr("Del")); 
	connect(btn_del_, SIGNAL(clicked(bool)), this, SLOT(ChooseDel(bool)));
	btn_commit_ = new QPushButton(tr("Commit")); 
	connect(btn_commit_, SIGNAL(clicked(bool)), this, SLOT(ChooseCommit(bool)));

 	btn_load_ = new QPushButton(tr("Load")); 
	connect(btn_load_, SIGNAL(clicked(bool)), this, SLOT(ChooseLoadFile(bool)));
	btn_save_ = new QPushButton(tr("Save")); 
	connect(btn_save_, SIGNAL(clicked(bool)), this, SLOT(ChooseSaveFile(bool)));
	
 
	grid->addWidget(strategy_table_,0,0,3,10);
	
	grid->addWidget(btn_new_,14,0,1,1);
	grid->addWidget(btn_del_,14,1,1,1);
	grid->addWidget(btn_commit_,14,2,1,1);

 	grid->addWidget(btn_load_,14,4,1,1);
	grid->addWidget(btn_save_,14,5,1,1);
	

	setLayout(grid);


	init_timer();

}


void strategy_dlg::time_accepte_order()
{
// 	std::multimap< std::string, protobuf_base*> mm_roles;
// 	SM_FACTORY.run_sm(mm_roles);
// 	std::list<order_schedule*> run_order = TASK_FACTORY.get_run_order();
// 	std::list<order_schedule*> hist_order = TASK_FACTORY.get_his_order();
// 	order_run_table_->show_order_list(run_order);
// 	order_his_table_->show_order_list(hist_order);
// 
// 	role_table_->show_role_list(mm_roles);
 	
}
void strategy_dlg::ChooseLoadFile( bool flag )
{

	STRATEGY_FACTORY.load_file(str_file_);
	strategy_table_->show_strategy( STRATEGY_FACTORY.get_schedule_list() );
	QMessageBox::information(0, tr("strategy"), tr("strategy Loaded!"));
}

void strategy_dlg::ChooseSaveFile( bool flag )
{
	STRATEGY_FACTORY.save_file(str_file_);
	QMessageBox::information(0, tr("strategy"), tr("strategy Saved!"));
}

void strategy_dlg::ChooseCommit( bool flag )
{
	QVector<QStringList> qv_data = strategy_table_->get_data();
	

	std::vector<schedule_interface_data*> v_si_data;
	foreach (QStringList row, qv_data) {

		int i_index = row.at(COL_STRATEGY_ID).toInt();

		schedule_interface_data* p_si_data = new schedule_interface_data();
		if(p_si_data){

			p_si_data->init(i_index);
			p_si_data->set_activated(row.at(COL_STRATEGY_ENABLE).toInt());
			p_si_data->set_start_role(row.at(COL_STRATEGY_ROLE_FROM).toStdString());
			p_si_data->set_start_gp_id(row.at(COL_STRATEGY_FROM_GP).toStdString());
			p_si_data->set_output_type(row.at(COL_STRATEGY_OUTPUT).toStdString());
			p_si_data->set_end_role(row.at(COL_STRATEGY_ROLE_TO).toStdString());
			p_si_data->set_end_gp_id(row.at(COL_STRATEGY_TO_GP).toStdString());
			p_si_data->set_input_type(row.at(COL_STRATEGY_INPUT).toStdString());
			p_si_data->set_match_from_start(row.at(COL_STRATEGY_MATCH_ST).toInt());
			p_si_data->set_agv_gp_id(row.at(COL_STRATEGY_AGV_ID_GP).toStdString());
			p_si_data->set_priority(row.at(COL_STRATEGY_PRIORYTY).toStdString());
			p_si_data->set_task_flow(row.at(COL_STRATEGY_TASK_FLOW).toStdString());
			v_si_data.push_back(p_si_data);
		}

	}

	STRATEGY_FACTORY.insert_schedule_rules(v_si_data);

	strategy_table_->show_strategy( STRATEGY_FACTORY.get_schedule_list() );

	QMessageBox::information(0, tr("strategy"), tr("strategy Committed!"));
}

void strategy_dlg::ChooseNew( bool flag )
{
	STRATEGY_FACTORY.new_schedule_rules();
	strategy_table_->show_strategy( STRATEGY_FACTORY.get_schedule_list() );
}

void strategy_dlg::ChooseDel( bool flag )
{
	std::map<int, int> m_del = strategy_table_->sel_schedule();
	auto it = m_del.begin();
	for ( ; it != m_del.end() ; ++it ){
		STRATEGY_FACTORY.del_schedule_rules(it->first);
	}
	strategy_table_->show_strategy( STRATEGY_FACTORY.get_schedule_list() );
}
