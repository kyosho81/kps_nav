#ifndef _SCHEDULE_INTERFACE_DATA_WANGHONGTAO_20151230_
#define _SCHEDULE_INTERFACE_DATA_WANGHONGTAO_20151230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include "buffer_con.hpp"

#include "RobotStruct.h"


typedef struct _SSch_Interface
{
	int index_;

	bool b_activated_;

	std::string str_role_start_;
	std::vector<std::string> v_start_gp_id_;
	std::vector<std::string> v_output_type_;

	std::string str_role_end_;
	std::vector<std::string> v_end_gp_id_;
	std::vector<std::string> v_input_type_;

	bool match_from_start_;
	std::vector<std::string> v_agv_gp_id_;

	int priority_;
	std::vector<std::string> v_task_flow_nm_;

}SSch_Interface;

class schedule_interface_data
{
public:
	schedule_interface_data();
	~schedule_interface_data();

	void init( int index = -1);
	int get_index();

	bool set_activated(bool b_activated);
	bool set_activated(std::string str_activated);
	bool activated();
	std::string activated_str();
	
	bool set_start_role(std::string str_role);
	std::string start_role();

	bool set_start_gp_id(std::vector<std::string> v_gp_id);
	bool set_start_gp_id(std::string str_gp_id);
	int start_gp_id(std::vector<std::string> &v_gp_id);
	std::string start_gp_id();

	bool set_output_type(std::vector<std::string> v_output_type);
	bool set_output_type(std::string str_output_type);
	int output_type(std::vector<std::string> &v_output_type);
	std::string output_type();

	bool set_end_role(std::string str_role);
	std::string end_role();

	bool set_end_gp_id(std::vector<std::string> v_gp_id);
	bool set_end_gp_id(std::string str_gp_id);
	int end_gp_id(std::vector<std::string> &v_gp_id);
	std::string end_gp_id();

	bool set_input_type(std::vector<std::string> v_input_type);
	bool set_input_type(std::string str_input_type);
	int input_type(std::vector<std::string> &v_input_type);
	std::string input_type();

	bool set_match_from_start(bool b_start);
	bool set_match_from_start(std::string str_start);
	bool match_from_start();
	std::string match_from_start_str();

	bool set_agv_gp_id(std::vector<std::string> v_agv_gp_id);
	bool set_agv_gp_id(std::string str_gp_id);
	int agv_gp_id(std::vector<std::string> &v_agv_gp_id);
	std::string agv_gp_id_str();

	bool set_priority(int priority);
	bool set_priority(std::string str_priority);

	int priority();
	std::string priority_str();

	bool set_task_flow(std::string str_task_flow_nms);
	bool set_task_flow(std::vector<std::string> v_task_flow_nm);
	int task_flow_nm(std::vector<std::string> &v_task_flow_nm);
	std::string task_flow_nm();

	std::string task_flow_str();

	bool is_put_storage();

protected:

private:
	bool check_role(std::string str_role);
	bool check_group(std::string str_group);
	bool check_role_id( std::string str_role, std::string str_id);
	bool check_agv_id(std::string str_id);
	bool check_pallet_type( std::string str_type );
	bool check_cargo_type( std::string str_type );
	bool check_task_flow( std::string str_task_flow_nm );

	std::string gp2string(std::vector<std::string> v_str);

	SSch_Interface sch_interface_;


};



#endif//_SCHEDULE_INTERFACE_DATA_WANGHONGTAO_20151230_
