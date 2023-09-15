
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
	std::cout<<"sub data name:"<<cTimerDiff::total_ms()<<" "<<name<<" "<<cComm::ByteToHexString(data,len)<<std::endl;
	return true;
}

int main(int argc, char* argv[]){

	::signal(SIGINT, shutdown);

	
//	test_msg_pool(argc,argv);
// 	shared_pipe_seg<40960> sh_pipe("aa");
// 	sh_pipe.init();
	if (argc == 1){

		pipe_shared_pool::init(argv);

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
			memset(data,i,PIPE_BUFFER_SIZE);
			//std::cout<<"pub odom:"<<cTimerDiff::total_ms() <<" "<<i<<std::endl;
			std::cout<<"pub pipe name:"<<cTimerDiff::total_ms()<<" "<<name<<" "<<i<<std::endl;
			if(!PUB_PIPE_SH_POOL("map", "odom", data,100 )){
				std::cout<<"pub_sh_msg(odom) err!"<<std::endl;
			}
			SLEEP(10);
		}
	}


}

