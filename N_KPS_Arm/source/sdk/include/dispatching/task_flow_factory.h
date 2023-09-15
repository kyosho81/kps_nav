#ifndef _TASK_FLOW_FACTORY_WANGHONGTAO_20230426_
#define _TASK_FLOW_FACTORY_WANGHONGTAO_20230426_

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
#include "dispatching/task_flow_data.h"


class task_flow_factory
{
public:
	task_flow_factory();
	~task_flow_factory();

	bool init();
	bool save_file();

	task_flow_data* new_task_flow_data(std::string str_task_flow_nm);
	task_flow_data* get_task_flow_data(std::string str_task_flow_nm);
	bool del_task_flow_data(std::string str_task_flow_nm);

	int get_task_flow_nms(std::vector<std::string> &v_task_flow_nms);
	bool check_task_flow(std::string str_task_flow_nm);


protected:



private:

	
private:
	

	int get_bind_action( protobuf_base* p_base , std::string type , std::list<KPS::mp_bind_action> &l_bind_action);
	int get_turn_id( std::vector<int> &v_turn_id, protobuf_base* p_base);

private:
	

	std::map<std::string,task_flow_data*> m_task_flow_;

private:
	bool load_file();
	
	void clear();
	std::string get_str(std::string str);
	std::string set_str(std::string str);
	std::string str_file_;

	boost::shared_mutex mu_read_write_taskflow_;
	typedef boost::shared_lock<boost::shared_mutex> read_lock;
	typedef boost::unique_lock<boost::shared_mutex> write_lock;

};

typedef boost::serialization::singleton<task_flow_factory> Singleton_Task_Flow_Factory;
#define TASK_FLOW_FACTORY Singleton_Task_Flow_Factory::get_mutable_instance()

#endif//_TASK_FLOW_FACTORY_WANGHONGTAO_20230426_
