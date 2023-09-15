#include <signal.h>

#include "interpro_shared/sh_pool.hpp"

#include "Comm/Comm.h"
#include "Comm/TimerDiff.h"
#include "dispatching/seg_path_against.h"
#include "dispatching/traffic_control.h"

bool b_run = true;


void shutdown(int sig)
{



	b_run = false;

	return;
}



bool callback(const sclose &cl){


	if (cl.over)
	{
		std::cout<<"shut down: call by core "<<std::endl;
		shutdown(1);
	}
	return true;
}


void init_shared_pool(char *argv[]){

	//shared_pool::init(argv);
	REG_POOL(argv);
	std::cout<<"loop closure init call back"<<std::endl;

	//core shut down
	boost::function<bool( const sclose &cl)> fnc_shutdown;
	fnc_shutdown = boost::bind(callback,_1);
	//shared_pool::Subscribe(shared_pool::name(),"shutdown",fnc_shutdown);

}
int main(int argc, char *argv[])
{
	::signal(SIGINT, shutdown);
	
	if(argc > 1){
		init_shared_pool(argv);
		std::cout<<"kps init shared pool"<<std::endl;
	}

	TRAFFIC_CONTROL.check_pause_loop();


	seg_path_against sa;
	sa.init("seg.txt",false);

	sa.check_against_path();
	sa.print_pause();
}
