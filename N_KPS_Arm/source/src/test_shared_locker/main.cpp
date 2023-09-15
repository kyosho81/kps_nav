
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


int main(int argc, char* argv[]){

	::signal(SIGINT, shutdown);

	
//	test_msg_pool(argc,argv);
// 	shared_pipe_seg<40960> sh_pipe("aa");
// 	sh_pipe.init();
#define MA "lc"

	
	if (argc == 1){

		locker_shared_pool::init(argv,true);

		REG_LOCKER_SH_POOL(MA);

		bool b = true;
		for ( int i = 0; i < 100 ; ++i){
		
			SET_LOCKER_SH_POOL(MA,true);
			std::cout<<cTimerDiff::total_ms()<<"th 1 set lock:"<<std::endl;

			SLEEP(1000);

			SET_LOCKER_SH_POOL(MA,false);
			std::cout<<cTimerDiff::total_ms()<<"th 1 set unlock:"<<std::endl;

		}

	}else {

		locker_shared_pool::init(argv);

		shared_locker* lc = REG_LOCKER_SH_POOL(MA);

		bool b = true;
		for ( int i = 0; i < 100 ; ++i){

			lc->lock();
			std::cout<<cTimerDiff::total_ms()<<"th 2 set lock:"<<std::endl;

			SLEEP(1000);

			lc->unlock();
			std::cout<<cTimerDiff::total_ms()<<"th 2 set unlock:"<<std::endl;
			//SLEEP(1000);
		}

	} 


}

