/***************************************************************************************************
* File name:    roto_control.h
* Description:   
* Version:      0.0.1
* History: 
* (1) Author:   wanghongtao
*     Date:     2015-11-25
*     Operate:  Create
*     Version:  0.0.1
* Others: 
***************************************************************************************************/
#ifndef _ROTO_CONTROL_WANGHONGTAO_H_
#define _ROTO_CONTROL_WANGHONGTAO_H_

#include <boost/timer.hpp>
#include <boost/thread/mutex.hpp>
#include "MyDefine.h"
#include "RobotStruct.h"
#include "interpro_shared/sh_pool.hpp"
#include "mapserver/map_def.h"
#include "my_tf.h"
#include "buffer_con.hpp"
#include "mapserver/MapServer.h"
#include "TimerDiff.h"

#include "run_path.h"

class roto_control
{
public:

	typedef enum{ CTL_OUT_OF_TARGET = -2, CTL_OUT_OF_LINE = -1, CTL_RUN = 0 , CTL_STOP = 1 , CTL_OBSTACLE_STOP = 2 , CTL_COMMAND_STOP = 3 , CTL_COLLISION_STOP = 4} CONTROL_STATUS;

public:
	roto_control();
	~roto_control();

	void init(const F32 &R);

	CONTROL_STATUS cal_speed( SSpeed &speed , run_path &path ,SPos robot_pos,move_ment_para para, F32 orientation);
	CONTROL_STATUS cal_speed( SSpeed &speed , const std::list<SOdomSpeed> &global_path,SPos robot_pos,move_ment_para para, F32 orientation);
	bool stopping( SSpeed &speed , F32 fdt, SOdomSpeed odom_speed , run_path &path, SPos robot_pos);
	F32 get_stop_target(SPos &final_target_pos);

public:

	void set_speed_limit(const F32 speed_limit);
	void set_max_vx(const F32 max_vx);
	void set_min_vx(const F32 min_vx);
	void set_inplace_max_vw(const F32 max_vw);
	void set_inplace_min_vw(const F32 min_vw);

	void set_out_of_target( const F32 &angle );
	void set_inplace_rotation_angle( const F32 &angle );
	void set_inplace_rotation_angle_end( const F32 &angle );
	void set_inplace_rotation_pid_p( const F32 &p );
	void set_local_path_pre_length(const F32& pre_len,const F32 &pre_ext);
	void set_reduce_speed1(const F32 &speed);
	void set_reduce_speed2(const F32 &speed);
private:
	CONTROL_STATUS circle_clt(F32 &line_speed ,F32 &angle_speed,const F32 &Vx ,const SPos &robot_pos,  const SPos &target_pos ,bool b_line ,bool b_limit_rotation);
	CONTROL_STATUS line_ctl(F32 &line_speed ,F32 &angle_speed,const F32 &Vx ,const SPos &robot_pos,  const SPos &target_pos );
	bool inplace_rotation_ok_;
private:

	F32 R_;
// 	F32 pre_head_;
// 	F32 go_straight_dy_;
	F32 out_of_line_;


private:
	void max_min_vx(F32 &target_vx);
	CONTROL_STATUS get_ex_speed_ctl(F32 &curent_speed);
	F32 reduce_speed1_;
	F32 reduce_speed2_;
	GridMap *prohibit_map_;
	F32 get_target_vx(run_path &path);
	SPos extern_pos(SPos target_pos , F32 pre_dis);
	SPos get_target_pos(SPos &target_pos,run_path &path, F32 local_path_pre_length, F32 orientation);
	SPos get_target_pos(SPos &target_pos,run_path &path, const move_ment_para &para ,const F32 &target_speed, F32 orientation);

	bool check_out_of_target(const SPos &robot_pos , const F32 target_speed, const F32 orientation);
	SOdomSpeed pos_on_path_;
	//bool b_line_;

	F32 close_to_path_;
	F32 angle_diff_;
	SPos robot_pos_;
	move_ment_para para_;
	CSBuffer<F32,20> buf_speed_limit_;

	F32 max_vx_;
	F32 min_vx_;

	F32 max_min_w(const F32 & vw);
	F32 max_inplace_vw_;
	F32 min_inplace_vw_;

	bool line_control_;
	F32 stop_distance_;
	F32 f_stop_acc_;
	SPos final_target_pos_;


	F32 local_path_pre_length_;
	int local_path_pre_count_;

	F32 stop_angle_diff_;

	F32 out_of_target_angle_;
	F32 inplace_rotation_angle_;
	F32 inplace_rotation_angle_end_;
	F32 inplace_rotation_pid_p_;

private:
	void set_show_pos(const SPos &pos);
	void set_show_pos( const SOdomSpeed &opos );
	void publish_pos();
	
	SparticlePub pub_;

	std::list<SOdomSpeed> show_pos_;


public:

	void set_dynamic_speed( U8 id, SDynamic_Speed dynamic_speed);

private:

	bool get_dynamic_targetVx( F32 &limit_vx );
	std::map<U8,SDynamic_Speed> mDynamic_speed_;
	cTimerDiff dt_dynamic_speed_;
	boost::mutex mu_dynamic_;
};

#endif//_ROTO_CONTROL_WANGHONGTAO_H_
