
// #include <stdio.h>
// #include <stdlib.h>
//#include <fcntl.h>
//#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Comm.h"
#include "TimerDiff.h"
#include "RobotStruct.h"
#include "mapserver/MapServer.h"
#include "robot/Astar.h"
#include "bag/cloest_filter.h"

// #include "interprocess/mu_shared_range.hpp"
// #include "interprocess/shared_range.hpp"
#include "interprocess/shared_pool.hpp"


void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	//brun = false;
	shared_pool::destructor();
	SLEEP(500);

	exit(0);

	return;
}

void init_shared_pool(char *argv[]){

	shared_pool::init(argv);
	std::cout<<"shared test init call back"<<std::endl;
}
int main(int argc, char* argv[]){

	//init_shared_pool(argv);
// 	GridMap* map = CREATE_MEM_LMAP("test");
// 	for (int i = 0 ; i < 100 ; ++i)
// 	{
// 		map->setgrid((U32)127,78 + i,MAP_OCCUPY_MAX);
// 	}
	GridMap* map = MAP_SERVER.LoadPngMap("M://MyRobot//N_KPS_Arm//bin//x64//Debug//map//408.pgm",map_data_base::MEM,"");
	if(!map){
		return 0;
	}
	MAP_SERVER.fast_inflation(0.3,map->Get_name());
	//MAP_SERVER.save_map(map->Get_name(),"astar.igm");
	//map->expand(GLOBAL_MAP_WIDTH,GLOBAL_MAP_HEIGHT);
	
	GridMap* global_inf_map = CREATE_SHARED_GMAP(GLOBAL_INF_MAP);
	GridMap* laser_inf_map = CREATE_SHARED_LMAP(LASER_INF_MAP);
	laser_inf_map->clear();

	MAP_SERVER.clone(map->Get_name(),global_inf_map->Get_name() );
	MAP_SERVER.RemoveGridMap(map);

	MAP_SERVER.set_map_diff(WORLD_LAYER,ODOM_LAYER,0.0,0.0);
 	

	GridMap* protential_map = CREATE_MEM_GMAP("protential");

	AStar as;
 	as.Init_map();
	
	std::vector<S16xy> path;
	std::list<SPos> wpath;

 	cTimerDiff dt;
 	for (int i = 0;i < 1;++i)
 	{
 		dt.Begin();
 
 		as.SetStart((F32)0,(F32)0);
 		as.SetEnd((F32)-6.4,(F32)-2.3);
 
 		if (as.GeneratePath())
 		{
 			//as.GetPath(path);
			//as.GetSmoothPath(path);
			//as.get_protential(protential_map);
 		}
		
// 		std::vector<S16xy>::iterator it = path.begin();
// 		for (;it != path.end() ; ++it)
// 		{
// 			SPos pos;
// 			pos.th_ = 0;
// 			global_inf_map->grid2world(it->x_,it->y_,pos.x_,pos.y_);
// 			wpath.push_back(pos);
// 		}
		//std::copy(path_list.begin(), path_list.end(), std::back_inserter(vpath));
 		std::cout<<"dt:"<<(long long)(dt.End())<<std::endl;
 	}
// 	cloest_filter filter;
// 	filter.make_cloest(wpath);
 	
  	std::vector<S16xy>::iterator it = path.begin();
  	for (; it != path.end() ; ++it)
  	{
  		global_inf_map->setgrid(U32((*it).x_) ,U32((*it).y_),-99);
  	}

//  	std::list<SPos>::iterator it = wpath.begin();
//  	for (; it != wpath.end() ; ++it)
//  	{
//  		global_inf_map->setgrid(it->x_ ,it->y_,-99);
//  	}

 	MAP_SERVER.save_map(global_inf_map->Get_name(),"after.igm");

	return 0;
}