

#include <signal.h>

#include "Comm/TimerDiff.h"
#include "interpro_shared/sh_pool.hpp"

bool b_run = true;

void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	b_run = false;

	return;
}
bool call_back_odom(const int &tp ){
	std::cout<<"sub odom:"<<cTimerDiff::total_ms() <<" "<<tp<<std::endl;

	return true;
}

int main(int argc, char* argv[]){

	::signal(SIGINT, shutdown);

	

	if(argc == 1){

		msg_shared_pool::init(argv);

		boost::function<bool(const int&)> fnc;
		fnc = boost::bind(call_back_odom,_1);
		std::string str_sub_msg = SUB_MSG_SH_POOL("odom",fnc);

		//while(b_run){

			SLEEP(10000);
		//}
		//msg_shared_pool::destroy(str_sub_msg);
		END_MSG_SH_POOL(int,str_sub_msg);
	}else{

		msg_shared_pool::init(argv);

		for (int i = 0 ; i < 100; ++i)
		{
			std::cout<<"count:"<<i<<std::endl;

			PUB_MSG_SH_POOL("odom", i );
			SLEEP(1000);
		}
	}
	

	return 0;
}