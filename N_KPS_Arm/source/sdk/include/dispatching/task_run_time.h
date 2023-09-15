#ifndef _TASK_PARA_WANGHONGTAO_KYOSHO_20200912_
#define _TASK_PARA_WANGHONGTAO_KYOSHO_20200912_

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <ctime>
#include <map>

#include <boost/lexical_cast.hpp>
#include <boost/serialization/singleton.hpp>
#include "boost/unordered/unordered_map.hpp"




#include "Comm/Comm.h"
#include "Comm/TimerDiff.h"
#include "Comm/configs.h"
#include "interpro_shared/sh_pool.hpp"


#include "mapserver/MapServer.h"
#include "project/project_manage.h"


#include "project/task_base.h"
#include "dispatching/order_factory.h"

class task_creater;

class task_run_time
{
public:
	task_run_time();
	~task_run_time();

	bool init(task_creater* p_task_creater);

	//agv sm check new task
	bool task_assigned();
	bool is_pack();
	bool is_charge();
	int do_task(std::string &str_err);
	void set_ord_sch(order_schedule* ord_sch);
	
	void set_ord_sch_done();
	void set_ord_sch_error();
	void clear_ord_sch();
	order_schedule::ACT_SEQ get_ord_sch_error();


	std::map<std::string,task_feadback> m_uuid_feadback_;
	void get_run_path(std::list<SPathData> &run_seg_path);

protected:
private:
	//task_rpc_client* task_rpc_;
	task_creater* task_creater_;

	boost::mutex mu_task_;
	order_schedule* ord_sch_;
	
	//from action path download
	std::vector<SPathData> run_seg_path_;

	int download_act(action_base* p_act_base);
	int check_act_done(action_base* p_act_base);
	void clear_down_act();

	std::map<int,action_base*> m_id_down_act_;
	std::map<std::string,action_base*> m_uuid_down_act_;
	std::map<action_base*,int> m_down_act_id_;
};


#endif //_TASK_PARA_WANGHONGTAO_KYOSHO_20200912_
