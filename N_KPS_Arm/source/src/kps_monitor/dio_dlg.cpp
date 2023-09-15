
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
#include "dio_table.h"
#include "dio_model.h"

#include "dio_dlg.h"

dio_dlg::dio_dlg( QWidget *parent)
{
	timer_ = 0;

	str_file_ = ".//cfg//strategy.txt";
	//str_file_ = ".//cfg//io.txt";
	dio_table_ = 0 ;

	b_begin_ = false;
	timer_ = new QTimer(this);
	timer_->setInterval(100);
	connect(timer_, SIGNAL(timeout()), this, SLOT(time_get_dio_data()));
}

dio_dlg::~dio_dlg()
{
	
}

void dio_dlg::bind_lab_event( qt_eve::mouse_event::Slot_Lab event_slot )
{
	map_scene_->bind_lab_event(event_slot);
}


void dio_dlg::do_timer(bool b_begin)
{
	if (b_begin){
		std::cout<<"dio_dlg activated,refresh dio bind fnc!"<<std::endl;
		get_dio_bind();

		timer_->start();
	}else{
		timer_->stop();
	}
	
}

bool dio_dlg::get_dio_bind()
{
	if (DATASERVER_XML_CLIENT.get_dio_bind(m_dio_bind_)){
		dio_table_->show_dio_para(m_dio_bind_);
		return true;
	}
	return false;
}

void dio_dlg::init( map_scene* map_scene ){

	assert(map_scene);
	map_scene_ = map_scene;

	dio_table_ = new dio_table(this);

	//STRATEGY_FACTORY.load_file(str_file_);
	//dio_table_->show_dio( STRATEGY_FACTORY.get_schedule_list() );
	//dio_table_->show_dio();


 	QGridLayout* grid = new QGridLayout();


	
	btn_commit_ = new QPushButton(tr("Commit")); 
	connect(btn_commit_, SIGNAL(clicked(bool)), this, SLOT(ChooseCommit(bool)));

 	btn_load_ = new QPushButton(tr("Load")); 
	connect(btn_load_, SIGNAL(clicked(bool)), this, SLOT(ChooseLoadFile(bool)));
	btn_save_ = new QPushButton(tr("Save")); 
	connect(btn_save_, SIGNAL(clicked(bool)), this, SLOT(ChooseSaveFile(bool)));
	
 
	grid->addWidget(dio_table_,0,0,3,10);
	

	grid->addWidget(btn_commit_,14,0,1,1);

 	grid->addWidget(btn_load_,14,4,1,1);
	grid->addWidget(btn_save_,14,5,1,1);
	

	setLayout(grid);


}


void dio_dlg::time_get_dio_data()
{
	std::cout<<"time_get_dio_data !!!"<<std::endl;
 	std::vector<SDIO_NM_INDEX> v_data;
	DATASERVER_XML_CLIENT.get_dio_data(v_data);
// 	for ( int i = 0 ; i < 12 ; ++i){
// 		v_data.push_back(cTimerDiff::get_now());
// 	}
	std::cout<<"DATASERVER_XML_CLIENT.get_dio_data size:"<<v_data.size()<<std::endl;
	dio_table_->show_dio_data(v_data);
// 	std::multimap< std::string, protobuf_base*> mm_roles;
// 	SM_FACTORY.run_sm(mm_roles);
// 	std::list<order_schedule*> run_order = TASK_FACTORY.get_run_order();
// 	std::list<order_schedule*> hist_order = TASK_FACTORY.get_his_order();
// 	order_run_table_->show_order_list(run_order);
// 	order_his_table_->show_order_list(hist_order);
// 
// 	role_table_->show_role_list(mm_roles);
 	
}
void dio_dlg::ChooseLoadFile( bool flag )
{

	//STRATEGY_FACTORY.load_file(str_file_);
	
}

void dio_dlg::ChooseSaveFile( bool flag )
{
	//STRATEGY_FACTORY.save_file(str_file_);
}

void dio_dlg::ChooseCommit( bool flag )
{
	b_begin_ = !b_begin_;

	do_timer(b_begin_);
	
	return;
	QVector<QStringList> qv_data = dio_table_->get_data();
	

	std::vector<schedule_interface_data*> v_si_data;
	foreach (QStringList row, qv_data) {

		int i_index = row.at(COL_DIO_SEQ).toInt();
#if 0
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
			p_si_data->set_match_from_start(true);
			p_si_data->set_agv_gp_id(row.at(COL_STRATEGY_AGV_ID_GP).toStdString());
			p_si_data->set_priority(row.at(COL_STRATEGY_PRIORYTY).toStdString());

			v_si_data.push_back(p_si_data);

		}
#endif
	}

	//STRATEGY_FACTORY.insert_schedule_rules(v_si_data);

	//dio_table_->show_dio( STRATEGY_FACTORY.get_schedule_list() );
}
