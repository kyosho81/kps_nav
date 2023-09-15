

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <vector>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#endif
#include <stdlib.h>
#include "Comm/Rand.hpp"
#include "Log4cppArm.hpp"
#include "log/log_client.h"

#include "trans_dev/traceroute.h"
#include "Comm.h"
//#include "Log.h"


#include "chassis/chassis_2wd.h"
#include "chassis/chassis_2wd_new.h"
#include "chassis/chassis_normal.h"
#include "chassis/chassis_steering_single.h"
#include "chassis/chassis_steering_multi.h"

#include "chassis/copley_driver.h"
#include "chassis/my_driver.h"
#include "chassis/sim_driver.h"
#include "chassis/xiongda_driver.h"
#include "chassis/it_servo_driver.h"
#include "chassis/normal_driver.h"
#include "chassis/ps30_driver.h"
#include "chassis/kinco_driver.h"

#include "interpro_shared/sh_pool.hpp"


bool gb_run = true;

void shutdown(int sig)
{



	//	std::cout<<"ctrl c shut down"<<std::endl;

	gb_run = false;

	std::cout<<"test odom ctrl c destructor"<<std::endl;

	return;
}


int main(int argc, char *argv[])
{
	REG_POOL(argv);

 	log4cpp::Priority::Value priority = log4cpp::Priority::DEBUG;
 	LOG.getLog(argv[0]).setPriority(priority);  //LOGS_PRIORITY_INFO("planner_tray");
	
	RPC_CONFIG_CLIENT_INIT("127.0.0.1");
	TCP_LOG.set_priority(priority);

	SSpeed sep;
	sep.vx_ = 0;
	sep.vy_ = 0;
	sep.vw_ = 0;

	std::stringstream ss;
	int i_com = 2;

	if (argc > 1){
		std::string str = argv[1];
		cComm::ConvertToNum(i_com,str);
	}
	if (argc > 2){
		std::string str = argv[2];
		cComm::ConvertToNum(sep.vx_,str);
	}
	if (argc > 3){
		std::string str = argv[3];
		cComm::ConvertToNum(sep.vy_,str);
	}
	if (argc > 4){
		std::string str = argv[4];
		cComm::ConvertToNum(sep.vw_,str);
	}
	ss<<"COM"<<i_com;
	std::cout<<"open COM>>>"<<ss.str()<<std::endl;
	std::cout<<"vx:"<<sep.vx_<<" vw:"<<sep.vw_<<std::endl;

	//std::string chassis_type_ = "sim";
	//std::string chassis_type_ = "fork";
	std::string chassis_type_ = "multi";

	//std::string chassis_para = "dia:0.18;axle:0.560";
	std::string chassis_para = "adia:0.15;multi_para:base_x=0.245,base_y=0,max_angle=120,min_angle=-120,angle_zero=0#base_x=-0.245,base_y=0,max_angle=120,min_angle=-120,angle_zero=0";
	//std::string chassis_para = "adia:0.15;multi_para:base_x=0.39,base_y=0,max_angle=200,min_angle=-200,angle_zero=0";
	//std::string chassis_para = "adia:0.15;base_x:0.593;base_y:0;angle_zero:1;";
#ifdef _WIN32
	//std::string chassis_com = "port:COM1;counts:10000;reduction:20";
	std::stringstream ss2;
	//port:COM2;counts:60;reduction:4.3 
	//ss2<<"port:"<<ss.str()<<";counts:60;reduction:4.3";
	//ss2<<"can_type:canalyst2;counts:10000;reduction:20";
	ss2<<"can_type:canalyst2;counts:10000;reduction:26.54";
	std::string chassis_com = ss2.str();
#else
	std::string chassis_com = "port:ttyUSB0;counts:10000;reduction:20";

#endif

	std::cout<<"dev_chassis_type:"<<chassis_type_<<std::endl;
	std::cout<<"dev_chassis_para:"<<chassis_para<<std::endl;
	std::cout<<"dev_chassis_com:"<<chassis_com<<std::endl;

	Driver_base* driver = 0;
	Chassis_base* base = 0;

	if(chassis_type_ == "kps"){
		base =(Chassis_base*)new Chassis_normal();
	}else if(chassis_type_ == "ps30"){
		base =(Chassis_base*)new Chassis_normal();
	}else if(chassis_type_ == "fork"){
		base =(Chassis_base*)new Chassis_steeing_single();
	}else if(chassis_type_ == "multi"){
		base =(Chassis_base*)new Chassis_steeing_multi();
	}else{
		base =(Chassis_base*)new Chassis_2wd_new();
	}

	if ((base) && ( base->init( chassis_para )))
	{
		driver = 0;

		if(chassis_type_ == "copley"){
			driver = (Driver_base*)new copley_driver();

		}else if(chassis_type_ == "kps"){
			driver = (Driver_base*)new My_driver();
		}else if(chassis_type_ == "xiongda"){
			driver = (Driver_base*)new xiongda_driver();
		}else if(chassis_type_ == "it_servo"){
			driver = (Driver_base*)new it_servo_driver();
		}else if(chassis_type_ == "normal"){
			driver = (Driver_base*)new normal_driver();
		}else if(chassis_type_ == "fork"){
			driver = (Driver_base*)new kinco_driver();
		}else if(chassis_type_ == "multi"){
			driver = (Driver_base*)new kinco_driver();
		}else{
			driver = (Driver_base*)new sim_driver();
		}
		//std::cout<<"init driver type:"<<chassis_type_<<std::endl;
		std::cout<<"init driver type:"<<chassis_type_<<std::endl;

		if( (driver) && ( driver->init( chassis_com )))
		{
			base->initDriver(driver);

			std::cout<<"chassis run loop!"<<std::endl;

			base->run(81);
			base->set_ms_loop(100);
		}
		else{
			std::cout<<"driver init err::port:COM1;counts:10000;reduction:60!!!!!!"<<std::endl;
			
			SLEEP(2000);
			//exit(0);
		}

	}else{
		std::cout<<"device init err!!"<<std::endl;
	}

	base->setSpeed(sep.vx_,sep.vy_,sep.vw_);

	while(gb_run){
		
		
		for (int i = 0 ; i < 100 ; ++i ){
			
			F32 ox,oy,oa;
			F32 ovx,ovy,ow;

			base->setSpeed(sep.vx_,sep.vy_,sep.vw_);

			base->getOdom(ox,oy,oa);

			base->getSpeed(ovx,ovy,ow);

			//std::cout<<"set vx:"<<sep.vx_<<" vw:"<<sep.vw_<<" vy:"<<sep.vy_;
			std::cout<<" get ox:"<<ox<<" oy:"<<oy<<" oa:"<<oa<<" get speed ovx:"<<ovx<<" ovy:"<<ovy<<" ow:"<<ow<<std::endl;
			SPos amcl_pos;
			amcl_pos.x_ = ox;
			amcl_pos.y_ = oy;
			amcl_pos.th_ = oa;
			PUB_MSG_SH_POOL("amcl_pos",amcl_pos);
		}

		std::cout<<"please input set speed vx vy w:"<<std::endl;
		std::string str;
		std::getline(std::cin,str);

		std::vector<std::string> v_str;
		cComm::SplitString(str," ",v_str);
		if (v_str.size() > 2){

			cComm::ConvertToNum(sep.vx_,v_str[0]);
			cComm::ConvertToNum(sep.vy_,v_str[1]);
			cComm::ConvertToNum(sep.vw_,v_str[2]);

		}

		std::cout<<"vx:"<<sep.vx_<<" vy:"<<sep.vy_<<" vw:"<<sep.vw_<<std::endl;
	}


	std::cout<<"control c! shutdown!"<<std::endl;
	base->setSpeed(0, 0 ,0 );

	SLEEP(2000);
}
