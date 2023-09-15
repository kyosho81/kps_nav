#ifndef _ODOM_CTL_WANGHONGTAO_2016_07_01_
#define _ODOM_CTL_WANGHONGTAO_2016_07_01_

#include <boost/thread.hpp>

#include "RobotStruct.h"
#include "Geometry.h"
#include "TimerDiff.h"

#include "angle_ctl.h"

class pos_ctl{
public:
	pos_ctl();
	~pos_ctl();

	void Set_ahead(const F32& ahead);
	void Make_target_line(const SPos& C,const SPos& L);
	void Cal_speed(SSpeed &speed,const SPos& target,const SPos& odom);
	void get_data(SVec& H,SLinePA& line,const SPos& C);

private:
	
	//ahead
	F32 f_ahead_;

	//current pos in odom (base_odom pos)
	SPos current_pos_;
	//temporary ahead in front of the robot (base_link pos)
	VecPosition v_H_;
	//mirror symmetry of v_H_
	VecPosition v_mH_;

	//closest point on planner's path
	VecPosition v_C_;
	//temporary point on planner's path
	VecPosition v_L_;
	

	//target line and vector
	Line target_line_;
	VecPosition v_target_;   //segment off target line , from v_C_ to v_L_ ,describe the target vector


	F32 get_target_mod();	 //use v_C_ and v_L_ cal target_mod ,target_mod * kv = vx
	F32 cal_vx();
	F32 cal_vw();

private:

	F32 f_stop_distance_;	//stop distance
	F32 f_stop_time_;		//stop time £ºreference to current speed_v and distance
	F32 f_stop_acc_; 		//stop acc
	bool b_moving_;        //stopping

	F32 min_speed_;

	angle_ctl actl_;

	F32 task_speed_v_;

	cTimerDiff dt_;

	bool moving(const VecPosition &v_stop);
};

#endif//_ODOM_CTL_WANGHONGTAO_2016_07_01_
