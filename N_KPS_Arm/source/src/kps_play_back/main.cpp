
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
#include "log/msg_play_back.h"
#include "interpro_shared/sh_pool.hpp"

bool gr_run = true;
void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	
	 gr_run = false;

	return;
}
int main(int argc, char* argv[]){

	RPC_CONFIG_CLIENT_INIT("127.0.0.1");

	REG_POOL(argv);

	std::vector<std::string> v_list;
	cComm::Find_files(".//pkg_log//","*.pkg",v_list);

	std::cout<<".//pkg_log:"<<std::endl;
	for ( int i = 0 ; i < v_list.size() ; ++i){
		std::cout<<"index:"<<i<<"   "<<v_list[i]<<std::endl;
	}
	std::cout<<"select play back index>>>";
	int index = -1;
	std::cin>>index;
	if ( (index >= 0) && (index < v_list.size())){
		//uppackage

		MSG_LOG_PKG.unpackage_db(v_list[index]);
		//play back
		MSG_PLAY_BACK.init();
		MSG_PLAY_BACK.play_db( MSG_LOG_PKG.get_unpackage_db_name() );
		
		::system("pause");
	}
	
	
}

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
