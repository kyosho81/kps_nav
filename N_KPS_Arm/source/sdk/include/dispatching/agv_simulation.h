#ifndef _AGV_SIMULATION_WANGHONGTAO_KYOSHO_20200912_
#define _AGV_SIMULATION_WANGHONGTAO_KYOSHO_20200912_

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


#include "mapserver/MapServer.h"
#include "project/project_manage.h"
#include "battery_strategy.h"
#include "schedule.h"
#include "task_run_time.h"
#include "dispatching/agv_base.h"

class agv_simulation : agv_base
{
public:
	agv_simulation();
	~agv_simulation();

	
	bool init(const std::string &str_ip, const SAGV_Info &agv_info);

protected:
private:
	bool do_init();
	AGV_SM run_sm();
	void set_off_line();
	bool do_check_charge();

	cTimerDiff dt_;
};


#endif //_AGV_SIMULATION_WANGHONGTAO_KYOSHO_20200912_
