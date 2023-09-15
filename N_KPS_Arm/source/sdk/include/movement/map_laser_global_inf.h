#ifndef _MAP_LASER_GLOBAL_INF_WANGHONGTAO_2023_03_16_
#define _MAP_LASER_GLOBAL_INF_WANGHONGTAO_2023_03_16_

#include <vector>
#include <map>
#include <boost/thread.hpp>

#include "MyDefine.h"
#include "TimerDiff.h"
#include "RobotStruct.h"
#include "buffer_con.hpp"
#include "robot/my_tf.h"
#include "mapserver/MapServer.h"

class map_laser_global_inf
{
public:

	map_laser_global_inf();
	~map_laser_global_inf();

	void init();

	void call_laser(const SLaser& used_laser);
	void call_rslaser(const SLaser& rs_laser);
	void call_back_amcl(const SPos &amcl_pos);

	void run();
	void exit();

	GridMap* get_laser_map();
protected:
private:

	void init_laser_inf_map();
	void clear_empty(const SLaser &used_laser,const SPos &robot_pos);
	void laser_inflation(const SPos &pos);
	void publish_show();
	bool b_first_clear_;
	F32 cos_laser_[LASER_COUNT];
	F32 sin_laser_[LASER_COUNT];

	GridMap* gmap_laser_inf_ ;
	CSBuffer<SLaser,1> call_laser_;
	SBuffer<SLaser> call_rs_laser_;
	SLaserXY laser_data_;
	SLaser used_laser_;

	my_tf tf_;

	SPos amcl_pos_;
	boost::mutex amcl_mutex_;
	bool first_laser_;

	filter2D_template f2d_;

	F32 laser_dx_;
	F32 laser_dy_;

	F32 laser_obs_inf_;
	int laser_inf_pub_;
	int publish_count_;
	F32 laser_obs_roi_;
};

#endif//_MAP_LASER_GLOBAL_INF_WANGHONGTAO_2023_03_16_
