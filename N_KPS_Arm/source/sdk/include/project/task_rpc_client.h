
#ifndef _TASK_RPC_CLIENT_H_
#define _TASK_RPC_CLIENT_H_

#include <vector>
#include <list>
#include <boost/serialization/singleton.hpp>

#include <RobotStruct.h>

#include "XmlRpc.h"
#include "task_base.h"
#include "Comm/PortDef.h"

using namespace XmlRpc;

class task_rpc_client
{
public:
	task_rpc_client();
	~task_rpc_client();
	void init(std::string ip, int port = RPC_TASK_SER_PORT);

	bool set_onboard_project(std::string str_project);
	int create_rand_path(const SPos &current_pos);
	int create_specified_path(const SPos &charge_pos);
	int create_charge_path(const SPos &charge_pos,F32 vx );
	int create_open_ctl(const SOdomSpeed &odom_clt , const SPos &amcl_pos, const SPos &target_pos, std::string str_obs_strategy);
	int create_fix_path(const std::vector<SPathData> &seg_path );
	int create_fork(const std::string &str_para);
	int create_task_act( const std::string &str_para );

	bool get_feadback(const int &i_task_id,std::vector<task_feadback> &v_feadback);
	bool remove_task(int i_task_id = -1);
	bool force_complete(int i_task_id = -1);
	bool redo(int i_task_id = -1);

	bool get_sim_init_pos(SPos &pos);
	
private:

	XmlRpcClient* client_;

	
};


typedef boost::serialization::singleton<task_rpc_client> Singleton_Task_Xml_Client;
#define TASK_XML_CLIENT Singleton_Task_Xml_Client::get_mutable_instance() 
#endif // _TASK_RPC_CLIENT_H_
