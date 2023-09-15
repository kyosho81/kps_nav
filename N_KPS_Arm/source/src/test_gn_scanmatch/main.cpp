
// #include <stdio.h>
// #include <stdlib.h>
//#include <fcntl.h>
//#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "msg_pump/msg_pump.hpp"
#include "interprocess_core/reg_msg.h"
#include "interprocess/shared_pool.hpp"

#include "Acc.h"
#include "Comm/Rand.hpp"
#include "Comm.h"

#include "Comm/tollage.h"
#include "Comm/file.h"
#include "mapserver/map_def.h"
#include "mapserver/MapServer.h"
#include "robot/Geometry.h"
#include "Comm/TimerDiff.h"

#include "gn_scan_match/gn_scan_match.h"

gn_scan_match gn;
SPos g_init_pos;


void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;

	return;
}
void s_update_laser( const SLaser &laser_data ){
	gn.call_gn_match(g_init_pos,laser_data);
	std::cout<<"gn match x:"<<g_init_pos.x_<<" y:"<<g_init_pos.y_<<" th:"<<g_init_pos.th_<<std::endl;
}
void s_update_odom( const SOdomSpeed &odomspeed ){

}
void s_init_pos(const SInit_Pos &init_pos){
	g_init_pos = init_pos.pos_ ;

}

int main(int argc, char* argv[]){
	
	
	
//	//GridMap* gn_map = CREATE_SHARED_GMAP(SHARED_AMCL_MAP);
//	std::stringstream ss;
//	ss<<".//map//gn.pgm";
//	std::cout<<"begin load map:"<<ss.str()<<std::endl;
//	GridMap* p_map = MAP_SERVER.LoadPgmMap(ss.str(),map_data_base::MEM,"");

// 	if (p_map)
// 	{
// 		MAP_SERVER.clone(p_map->Get_name(),SHARED_AMCL_MAP);
// 		std::cout<<"load map over!!clone map to shared map:"<<ss.str()<<std::endl;
// 	}
	GridMap* gn_map = CREATE_MEM_GMAP("test");
	gn_map->clear();
	//gn_map->setgrid((U32)4095,(U32)4096,MAP_OCCUPY_MAX);
	//gn_map->setgrid((U32)4095,(U32)4097,MAP_OCCUPY_MAX);

// 	gn_map->setgrid((U32)4096,(U32)4096,MAP_OCCUPY_MAX);
// 	gn_map->setgrid((U32)4096,(U32)4097,MAP_OCCUPY_MAX);
// 	gn_map->setgrid((U32)4097,(U32)4096,MAP_OCCUPY_MAX);
// 	gn_map->setgrid((U32)4097,(U32)4097,MAP_OCCUPY_MAX);

	g_init_pos.x_ = 0.02 ;
	g_init_pos.y_ = -0.014 ;
	g_init_pos.th_ = 0.3 ;

	gn.init();
	
	
	SLaser laser_data;
	memset(&laser_data,0,sizeof(SLaser));
	laser_data.range_max_ = 20.0;
	laser_data.range_min_ = 0.1;
	laser_data.resolution_ = Deg2Rad(0.5);
	memset(laser_data.seg_,0,sizeof(U8)*LASER_COUNT);
	laser_data.stamp_ = 0 ; 
	laser_data.start_angle_ = -(Deg2Rad(135));
	laser_data.used_ = 0;
	memset(laser_data.data_,0,sizeof(F32)*LASER_COUNT);

	F32 test_line = 0.15;
	int i_begin = 0;
	int i_end = 0;
	
	F32 px = 0.1;

	for (int i = 0 ; i < 3 ; ++i)
	{
		 
		F32 py = -0.05 + i * 0.05;
		if ( i == 0 )
		{
			VecPosition vp(px,py);
			i_begin = (Deg2Rad(vp.getDirection()) - laser_data.start_angle_) / laser_data.resolution_;
 
		}else if( i == 2){
			VecPosition vp(px,py);
			i_end = (Deg2Rad(vp.getDirection()) - laser_data.start_angle_) / laser_data.resolution_;

		}

		gn_map->setgrid((F32)px,(F32)py,MAP_OCCUPY_MAX);
	}
	gn.init_amcl_map(gn_map);

	for (int i = i_begin ; i <= i_end ; ++i){
	
		F32 angle = laser_data.start_angle_ + i*laser_data.resolution_;

		laser_data.data_[i] = px / cos(angle);
		laser_data.seg_[i] = 255;
	}

	
	cTimerDiff dt;
	dt.Begin();
	gn.call_gn_match(g_init_pos,laser_data);
	F32 fdt = dt.End();
	fdt /= 1e3;
	std::cout<<"match dt ms:"<<fdt<<std::endl;
#if 0
	boost::function<void( const SInit_Pos &init_pos)> fnc_ui;
	fnc_ui = boost::bind(s_init_pos ,_1);
	shared_pool::Subscribe(shared_pool::name(),"set_estimate_pos",fnc_ui);

	boost::function<void( const SLaser &laser_data )> fnc_laser;
	fnc_laser = boost::bind(&s_update_laser,_1);
	shared_pool::Subscribe(shared_pool::name(),"laser",fnc_laser);

	boost::function<void( const SOdomSpeed &odomspeed )> fnc_odom;
	fnc_odom = boost::bind(&s_update_odom,_1);
	shared_pool::Subscribe(shared_pool::name(),"odom",fnc_odom);

#endif
	MAP_SERVER.RemoveGridMap(gn_map);

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
