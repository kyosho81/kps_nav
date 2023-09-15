#ifndef _LOCAL_PLANNER_CARROT_KYOSHO_20150906_
#define _LOCAL_PLANNER_CARROT_KYOSHO_20150906_

#include <vector>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "robot/pos_ctl.h"

class local_planner_carrot{
public:
	local_planner_carrot();
	~local_planner_carrot();

	void init();

	void planner(SSpeed& speed,const SPos& current_pos,const SPos& C,const SPos& L,const SPos& target);
	
private:

	void publish(SSpeed& speed, const SPos& current_pos,const SPos& C,const SPos& L);

	pos_ctl pctl_;
};



#endif//_LOCAL_PLANNER_CARROT_KYOSHO_20150906_
