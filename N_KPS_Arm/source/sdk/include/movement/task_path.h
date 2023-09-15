/***************************************************************************************************
* File name:    task_path.h
* Description:   
* Version:      0.0.1
* History: 
* (1) Author:   wanghongtao
*     Date:     2019-4-17
*     Operate:  Create
*     Version:  0.0.1
* Others: 
***************************************************************************************************/
#ifndef _TASK_PATH_WANGHONGTAO_H_
#define _TASK_PATH_WANGHONGTAO_H_

#include <boost/timer.hpp>
#include <boost/thread/mutex.hpp>
#include "MyDefine.h"
#include "RobotStruct.h"

#include "interpro_shared/sh_pool.hpp"

#include "my_tf.h"
#include "buffer_con.hpp"
#include "robot/RobotStruct.h"

#define PATH_SIZE 120




class task_path
{
public:

	task_path();
	~task_path();

	
	void init_file(std::string str_path_name);
	void init_suro(const std::list<SPathData> &src_task_list);
	void init_test();
	void clear_data();

	//set current path segment in src task list
	void get_current_p_list(const SPos &current_robot,const F32 path_radius);
	//get tmp target point on current_p_list
	SPos get_tmp_begin_point(const SPos &current_robot);

	EPath_status get_path_status();
	
	const std::list<SPathData> &get_task_statue();

	//set current_data of src_task_list_ x%
	//if robot pos over the end of current_data to point set 100%
	//precent only increase
	//if no path to run return false
	bool update_task_list_percent(const SPos &current_robot);
	int get_spath_seg(std::vector<SPathData> &v_seg_path);

	//update begin pos where robot pos drop on line
	bool update_begin_pos(const SPos &current_robot);
	
	void create_run_path();
	void erase_path(const SPos &robot_pos);
	void erase_path_sim(const SPos &robot_pos);
	std::list< std::list<SOdomSpeed>::iterator >& get_run_path(const SPos &robot_pos,bool b_sim = false);
	bool last_seg();

	int path_size();
	std::list< std::list<SOdomSpeed>::iterator >& get_tmp_run_path();
	void clear_tmp_run_path();

	std::list<SOdomSpeed> get_earse_path_points();
	//std::list<SOdomSpeed>& get_new_path_points();
	std::list<SOdomSpeed>& get_all_path();

	F32 path_max_v_;
	F32 path_min_v_;
	F32 path_radius_;

	//shift move angle(left shift 1.57 right shift -1.57)
	F32 orientation_;
	bool negative_speed_;
	void print();

private:

	void add_path(const SPathData &task_path);
	void clear_path_data(SPathData &path_data);
	
	//find current path segment
	bool find_current_path();
	std::list<SPathData>::iterator it_current_path_data_;
	std::list<SPathData> src_task_list_;

	bool path_to_run(const F32 precent);

	

private:
	F32 far_from_begin_pos_;
	SPos begin_pos_;
	VecPosition sp2vec(const SPos &pos);
	F32 disof2sp(const SPos &sb,const SPos &se);
	bool check_inline( const SOdomSpeed &A,const SOdomSpeed &B,const SOdomSpeed &C );
	
	std::list<SOdomSpeed> path_points_;
	std::list<SOdomSpeed> earse_path_points_;
	std::list<SOdomSpeed> new_path_points_;

	//int erase_tmp_run_path(std::list<SOdomSpeed>::iterator it_e);
	std::list< std::list<SOdomSpeed>::iterator > tmp_run_path_;
	F32 discrete_path_dx_;
	int discrete_path_cnt_;
	F32 explore_dis_;

	EPath_status path_status_;
};


#endif//_TASK_BASE_WANGHONGTAO_H_
