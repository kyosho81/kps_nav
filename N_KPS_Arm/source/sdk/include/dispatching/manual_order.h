#ifndef _MANUAL_ORDER_WANGHONGTAO_20220303_
#define _MANUAL_ORDER_WANGHONGTAO_20220303_

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
#include "Comm/data_time.h"

class protobuf_base;
class order_schedule;

class manual_order
{
public:
	manual_order();
	~manual_order();
	
	typedef enum{ 
		MANUAL_NONE = 0,
		MANUAL_COMMIT = 1,
		MANUAL_DOING = 2,
		MANUAL_DONE = 3,
		MANUAL_ERROR = 4
	} MANUAL_STATE;

	std::string str_order_id_;

	std::string str_from_role_;
	std::string str_to_role_;

	std::string str_from_role_gp_id_;
	std::string str_to_role_gp_id_;

	std::string str_from_carry_type_;
	std::string str_to_carry_type_;

	std::string str_agv_gp_id_;

	std::string str_order_time_;

	data_time time_;

	int i_order_factory_index_;
	MANUAL_STATE state_;
	
	std::string str_err_;
};

class manual_order_factory
{
public:
	manual_order_factory();
	~manual_order_factory();

	manual_order* new_manual_order( std::map<std::string,std::string> m_para);
	manual_order* insert_manual_order( std::map<std::string,std::string> m_para);
	manual_order* insert_manual_order(manual_order* p_manual);

	int get_manual_order(std::map<std::string ,manual_order*> &m_manual_order);
	int get_manual_order(std::list<manual_order*> &l_manual_order,bool b_sort = false);
	bool do_order_schedule(std::list<order_schedule*> &l_order_schedule, std::multimap< std::string, protobuf_base* > &mm_roles);

	bool set_manual_order_state( std::string str_order_id, manual_order::MANUAL_STATE state,std::string str_msg = "");

protected:
private:
	bool check_para( std::string str_name, std::string str_value) ;

	boost::mutex mu_data_;
	std::map<std::string ,manual_order*> m_order_;

	void filter_roles(std::multimap< std::string, protobuf_base* > &mm_roles);
};

typedef boost::serialization::singleton<manual_order_factory> Singleton_Manual_Order_Factory;
#define MANUAL_ORDER_FACTORY Singleton_Manual_Order_Factory::get_mutable_instance()

#endif//_MANUAL_ORDER_WANGHONGTAO_20220303_
