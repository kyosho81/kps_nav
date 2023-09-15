/***************************************************************************************************
* File name:    global_planner.h
* Description:   
* Version:      0.0.1
* History: 
* (1) Author:   wanghongtao
*     Date:     2019-4-19
*     Operate:  Create
*     Version:  0.0.1
* Others: 
***************************************************************************************************/
#ifndef _GLOBAL_PLANNER_WANGHONGTAO_H_
#define _GLOBAL_PLANNER_WANGHONGTAO_H_

#include <boost/timer.hpp>
#include <boost/thread/mutex.hpp>
#include "MyDefine.h"
#include "RobotStruct.h"
#include "interpro_shared/sh_pool.hpp"
#include "mapserver/map_def.h"
#include "my_tf.h"
#include "buffer_con.hpp"
#include "mapserver/MapServer.h"

//#include "bag/recoder.h"
#include "task_path.h"

class global_planner{

public:

	global_planner();
	~global_planner();

	bool init(task_path* p_path);

	bool plan(const SPos &robot_pos);
	void stop_plan();


private:
	THSafe<SPos> c_robot_pos_;
	

	void init_th();
	THSafe<int> i_run_;
	void th_run();
	boost::thread* th_run_;
	THSafe<bool> ts_planner_over_;

	void make_path();

	task_path* p_task_path_;
};


#endif//_GLOBAL_PLANNER_WANGHONGTAO_H_
