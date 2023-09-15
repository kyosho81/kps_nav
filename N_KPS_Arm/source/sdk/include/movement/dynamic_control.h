/***************************************************************************************************
* File name:    dynamic_control.h
* Description:   
* Version:      0.0.1
* History: 
* (1) Author:   wanghongtao
*     Date:     2019-5-21
*     Operate:  Create
*     Version:  0.0.1
* Others: 
***************************************************************************************************/
#ifndef _DYNAMIC_CONTROL_WANGHONGTAO_H_
#define _DYNAMIC_CONTROL_WANGHONGTAO_H_

#include <boost/timer.hpp>
#include <boost/thread/mutex.hpp>
#include "MyDefine.h"
#include "RobotStruct.h"
// #include "interprocess_core/reg_msg.h"
// #include "interprocess/shared_pool.hpp"
#include "interpro_shared/sh_pool.hpp"

#include "my_tf.h"
#include "buffer_con.hpp"

#include "vpp_container.h"
#include "robot/robot_remote_para.h"
#include "task_path.h"
#include "laser_filter/laser_filter.h"
#include "robot/mid_filter.hpp"

#include "protobuf_msg/protobuf_path.h"

class GridMap;



class dynamic_ctl_para{
public:

	dynamic_ctl_para();
	~dynamic_ctl_para();

	void update_para();

	void cal_range(const SLaser &laser_data);
	void save_laser(const std::string &file_nm,const SLaser &laser_data);

	F32 prediction_dx_;
	F32 dx0_weight_;
	F32 dx1_weight_;

	F32 inplace_rotate_w_;

	std::string obs_range_;
	std::string empty_range_;
	SPos laser_diff_;

	F32 laser_min_range_;
	F32 laser_max_range_;

	F32 laser_min_angle_;
	F32 laser_max_angle_;

	F32 f_check_front_empty_sim_laser_;

	bool b_first_laser_;
	SLaser obs_laser_range_;
	SLaser empty_laser_range_;

	F32 detour_ctl_vx_;
	F32 path_inf_;
	F32 goal_inf_;

	F32 close_to_end_path_;
	F32 out_of_path_;
	F32 back_to_path_;
	F32 roto_path_enough_;
	F32 back_to_path_angle_;

	F32 dy_max_angle_diff_;

	F32 dy_global_map_inf_;
	F32 dy_prohibit_map_inf_;

	F32 dy_dis_goal_to_robot_;

	F32 dy_far_away_target_dis_;
	F32 dy_far_away_target_angle_;

	laser_filter p_l_filter_;

	void pub_laser_range(const Range_type& range_type , const SLaser &laser_data);
};
class dynamic_control
{
public:

	typedef enum{
		DCTL_STATUS_ROT_TARGET = 0,
		DCTL_STATUS_ROT_CHECK = 1,
		DCTL_STATUS_ROT = 2,
		DCTL_STATUS_DETOUR = 3,
		DCTL_STATUS_GOSTRAIGHT = 4,
		DCTL_STATUS_STRAIGHT = 5,
		DCTL_STATUS_RSTOPPING = 6,
		DCTL_STATUS_DSTOPPING = 7,
		DCTL_STATUS_DONE = 8,
		DCTL_STATUS_ERROR_PATH = 9,
		DCTL_STATUS_ERROR_ANGLE = 10
	}EDCTL_state;

	typedef enum{
		FORWARD,
		BACKWARD
	}DIR;

	dynamic_control();
	~dynamic_control();

	void init( GridMap* laser_inf_gmap ,bool b_check_backtopath);
	
	void reset();
	dynamic_control::EDCTL_state cal_speed( SSpeed &set_speed , task_path &path, SPos robot ,SOdomSpeed odom );
	void get_target(SPos &current_drop, SPos &current_target ,DIR &direction, F32 &stop_dis);
	bool check_away_target( const SPos &target ,const SPos &robot);

	void set_laser( const SLaser &laser);

	void test_map();
	void test_path_map();

	F32 set_stop_pos(SPos &target_pos, SPos &current_drop, const SPos &robot_pos);
	void draw_prohibit_path(const std::list<SLine2P> &prohibit_path);

protected:
private:

	dynamic_ctl_para para_;

	GridMap* global_nav_map_;
	GridMap* global_prohibit_map_;
	GridMap* laser_inf_gmap_;

	GridMap* path_inf_map_;
	GridMap* goal_inf_map_;

	bool check_front_obs(F32 &angle_head , SPos pos);
	int check_front_empty(F32 &angle_head , SPos pos);
	bool waitstopover(const SOdomSpeed &odom);
	bool roto_ctl( SSpeed &set_speed , const F32 &tar_angle,const F32 &robot_angle);
	void roto_ctl( SSpeed &set_speed , const F32 &angle);
	bool get_total_weiht( S32 &total_path_weight, sim_path &path, const SPos &robot_pos);
	bool get_path_weiht(S32 &total_path_weight,sim_path &path,const SPos &robot_pos);
	bool filter_sim_path( sim_path &path , int i_del_size );

	bool detour_ctl( SSpeed &set_speed , const SPos &robot_pos);
	//bool get_inplace_rot(F32 &angle_head);
	bool get_inplace_rot_potential(F32 &angle_head,const SPos &robot_pos);
	bool init_roto_potential();
	std::vector<SPath_VW> v_roto_potential_;

	S16 get_value(const F32 &fx, const F32 &fy);
	S8 get_obs_value(const U32 &gx, const U32 &gy);
	S8 get_obs_value2(const U32 &gx, const U32 &gy);

	bool update_pos_from_path( SPos &current_drop ,SPos &current_target, std::list< std::list<SOdomSpeed>::iterator > path);
	bool update_global_path_map(std::list<SOdomSpeed> &earse_path_points,std::list<SOdomSpeed> &new_path_points);

private://dy path search
	vpp_container vpp_container_;
	filter2D_template f2d_;
	filter2D_template f2d_path_;

	void set_state(EDCTL_state new_dy_status);
	EDCTL_state dy_state_;
	SPos go_straight_begin_;
	
	bool check_laser(F32 &angle, const SLaser &real_laser,const SLaser &ref_laser);
	
	CSBuffer<SLaser,1> real_laser_;
	F32 angle_empty_;
	F32 rot_robot_angle_;
	int rot_continue_;
	F32 empty_angle_;
	F32 last_w_;

private:
	bool b_check_backtopath_;
	//F32 SPos2VecP( VecPosition &vec, const SPos &spos );
	bool check_endofpath( const SPos &target,const SPos &robot);
	bool check_backtopath( const SPos &drop,const SPos &robot);
	
	F32 last_dis2path_;
	bool b_call_dis2path_;


	SPos current_drop_;
	SPos current_target_;
	F32 stop_dis_;
	DIR direction_;

	bool b_first_call_;
private:

	protobuf_path pub_path_;
	void publish_data(std::vector<SPath_VW> vw_list,const S32 &select_id);

	void pub_laser_range_show(const Range_type& range_type);

private:
	SPos begin_rot_pos_;
	
	void set_begin_rot(const SPos &robot_pos);
	bool roto_dis_enough(const SPos &robot_pos);

	
private:
	void draw_prohibit_path(const SVec &p1 , const SVec &p2);
	int i_max_prohibit_path_;

	bool get_laser_with_simdata(SLaser &laser, SPos pos);
	bool sim_laser(SLaser &laser_data, SPos pos);
	
	bool b_sim_first_;

	F32* cos_;
	F32* sin_;

	mid_filter<F32> rot_w_filter_;
	SLaserXYEx pub_sim_laser_;
	laser_filter l_filter_;
	SLaser laser_filter_range_;
};
#endif//_DYNAMIC_CONTROL_WANGHONGTAO_H_
