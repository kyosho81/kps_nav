
#include <signal.h>


#include <iostream>
#include <fstream>
//#include <unistd.h>

#include <string>
#include <cassert>
#include "Comm.h"
#include "Geometry.h"
#include "TimerDiff.h"

#ifdef _WIN32
#include "sick/lms111.h"
#else
#include "sick/LMS1xx.h"
//#include "sick/lms111.h"
#endif

#include "RobotStruct.h"
//#include "polygon.h"
#include "laser_filter/laser_filter.h"

#include "interpro_shared/sh_pool.hpp"

#include "robot/my_tf.h"
#include "msg_pump/msg_pump.hpp"


bool brun = true; 


void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	brun = false;
	
	SLEEP(500);

	return;
}
void callback(const sclose &cl){


	if (cl.over)
	{
		
		shutdown(1);
	}

}


bool update( const int& laser ){
	std::cout<<"up1:"<<cTimerDiff::total_ms()<<" "<<laser<<std::endl;
	return true;
}
bool update2( const int& laser ){
	std::cout<<"up2:"<<cTimerDiff::total_ms()<<" "<<laser<<std::endl;
	return true;
}


class A{
public:
	A(){
		i = 0;
	};
	~A(){
		std::cout<<"destrust A"<<std::endl;
	};
	bool update( const int& laser ){
		if (i++ < 1000)
		{
			std::cout<<"aa"<<i<<std::endl;
			return  true;
		}else{
			std::cout<<"aa"<<std::endl;
			return  false;
		}
		
		
		
	};
	int i ;
};

int main(int argc, char *argv[])
{
	msg_list< SOdomSpeed > l;
	int data_size = sizeof( l );
	boost::circular_buffer<SOdomSpeed> buffer_list(10);
	data_size = sizeof(buffer_list);

	SOdomSpeed sd[10];
	data_size = sizeof(sd);

	::signal(SIGINT, shutdown);

	boost::function<bool( const int& laser )> fnc_laser;
	fnc_laser = boost::bind(&update,_1);
	int id1 = msg_pump::sub_msg("classA",fnc_laser);

	fnc_laser = boost::bind(&update2,_1);
	int id2 = msg_pump::sub_msg("classA",fnc_laser);


// 	A* a = new A();
// 	fnc_laser = boost::bind(&A::update,a,_1);
// 	int sub_id = msg_pump::sub_msg("classA",fnc_laser);
	
	SLEEP(1000);
	int i = 0;
	while(1){
		
		msg_pump::pub_msg("classA",i++);
		if ((i % 20) == 0)
		{
 			msg_pump::end_Sub(id1,int());
			fnc_laser = boost::bind(&update,_1);
			id1 = msg_pump::sub_msg("classA",fnc_laser);

			SLEEP(3000);

			msg_pump::end_Sub(id2,int());
			fnc_laser = boost::bind(&update2,_1);
			id2 = msg_pump::sub_msg("classA",fnc_laser);
// 			SDelete(a);
		}
		//std::cout<<"pu0:"<<" "<<i<<std::endl;
		std::cout<<"pu0:"<<cTimerDiff::total_ms()<<" "<<i<<std::endl;
		SLEEP(300);
	}

	


	return 0;
}
