#ifndef _ACTION_FACTORY_WANGHONGTAO_20230508_
#define _ACTION_FACTORY_WANGHONGTAO_20230508_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "protobuf_msg/sm_def.h"
#include "protobuf_msg/protobuf_base.h"

class device_exaction_base;

class action_factory
{
public:
	action_factory();
	~action_factory();

	bool init();
	int get_action_nms(std::vector<std::string> &v_nms);
	void get_action(std::map<U8,std::string> &m_type_name,std::map<U8,std::pair<std::string,std::string>> &m_type_para);
	bool get_action_para(std::pair<std::string,std::string> &p_para,std::string str_type_name);

protected:

	
	std::map<U8,std::string> m_type_name_;

	std::map<U8,std::pair<std::string,std::string>> m_type_para_;
	std::map<std::string,std::pair<std::string,std::string>> m_name_para_;

private:

	void clear();
	void init_action_name();
	void init_action_para();


	boost::shared_mutex mu_read_write_taskflow_;
	typedef boost::shared_lock<boost::shared_mutex> read_lock;
	typedef boost::unique_lock<boost::shared_mutex> write_lock;

};

typedef boost::serialization::singleton<action_factory> Singleton_Action_Factory;
#define ACTION_FACTORY Singleton_Action_Factory::get_mutable_instance()

#endif//_ACTION_FACTORY_WANGHONGTAO_20230508_
