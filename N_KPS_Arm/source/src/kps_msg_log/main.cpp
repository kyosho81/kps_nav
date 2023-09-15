
// #include <stdio.h>
// #include <stdlib.h>
//#include <fcntl.h>
//#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>

#include "Comm/Comm.h"
#include "interface/rpc_config_client.h"
#include "log/msg_log_server.h"
#include "log/msg_log_pkg.h"
#include "interpro_shared/sh_pool.hpp"
#include "project/task_rpc_client.h"
#include "project/task_creater.h"

bool gb_run = true;
void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	
	gb_run = false;
	MSG_LOG_SERVER.destruct();
	MSG_LOG_PKG.destruct();

	return;
}

void pub_monitor_status( U8 status, U16 err_code)
{
	SPubDevStatus pub_sta;
	memset(&pub_sta,0,sizeof(SPubDevStatus));
	std::string str = "msg_log";
	memcpy(pub_sta.name_,str.c_str(),str.length());
	pub_sta.dev_status_.device_id_ = Comm_Dev_Id::ID_MSG_LOG;
	pub_sta.dev_status_.status_ = status;
	pub_sta.dev_status_.err_code_ = err_code;
	//shared_pool::Publish(shared_pool::name(),"device_status",pub_sta);
	PUB_MSG_SH_POOL("device_status",pub_sta);
}

int main(int argc, char* argv[]){



	RPC_CONFIG_CLIENT_INIT("127.0.0.1");

	REG_POOL(argv);

	MSG_LOG_SERVER.init();
	MSG_LOG_PKG.init();

	LOG_State log_state = LOG_IDLE;
	U16 u16_err_code = 0;

	pub_monitor_status(log_state,u16_err_code);

	SLEEP(500);

	//MSG_LOG_PKG.unpackage_db(".//pkg_log//2021-1-20-10-47-37_1611139657858690.pkg");
	while(gb_run){

		std::string str_db_name;
		if(MSG_LOG_SERVER.get_save_db(str_db_name)){
			log_state = LOG_PKG;
			pub_monitor_status(log_state,u16_err_code);
			MSG_LOG_PKG.package_db(str_db_name);
		}
		log_state = LOG_RUN;
		pub_monitor_status(log_state,u16_err_code);

		SLEEP(200);
	}
}
// std::vector<SPathData> suro_path;
// SPathData sd;
// memset(&sd,0,sizeof(SPathData));
// sd.tn_from_.x_ = 0 ; 
// sd.tn_from_.y_ = 0 ; 
// sd.tn_to_.x_ = 4.5 ; 
// sd.tn_to_.y_ = 0 ; 
// sd.speed_ = 0.8;
// sd.speed_from_ = 0.2;
// sd.orientation_ = 0;
// suro_path.push_back(sd);
// sd.tn_from_.x_ = 4.5 ; 
// sd.tn_from_.y_ = 0 ; 
// sd.tn_to_.x_ = 4.5 ; 
// sd.tn_to_.y_ = 3.0 ; 
// sd.speed_ = 0.2;
// sd.speed_from_ = 0.8;
// sd.orientation_ = 0;
// suro_path.push_back(sd);
// 
// 
// task_rpc_client* p_rpc_task = new task_rpc_client();
// p_rpc_task->init("127.0.0.1",RPC_TASK_SER_PORT + 1 );
// task_creater* task_creater_ = new task_creater(p_rpc_task);
// task_creater_->create_fix_path(suro_path);
// return 0;

//int main2(int argc, char* argv[]){
//
//
//	int result;
//	if(-1==(result=gethostid()))
//	{
//		printf("gethostid err\n");
//		exit(0);
//	}
//	printf("hosid is :%d\n",result);
//
//
//	//std::::system("ifconfig eth0 | grep "HWaddr" | awk '{print $5}'");
//	std::string str_rec = "" ;
//	system::cmd("ifconfig eth0 | grep ''HWaddr'' | awk '{print $5}'",str_rec);
//	str_rec = cComm::trim_n(str_rec);
//
//
//	std::stringstream ss;
//	ss<<result<<"-"<<str_rec;
//
//
//
//	return 0;
//}
