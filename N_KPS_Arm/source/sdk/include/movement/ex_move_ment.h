/***************************************************************************************************
* File name:    move_ment.h
* Description:   
* Version:      0.0.1
* History: 
* (1) Author:   wanghongtao
*     Date:     2019-4-16
*     Operate:  Create
*     Version:  0.0.1
* Others: 
***************************************************************************************************/
#ifndef _EX_MOVE_MENT_KYOSHO_H_
#define _EX_MOVE_MENT_KYOSHO_H_

#include <boost/timer.hpp>
#include <boost/thread/mutex.hpp>
#include "MyDefine.h"
#include "RobotStruct.h"
#include "interpro_shared/sh_pool.hpp"
#include "mapserver/map_def.h"
#include "my_tf.h"
#include "buffer_con.hpp"
#include "mapserver/MapServer.h"


#include "roto_control.h"
#include "dynamic_control.h"
#include "laser_filter/laser_filter.h"

#include "movement/map_laser_inf.h"
#include "movement/map_laser_global_inf.h"
#include "movement/check_obs.h"
#include "movement/arc_rot_control.h"

class global_planner;



class ex_move_ment{

public:
	ex_move_ment();
	~ex_move_ment();

	void init(bool b_suro = false);


	int spin();
	int run();
	bool do_once();

	void exit();

	void set_run(std::string str_plan);

//	bool update(const SPos &pos);

	//call back
	bool call_back_odom(const SOdomSpeed &odomspeed);
	bool call_back_amcl( const SPos &amcl_pos );
	bool call_back_path( const SRunPath &path );
	bool call_back_ref( const SPOS_CONFIDENCE &ref_pos );
	bool draw_prohibit_path( const std::list<SLine2P> &prohibit_path );
	bool call_laser(SLaser used_laser);
	bool call_laser(SLaser used_laser,SLaser rs_laser);
	bool call_back_dynamic_speed( const SDynamic_Speed &dynmic_speed );
	void call_back_suro_path(const std::list<SPathData> &suro_path);
	void call_back_stop_run();
	bool call_back_pause( const int &i_pause);

	void bind_task_feedback(boost::function< void( const std::list<SPathData> &task_data,SRunStatus run_status )> fnc_task_status){
		fnc_task_status_ = fnc_task_status;
	};
	void bind_set_speed(boost::function<void( const SSpeed &speed)> fnc_set_speed){
		fnc_set_speed_ = fnc_set_speed;
	};

	std::string get_str_m_status();

private:

	void init_call_back();

	CSBuffer<SPos,30> buf_amcl_pos_;
	THSafe<SOdomSpeed> ths_odom_;
	THSafe<bool> th_pause_;
	
private:
	
	void set_speed(SSpeed speed);
	void set_stop_wait();
	SSpeed target_speed_;

    void publish_path(std::list<SOdomSpeed> &global_path);

	//state mechine
private:

	void st_plan();
	void st_stopping();
	void st_dy_moving();
	void st_fix_moving();
	void st_idle();
	void st_err();

	void st_to_plan();
	void st_to_moving();
	
	void st_to_stopping();
	void st_to_idle();
	void st_to_error(const U16 err_code);
	
		
	THSafe<EX_MState> st_state_;
	U16 err_code_;

	F32 fdt_runtotal_;
	bool check_health(const F32 &dt);
	SPos robot_pos_;


	THSafe<bool> th_over_;
	void check_over();

	SRunStatus run_status_;

	bool check_pub_time();
	bool is_pub_time();
	void pub_state();
	void set_state(EX_MState state);

	int mverr2deverr(int err_code);
	int mvsta2devsta(int mv_sta);
	void pub_monitor_status( U8 status, U16 err_code);

	void pub_new_err();

	void pub_task();


	boost::function<void( const std::list<SPathData> &task_data,SRunStatus run_status)> fnc_task_status_;
	boost::function<void( const SSpeed &speed)> fnc_set_speed_;

private:
	void init_th();
	bool b_run_;
	void th_run();

	cTimerDiff dt_;
	F32 fdt_;
	int ms_run_loop_;
	int i_pub_cnt_;
	int ms_pub_cycle_;
	bool b_pub_time_;
//make plan thread
private:
	

	bool make_planner();
	global_planner* global_planner_;
	std::string str_plan_;

	task_path task_path_;

	run_path run_path_;
	
	roto_control control_;

private:
	bool b_pub_run_path_;
	SparticlePub pub_;
	void show_run_path(CrList<SOdomSpeed, PATH_SIZE> run_path);
	//pub for action tray
	void pub_seg_path();

private:
	void update_para();
	move_ment_para para_;

public:
	CSBuffer<int,1> th_state_thread_run_;

	//dynamic speed
private:
	void set_dynamic_speed( U8 id, SDynamic_Speed dynamic_speed);

	
private:
	dynamic_control dynamic_control_;

private:
	bool check_out_of_target(const SPos &robot_pos);
	int stopping(SSpeed &speed , F32 fdt, SOdomSpeed odom_speed, const SPos &robot_pos);
	
	SPos final_target_pos_;
	SPos pos_on_path_;
	dynamic_control::DIR dir_;

	F32 stop_distance_;
	F32 f_stop_acc_;
	
private:
	map_laser_inf map_laser_inf_;
	map_laser_global_inf map_laser_global_inf_;

	bool first_laser_ ;
	laser_filter l_filter_;
	bool b_suro_;

	bool b_tollage_;

	
private:
	bool update_pipe_seg_path( std::string name,U8* data,U32 len );
	boost::mutex pipe_mu_;
	std::list<SPathData> v_seg_path_;

	bool b_laser_safe_;
	bool check_laser_safe(std::list< std::list<SOdomSpeed>::iterator > &cpath,std::list<SOdomSpeed> &global_path);
	SBuffer<SLaser> buf_real_laser_;
	check_obs check_obs_;

	check_obs::EOBS check_obs_on_path( const F32 &dt,const SLaser &laser);
	
	F32 obs_on_path_add_;
	F32 max_on_path_add_;
	F32 fix_slow_speed_;
	

	SLaser test_laser_;
//
private:
	arc_rot_control arc_rot_control_;

	SSpeed last_set_peed_;

};


#endif//_EX_MOVE_MENT_KYOSHO_H_
