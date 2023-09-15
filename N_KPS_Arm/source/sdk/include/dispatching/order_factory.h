#ifndef _ORDER_FACTORY_WANGHONGTAO_20220303_
#define _ORDER_FACTORY_WANGHONGTAO_20220303_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "protobuf_msg/sm_def.h"
#include "protobuf_msg/base.pb.h"
#include "dispatching/schedule_interface.h"
#include "dispatching/action_base.h"
#include "Comm/data_time.h"

class protobuf_base;
class protobuf_charge;

class one_task
{
public:
	one_task();
	~one_task();

	int i_agv_node_id_;
	F32 f_agv_ori_;
	SRobot_Inf r_info_;

	protobuf_base* p_from_role_;
	int i_from_node_id_;
	F32 f_from_ori_;
	protobuf_base* p_to_role_;
	int i_to_node_id_;
	F32 f_to_ori_;
	protobuf_base* p_release_role_;

	std::string str_pallet_uuid_;
	std::string str_cargo_uuid_;
	int i_agv_id_;
	int i_sch_index_;

	//ex fnc
	bool b_cross_noload_;

};


class spirit_node
{
public:
	spirit_node(){};
	~spirit_node(){};

	int node_id_;
	std::vector<KPS::mp_bind_action> v_bind_act_;

};



class spirit_path
{
public:
	spirit_path(){};
	~spirit_path(){};

	std::list<spirit_node> l_node_list_;
	ORIENTAION ori_;
};

class spirit_action
{
public:
	spirit_action(){
		//i_index_ = 0;
		i_sub_index_ = 0;

		ACT_DEC act_dec_;

		str_act_type_ = "";
		
		str_para_ = "";

		str_get_put_ = "";
		str_mv_seg_ = "";
		
		str_task_flow_nm_ = "";
		i_task_flow_seq_ = -1;
		i_action_seq_ = -1;

		i_node_id_ = -1;
		i_node_seq_ = 0;

		i_pre_node_id_ = -1;
		i_next_node_id_ = -1;

		f_trigger_para_ = .0;

		act_dec_ = ACT_DEC::ACT_DISABLE;

	};
	~spirit_action(){};

	//int i_index_;
	int i_sub_index_;

	std::string str_act_type_;
	std::string str_para_;

	std::string str_get_put_;
	std::string str_mv_seg_;
	std::string str_task_flow_nm_;
	int i_task_flow_seq_;
	int i_action_seq_;

	ACT_DEC act_dec_;

	int i_node_id_;
	int i_node_seq_;

	int i_pre_node_id_;
	int i_next_node_id_;

	F32 f_trigger_para_;
};

class act_list
{
public:
	act_list(){};
	~act_list(){};

	int put_act(spirit_action &sp_act);
	int put_act(int i_index, spirit_action &sp_act);
	int put_act(int i_index, int i_sub_index, spirit_action &sp_act);
	std::multimap<int,spirit_action> mt_acts_;
};

class order_schedule
{
public:
	order_schedule();
	~order_schedule(){};

	protobuf_base* p_from_;
	protobuf_base* p_to_;
	protobuf_base* p_release_role_;

	int i_agv_id_;
	int i_sch_index_;
	int i_order_index_;
	std::string str_manual_id_;

	one_task one_task_;

	std::list<spirit_path> l_path_get_;
	std::list<spirit_path> l_path_put_;

	static int i_max_index_;

	void set_begin();
	void set_end();
	data_time data_t_;
	float f_time_min_;

	std::string str_begin_;
	std::string str_end_;

	typedef enum{
		ODR_FF_TRANSFER = 0,
		ODR_FB_TRANSFER = 1,
		ODR_BFB_TRANSFER = 2,
		ODR_FBFB_TRANSFER = 3,
		ODR_SF_TRANSFER = 4,
		ODR_STORAGE = 5,
		ODR_PACK = 6,
		ODR_CHARGE = 7
	}ORDRE_TYPE;

	ORDRE_TYPE order_type_;
	std::vector<std::string> v_task_flow_nm_;
public:
	//from task_flow with string para
	act_list acts_;
	action_queue act_que_;

	bool b_qualified_;

	typedef enum{
		ACT_SEQ_FILL = 0,
		ACT_SEQ_ASSIGN = 1,
		ACT_SEQ_DOING = 2,
		ACT_SEQ_DONE = 3,
		ACT_SEQ_ERROR = 4
	}ACT_SEQ;
	THSafe<ACT_SEQ> th_assigned_;

	
};

//match roles and create order 
//one order contain get task, put task
class order_factory
{
public:
	order_factory();
	~order_factory();

	bool do_pack_charge(std::vector<protobuf_charge*> v_pack);
	void filter_err_roles(std::multimap< std::string, protobuf_base*> &mm_roles);
	bool do_manual_order(std::list<order_schedule*> &l_odr_schedule, std::multimap< std::string, protobuf_base* > &mm_roles);
	bool do_match_roles(std::list<order_schedule*> &l_odr_schedule, std::multimap< std::string, protobuf_base* > mm_roles_src ,std::multimap< std::string, protobuf_base* > mm_roles_des);

	std::string get_order_state(order_schedule::ACT_SEQ i_state);

	void set_unreach_node( std::vector<int> &v_unreach_node );

	void filter_storage_occupyincol(std::multimap< std::string, protobuf_base* > &mm_roles_src ,std::multimap< std::string, protobuf_base* > &mm_roles_des, std::multimap< std::string, protobuf_base*> &mm_all_roles);

protected:
private:
	

private:

	void sort_schedule();
	//order schedule by priority
	std::multimap<int , schedule_interface_data*>  mm_order_schedule_;
	

private:
	//check match agv id or group or type
	int filter_agv(schedule_interface_data* ps);
	std::map<int,SRobot_Inf> m_specified_agv_;
	int get_closest_agv(std::map<int,SRobot_Inf> m_specified_agv, protobuf_base* p_from, protobuf_base* p_to);
	int get_closest_agv(std::map<int,SRobot_Inf> m_specified_agv, SPos pos_from, SPos pos_to);

	bool can_assign(int i_agv_id , std::map<int, SRobot_Inf> m_specified_agv);
	//get intput output merge carry type
	int merge_ct(schedule_interface_data* ps);
	std::vector<std::string> v_role_carry_type_;

	
	
private:
	std::list<std::pair<std::string, protobuf_base*>> sort_role_priority(std::multimap< std::string, protobuf_base*> mm_roles);
	std::list<std::pair<std::string, protobuf_base*>> l_roles_src_;
	std::list<std::pair<std::string, protobuf_base*>> l_roles_des_;

	std::list<std::pair<std::string, protobuf_base*>> filter_role_type_gp(const std::list<std::pair<std::string, protobuf_base*>> &l_roles, std::string str_role_nm, std::string str_role_gp_id);
	std::list<std::pair<std::string, protobuf_base*>> filter_role_category(const std::list<std::pair<std::string, protobuf_base*>> &l_roles, std::vector<std::string> v_ps_carry_type );
	
	
	void filter_storage_insamecol( std::list<std::pair<std::string, protobuf_base*>> &l_roles, bool b_put_storage);
	
	int remove_role(std::list<std::pair<std::string, protobuf_base*>> &l_roles, protobuf_base* p_role);
	bool match_start_end_role( protobuf_base* &p_role_begin, protobuf_base* &p_role_end, std::list<std::pair<std::string, protobuf_base*>> &l_roles_begin, std::list<std::pair<std::string, protobuf_base*>> &l_roles_end);

 	typedef std::multimap<std::string, protobuf_base*>::iterator M_it;
// 	typedef std::pair< M_it , M_it > P_it;
// 	M_it find_ready_role(std::string str_role);
// 	bool remove_ready_role(M_it it);

	SPos get_role_pos(M_it it);
//	int storage_put_get( M_it it );

	//input from state_machine_factory
	//string roles type
	//roles pt
	bool put_order_pack( protobuf_base* p_base, int i_agv_id, std::string str_manual_id);
	bool put_order_charge( protobuf_base* p_base, int i_agv_id, std::string str_manual_id);
	bool put_order_manual( protobuf_base* p_from, protobuf_base* p_to , int i_agv_id, std::string str_manual_id);
	bool put_order_schedule( protobuf_base* p_from, protobuf_base* p_to, int i_agv_id,int i_sch_index, std::vector<std::string> &v_task_flow_nm);
	
	protobuf_base* get_protobuf_base(std::string str_role, std::string str_id );
	bool check_group(std::string str_group);
	void remove_role(protobuf_base* p_base,std::multimap< std::string, protobuf_base* > &mm_roles);
	
	
	protobuf_charge* find_charge_station( SRobot_Inf robot_charge, std::vector<protobuf_charge*> v_pack);
	protobuf_charge* find_pack_station( SRobot_Inf robot_pack, std::vector<protobuf_charge*> v_pack);
	void remove_charge( std::vector<protobuf_charge*> &v_pack , protobuf_charge* p_charge );
	bool is_storage_transfer(protobuf_base* p_from, protobuf_base* p_to);

	std::list<order_schedule*> l_order_schedule_;

private:

	std::map<order_schedule::ACT_SEQ,std::string> m_state_str_;

	std::vector<int> v_unreach_node_;
};

typedef boost::serialization::singleton<order_factory> Singleton_Order_Factory;
#define ORDER_FACTORY Singleton_Order_Factory::get_mutable_instance()

#endif//_ORDER_FACTORY_WANGHONGTAO_20220303_
