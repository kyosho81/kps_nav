#ifndef _BATTERY_STRATEGY_WANGHONGTAO_KYOSHO_20200912_
#define _BATTERY_STRATEGY_WANGHONGTAO_KYOSHO_20200912_

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <ctime>
#include <map>

#include <boost/lexical_cast.hpp>
#include <boost/serialization/singleton.hpp>
#include "boost/unordered/unordered_map.hpp"




#include "Comm/Comm.h"
#include "Comm/TimerDiff.h"
#include "Comm/configs.h"
#include "interpro_shared/sh_pool.hpp"
#include "robot/RobotStruct.h"

#include "mapserver/MapServer.h"
#include "project/project_manage.h"
#include "Comm/buffer_con.hpp"

class battery_strategy
{
public:
	battery_strategy();
	~battery_strategy();


	

	eBatSta get_bat_sta(const F32 &bat_level);
	F32 get_per();

protected:
private:

	filter<F32,5> filter_;

	F32 full_level_;
	F32 low_level_;
	F32 charge_level_;
	F32 shutdown_level_;

	eBatSta bat_sta_;
	F32 percent_;
};

#endif //_BATTERY_STRATEGY_WANGHONGTAO_KYOSHO_20200912_
