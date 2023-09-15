#ifndef _ROBOT_RPC_BIND_2015_08_07_
#define _ROBOT_RPC_BIND_2015_08_07_

#include "XmlRpc.h"
#include "mapserver/map_def.h"
#include "interface/data_server.h"
#include "interface/view_data.h"
#include "interface/cfg.hpp"
//using namespace XmlRpc;


class getLaser : public XmlRpc::XmlRpcServerMethod
{
public:
	getLaser(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_laser", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		std::vector<double> v_dist;
		//std::vector<double> v_rssi;

		XmlRpc::XmlRpcValue res;

		Singleton_Data_Server::get_mutable_instance().get_Laser_data(v_dist);
		
		int index = 0;

		for (int i=0; i<v_dist.size(); ++i){
			//v_list.push_back( double(params[i]));
			res[index++] = double(v_dist[i]);
		}
		
// 		for (int i=0; i<v_rssi.size(); ++i){
// 			//v_list.push_back( double(params[i]));
// 			res[index++] = double(v_rssi[i]);
// 		}
	
		
		result  = res;

		
		
	};
};

class getUsedLaser : public XmlRpc::XmlRpcServerMethod
{
public:
	getUsedLaser(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_used_laser", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		std::vector<double> v_dist;
		std::vector<double> v_angle;

		XmlRpc::XmlRpcValue res;

		Singleton_Data_Server::get_mutable_instance().get_Used_Laser_data(v_dist,v_angle);

		int index = 0;

		for (int i=0; i<v_dist.size(); ++i){
			//v_list.push_back( double(params[i]));
			res[index++] = double(v_angle[i]);
			res[index++] = double(v_dist[i]);
		}

		// 		for (int i=0; i<v_rssi.size(); ++i){
		// 			//v_list.push_back( double(params[i]));
		// 			res[index++] = double(v_rssi[i]);
		// 		}


		result  = res;
	


	};
};
class getExLaser : public XmlRpc::XmlRpcServerMethod
{
public:
	getExLaser(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_ex_laser", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		std::vector<double> v_dist;
		std::vector<double> v_angle;

		XmlRpc::XmlRpcValue res;

		Singleton_Data_Server::get_mutable_instance().get_Ex_Laser_data(v_dist,v_angle);

		int index = 0;

		for (int i=0; i<v_dist.size(); ++i){
			//v_list.push_back( double(params[i]));
			res[index++] = double(v_angle[i]);
			res[index++] = double(v_dist[i]);
		}

		// 		for (int i=0; i<v_rssi.size(); ++i){
		// 			//v_list.push_back( double(params[i]));
		// 			res[index++] = double(v_rssi[i]);
		// 		}


		result  = res;



	};
};
class getParticles : public XmlRpc::XmlRpcServerMethod
{
public:
	getParticles(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_particles", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
	
		std::vector<SparticleFAW> v_particle;
		//std::vector<double> v_rssi;

		XmlRpc::XmlRpcValue res;

		Singleton_Data_Server::get_mutable_instance().get_particles(v_particle);

		int index = 0;

		for (int i=0; i<v_particle.size(); ++i){
			//v_list.push_back( double(params[i]));
			res[index++] = double(v_particle[i].x);
			res[index++] = double(v_particle[i].y);
			res[index++] = double(v_particle[i].th);
			res[index++] = double(v_particle[i].aw);
		}

		// 		for (int i=0; i<v_rssi.size(); ++i){
		// 			//v_list.push_back( double(params[i]));
		// 			res[index++] = double(v_rssi[i]);
		// 		}
		//std::cout<<"get particles:"<<index<<std::endl;

		result  = res;



	};
};

class get_robot_pos : public XmlRpc::XmlRpcServerMethod
{
public:
	get_robot_pos(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_robot_pos", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		double x = 0;
		double y = 0;
		double th = 0;


		Singleton_Data_Server::get_mutable_instance().get_robot_pos(x,y,th);

		result[0] = x;
		result[1] = y;
		result[2] = th;
		
		
	};
};

class get_robot_pos_hb : public XmlRpc::XmlRpcServerMethod
{
public:
	get_robot_pos_hb(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_robot_pos_hb", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		double x = 0;
		double y = 0;
		double th = 0;

		SHeartBeat hb;
 		int nArgs = params.size();
 		if(nArgs > 1){
 			
			hb.i_heart_beat_ = int(params[0]);
			hb.i_sim_speed_ = int(params[1]);
 		}else{
 			hb.i_heart_beat_ = 0;
 			hb.i_sim_speed_ = 0;
 		}
		
		
		Singleton_Data_Server::get_mutable_instance().get_robot_pos(x,y,th);
		Singleton_Data_Server::get_mutable_instance().set_heart_beat(hb);

		result[0] = x;
		result[1] = y;
		result[2] = th;


	};
};

class get_robot_odom : public XmlRpc::XmlRpcServerMethod
{
public:
	get_robot_odom(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_robot_odom", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		double x = 0;
		double y = 0;
		double th = 0;
		double vx = 0;
		double vy = 0;
		double vw = 0;


		Singleton_Data_Server::get_mutable_instance().get_robot_odom(x,y,th,vx,vy,vw);

		result[0] = x;
		result[1] = y;
		result[2] = th;
		result[3] = vx;
		result[4] = vy;
		result[5] = vw;

	};
};

class get_para : public XmlRpc::XmlRpcServerMethod
{
public:

	get_para(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_para", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		int nArgs = params.size();
		if(nArgs == 1){

			std::string name = params[0];

			std::string value = Singleton_Data_Server::get_mutable_instance().get_para(name);
			result[0] = value;
			std::cout<<"get_para name:"<<name<<" value:"<<value<<std::endl;
		}else{
			result[0] = "";
		}



	};
};
class setEstimate_pos : public XmlRpc::XmlRpcServerMethod
{
public:
	setEstimate_pos(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_estimate_pos", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		double x = 0;
		double y = 0;
		double th = 0;
		double para1 = 3.0;
		double para2 = 3.0;
		double para3 = 0;
		double para4 = 0;

		int nArgs = params.size();
		if(nArgs > 2){

			x = params[0];
			y = params[1];
			th = params[2];

			std::cout<<"set current pos x:"<<x<<" y:"<<y<<" th:"<<th<<std::endl;
		}
		std::cout<<"size:"<<nArgs<<std::endl;


		if(nArgs > 6){
			para1 = params[3];
			para2 = params[4];
			para3 = params[5];
			para4 = params[6];
		}
		//Singleton_Data_Server::get_mutable_instance().set_estimate_pos(1,2,3,4,5,6,7);
		if( Singleton_Data_Server::get_mutable_instance().set_estimate_pos(x,y,th,para1,para2,para3,para4)){
			Singleton_Data_Server::get_mutable_instance().set_amcl_run(true);
			std::cout<<"set estimate over! para1:"<<para1<<" para2:"<<para2<<" para3:"<<para3<<" para4:"<<para4<<std::endl;
			result = 99;
		}else{
			std::cout<<"set estimate err! para1:"<<para1<<" para2:"<<para2<<" para3:"<<para3<<" para4:"<<para4<<std::endl;
			result = -99;
		}
		

		
	};
};
class setSim_pos : public XmlRpc::XmlRpcServerMethod
{
public:
	setSim_pos(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_sim_pos", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs == 3){

			Singleton_Data_Server::get_mutable_instance().set_sim_pos(params[0],params[1],params[2]);

			double x = 0;
			double y = 0;
			double th = 0;

			x = params[0];
			y = params[1];
			th = params[2];

			std::cout<<"set sim pos x:"<<x<<" y:"<<y<<" th:"<<th<<std::endl;
		}


		result = 99;
	};
};

class setTarget_pos : public XmlRpc::XmlRpcServerMethod
{
public:
	setTarget_pos(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_target_pos", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs >= 3){
			
			Singleton_Data_Server::get_mutable_instance().set_target_pos(params[0],params[1],params[2]);
			
			double x = 0;
			double y = 0;
			double th = 0;

			x = params[0];
			y = params[1];
			th = params[2];

			std::cout<<"set target pos x:"<<x<<" y:"<<y<<" th:"<<th<<std::endl;
		}


		result = 99;
	};
};

class getGlobalPath : public XmlRpc::XmlRpcServerMethod
{
public:
	getGlobalPath(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_globla_path", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		std::list<SGridXY> v_path;
		//std::vector<double> v_rssi;

		XmlRpc::XmlRpcValue res;

		Singleton_Data_Server::get_mutable_instance().global_path_.rpc_global_path(v_path);

		int index = 0;
		std::list<SGridXY>::iterator it = v_path.begin();
		for ( ; it != v_path.end(); ++it ){
			//v_list.push_back( double(params[i]));
			res[index++] = int(it->x_ );
			res[index++] = int(it->y_ );
			res[index++] = int(it->value_ );
		}

		// 		for (int i=0; i<v_rssi.size(); ++i){
		// 			//v_list.push_back( double(params[i]));
		// 			res[index++] = double(v_rssi[i]);
		// 		}


		result  = res;



	};
};
class getLocalMap : public XmlRpc::XmlRpcServerMethod
{
public:
	getLocalMap(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_local_map", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		std::list<SGridXY> v_map;
		//std::vector<double> v_rssi;

		XmlRpc::XmlRpcValue res;
		std::string map_name = params[0];
		if ( map_name == SHARED_LASER_INF_MAP )
		{
			Singleton_Data_Server::get_mutable_instance().laser_inf_map_.rpc_local_map(v_map);
			//std::cout<<"get laser_inf map:"<<map_name<<std::endl;
		}else if( map_name == LOCAL_PATH_MAP ){
			Singleton_Data_Server::get_mutable_instance().path_map_.rpc_local_map(v_map);
			//std::cout<<"get path map:"<<map_name<<std::endl;
		}
		else if( map_name == GOAL_MAP ){
			Singleton_Data_Server::get_mutable_instance().goal_map_.rpc_local_map(v_map);
			//std::cout<<"get goal map:"<<map_name<<std::endl;
		}

// 		else if(){
// 
// 		}
		

		int index = 0;
		std::list<SGridXY>::iterator it = v_map.begin();
		for ( ; it != v_map.end(); ++it ){
			//v_list.push_back( double(params[i]));
			res[index++] = int(it->x_ );
			res[index++] = int(it->y_ );
			res[index++] = int(it->value_ );
		}

		// 		for (int i=0; i<v_rssi.size(); ++i){
		// 			//v_list.push_back( double(params[i]));
		// 			res[index++] = double(v_rssi[i]);
		// 		}


		result  = res;



	};
};
class setStop : public XmlRpc::XmlRpcServerMethod
{
public:

	setStop(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_stop", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs == 1){
			int istop = params[0];
			if( istop > 0){
				//Singleton_Data_Server::get_mutable_instance().set_stop_navigation(true);
			}

			std::cout<<"set stop "<<params[0]<<std::endl;
		}


		result = 99;
	};
};

class getLocal_show : public XmlRpc::XmlRpcServerMethod
{
public:

	getLocal_show(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_local_show", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		XmlRpc::XmlRpcValue res;

		LocalShow local_show;
		Singleton_Data_Server::get_mutable_instance().get_local_show(local_show);
		res[0] = local_show.C_.x_;
		res[1] = local_show.C_.y_;
		res[2] = local_show.L_.x_;
		res[3] = local_show.L_.y_;
		res[4] = local_show.H_.x_;
		res[5] = local_show.H_.y_;

		res[6] = local_show.v_;
		res[7] = local_show.w_;

		res[8] = local_show.line_.p_.x_;
		res[9] = local_show.line_.p_.y_;
		res[10] = local_show.line_.angle_;

		result  = res;
	};
};



class getStatus : public XmlRpc::XmlRpcServerMethod
{
public:

	getStatus(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_status", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		U8 status = 0;
		U16 err_code = 0;
		//Singleton_Data_Server::get_mutable_instance().get_status(status,err_code);
		result[0] = status;
		result[1] = err_code;


		//std::cout<<"getStatus:"<<std::endl;


	};
};

class getLaserfilter : public XmlRpc::XmlRpcServerMethod
{
public:
	getLaserfilter(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_laser_filter", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		std::vector<double> v_dist;
		std::vector<double> v_angle;

		XmlRpc::XmlRpcValue res;

		//Singleton_Data_Server::get_mutable_instance().get_Laser_filter_data(v_dist,v_angle);

		int index = 0;

		for (int i=0; i<v_dist.size(); ++i){
			//v_list.push_back( double(params[i]));
			res[index++] = double(v_angle[i]);
			res[index++] = double(v_dist[i]);
		}

		// 		for (int i=0; i<v_rssi.size(); ++i){
		// 			//v_list.push_back( double(params[i]));
		// 			res[index++] = double(v_rssi[i]);
		// 		}


		result  = res;



	};
};

class getDevStatus : public XmlRpc::XmlRpcServerMethod
{
public:

	getDevStatus(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_dev_status", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		XmlRpc::XmlRpcValue res;
		int i_dev_id = -1;
		if (params.size() > 0){
			i_dev_id = int(params[0]);
		}else{
			return;
		}
		if( -1 != i_dev_id){
			
			SPubDevStatus ds;
			Singleton_Data_Server::get_mutable_instance().get_dev_status(ds,i_dev_id);
			int i = 0;
			res[i]["name"] = std::string(ds.name_);
			res[i]["id"] = int(ds.dev_status_.device_id_);
			res[i]["status"] = int(ds.dev_status_.status_);
			res[i]["err_code"] = int(ds.dev_status_.err_code_);
			res[i]["cycle_ms"] = double(ds.dev_status_.cycle_ms_);
			res[i]["run_ms"] = double(ds.dev_status_.run_ms_);

		}else{
			std::map<int,SPubDevStatus> dev_status;
			Singleton_Data_Server::get_mutable_instance().get_dev_status(dev_status);


			int i = 0;
			std::map<int,SPubDevStatus>::iterator it = dev_status.begin();
			for (; it != dev_status.end() ; ++it)
			{
				SPubDevStatus &ds(it->second);
				res[i]["name"] = std::string(ds.name_);
				res[i]["id"] = int(ds.dev_status_.device_id_);
				res[i]["status"] = int(ds.dev_status_.status_);
				res[i]["err_code"] = int(ds.dev_status_.err_code_);
				res[i]["cycle_ms"] = double(ds.dev_status_.cycle_ms_);
				res[i]["run_ms"] = double(ds.dev_status_.run_ms_);
				i++;
			}


			
		}
		
		result = res;

		//std::cout<<"getStatus:"<<std::endl;


	};
};

class setMappingCmd : public XmlRpc::XmlRpcServerMethod
{
public:
	setMappingCmd(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_mapping_cmd", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs == 1){

			std::string str = params[0];

			Singleton_Data_Server::get_mutable_instance().set_mapping_cmd(str);

			std::cout<<"set mapping cmd:"<<str<<std::endl;
		}


		result = 99;
	};
};
class get_file_list : public XmlRpc::XmlRpcServerMethod
{
public:
	get_file_list(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_file_list", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs >= 1){

			int index = 0;

			std::string str_path = params[0];
			std::string str_file_nm = params[1];

			

			std::vector<std::string> v_str_name;
			Singleton_Data_Server::get_mutable_instance().get_file_list(v_str_name,str_path,str_file_nm);
			std::vector<std::string>::iterator it = v_str_name.begin();
			
			for ( ; it != v_str_name.end() ; ++it)
			{
				result[index++] = *it;
			}
			std::cout<<"get_file_list cmd:"<<str_path<<std::endl;
		}
	};
};

class get_map : public XmlRpc::XmlRpcServerMethod
{
public:
	get_map(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_map", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs == 1){

			int index = 0;

			std::string str_map_name = params[0];

			std::vector<int> v_data;
			std::cout<<"begin get_map data!"<<std::endl;

			int occupy_size = Singleton_Data_Server::get_mutable_instance().get_map(v_data,str_map_name);
			if (occupy_size > 600000)
			{
				std::cout<<"map so large!!!!!!"<<std::endl;
				return;

			}
			
			std::vector<int>::iterator it = v_data.begin();

			for ( ; it != v_data.end() ; ++it)
			{
				result[index++] = *it;
			}
			std::cout<<"get_map over:"<<str_map_name<<std::endl;
		}
	};
};
class get_map_separate : public XmlRpc::XmlRpcServerMethod
{
public:
	get_map_separate(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_map_separate", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs == 2){

			int index = 0;

			std::string str_cmd = params[0];
			std::string str_map_name = params[1];

			std::vector<int> v_data;
			std::cout<<"begin get_map data!"<<std::endl;

			int occupy_size = Singleton_Data_Server::get_mutable_instance().get_map(v_data,str_cmd,str_map_name);
			if ( str_cmd == "load"){
				//load
				result[0] = std::string("load");
				result[1] = occupy_size;
			}else{
				//read data
				result[0] = std::string("read");
				std::vector<int>::iterator it = v_data.begin();
				int index = 1;
				for ( ; it != v_data.end() ; ++it)
				{
					result[index++] = *it;
				}
			}

			std::cout<<"get_map read data:"<<v_data.size()<<std::endl;
		}
	};
};
class set_map_cmd : public XmlRpc::XmlRpcServerMethod
{
public:
	set_map_cmd(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_map_cmd", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs == 1){

			std::string str = params[0];

			Singleton_Data_Server::get_mutable_instance().set_map_cmd(str);

			std::cout<<"set map cmd:"<<str<<std::endl;
		}


		result = 99;
	};
};
class set_map : public XmlRpc::XmlRpcServerMethod
{
public:
	set_map(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_map", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int type = params[0];

		if(type == -1 ){
			//lock and stop amcl
			Singleton_Data_Server::get_mutable_instance().set_amcl_run(false);
			std::cout<<"xml set_map:set_amcl_run false"<<std::endl;
			Singleton_Data_Server::get_mutable_instance().set_map_lock(true);
			std::cout<<"xml set_map:set_map_lock true"<<std::endl;
			Singleton_Data_Server::get_mutable_instance().set_map_fill(MAP_UNKNOWN);
			std::cout<<"xml set_map:set_map_fill unknow"<<std::endl;
		}else if(type == -2){
			std::cout<<"xml set_map:set_map_value over! "<<std::endl;
			Singleton_Data_Server::get_mutable_instance().set_map_lock(false);
			std::cout<<"xml set_map:set_map_lock false! "<<std::endl;
			Singleton_Data_Server::get_mutable_instance().set_map_reflash();
			std::cout<<"xml set_map:set_map_reflash ! "<<std::endl;

			std::cout<<"set map over!"<<std::endl;
		}else{

			int nArgs = params.size();
			
			if(nArgs > 1){

				for (int i = 1; i < nArgs ; i = i +3 )
				{
					int gx = (int) params[i + 0];
					int gy = (int) params[i + 1];
					int value = (int) params[i + 2];
					Singleton_Data_Server::get_mutable_instance().set_map_value(gx,gy,value);

				}
			}
			std::cout<<"xml set_map:set_map_value connt:"<<params[0]<<std::endl;
		}


		result[0] = int(0);
	};
};

class set_onboard_map : public XmlRpc::XmlRpcServerMethod
{
public:
	set_onboard_map(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_onboard_map", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		std::string map_name = params[0];

		//lock and stop amcl
		std::string map_path = "./map/";
		Config::getConfig("dev_map_path",map_path);
		map_path += map_name;
		if(!cComm::FileExist(map_path)){
			std::cout<<"set_onboard_map file not exist!"<<map_path<<std::endl;
			result[0] = 1;
			return;
		}
		std::stringstream ss;
		ss<<"load "<<map_name;
		Singleton_Data_Server::get_mutable_instance().set_amcl_run(false);
		Singleton_Data_Server::get_mutable_instance().set_onboard_map(map_path);
		Singleton_Data_Server::get_mutable_instance().set_loop_clousure_cmd(ss.str());
		Singleton_Data_Server::get_mutable_instance().set_map_reflash();
		std::cout<<"xml set_map:set_map_reflash ! "<<std::endl;

		std::cout<<"set onboard map over!"<<std::endl;

		result[0] = int(0);
	};
};
class set_log_cmd : public XmlRpc::XmlRpcServerMethod
{
public:

	set_log_cmd(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_log_cmd", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs == 1){

			std::string str = params[0];

			int ires = Singleton_Data_Server::get_mutable_instance().set_log_cmd(str);
			result[0] = ires;

			std::cout<<"set log cmd:"<<str<<" ires:"<<ires<<std::endl;
		}


		result = 99;
	};
};
class set_log_ex_cmd : public XmlRpc::XmlRpcServerMethod
{
public:

	set_log_ex_cmd(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_log_ex_cmd", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs == 1){

			std::string str = params[0];

			int ires = Singleton_Data_Server::get_mutable_instance().set_log_ex_cmd(str);
			result[0] = ires;

			std::cout<<"set log ex cmd:"<<str<<" ires:"<<ires<<std::endl;
		}


		result = 99;
	};
};
class set_speed_cmd : public XmlRpc::XmlRpcServerMethod
{
public:

	set_speed_cmd(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_speed_cmd", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs == 1){

			std::string str = params[0];

			Singleton_Data_Server::get_mutable_instance().set_speed_cmd(str);

			std::cout<<"set log cmd:"<<str<<std::endl;
		}


		result = 99;
	};
};
// 
// class set_log_upload : public XmlRpc::XmlRpcServerMethod
// {
// public:
// 
// 	set_log_upload(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_log_upload", s) {};
// 
// 	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
// 	{
// 		int nArgs = params.size();
// 		if(nArgs == 1){
// 
// 			std::string str = params[0];
// 			SPUB_BAG p_bag;
// 
// 			if(Singleton_Data_Server::get_mutable_instance().upload_bag(p_bag,str)){
// 
// 			}
// 			std::cout<<"set log cmd:"<<str<<std::endl;
// 		}
// 
// 		result = 99;
// 	};
// };

class get_process_bar : public XmlRpc::XmlRpcServerMethod
{
public:
	get_process_bar(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_process_bar", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs == 1){
			std::string str_pro_name = params[0];
			
			SProcess_Bar pro_bar;
			memset(&pro_bar,0,sizeof(SProcess_Bar));

			Singleton_Data_Server::get_mutable_instance().get_process_bar(pro_bar);
			std::string str_current = pro_bar.name_;
			if ( ( str_pro_name.length() < 1 ) || ( str_current == str_pro_name ))
			{
				result[0]  = std::string(pro_bar.name_);
				result[1]  = int(pro_bar.current_step_);
				result[2]  = int(pro_bar.max_step_);
			}
			
			//std::cout<<"get_process_bar!"<<std::endl;
		}
	};
};

class get_pub_bag : public XmlRpc::XmlRpcServerMethod
{
public:

	get_pub_bag(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_pub_bag", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		result[0] = int(0);
		int nArgs = params.size();
		if(nArgs == 1){
			
			char* ch_data = 0;
			int ilen = 0;
			if(Singleton_Data_Server::get_mutable_instance().get_bag(ch_data,ilen)){
				result[0] = int(ilen);
				result[1] = XmlRpc::XmlRpcValue(ch_data,ilen);

				delete[] ch_data;
				//std::cout<<"get_pub_bag len:"<<ilen<<std::endl;
			}else{
				result[0] = int(0);
				result[1] = "";
				//std::cout<<"get_pub_bag empty!"<<std::endl;
			}
			
			
			
		}
	};
};
class get_pub_bag_ex : public XmlRpc::XmlRpcServerMethod
{
public:

	get_pub_bag_ex(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_pub_bag_ex", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		result[0] = int(0);
		int nArgs = params.size();
		if(nArgs == 1){

			char* ch_data = 0;
			int ilen = 0;
			if(Singleton_Data_Server::get_mutable_instance().get_ex_bag(ch_data,ilen)){
				result[0] = int(ilen);
				result[1] = XmlRpc::XmlRpcValue(ch_data,ilen);

				delete[] ch_data;
				//std::cout<<"get_pub_bag len:"<<ilen<<std::endl;
			}else{
				result[0] = int(0);
				result[1] = "";
				//std::cout<<"get_pub_bag empty!"<<std::endl;
			}



		}
	};
};
class get_pub_laser_ex_ref : public XmlRpc::XmlRpcServerMethod
{
public:

	get_pub_laser_ex_ref(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_pub_laser_ex_ref", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		result[0] = int(0);
		int nArgs = params.size();
		if(nArgs == 1){

			char* ch_data = 0;
			int ilen = 0;
			if(Singleton_Data_Server::get_mutable_instance().get_laser_ex_ref(ch_data,ilen)){
				
				
				result[0] = int(ilen);
				result[1] = XmlRpc::XmlRpcValue(ch_data,ilen);

				delete[] ch_data;
				//std::cout<<"get_pub_bag len:"<<ilen<<std::endl;
			}else{
				result[0] = int(0);
				result[1] = "";
				//std::cout<<"get_pub_bag empty!"<<std::endl;
			}



		}
	};
};
class get_pub_laser_ex_cab : public XmlRpc::XmlRpcServerMethod
{
public:

	get_pub_laser_ex_cab(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_pub_laser_ex_cab", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		std::vector<double> v_x;
		std::vector<double> v_y;

		XmlRpc::XmlRpcValue res;

		Singleton_Data_Server::get_mutable_instance().get_Excab_Laser_data(v_x,v_y);

		int index = 0;

		for (int i=0; i<v_x.size(); ++i){
			//v_list.push_back( double(params[i]));
			res[index++] = double(v_x[i]);
			res[index++] = double(v_y[i]);
		}

		// 		for (int i=0; i<v_rssi.size(); ++i){
		// 			//v_list.push_back( double(params[i]));
		// 			res[index++] = double(v_rssi[i]);
		// 		}


		result  = res;
	};
};
class get_sim_laser : public XmlRpc::XmlRpcServerMethod
{
public:

	get_sim_laser(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_sim_laser", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		std::vector<double> v_x;
		std::vector<double> v_y;

		XmlRpc::XmlRpcValue res;

		Singleton_Data_Server::get_mutable_instance().get_Sim_Laser_data(v_x,v_y);

		int index = 0;

		for (int i=0; i<v_x.size(); ++i){

			res[index++] = double(v_x[i]);
			res[index++] = double(v_y[i]);
		}


		result  = res;
	};
};
class set_path : public XmlRpc::XmlRpcServerMethod
{
public:
	set_path(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_path", s) {};

	void execute(  XmlRpc::XmlRpcValue & params, XmlRpc::XmlRpcValue& result)
	{

		std::vector<SOdomSpeed> run_path;
		std::string str_path;
		if (params.size() > 0)
		{
			str_path = std::string(params[0]);
		}
		SOdomSpeed speed;
		for(int i = 1; i<params.size()-1; i += 6)
		{
			speed.x_ = double(params[ i + 0 ]);
			speed.y_ = double(params[ i + 1 ]);
			speed.th_ = double(params[ i + 2 ]);
			speed.vx_ = double(params[ i + 3 ]);
			speed.vy_ = double(params[ i + 4 ]);
			speed.vw_ = double(params[ i + 5 ]);
			run_path.push_back(speed);
			//std::cout<<"path x,y:"<<temp.x_<<", "<<temp.y_<<std::endl;
		}

		Singleton_Data_Server::get_mutable_instance().set_path(str_path,run_path);

		std::cout<<"set task path:"<<str_path<<std::endl;

		//std::cout<<"run called in task set"<<std::endl;
		result  = 99;

	};
};


class set_seg_path : public XmlRpc::XmlRpcServerMethod
{
public:
	set_seg_path(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_seg_path", s) {};

	void execute(  XmlRpc::XmlRpcValue & params, XmlRpc::XmlRpcValue& result)
	{
		XmlRpc::XmlRpcValue::BinaryData vpath = params[0];
		if (vpath.size())
		{

			//std::vector<SOdomSpeed> run_path( (SOdomSpeed*)&vpath[0], ((SOdomSpeed*)(&vpath[0])) + (vpath.size()/sizeof(SOdomSpeed)));
			//std::copy((SOdomSpeed*)&vpath[0],((SOdomSpeed*)(&vpath[0])) + (vpath.size()/sizeof(SOdomSpeed) + 1)  ,run_path.begin());
			Singleton_Data_Server::get_mutable_instance().set_seg_path(&vpath[0],vpath.size());
		}
		
		result  = 99;

	};
};
class get_check_laser_range : public XmlRpc::XmlRpcServerMethod
{
public:
	get_check_laser_range(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_check_laser_range", s) {};

	void execute(  XmlRpc::XmlRpcValue & params, XmlRpc::XmlRpcValue& result)
	{
		int itype = params[0];
		char* data = 0;
		int ilen = 0;
		Singleton_Data_Server::get_mutable_instance().get_check_laser_range((Range_type)itype,data,ilen);
		result[0] = XmlRpc::XmlRpcValue(data,ilen);
		
	}
};

class get_chk_laser_show : public XmlRpc::XmlRpcServerMethod
{
public:
	get_chk_laser_show(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_chk_laser_show", s) {};

	void execute(  XmlRpc::XmlRpcValue & params, XmlRpc::XmlRpcValue& result)
	{
		std::vector<int> v_show;
		Singleton_Data_Server::get_mutable_instance().get_check_laser_range_show(v_show);
		std::vector<int>::iterator it = v_show.begin();
		int i = 0;
		for ( ; it != v_show.end() ; ++it )
		{
			result[i++] = (int)(*it);
		}

	}
};

class get_sim_path : public XmlRpc::XmlRpcServerMethod
{
public:
	get_sim_path(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_sim_path", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
	
		U8* data = 0;
		int ilen = 0;
		Singleton_Data_Server::get_mutable_instance().sim_path_.rpc_get_data(data,ilen);
		
		if (ilen > 0)
		{
			XmlRpc::XmlRpcValue res(data,ilen);
			result  = res;

			if (data)
			{
				delete[] data;
				data = 0;
			}
			
		}
		

	};
};


class get_remote_file : public XmlRpc::XmlRpcServerMethod
{
public:

	get_remote_file(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_remote_file", s) {
		p_data_ = new char[500000];
		memset(p_data_,0,500000);
		ilen_ = 500000;
	};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		XmlRpc::XmlRpcValue res;
		std::string str_cmd = params[0];
		

		ilen_ = 500000;
		int ires = Singleton_Data_Server::get_mutable_instance().get_remote_file(p_data_,ilen_,str_cmd);
		res[0] = ires;
		if ( ires > 0 )
		{
			res[1] = XmlRpc::XmlRpcValue(p_data_,ilen_);
		}

		result  = res;
	};

private:
	char* p_data_;
	int ilen_;
};

class get_scan_reflector : public XmlRpc::XmlRpcServerMethod
{
public:
	get_scan_reflector(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_scan_reflector", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		SReflector ref;

		XmlRpc::XmlRpcValue res;

		Singleton_Data_Server::get_mutable_instance().get_reflector(ref);


		for ( int i = 0 ; i < ref.used_ ; ++i )
		{
	
			res[i]["id"] = int(ref.id_[i]);
			res[i]["x"] = double(ref.pos_[i].x_);
			res[i]["y"] = double(ref.pos_[i].y_);

		}


		result  = res;



	};
};


class get_reflector_pos : public XmlRpc::XmlRpcServerMethod
{
public:
	get_reflector_pos(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_reflector_pos", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		SPOS_CONFIDENCE pos_confi;

		if( Singleton_Data_Server::get_mutable_instance().get_ref_pos(pos_confi)){
			result[0] = double(pos_confi.pos_.x_);
			result[1] = double(pos_confi.pos_.y_);
			result[2] = double(pos_confi.pos_.th_);
			result[3] = int(pos_confi.confidence_.b_amcl_confidence_);
			result[4] = double(pos_confi.confidence_.amcl_confidence_);
		}else{
			result[0] = 99;
		}
	};
};

class get_loop_closure : public XmlRpc::XmlRpcServerMethod
{
public:
	get_loop_closure(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_loop_closure", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		SLoopCLosurePos spos;
		if (Singleton_Data_Server::get_mutable_instance().get_loop_closure_pos(spos))
		{
			result[0] = spos.pos_.x_;
			result[1] = spos.pos_.y_;
			result[2] = spos.pos_.th_;
			result[3] = spos.confidence_;
		}else{
			result[0] = 99.0;
		}
		
		

	};
};

class set_loop_closure_cmd : public XmlRpc::XmlRpcServerMethod
{
public:

	set_loop_closure_cmd(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_loop_closure_cmd", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs == 1){

			std::string str = params[0];

			Singleton_Data_Server::get_mutable_instance().set_loop_clousure_cmd(str);

			std::cout<<"set loop_clousure cmd:"<<str<<std::endl;
		}


		result = 99;
	};
};

class get_amcl_entropy : public XmlRpc::XmlRpcServerMethod
{
public:
	get_amcl_entropy(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_amcl_entropy", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		SAMCL_ENTROPY ae;
		if (Singleton_Data_Server::get_mutable_instance().get_amcl_entropy(ae))
		{
			result[0] = int(ae.b_amcl_entropy_);
			result[1] = double(ae.amcl_xy_entropy_);
			result[2] = double(ae.amcl_theta_entropy_);
			result[3] = double(ae.amcl_entropy_);
			

		}else{
			result[0] = 99.0;
		}



	};
};


class get_amcl_confidence : public XmlRpc::XmlRpcServerMethod
{
public:
	get_amcl_confidence(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_amcl_confidence", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		SAMCL_CONFIDENCE cf;
		if (Singleton_Data_Server::get_mutable_instance().get_amcl_confidence(cf))
		{
			result[0] = int(cf.b_amcl_confidence_);
			result[1] = double(cf.amcl_confidence_);
		
		}else{
			result[0] = 99.0;
		}



	};
};

class do_upload_map : public XmlRpc::XmlRpcServerMethod
{
public:

	do_upload_map(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("do_upload_map", s) {

	};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		XmlRpc::XmlRpcValue res;
		std::string str_cmd = params[0];
		std::vector<std::string> v_res;
		cComm::SplitString(str_cmd," ",v_res);
		assert( v_res.size() > 0 );

		if ( "load" == v_res[0] && v_res.size() > 1)
		{
			std::vector<int> v_data;//load data ignore
			if (!Singleton_Data_Server::get_mutable_instance().get_map(v_data,v_res[0],v_res[1]))
			{
				result[0] = -1;
				return;
			}else{
				result[0] = -1;
				return;
			}

		}else if ( "read" == v_res[0] ){

			XmlRpc::XmlRpcValue::BinaryData vdata = params[1];

			if (!Singleton_Data_Server::get_mutable_instance().download_file(&vdata[0],vdata.size()))
			{
				result[0] = -3;
				return;
			}
		}else{
			result[0] = -4;
			return;
		}

		result[0] = 99;

	};

};

class do_download_file : public XmlRpc::XmlRpcServerMethod
{
public:

	do_download_file(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("do_download_file", s) {
	
	};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		XmlRpc::XmlRpcValue res;
		std::string str_cmd = params[0];
		std::vector<std::string> v_res;
		cComm::SplitString(str_cmd," ",v_res);
		assert( v_res.size() > 0 );

		if ( "open" == v_res[0] && v_res.size() > 1)
		{
			if (!Singleton_Data_Server::get_mutable_instance().download_file(v_res[0],v_res[1]))
			{
				result[0] = -1;
				return;
			}

		}else if ( "close" == v_res[0] ){
			if (!Singleton_Data_Server::get_mutable_instance().download_file(v_res[0]))
			{
				result[0] = -2;
				return;
			}
		}else if ( "write" == v_res[0] ){
			
			XmlRpc::XmlRpcValue::BinaryData vdata = params[1];
				
			if (!Singleton_Data_Server::get_mutable_instance().download_file(&vdata[0],vdata.size()))
			{
				result[0] = -3;
				return;
			}
		}else{
			result[0] = -4;
			return;
		}
		
		result[0] = 99;
		
	};

};

class get_view_data : public XmlRpc::XmlRpcServerMethod
{
public:

	get_view_data(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_view_data", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		
		int nArgs = params.size();
		if(nArgs == 1){

			
			std::vector<SView_Data> v_data;
			Singleton_View_Data::get_mutable_instance().get_view_data(v_data);

			U8* ch_data = 0;
			int ilen = 0;
			std::string str_name;

			if(v_data.size() > 0){

				int i = 0;
				std::vector<SView_Data>::iterator it = v_data.begin();
				for ( ; it != v_data.end() ; ++it ){
					str_name = it->name_;
					ilen = it->ilen_;
					ch_data = it->uc_data_;

					result[ i + 0 ] = str_name;
					result[ i + 1] = int(ilen);
					result[ i + 2] = XmlRpc::XmlRpcValue(ch_data,ilen);
					i += 3;

					delete[] ch_data;
				}
				
				//std::cout<<"get_pub_bag len:"<<ilen<<std::endl;
			}else{
				result[0] = "empty";

				//std::cout<<"get_pub_bag empty!"<<std::endl;
			}

		}
	};
};


class get_battery : public XmlRpc::XmlRpcServerMethod
{
public:
	get_battery(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_battery", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		SBattery bt;
		if (Singleton_Data_Server::get_mutable_instance().get_battery(bt))
		{
			result[0] = cComm::ConvertToString(bt.time_stamp_);
			result[1] = double(bt.voltage_);
			result[2] = double(bt.percent_);
			result[3] = double(bt.charge_current_);
			result[4] = double(bt.run_current_);
			result[5] = int(bt.set_contactor_out_);
			result[6] = int(bt.get_contactor_in_);

		}else{
			result[0] = 99.0;
		}



	};
};
class set_bt_contact : public XmlRpc::XmlRpcServerMethod
{
public:

	set_bt_contact(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_bt_contact", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs == 1){

			int bt_contact = (int)params[0];

			Singleton_Data_Server::get_mutable_instance().set_bt_contact(bt_contact);

			std::cout<<"set bt_contact cmd:"<<bt_contact<<std::endl;
		}


		result = 99;
	};
};



class get_special_loc_conpos : public XmlRpc::XmlRpcServerMethod
{
public:
	get_special_loc_conpos(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_special_loc_conpos", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		SPOS_CONFIDENCE conpos;
		if (Singleton_Data_Server::get_mutable_instance().get_special_loc_conpos(conpos))
		{
			result[0] = double(conpos.pos_.x_);
			result[1] = double(conpos.pos_.y_);
			result[2] = double(conpos.pos_.th_);

			result[3] = int(conpos.confidence_.b_amcl_confidence_);
			result[4] = double(conpos.confidence_.amcl_confidence_);

		}else{
			result[0] = 99.0;
		}



	};
};


class get_special_landmark : public XmlRpc::XmlRpcServerMethod
{
public:
	get_special_landmark(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_special_landmark", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		SWorldLM wlm;
		if (Singleton_Data_Server::get_mutable_instance().get_special_landmark(wlm))
		{
			result[0] = double(wlm.robot_in_world_.x_);
			result[1] = double(wlm.robot_in_world_.y_);
			result[2] = double(wlm.robot_in_world_.th_);

			result[3] = double(wlm.landmark_in_robot_.x_);
			result[4] = double(wlm.landmark_in_robot_.y_);
			result[5] = double(wlm.landmark_in_robot_.th_);

			result[6] = double(wlm.landmark_in_world_.x_);
			result[7] = double(wlm.landmark_in_world_.y_);
			result[8] = double(wlm.landmark_in_world_.th_);

		}else{
			result[0] = 99.0;
		}



	};
};

class set_sim_init_pos : public XmlRpc::XmlRpcServerMethod
{
public:
	set_sim_init_pos(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_sim_init_pos", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		SPos sim_init_pos;
		sim_init_pos.x_ = 0;
		sim_init_pos.y_ = 0;
		sim_init_pos.th_ = 0;

		int nArgs = params.size();
		if(nArgs > 2){

			sim_init_pos.x_ = double(params[0]);
			sim_init_pos.y_ = double(params[1]);
			sim_init_pos.th_ = double(params[2]);

			if( Singleton_Data_Server::get_mutable_instance().set_sim_init_pos(sim_init_pos)){
				std::cout<<"set_sim_init_pos x:"<<sim_init_pos.x_<<" y:"<<sim_init_pos.y_<<" th:"<<sim_init_pos.th_<<std::endl;
				result = 99;
			}else{
				std::cout<<"set_sim_init_pos pub err!"<<std::endl;
				result = -99;
			}

		}
		

	};
};
class set_pause : public XmlRpc::XmlRpcServerMethod
{
public:
	set_pause(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("set_pause", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int i_pause = int(params[0]);

		if( Singleton_Data_Server::get_mutable_instance().set_pause(i_pause)){
			std::cout<<"set_pause"<<i_pause<<std::endl;
			result[0] = 99;
		}else{
			std::cout<<"set_pause err!"<<i_pause<<std::endl;
			result[0] = -99;
		}


	};
};

class get_fork : public XmlRpc::XmlRpcServerMethod
{
public:
	get_fork(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_fork", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		SAct_Fork fork_para;
		if (Singleton_Data_Server::get_mutable_instance().get_fork(fork_para))
		{

			result[0] = int(fork_para.act_base_.node_from_);
			result[1] = int(fork_para.act_base_.node_to_);
			result[2] = double(fork_para.act_base_.trig_per_);
			result[3] = double(fork_para.act_base_.check_per_);

			result[4] = int(fork_para.act_base_.init_);
			result[5] = int(fork_para.act_base_.force_done_);

			result[6] = int(fork_para.act_base_.force_error_);
			result[7] = int(fork_para.act_base_.redo_);

			result[8] = double(fork_para.act_data_.level_);
			result[9] = double(fork_para.act_data_.speed_);

		}else{
			result[0] = 99.0;
		}



	};
};

class get_steering : public XmlRpc::XmlRpcServerMethod
{
public:
	get_steering(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_steering", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		std::vector<SSteering> v_st;
		if (Singleton_Data_Server::get_mutable_instance().get_steering(v_st))
		{

			for ( int i = 0; i < v_st.size() ; ++i ){
				SSteering &st = v_st[i];

				result[i]["id"] = int(st.id_);

				result[i]["pos_x"] = double(st.pos_.x_);
				result[i]["pos_y"] = double(st.pos_.y_);
				result[i]["pos_th"] = double(st.pos_.th_);

				result[i]["max_a"] = double(st.max_angle_);
				result[i]["min_a"] = double(st.min_angle_);

				result[i]["zero_a"] = double(st.zero_angle_);

				result[i]["set_angle"] = double(st.set_angle_);
				result[i]["set_speed"] = double(st.set_speed_);

				result[i]["cur_angle"] = double(st.cur_angle_);
				result[i]["cur_speed"] = double(st.cur_speed_);

			}


		}



	};
};

class get_dio_bind : public XmlRpc::XmlRpcServerMethod
{
public:
	get_dio_bind(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_dio_bind", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		std::map<std::string, SDIO_NM_INDEX> m_fnc_bind;
		if (Singleton_Data_Server::get_mutable_instance().get_dio_bind(m_fnc_bind))
		{
			int index = 0;
			auto it = m_fnc_bind.begin();
			for ( ; it != m_fnc_bind.end() ; ++it ){
				SDIO_NM_INDEX &dio_nm_index = it->second;

				result[index]["fnc_nm"] = std::string(dio_nm_index.str_fnc_nm_);
				result[index]["dev_nm"] = std::string(dio_nm_index.str_dev_nm_);
				result[index]["data_type"] = std::string(dio_nm_index.str_type_);
				result[index]["data_index"] = int(dio_nm_index.i_dio_index_);
	
				index++;
			}
			
			
		}



	};
};
class get_dio_data : public XmlRpc::XmlRpcServerMethod
{
public:
	get_dio_data(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_dio_data", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{

		std::vector<SDIO_NM_INDEX> v_data;
		if (Singleton_Data_Server::get_mutable_instance().get_dio_data(v_data))
		{
			int index = 0;
			auto it = v_data.begin();
			for ( ; it != v_data.end() ; ++it ){
				SDIO_NM_INDEX &dio_nm_index = *it;
				result[index]["fnc_nm"] = std::string(dio_nm_index.str_fnc_nm_);
				result[index]["data"] = std::string(dio_nm_index.str_value_);
				
				index++;
			}
		}

		//std::cout<<"get_dio_data:"<<std::endl;


	};
};

class get_qr_code : public XmlRpc::XmlRpcServerMethod
{
public:
	get_qr_code(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("get_qr_code", s) {};

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		int nArgs = params.size();
		if(nArgs == 1){
			std::string str_cmd = params[0];

			SQrCode qr_code;
			memset(&qr_code,0,sizeof(SQrCode));

			if( Singleton_Data_Server::get_mutable_instance().get_qr_code(qr_code)){
// 				std::string str_time_stemp = cComm::ConvertToString(qr_code.time_stemp_);
// 				result[0]  = int(qr_code.qr_id_);
// 				result[1]  = std::string(str_time_stemp);
// 				result[2]  = double(qr_code.pos_.x_);
// 				result[3]  = double(qr_code.pos_.y_);
// 				result[4]  = double(qr_code.pos_.th_);
// 				result[5]  = std::string(qr_code.ch_des_);

				

			}else{
				//std::cout<<"get_qr_code none!"<<std::endl;
			}
			result[0] = XmlRpc::XmlRpcValue(&qr_code,sizeof(SQrCode));
			//std::cout<<"get_qr_code!"<<std::endl;
		}
	};
};

class Hello : public XmlRpc::XmlRpcServerMethod{

public:

	Hello(XmlRpc::XmlRpcServer* s) : XmlRpc::XmlRpcServerMethod("HelloName", s) {}

	void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
	{
		std::string resultString = "Hello, ";
		resultString += std::string(params[0]);
		result = resultString;
	}

	std::string help() { return std::string("Say hello"); }

};
class rpc_bind{

public:

	rpc_bind();
	~rpc_bind();

	void init(int port);
	void destruct();

private:
	void th_rpc_(void);

	XmlRpc::XmlRpcServer s_;

	void init_s();

	getLaser* get_laser_;
	getUsedLaser* get_used_laser_;
	getExLaser* get_ex_laser_;
	get_pub_laser_ex_cab* get_pub_laser_ex_cab_;
	get_sim_laser* get_sim_laser_;
	getParticles* get_particle_;

	get_robot_pos* get_robot_pos_;
	get_robot_pos_hb* get_robot_pos_hb_;
	get_robot_odom* get_robot_odom_;
	get_para* get_para_;

	setEstimate_pos* set_extimate_pos_;
	setSim_pos* set_sim_pos_;

	setTarget_pos* set_target_pos_;
	setStop* set_stop_;

	getGlobalPath* get_global_path_;
	getLocalMap* get_local_map_;

	getLocal_show* get_local_show_;

	getStatus* get_status_;
	getLaserfilter* get_laser_filter_;
	getDevStatus* get_dev_status_;
	setMappingCmd* set_mapping_cmd_;
	get_file_list* get_file_list_;
	get_map* get_map_;
	get_map_separate* get_map_separate_;
	set_map_cmd* set_map_cmd_;
	set_map* set_map_;
	set_log_cmd* set_log_cmd_;
	set_log_ex_cmd* set_log_ex_cmd_;
	set_speed_cmd* set_speed_cmd_;
	set_loop_closure_cmd* set_loop_closure_cmd_;

	get_process_bar* get_process_bar_;
	get_pub_bag* get_pub_bag_;
	get_pub_bag_ex* get_pub_bag_ex_;
	get_pub_laser_ex_ref* get_pub_laser_ex_ref_;
	set_path* set_path_;
	set_seg_path* set_seg_path_;
	get_check_laser_range* get_check_laser_range_;
	get_chk_laser_show* get_chk_laser_show_;

	get_sim_path* get_sim_path_;
	get_remote_file* get_remote_file_;
	set_onboard_map* set_onboard_map_;
	get_scan_reflector* get_scan_reflector_;
	get_reflector_pos* get_reflector_pos_;
	get_loop_closure* get_loop_closure_;
	get_amcl_entropy* get_amcl_entropy_;
	get_amcl_confidence* get_amcl_confidence_;

	do_download_file* do_download_file_;

	get_view_data* get_view_data_;
	get_battery* get_battery_;
	set_bt_contact* set_bt_contact_;

	get_special_loc_conpos* get_special_loc_conpos_;
	get_special_landmark* get_special_landmark_;


	//sim agv
	set_sim_init_pos* set_sim_init_pos_;
	set_pause* set_pause_;
	get_fork* get_fork_;
	get_steering* get_steering_;

	get_dio_bind* get_dio_bind_;
	get_dio_data* get_dio_data_;

	get_qr_code* get_qr_code_;

	Hello* hello_;
};

#endif//_ROBOT_RPC_BIND_2015_08_07_
