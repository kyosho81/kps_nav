#ifndef _GROUP_DATA_20121101_
#define _GROUP_DATA_20121101_

#include <map>
#include <fstream>
#include "boost/unordered/unordered_map.hpp"
#include <boost/serialization/singleton.hpp>

#include "MyDefine.h"
#include "Comm/Comm.h"
#include "robot/RobotStruct.h"

class group_data
{
public:
	group_data();
	~group_data(){};

	int get_group_map(std::map<std::string,int> &m_group, std::string str_sel_group, std::vector<std::string> v_group);
	bool check_group_name(std::string str_group);

	std::vector<std::string> v_group_;
	std::string str_delimiter_;

protected:
private:
};


typedef boost::serialization::singleton<group_data> Singleton_Group_Data;
#define GROUP_DELIMITER Singleton_Group_Data::get_mutable_instance().str_delimiter_
#define GROUP_DATA Singleton_Group_Data::get_mutable_instance().v_group_

#endif //_GROUP_DATA_20121101_
