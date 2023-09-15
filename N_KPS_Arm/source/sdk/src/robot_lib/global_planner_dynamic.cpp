#include "Geometry.h"
#include "math.h"
#include "mapserver/map_def.h"
#include "mapserver/MapServer.h"

#include "robot/Astar.h"

#include "robot/global_planner_dynamic.h"

global_planner_dynamic::global_planner_dynamic()
{

}

global_planner_dynamic::~global_planner_dynamic()
{

}
void global_planner_dynamic::init_astar(){
	astar_ = new AStar();
	astar_->Init_map();
}
bool global_planner_dynamic::begin_planner(std::list<SGridXY> &path,const SPos& current_pos,const SPos& goal_pos){
	
	astar_->SetStart(current_pos.x_,current_pos.y_);
	astar_->SetEnd(goal_pos.x_,goal_pos.y_);

	GridMap* laser_map_ = MAP_SERVER.GetGridMap(SHARED_LASER_INF_MAP);
	laser_map_->lock();

	if (astar_->GeneratePath())
	{
		astar_->GetPath(path);
		//astar_->GetSmoothPath(path);
		laser_map_->unlock();
		return true;
	}
	laser_map_->unlock();
	return false;
}
void global_planner_dynamic::stop_planner(){
	astar_->stop();
	std::cout<<"stop planner!!"<<std::endl;
}