#ifndef _LASER_SPECIAL_LOCALIZATION_KYOSHO_20210704_
#define _LASER_SPECIAL_LOCALIZATION_KYOSHO_20210704_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "robot/tf_2d_server.h"

#include "special_loc_base.h"
#include "triangle_sm.h"
#include "sensor/laser_filter/laser_filter.h"

class laser_special_loc : public special_loc_base
{
public:
	laser_special_loc();
	virtual ~laser_special_loc();

	bool init_sensor_diff(F32 laser_dx,F32 laser_dy,F32 laser_th);

private:

	bool init_sub_msg();
	bool init_sensor_diff();

	bool sm_robot_in_loc_ori( SPos &pos );

	triangle_sm triangle_sm_;

	std::string str_robot_shape_;
	SPos laser_in_base_link_;
	laser_filter l_filter_;
	bool b_init_filter_;
	//sub
	int sub_id_laser_;
	bool updata_used_laser(const SLaser &new_laser);
};


#endif//_LASER_SPECIAL_LOCALIZATION_KYOSHO_20210704_
