
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Comm.h"
#include "TimerDiff.h"
#include "RobotStruct.h"

#include "angle_ctl.h"
#include "movement/speed_smooth.h"

#include "interprocess/shared_pool.hpp"

bool brun = true;

angle_ctl actl;
speed_smooth spsm;

boost::mutex mu;

SSpeed speed;

F32 target_w = 0;

std::ofstream of;

void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;

	brun = false;

	return;
}
void update_odom( const SOdomSpeed& new_odom ){

	{
		boost::mutex::scoped_lock lock(mu);
 		
		//actl.Cal_vw(target_w,new_odom.th_,0.0);
		F32 acc = 0;
		speed.vw_ = spsm.sm(target_w,new_odom.vw_,acc);
		speed.vx_ = 0;
		speed.vy_ = 0;
		std::cout<<"target_w:"<<target_w<<" s w:"<<speed.vw_<<" o w:"<<new_odom.vw_<<" acc:"<<acc<<std::endl;
		of<<target_w<<" "<<speed.vw_<<" "<<new_odom.vw_<<" "<<acc<<std::endl;
		shared_pool::Publish(shared_pool::name(),"setspeed",speed);
	}

	std::cout<<"sx:"<<speed.vx_<<" sy:"<<speed.vy_<<" sw:"<<speed.vw_<<std::endl;

}
void init_shared_pool(char *argv[]){

	shared_pool::init(argv);
	std::cout<<"shared test init call back"<<std::endl;


	boost::function<void( const SOdomSpeed &odomspeed )> fnc_odom;
	fnc_odom = boost::bind(&update_odom ,_1);
	shared_pool::Subscribe(shared_pool::name(),"odom",fnc_odom);

}
int main(int argc, char* argv[]){

	::signal(SIGINT, shutdown);

	actl.Init_pid(1.0,0);
	spsm.init();

	of.open("of.txt",std::ios::binary | std::ios::trunc);

	speed.vx_ = 0;
	speed.vy_ = 0;
	speed.vw_ = 0;

	if(argc > 1){
		init_shared_pool(argv);
	}

	for ( int i = 0 ; i < 20 ; ++i )
	{
		shared_pool::Publish(shared_pool::name(),"setspeed",speed);
		SLEEP(100);
	}

	
	cTimerDiff dt_loop;

	while(brun){
		std::cout<<"input w:"<<std::endl;
		F32 fin = 0;
		std::cin>>fin;
		{
			boost::mutex::scoped_lock lock(mu);
			target_w = fin;
		}
		std::cout<<"target_w:"<<target_w<<std::endl;
		//dt_loop.ms_loop(1000);
	}

	speed.vx_ = 0;
	speed.vy_ = 0;
	speed.vw_ = 0;

	for ( int i = 0 ; i < 20 ; ++i )
	{
		shared_pool::Publish(shared_pool::name(),"setspeed",speed);
		SLEEP(100);
	}
	of.close();
	shared_pool::destructor();
	return 0;
}