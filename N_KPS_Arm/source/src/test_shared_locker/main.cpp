//MIT License
//Copyright (c) 2005-2023 kyosho81
//KPS tgv1.taobao.com

//a example for interprocess shared lock 
//using boost
// interprocess shared memory

// msg_shared_pool::init(argv,true);  // for regist shared master should run first, also can be standalone
// msg_shared_pool::init(argv);       // for each process should be run first


// process A sub
// REG_LOCKER_SH_POOL(LC);              //regist a shared locker 
// SET_LOCKER_SH_POOL(LC,true);         //set lock
// SET_LOCKER_SH_POOL(LC,false);        //set unlock 

// process B pub
// shared_locker* lc = REG_LOCKER_SH_POOL(LC);   // regist a shared locker
// lc->lock();                                   // set lock
// lc->unlock();                                 // set unlock 


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

	
#define LC "lc"

	
	if (argc == 1){

		locker_shared_pool::init(argv,true);

		REG_LOCKER_SH_POOL(LC);

		bool b = true;
		for ( int i = 0; i < 100 ; ++i){
		
			SET_LOCKER_SH_POOL(LC,true);
			std::cout<<cTimerDiff::total_ms()<<"th 1 set lock:"<<std::endl;

			SLEEP(1000);

			SET_LOCKER_SH_POOL(LC,false);
			std::cout<<cTimerDiff::total_ms()<<"th 1 set unlock:"<<std::endl;

		}

	}else {

		locker_shared_pool::init(argv);

		shared_locker* lc = REG_LOCKER_SH_POOL(LC);

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

