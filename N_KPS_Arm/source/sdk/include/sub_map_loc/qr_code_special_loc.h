#ifndef _QR_CODE_SPECIAL_LOCALIZATION_KYOSHO_20210704_
#define _QR_CODE_SPECIAL_LOCALIZATION_KYOSHO_20210704_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "robot/tf_2d_server.h"

#include "special_loc_base.h"

class qr_code_special_loc : public special_loc_base
{
public:
	qr_code_special_loc();
	virtual ~qr_code_special_loc();

private:
	bool sm_robot_in_loc_ori( SPos &pos );
};


#endif//_LASER_SPECIAL_LOCALIZATION_KYOSHO_20210704_
