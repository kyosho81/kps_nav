#ifndef _CARRY_TYPE_WANGHONGTAO_20220303_
#define _CARRY_TYPE_WANGHONGTAO_20220303_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"


class carry_type
{
public:
	carry_type();
	~carry_type();

	static void replace_ct(std::vector<std::string> &v_carry_type);
	static std::vector<std::string> merge_carry_type(std::vector<std::string> group_t1 , std::vector<std::string> group_t2 );
	static bool check_type(std::string str_t1,std::string str_t2);

	//check group or id match
	static bool check_gp_id( int i_agv_id, std::string str_agv_group, std::vector<std::string> v_gp_id );
	static bool check_gp_id( int i_agv_id, std::vector<std::string> v_agv_gp, std::vector<std::string> v_gp_id );
	static bool check_gp_id( int i_agv_id, std::vector<std::string> v_agv_gp, std::string str_gp_id );
};


#endif//_CARRY_TYPE_WANGHONGTAO_20220303_
