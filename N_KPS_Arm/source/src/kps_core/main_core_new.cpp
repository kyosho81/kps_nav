
//#include <cstdlib> //std::system
//#include <sstream>

// #include <iostream>
// #include <fstream>
#include <string>
#include <signal.h>



#include "Comm.h"
#include "TimerDiff.h"
#include "buffer_con.hpp"

#include "interpro_shared/sh_pool.hpp"

#include "mapserver/map_def.h"
#include "log/log_server.h"
#include "interface/rpc_config_server.h"

bool b_run = true;
rpc_config_server rpc_cfg_svr;

void shutdown(int sig)
{
	

	std::cout<<"shutdown child process"<<std::endl;
	rpc_cfg_svr.destruct();

	sclose cl;
	cl.over = 1;
	//shared_pool::Publish(shared_pool::name(),"shutdown",cl);
	PUB_MSG_SH_POOL("shutdown",cl);

	SLEEP(1000);

	//std::cout<<"core shutdown all over!!!"<<std::endl;

	b_run = false;
	TCP_LOG_SERVER.destruct();

	
	return;
}

static bool Reg_sh_map(std::string sh_name,U32 dsize){
	if (!block_shared_pool::Reg_sh_range(sh_name,dsize))
	{
		return false;
	}
	if (!locker_shared_pool::reg_locker(sh_name + "_lock"))
	{
		return false;
	}

	return true;
};
int main(int argc, char *argv[])
{

	::signal(SIGINT, shutdown);

	rpc_cfg_svr.init();
	std::cout<<"rpc_cfg_svr.init!"<<std::endl;
	TCP_LOG_SERVER.init_listen();
	std::cout<<"TCP_LOG_SERVER.init_listen!"<<std::endl;

	msg_shared_pool::init(argv,true);
	std::cout<<"msg_shared_pool!"<<std::endl;
	pipe_shared_pool::init(argv,true);
	std::cout<<"pipe_shared_pool!"<<std::endl;
	block_shared_pool::init(argv,true);
	std::cout<<"block_shared_pool!"<<std::endl;
	locker_shared_pool::init(argv,true);
	std::cout<<"locker_shared_pool!"<<std::endl;

	Reg_sh_map(SHARED_AMCL_MAP,GLOBAL_MAP_SIZE);
	Reg_sh_map(SHARED_GLOBAL_INF_MAP,GLOBAL_MAP_SIZE);
	Reg_sh_map(SHARED_GLOBAL_LASER_INF_MAP,GLOBAL_MAP_SIZE);
	Reg_sh_map(SHARED_LASER_INF_MAP,LOCAL_MAP_SIZE);
	Reg_sh_map(SHARED_GLOBAL_PROHIBIT_INF_MAP,GLOBAL_MAP_SIZE);

	Reg_sh_map(SHARED_PROHIBIT_MAP,GLOBAL_MAP_SIZE);

	std::cout<<"kps_core run loop begin!!!!!!!!!"<<std::endl;

	while(b_run){
		TCP_LOG_SERVER.run_once();
		//msg_shared_pool::print_all_msg();
		//SLEEP(500);
	}

	msg_shared_pool::reset();
	pipe_shared_pool::reset();
	block_shared_pool::reset();
	locker_shared_pool::reset();
}
