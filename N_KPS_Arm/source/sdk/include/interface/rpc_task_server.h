#ifndef _RPC_TASK_SERVER_KYOSHO_KYOSHO_20200912_
#define _RPC_TASK_SERVER_KYOSHO_KYOSHO_20200912_

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

#include "XmlRpc.h"

#include "Comm/Comm.h"
#include "Comm/TimerDiff.h"
#include "Comm/configs.h"
#include "interpro_shared/sh_pool.hpp"


#include "mapserver/MapServer.h"
#include "project/project_manage.h"
#include "interface/cfg.hpp"

#include "project/task_manage.h"

class map_tools
{
public:
	static void set_amcl_run(const bool &run);
	static void set_map_lock( const bool &block );
	static void set_map_fill(const int &value);
	static void set_map_reflash();
	static void draw_prohibit_path(GridMap* prohibit_map, const Sxy &p1 , const Sxy &p2);

	static bool reflash_map_over();

	static void sub_reflash_over();
	static bool call_back( const int &reflash );

	static bool b_sim_;

protected:
private:
	static int i_max_prohibit_path_;

	static SBuffer<int> th_reflash_;
};

class set_onboard_project : public XmlRpc::XmlRpcServerMethod
{
public:
	set_onboard_project(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_onboard_project", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs == 1){

			std::string str_pro_name = params[0];

			if(PRO_MANAGE.open_pro(str_pro_name)){

				map_tools::set_amcl_run(false);
				GridMap* pro_map = PRO_MANAGE.get_raw_map(CURRENT_PRO);

				map_tools::set_map_lock(true);
				std::cout<<"task set_map:set_map_lock true"<<std::endl;
				map_tools::set_map_fill(MAP_UNKNOWN);
				std::cout<<"task set_map:set_map_fill unknown"<<std::endl;

			
				GridMap* g_map = MAP_SERVER.GetGridMap(SHARED_AMCL_MAP);

				if ( pro_map && g_map)
				{
					MAP_SERVER.clone( pro_map->Get_name() , g_map->Get_name());

					MAP_SERVER.RemoveGridMap(pro_map);
				}
				//init prohibitmap
				g_map = MAP_SERVER.GetGridMap(SHARED_GLOBAL_PROHIBIT_INF_MAP);

				if ( g_map)
				{
					g_map->lock();
					g_map->clear();

					protobuf_range* p_range = 0;
					p_range = PRO_MANAGE.get_next_range("","");

					while(p_range){


						std::vector<Sxy> v_list;
						p_range->get_range(v_list);
						if (v_list.size() < 3){
							break;
						}
						v_list.push_back(v_list[0]);

						std::vector<Sxy>::iterator it_from = v_list.begin();
						std::vector<Sxy>::iterator it_to = it_from;
						it_to++;

						for ( ;it_to != v_list.end(); ++it_to ){
							map_tools::draw_prohibit_path(g_map,(*it_from),(*it_to));
							it_from = it_to;
						}

						p_range = PRO_MANAGE.get_next_range("",p_range->get_name());
					}


					F32 global_map_inf = 0.2;
					Config::getConfig("mv_global_map_inf",global_map_inf);

					
					std::cout<<"mv_global_map_inf:"<<global_map_inf<<std::endl;
					MAP_SERVER.fast_inflation(global_map_inf,g_map->Get_name());
					
					//MAP_SERVER.save_map(g_map->Get_name(),".//prohibit.igm");

					g_map->unlock();
				}

				
				

				std::string str_lm_map = ".//map//";//"pro.lm"
				RPC_CONFIG_CLIENT.get_config(str_lm_map,"dev_map_path");
				str_lm_map += "pro.lm";
				PRO_MANAGE.save_reflector_map(CURRENT_PRO,str_lm_map);
				////////////////////pub load reflected pillar map////////////////////
 				std::stringstream ss;
 				ss<<"load pro.lm";
 				SCmd scmd;
 				memset(scmd.cmd_str_,0,200);
 		
 				memcpy(scmd.cmd_str_,ss.str().c_str(),ss.str().length() );
 				//shared_pool::Publish(shared_pool::name(),"set_map_cmd",scmd);
 				PUB_MSG_SH_POOL("set_map_cmd",scmd);
				////////////////////pub load reflected pillar map////////////////////

				std::cout<<"task set_map:set_map_value over! "<<std::endl;
				map_tools::set_map_lock(false);
				std::cout<<"task set_map:set_map_lock false! "<<std::endl;
				map_tools::set_map_reflash();
				std::cout<<"set_onboard_project:"<<str_pro_name<<std::endl;
				
				if( map_tools::reflash_map_over() ){
					result = (int)0;
				}else{
					result = (int)-2;
				}
				
				return;
			}


		}

		std::cout<<"set_onboard_project err "<<std::endl;

		result = (int)-1;
	};
};

class get_feadback : public XmlRpc::XmlRpcServerMethod
{
public:

	get_feadback(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_feadback", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		int nArgs = params.size();
		if(nArgs == 1){

			int i_task_id = int(params[0]);
			std::vector<task_feadback> v_task_feadback;
			TASK_MANAGE.get_task_feedback(v_task_feadback,i_task_id);

			
			std::vector<task_feadback>::iterator it = v_task_feadback.begin();

			int index = 0;
			for ( ; it != v_task_feadback.end() ; ++it ){
				task_feadback &tfb(*it);
				result[index]["task_id"] = (int)tfb.get_task_id();
				result[index]["init_para"] = (std::string)tfb.get_init_para();
				result[index]["str_status"] = (std::string)tfb.get_str_status();
				result[index]["status"] = (int)tfb.get_status();
				result[index]["str_uuid"] = (std::string)tfb.get_str_uuid();
				index++;
			}
			//std::cout<<"get_task_feedback size:"<<v_task_feadback.size()<<std::endl;
		}

	};
};


class create_rand_path : public XmlRpc::XmlRpcServerMethod
{
public:

	create_rand_path(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("create_rand_path", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{


		SPos robot_pos;
		memset(&robot_pos,0,sizeof(SPos));

		int nArgs = params.size();
		if(nArgs > 2){

// 			robot_pos.x_ = (double)params[0];
// 			robot_pos.y_ = (double)params[1];
// 			robot_pos.th_ = (double)params[2];

			std::list<int> l_path;
			int task_index = (int)TASK_MANAGE.create_rand_path(l_path);

			if (task_index >= 0){
				result[0] = task_index;
				result[1] = "create create_rand_path successful";
			}else{
				result[0] = (int)-1;
				result[1] = "create_rand_path err£¡";
			}
			

		}else{
			result[0] = (int)-1;
			result[1] = "create_rand_path para err£¡";
		}

	};
};


class create_specified_path : public XmlRpc::XmlRpcServerMethod
{
public:

	create_specified_path(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("create_specified_path", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{


		SPos specified_pos;
		memset(&specified_pos,0,sizeof(SPos));

		int nArgs = params.size();
		if(nArgs > 2){

			specified_pos.x_ = (double)params[0];
			specified_pos.y_ = (double)params[1];
			specified_pos.th_ = (double)params[2];

			std::list<int> l_path;
			int task_index = (int)TASK_MANAGE.create_specified_path(l_path,specified_pos);

			if (task_index >= 0){
				result[0] = task_index;
				result[1] = "create create_specified_path successful";
			}else if( task_index == -1 ){
				result[0] = (int)-1;
				result[1] = "create_specified_path near target pos£¡";
			}else{
				result[0] = task_index;
				result[1] = "create_specified_path  pos£¡";
			}


		}else{
			result[0] = (int)-1;
			result[1] = "create_specified_path para size err£¡";
		}

	};
};
class create_charge_path : public XmlRpc::XmlRpcServerMethod
{
public:

	create_charge_path(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("create_charge_path", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		SPos charge_pos;
		memset(&charge_pos,0,sizeof(SPos));

		int nArgs = params.size();
		if(nArgs > 3){


			charge_pos.x_ = (double)params[0];
			charge_pos.y_ = (double)params[1];
			charge_pos.th_ = (double)params[2];
			F32 vx = (double)params[3];

			int task_index = (int)TASK_MANAGE.create_charge_path( charge_pos, vx);

			if (task_index >= 0){
				result[0] = task_index;
				result[1] = "create create_open_ctl successful";
			}else{
				result[0] = (int)-1;
				result[1] = "create_open_ctl err£¡";
			}


		}else{
			result[0] = (int)-1;
			result[1] = "create_open_ctl para err£¡";
		}

	};
};
class create_open_ctl : public XmlRpc::XmlRpcServerMethod
{
public:

	create_open_ctl(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("create_open_ctl", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{


// 		SOdomSpeed ctl_odom;
// 		memset(&ctl_odom,0,sizeof(SOdomSpeed));
// 		SPos amcl_pos;
// 		memset(&amcl_pos,0,sizeof(SPos));

		int nArgs = params.size();
		if(nArgs > 9){

// 			ctl_odom.x_ = (double)params[0];
// 			ctl_odom.y_ = (double)params[1];
// 			ctl_odom.th_ = (double)params[2];
// 			ctl_odom.vx_ = (double)params[3];
// 			ctl_odom.vy_ = (double)params[4];
// 			ctl_odom.vw_ = (double)params[5];
// 
// 			amcl_pos.x_ = (double)params[6];
// 			amcl_pos.y_ = (double)params[7];
// 			amcl_pos.th_ = (double)params[8];

			std::vector<int> v_path;
			int task_index = (int)TASK_MANAGE.create_open_ctl(params);

			if (task_index >= 0){
				result[0] = task_index;
				result[1] = "create create_open_ctl successful";
			}else{
				result[0] = (int)-1;
				result[1] = "create_open_ctl err£¡";
			}


		}else{
			result[0] = (int)-1;
			result[1] = "create_open_ctl para err£¡";
		}

	};
};

class create_fix_path : public XmlRpc::XmlRpcServerMethod
{
public:

	create_fix_path(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("create_fix_path", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{



		int nArgs = params.size();
		if(nArgs > 0){


			int task_index = (int)TASK_MANAGE.create_fix_path(params);

			if (task_index >= 0){
				result[0] = task_index;
				result[1] = "create create_fix_path successful";
			}else{
				result[0] = (int)-1;
				result[1] = "create_fix_path err£¡";
			}


		}else{
			result[0] = (int)-1;
			result[1] = "create_fix_path para err£¡";
		}

	};
};

class create_fork : public XmlRpc::XmlRpcServerMethod
{
public:

	create_fork(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("create_fork", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{



		int nArgs = params.size();
		if(nArgs > 0){


			int task_index = (int)TASK_MANAGE.create_fork(params);

			if (task_index >= 0){
				result[0] = task_index;
				result[1] = "create create_fork successful";
			}else{
				result[0] = (int)-1;
				result[1] = "create_fork err£¡";
			}


		}else{
			result[0] = (int)-1;
			result[1] = "create_fork para err£¡";
		}

	};
};
class create_task_act : public XmlRpc::XmlRpcServerMethod
{
public:

	create_task_act(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("create_task_act", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{



		int nArgs = params.size();
		if(nArgs > 0){


			int task_index = (int)TASK_MANAGE.create_task_act(params);

			if (task_index >= 0){
				result[0] = task_index;
				result[1] = "create_task_act successful";
			}else{
				result[0] = (int)-1;
				result[1] = "create_task_act err£¡";
			}


		}else{
			result[0] = (int)-1;
			result[1] = "create_task_act para err£¡";
		}

	};
};
class remove_task : public XmlRpc::XmlRpcServerMethod
{
public:

	remove_task(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("remove_task", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{


		int nArgs = params.size();
		if(nArgs > 0){

			int i_task_id  = (int)params[0];
			int task_size = (int)TASK_MANAGE.remove_task(i_task_id);


			//return del task size
			//input -1 del all task return del task size
			//input >=0 del exactly task return 0 means del error
			//                           return 1 means  del ok
			result[0] = task_size;
			result[1] = "remove_task successful ";


		}else{
			result[0] = (int)-1;
			result[1] = "remove_task para err£¡";
		}

	};
};

class force_complete : public XmlRpc::XmlRpcServerMethod
{
public:

	force_complete(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("force_complete", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{


		int nArgs = params.size();
		if(nArgs > 0){

			int i_task_id  = (int)params[0];
			int task_size = (int)TASK_MANAGE.force_complete(i_task_id);


			//return complete task size
			//input -1 deal all task return del task size
			//input >=0 deal exactly task return 0 means complete error
			//                           return 1 means  complete ok
			result[0] = task_size;
			result[1] = "force_complete task successful ";


		}else{
			result[0] = (int)-1;
			result[1] = "force_complete task para err£¡";
		}

	};
};
class redo : public XmlRpc::XmlRpcServerMethod
{
public:

	redo(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("redo", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{


		int nArgs = params.size();
		if(nArgs > 0){

			int i_task_id  = (int)params[0];
			int task_size = (int)TASK_MANAGE.redo(i_task_id);


			//return redo task size
			//input -1 redo all task return redo task size
			//input >=0 deal exactly task return 0 means redo error
			//                           return 1 means  redo ok
			result[0] = task_size;
			result[1] = "redo task successful ";


		}else{
			result[0] = (int)-1;
			result[1] = "redo task para err£¡";
		}

	};
};

class get_sim_init_pos : public XmlRpc::XmlRpcServerMethod
{
public:

	get_sim_init_pos(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_sim_init_pos", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{


		SPos pos;
		pos.x_ = 0;	
		pos.y_ = 0;
		pos.th_ = 0;
		TASK_MANAGE.get_sim_init(pos);
		result[0] = double(pos.x_);
		result[1] = double(pos.y_);
		result[2] = double(pos.th_);

	};
};


class rpc_task_server
{
public:

	rpc_task_server();
	~rpc_task_server();

	bool init(int i_task_rpc_port, bool b_sim = false);
	void destruct();

	

protected:
private:
	
	
	//rpc
private:

	void init_s();
	void th_rpc_(void);
	

	XmlRpc::XmlRpcServer s_;

	set_onboard_project* set_onboard_project_;
	create_rand_path* create_rand_path_;
	create_specified_path* create_specified_path_;
	create_charge_path* create_charge_path_;
	create_open_ctl* create_open_ctl_;
	create_fix_path* create_fix_path_;
	create_fork* create_fork_;
	create_task_act* create_task_act_;

	get_feadback* get_feadback_;
	remove_task* remove_task_;
	force_complete* force_complete_;
	redo* redo_;
	get_sim_init_pos* get_sim_init_pos_;

	bool b_sim_;

};

#endif //_RPC_TASK_SERVER_KYOSHO_KYOSHO_20200912_
