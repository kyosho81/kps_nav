#ifndef _GLOBAL_PLANNER_DYNAMIC_KYOSHO_20150906_
#define _GLOBAL_PLANNER_DYNAMIC_KYOSHO_20150906_

#include <vector>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"

class AStar;

class global_planner_dynamic{
public:
	global_planner_dynamic();
	~global_planner_dynamic();

	void init_astar();

	bool begin_planner(std::list<SGridXY> &path,const SPos& current_pos,const SPos& goal_pos);
	void stop_planner();

private:
	
	AStar* astar_;

};



#endif//_GLOBAL_PLANNER_DYNAMIC_KYOSHO_20150906_
