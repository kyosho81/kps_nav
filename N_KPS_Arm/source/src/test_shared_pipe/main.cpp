//MIT License
//Copyright (c) 2005-2023 kyosho81
//KPS tgv1.taobao.com

//a example for interprocess buffer message passing , size must less then PIPE_BUFFER_SIZE(default:40960)
//using boost
//publish-subscribe
// no use serialization 
// msg_shared_pool::init(argv,true);  // for regist shared master should run first, also can be standalone
// msg_shared_pool::init(argv);       // for each process should be run first


// process A sub
// bool call_pipe(std::string name,U8* data,U32 len);      //message callback function [ name:message name ,data: stream pt , len: stream size ]
// std::string str_sub_pipe = SUB_PIPE_SH_POOL("map",fnc); //sub a stream message name = "map"  
// END_PIPE_SH_POOL(str_sub_pipe);                         //end sub

// process B pub
// PUB_PIPE_SH_POOL("map", "data", data, 100 );            //pub stream message name = "map" ,name:data len:100(<40960)

#include <signal.h>

#include "Comm/TimerDiff.h"
#include "interpro_shared/sh_pool.hpp"

//using namespace boost::interprocess;

bool b_run = true;

void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	b_run = false;

	return;
}

bool call_pipe(std::string name,U8* data,U32 len){
	std::cout<<"sub time:"<<cTimerDiff::total_ms()<<" "<<name<<" data name:"<<cComm::ByteToHexString(data,len)<<std::endl;
	return true;
}

int main(int argc, char* argv[]){

	::signal(SIGINT, shutdown);


	if (argc == 1){

		pipe_shared_pool::init(argv,true);

		boost::function<bool (std::string name,U8* data,U32 len)> fnc;
		fnc = boost::bind(&call_pipe,_1,_2,_3);
		std::string str_sub_pipe = SUB_PIPE_SH_POOL("map",fnc);

		while(b_run){

			SLEEP(1000);
		}

		END_PIPE_SH_POOL(str_sub_pipe);

	}else{

		pipe_shared_pool::init(argv);

		std::string name = "map";
		U8* data = new U8[PIPE_BUFFER_SIZE];
		U32 len = PIPE_BUFFER_SIZE;
		memset(data,0xaa,PIPE_BUFFER_SIZE);

		for (int i = 0 ; i < 1000; ++i)
		{
			memset(data,i,100);
			//std::cout<<"pub odom:"<<cTimerDiff::total_ms() <<" "<<i<<std::endl;
			std::cout<<"pub pipe name:"<<cTimerDiff::total_ms()<<" "<<name<<" "<<i<<std::endl;
			if(!PUB_PIPE_SH_POOL("map", "data", data, 100 )){
				std::cout<<"pub_sh_msg(map) err!"<<std::endl;
			}
			SLEEP(10);
		}
	}


}

