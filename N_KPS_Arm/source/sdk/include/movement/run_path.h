/***************************************************************************************************
* File name:    run_path.h
* Description:   
* Version:      0.0.1
* History: 
* (1) Author:   wanghongtao
*     Date:     2015-11-25
*     Operate:  Create
*     Version:  0.0.1
* Others: 
***************************************************************************************************/
#ifndef _RUN_PATH_WANGHONGTAO_H_
#define _RUN_PATH_WANGHONGTAO_H_

#include <boost/timer.hpp>
#include <boost/thread/mutex.hpp>
#include "MyDefine.h"
#include "RobotStruct.h"
#include "mapserver/map_def.h"
#include "my_tf.h"
#include "buffer_con.hpp"
#include "mapserver/MapServer.h"


class move_ment_para{
public:

	move_ment_para();
	~move_ment_para();

	void update();
	F32 max_min_w(const F32 & vw);


	F32 local_path_pre_length_;
	F32 stop_pre_ahead_;
	F32 go_stop_model_dis_;
	F32 go_next_path_dis_;

	F32 v_acc_;
	F32 v_dec_;
	F32 w_acc_;
	F32 w_dec_;
	
	F32 max_vx_;
	F32 min_vx_;
	F32 max_inplace_vw_;
	F32 min_inplace_vw_;

	F32 out_of_target_angle_;
	F32 inplace_rotation_angle_;
	F32 inplace_rotation_angle_end_;
	F32 inplace_rotation_pid_p_;

	F32 reduce_speed1_;
	F32 reduce_speed2_;
	
	//F32 stop_angle_diff_;

protected:
private:
	//int local_path_pre_count_;

};


class run_path{

public:
	run_path();
	~run_path();

	bool init( const std::list<SOdomSpeed> &global_path,const SPos robot_pos,GridMap* global_inf_map );

	bool path_ok();
	
	void set_interrupt_path(const std::list<SOdomSpeed> &global_path);
	int update(const SPos &robot_pos);

	//create_local_path and check inplace rotation
	void create_local_path(F32 stop_dis, F32 go_next_path_dis);
	SOdomSpeed get_current_pos_on_path();
	bool get_on_line();

	std::vector<SOdomSpeed> separate_path( F32 &angle_diff, std::list<SOdomSpeed>::iterator &it, std::list<SOdomSpeed>::iterator it_end);

	bool is_last_path();
	bool is_stop_path();


	bool limit_rotation();

	void get_current_speed(SOdomSpeed &speed);

	void get_target_pos(SPos &target_pos,int local_path_pre_count);


	bool is_end_of_path( F32 &current_dis , const SPos &robot_pos,const SPos &final_target_pos, const F32 &stop_dis );
	bool is_long_path(const F32 &pre_head);

	std::list<SOdomSpeed> get_global_path();

	F32 get_final_target_angle();

	bool is_end_of_global_path();
	void erase_global_path();

////////////
	F32 get_path_size(std::vector<SOdomSpeed> &path);
	void get_pos_pre_on_path(SPos &final_target_pos, const std::vector<SOdomSpeed> &path,const F32 &dis);
	F32 get_line_target_pos( SPos &final_target_pos, const move_ment_para &para ,const F32 &pre_speed_dis );
	F32 get_arc_target_pos( SPos &final_target_pos, const move_ment_para &para);

private:
	int impossible_map_cost_;
	bool check_path_available();
	bool go_close_to_robot(const SPos robot_pos);

	std::list<SOdomSpeed> global_path_;
	boost::mutex mu_inr_;
	std::list<SOdomSpeed> interrupt_path_;
	
	GridMap *global_inf_map_;

	SPos get_on_straight_path(std::vector<SOdomSpeed> local_path,int local_path_pre_count);
	SPos get_on_arc_path(std::vector<SOdomSpeed> local_path,SOdomSpeed cur_pos,F32 R);

	std::vector<SOdomSpeed> local_path_;
	std::vector<SOdomSpeed> local_path2_;
	SOdomSpeed current_pos_;
	SOdomSpeed pos_on_path_;
	bool b_line_;

	F32 final_target_angle_;

	bool b_inplace_rotation_;

private:

	F32 path_segment_angle_diff_;
	F32 close_to_path_dis_;
	F32 upload_path_dis_;
	void getPara();

private:
	void publish_upload_path(std::list<SOdomSpeed> &global_path);
	void public_path();
	SparticlePub pub_;
};


#endif//_RUN_PATH_WANGHONGTAO_H_
