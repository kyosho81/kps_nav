#include "math.h"


#include "interpro_shared/sh_pool.hpp"

#include "Geometry.h"

#include "mapserver/map_def.h"
#include "mapserver/MapServer.h"


#include "robot/local_planner_carrot.h"

local_planner_carrot::local_planner_carrot()
{

}

local_planner_carrot::~local_planner_carrot()
{

}

void local_planner_carrot::init()
{

}

void local_planner_carrot::planner(SSpeed& speed, const SPos& current_pos,const SPos& C,const SPos& L,const SPos& target)
{

	
	pctl_.Make_target_line(C,L);

	pctl_.Cal_speed(speed,target,current_pos);

	publish(speed,current_pos,C,L);
}
void local_planner_carrot::publish(SSpeed& speed, const SPos& current_pos,const SPos& C,const SPos& L){
	
	LocalShow ls;
	ls.C_.x_ = C.x_;
	ls.C_.y_ = C.y_;
	ls.L_.x_ = L.x_;
	ls.L_.y_ = L.y_;

	pctl_.get_data(ls.H_,ls.line_,C);

	ls.v_ = speed.vx_;
	ls.w_ = speed.vw_;

	//shared_pool::Publish(shared_pool::name(),"local_show",ls);
	PUB_MSG_SH_POOL("local_show",ls);

}