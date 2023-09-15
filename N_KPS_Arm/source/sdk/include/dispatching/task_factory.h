#ifndef _TASK_FACTORY_WANGHONGTAO_20220303_
#define _TASK_FACTORY_WANGHONGTAO_20220303_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "protobuf_msg/sm_def.h"
#include "dispatching/schedule_interface.h"
#include "dispatching/action_base.h"
#include "dispatching/order_factory.h"

class task_factory
{
public:
	task_factory();
	~task_factory(){};

	int insert_order_sch(order_schedule* p_ord_sch);
	
	void create_action_queue();
	
	void fill_path_action( order_schedule* p_ord_sch );
	void fill_path_action2( order_schedule* p_ord_sch );
	void split_path( action_queue &act_que , spirit_path &spath , protobuf_base* p_base , int i_agv_id );
	
	boost::function<int(void)> create_call_back( protobuf_base* p_base , int i_agv_id);

	std::list<order_schedule*> get_run_order();
	std::list<order_schedule*> get_his_order();

	std::list<order_schedule*>::iterator release_order( std::list<order_schedule*>::iterator it );

	
private:

	std::string cov_path(std::string str_path);
	bool create_action(action_queue &act_que , int i_task_index, KPS::mp_bind_action &k_act,int i_cur_node_id, int i_last_node_id , int i_next_node_id , F32 f_trigger , protobuf_base* p_base , int i_agv_id);
	bool create_action2(action_queue &act_que , spirit_action spact , int i_agv_id);
	void print_act();

	std::list<order_schedule*> l_ord_sch_run_time_;
	std::list<order_schedule*> l_ord_sch_history_;
	int i_task_index_;
	//static bool create_action_queue( action_queue &action_que, std::list<order_schedule> );

	void save_his(order_schedule* p_ord_sch);

protected:
private:
	std::string get_order_log_name();
	bool check_log_size_save();
	
	int i_max_save_log_;

	std::string str_log_file_;
	std::string str_path_;
};

typedef boost::serialization::singleton<task_factory> Singleton_Task_Factory;
#define TASK_FACTORY Singleton_Task_Factory::get_mutable_instance()

#endif//_TASK_CREATER_WANGHONGTAO_20220303_
