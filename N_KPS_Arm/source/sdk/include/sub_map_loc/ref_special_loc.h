#ifndef _REF_SPECIAL_LOCALIZATION_KYOSHO_20230504_
#define _REF_SPECIAL_LOCALIZATION_KYOSHO_20230504_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "robot/tf_2d_server.h"

#include "special_loc_base.h"

class ref_special_loc : public special_loc_base
{
public:
	ref_special_loc();
	virtual ~ref_special_loc();

	bool update_ref(const SReflector &ref);

private:
	bool init_special();
	bool init_sub_msg();
	bool parse_para(std::string str_name, std::string str_para);

	void set_loc_odom(SOdomSpeedEx odom_ex);

	bool sm_robot_in_loc_ori( SPos &pos );

	int sub_id_ref_loc_;

};


#endif//_REF_SPECIAL_LOCALIZATION_KYOSHO_20230504_
