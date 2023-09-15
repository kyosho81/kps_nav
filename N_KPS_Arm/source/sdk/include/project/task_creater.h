
#ifndef _TASK_CREATER_CLIENT_H_
#define _TASK_CREATER_CLIENT_H_

#include <vector>
#include <list>
#include <boost/serialization/singleton.hpp>

#include <RobotStruct.h>

#include "XmlRpc.h"
#include "task_base.h"
#include "Comm/PortDef.h"

class task_rpc_client;

class task_creater
{
public:
	task_creater(task_rpc_client* client = 0);
	~task_creater();
	
	int create_rand_path(const SPos &current_pos);
	int create_specified_path(const SPos &charge_pos);
	int create_charge_path(const SPos &charge_pos, F32 vx);
	int create_fix_path(const std::vector<SPathData> &seg_path );
	int create_fork(std::string str_para);
	int create_task_act(std::string str_para);

	bool do_update_task();
	int do_update_task( std::map<int,task_feadback> &m_run_task );
	int check_task_done(int i_task_id);
	void clear_run_task();
private:

	bool check_task_init(task_feadback &fb,int i_task_id);
	bool insert_run_task_list(int i_task_id,const task_feadback &fb);
	

	boost::mutex mu_task_;
	std::map<int,task_feadback> m_run_task_;
	std::list<task_feadback> l_his_task_;


	task_rpc_client* task_rpc_client_;
};


//typedef boost::serialization::singleton<task_rpc_client> Singleton_Task_Xml_Client;
//#define TASK_XML_CLIENT Singleton_Task_Xml_Client::get_mutable_instance() 
#endif // _TASK_CREATER_CLIENT_H_
