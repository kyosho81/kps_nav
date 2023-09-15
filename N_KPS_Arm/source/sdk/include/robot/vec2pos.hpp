#ifndef _VEC2POS_POS2VEC_KYOSHO_2019_09_17_
#define _VEC2POS_POS2VEC_KYOSHO_2019_09_17_

#include "robot/Geometry.h"
#include "robot/RobotStruct.h"

static void Vec2Pos(SPos &pos,VecPosition vec,double angle)
{
	pos.x_ = vec.getX();
	pos.y_ = vec.getY();
	pos.th_ = angle;
};

static double Pos2Vec(VecPosition &vec,const SPos &pos)
{
	vec.setX(pos.x_);
	vec.setY(pos.y_);
	return pos.th_;
};
#endif//_VEC2POS_POS2VEC_KYOSHO_2019_09_17_