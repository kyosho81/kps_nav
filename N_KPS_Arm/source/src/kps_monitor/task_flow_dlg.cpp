
#include <QDebug>
#include "interpro_shared/sh_pool.hpp"
#include "robot/RobotStruct.h"
#include "interface/xml_rpc_client.h"


#include "robot/Geometry.h"
#include "Comm/Comm.h"
#include "dispatching/traffic_control.h"
#include "mapserver/MapServer.h"

#include "task_flow_para_dlg.h"
#include "task_flow_edit_dlg.h"

#include "dispatching/task_flow_factory.h"
#include "action/action_factory.h"
#include "protobuf_msg/task_flow_def.h"
#include "project/project_manage.h"
#include "protobuf_msg/protobuf_base.h"
#include "dispatching/order_factory.h"
#include "dispatching/disassembly_order.h"

#include "task_flow_dlg.h"

task_flow_dlg::task_flow_dlg( QWidget *parent)
{

	TASK_FLOW_FACTORY.init();
	ACTION_FACTORY.init();

	task_flow_para_dlg_ = 0 ;
	task_flow_edit_dlg_ = 0 ;

}

task_flow_dlg::~task_flow_dlg()
{
	
}


void task_flow_dlg::init( map_scene* map_scene ){

	assert(map_scene);
	map_scene_ = map_scene;

	task_flow_para_dlg_ = new task_flow_para_dlg(this);
	task_flow_edit_dlg_ = new task_flow_edit_dlg(this);

//	order_run_table_ = new order_table(this);
//	order_his_table_ = new order_table(this);
//	map_view_->zoom(25);
//	map_view_->centerOn(0,0);
//	
	
	QSplitter *pSplitter = new QSplitter(Qt::Orientation::Vertical, this);

 	QGridLayout* grid = new QGridLayout();

	pSplitter->addWidget(task_flow_edit_dlg_);
	pSplitter->addWidget(task_flow_para_dlg_);
	
	

	
	//connect(btn_his_order_,SIGNAL(toggled(bool)),this,SLOT(ChooseRunHis(bool)));
	//connect(btn_accepte_order_, SIGNAL(clicked(bool)), this, SLOT(ChooseAccepteOrder(bool)));

	//grid->addWidget(role_table_,0,0,3,10);
	//grid->addWidget(order_run_table_,4,0,3,10);
	grid->addWidget(pSplitter,0,0,13,10);

	setLayout(grid);

}
void task_flow_dlg::ChooseAnalyze(bool flag)
{
	task_flow_edit_dlg_->save_data();

	task_flow_data* tf = task_flow_edit_dlg_->get_task_flow();

	std::map<std::string,std::string> m_main_para;
	task_flow_para_dlg_->get_main_para(m_main_para);
	
	std::map<std::string,std::string> m_ext_para;
	task_flow_para_dlg_->get_ext_para(m_ext_para);

	do_analyze(tf, m_main_para, m_ext_para);
}

void task_flow_dlg::ChooseInstantiation(bool flag)
{

}
protobuf_base* task_flow_dlg::get_role( std::string str_name, std::map<std::string,std::string> m_para){

	std::string str_role_id = get_para( str_name, m_para);

	protobuf_base* p_base = PRO_MANAGE.get_role(CURRENT_PRO,str_role_id);

	return p_base;
}
std::string task_flow_dlg::get_para(std::string str_name,std::map<std::string,std::string> m_para){
	auto it_role_from = m_para.find(str_name);
	if ( it_role_from != m_para.end()){
		return it_role_from->second;
	}
	return "";
}
int task_flow_dlg::filter_action(std::list<KPS::mp_bind_action> &l_bind_action, std::string type){
	for ( auto it = l_bind_action.begin() ; it != l_bind_action.end() ; ){
		//type length = 0  then check type match
		if ( (type.length() > 0) && (it->action_type_uuid() != type) ){
			it = l_bind_action.erase(it);
		}else{
			++it;
		}
	}
	return l_bind_action.size();
}

int task_flow_dlg::get_turn_action(std::vector<int> &v_turn_node, std::list<KPS::mp_bind_action> l_bind_action)
{
	
	v_turn_node.clear();
	for ( auto it = l_bind_action.begin() ; it != l_bind_action.end() ; ){
		if (it->turn()){
			int i_node_id = -1;
			cComm::ConvertToNum(i_node_id,it->node_id());
			v_turn_node.push_back(i_node_id);
		}
	}
	return v_turn_node.size();
}

int task_flow_dlg::do_analyze( task_flow_data* tf, std::map<std::string,std::string> m_main_para , std::map<std::string,std::string> m_ext_para )
{
	if (!tf){
		std::cout<<"analyze err: select task flow first!"<<std::endl;
		return 1;
	}
	order_schedule* p_osch = new order_schedule();

	std::string str_node_id = get_para(TF_NODE_ID,m_main_para);
	std::string str_angle = get_para(TF_START_ANGLE,m_main_para);
	cComm::ConvertToNum(p_osch->one_task_.i_agv_node_id_,str_node_id);
	cComm::ConvertToNum(p_osch->one_task_.f_agv_ori_,str_angle);
	//memset(&task_para.r_info_,0,sizeof(SRobot_Inf));
	p_osch->one_task_.i_agv_id_ = -1;


	p_osch->p_from_ = get_role( TF_FROM_ROLE, m_main_para );
	if(!p_osch->p_from_){
		return 2;
	}
	

	p_osch->p_to_ = get_role( TF_TO_ROLE, m_main_para );
	if( !p_osch->p_to_ ){
		return 3;
	}


	p_osch->one_task_.str_pallet_uuid_ = get_para(TF_PALLET_TYPE,m_main_para);
	p_osch->one_task_.str_cargo_uuid_ = get_para(TF_CARGO_TYPE,m_main_para);

	p_osch->i_sch_index_ = 999999;
	std::string str_cross_noload = get_para(TF_EX_CROSS_NOLOAD,m_ext_para);
	int i_cross_noload = 0;
	cComm::ConvertToNum( i_cross_noload, str_cross_noload );
	if (i_cross_noload){
		p_osch->one_task_.b_cross_noload_ = true;
	}else{
		p_osch->one_task_.b_cross_noload_ = false;
	}
	

	std::string str_msg = DISASSEMBLY_ORDER.disassembly(tf, p_osch );
	
	std::cout<<str_msg<<std::endl;

	std::cout<<">>>>>>>>>>>do_analyze over!!!<<<<<<<<<<<<<<<<<<"<<std::endl;

	SDelete(p_osch);

#if 0
	std::list<KPS::mp_bind_action> l_from_action;
	p_from_role->get_bind_action(l_from_action);
	std::vector<int> v_turn_from;
	get_turn_action(v_turn_from, l_from_action);


	SPos from_pos;
	p_from_role->get_bind_pos(from_pos);
	int i_from_id = p_from_role->get_bind_node_id();

	SPos to_pos;
	p_to_role->get_bind_pos(to_pos);
	int i_to_id = p_to_role->get_bind_node_id();
#endif
	
}
