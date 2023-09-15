
// #include <stdio.h>
// #include <stdlib.h>
//#include <fcntl.h>
//#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Acc.h"
#include "Comm/Rand.hpp"
#include "Comm.h"

#include "Comm/tollage.h"
#include "Comm/file.h"
#include "robot/Geometry.h"

#include "robot/laser_move_distortion_calib.h"

void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	


	return;
}

laser_md_calib lc;

int main(int argc, char* argv[]){

	std::cout<<std::setprecision(20);

	SOdomSpeedEx odom;
	memset(&odom,0,sizeof(SOdomSpeedEx));
	F64 begin_time = cTimerDiff::total_ms();
	begin_time *= 1e-6;
	odom.time_stamp_ = begin_time;

	for ( int i = 0 ; i < 6 ; ++i )
	{
		//odom.x_ += 0.05;
		//odom.y_ -= 0.05;
		odom.th_ += Deg2Rad(1);
		odom.time_stamp_ += 0.1;
		lc.set_odom(odom);
	}
	
#if 0
	for ( int i = 0 ; i < 100 ; ++i )
	{
		if( lc.get_odom_interpolation(odom,begin_time + 0.01*i) ){
			std::cout<<" odom_interpolation dt:"<<begin_time + 0.01*i<<" x y th:"<<odom.x_<<" "<<odom.y_<<" "<<Rad2Deg(odom.th_)<<std::endl;
		}else{
			std::cout<<" odom_interpolation err dt:"<<begin_time + 0.01*i<<" x y th:"<<odom.x_<<" "<<odom.y_<<" "<<Rad2Deg(odom.th_)<<std::endl;
		}

	}
#endif
	SLaser_Ex laser_ex;
	SLaserXYEx laser_calibInodom;

	memset(&laser_ex,0,sizeof(SLaser_Ex));
	memset(&laser_calibInodom,0,sizeof(SLaserXYEx));

	laser_ex.dx_ = 0;
	laser_ex.dy_ = 0;
	laser_ex.bean_dt_ = 0.1 / LASER_COUNT;
	laser_ex.range_max_ = 20.0;
	laser_ex.range_min_ = 0.01;
	laser_ex.stamp_ = 0 ; 
	laser_ex.start_angle_ = -Deg2Rad(135);
	laser_ex.resolution_ = Deg2Rad(0.5);
	laser_ex.used_ray_ = 0;
	laser_ex.time_stamp_ = begin_time;
	for ( int i = 0 ; i < LASER_COUNT ; ++i ){
		F32 angle  = laser_ex.start_angle_ +  laser_ex.resolution_*i;
		if (fabs(angle) < Deg2Rad(30))
		{
			//cos(th) = x / range>>range = x / cos(th);
			laser_ex.data_[i] = 1.0 / cos(angle);
			laser_ex.seg_[i] = 255;
			laser_ex.used_ray_++;
		}
	}

	lc.laser_calib(laser_calibInodom,laser_ex);

	std::cout.unsetf( std::ios::fixed ); 

	return 0;
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
