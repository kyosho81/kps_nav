#ifndef _SUB_MAP_LOCALIZATION_KYOSHO_20210704_
#define _SUB_MAP_LOCALIZATION_KYOSHO_20210704_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "robot/tf_2d_server.h"

class sub_map_localization
{
public:
	sub_map_localization();
	~sub_map_localization();

	bool init();

protected:
private:
	void sub_callback();
};


#endif//_SUB_MAP_LOCALIZATION_KYOSHO_20210704_
