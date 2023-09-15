#ifndef _MAP_LASER_INF_WANGHONGTAO_2017_05_26_
#define _MAP_LASER_INF_WANGHONGTAO_2017_05_26_

#include <vector>
#include <map>
#include <boost/thread.hpp>

#include "MyDefine.h"
#include "TimerDiff.h"
#include "RobotStruct.h"
#include "buffer_con.hpp"
#include "robot/my_tf.h"
#include "mapserver/MapServer.h"

class map_laser_inf
{
public:

	map_laser_inf();
	~map_laser_inf();

	void init();

	void call_laser(const SLaser& used_laser);
	void call_back_amcl(const SPos &amcl_pos);

	void run();
	void exit();

	GridMap* get_laser_map();
protected:
private:

	void init_laser_inf_map();
	void laser_inflation(const SLaserXY& after_tf);
	void publish_show();


	GridMap* laser_inf_ ;
	CSBuffer<SLaser,1> call_laser_;
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

#endif//_MAP_LASER_INF_WANGHONGTAO_2017_05_26_
