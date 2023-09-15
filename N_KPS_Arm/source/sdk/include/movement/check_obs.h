/***************************************************************************************************
* File name:    check_obs.h
* Description:   
* Version:      0.0.1
* History: 
* (1) Author:   wanghongtao
*     Date:     2019-4-17
*     Operate:  Create
*     Version:  0.0.1
* Others: 
***************************************************************************************************/
#ifndef _CHECK_OBS_WANGHONGTAO_H_
#define _CHECK_OBS_WANGHONGTAO_H_

#include <boost/timer.hpp>
#include <boost/thread/mutex.hpp>
#include "MyDefine.h"
#include "RobotStruct.h"
// #include "interprocess_core/reg_msg.h"
// #include "interprocess/shared_pool.hpp"
#include "interpro_shared/sh_pool.hpp"

#include "my_tf.h"
#include "buffer_con.hpp"
#include "robot/RobotStruct.h"

#include "laser_filter/laser_filter.h"

class check_obs
{
public:
	typedef enum{
		EMPTY,
		SLOW,
		STOP,
		BLOCK
	}EOBS;

	check_obs();
	~check_obs();

	void init();

	int check_obs_continue(const SLaser &laser_range ,const SLaser &laser_data );
	
	EOBS check_obs_on_line(const F32 &dt , const SLaser &laser_data);

protected:
private:

	SLaser obs_range_in_;
	SLaser obs_range_out_;
	SLaser obs_range_slow_;

	std::string str_obs_range_in_;
	std::string str_obs_range_out_;
	std::string str_obs_range_slow_;

	bool b_first_laser_;

	laser_filter l_filter_;

	SPos laser_diff_;

	F32 laser_min_angle_;
	F32 laser_max_angle_;

	int ignore_obs_cnts_;

	bool last_in_;

	void pub_laser_range(const Range_type& range_type , const SLaser &laser_data);
	void pub_laser_range_show( const Range_type& range_type );
};

#endif//_CHECK_OBS_WANGHONGTAO_H_
