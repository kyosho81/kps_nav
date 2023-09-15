#ifndef _STATE_MACHINE_CHARGE_WANGHONGTAO_20211230_
#define _STATE_MACHINE_CHARGE_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "protobuf_msg/sm_def.h"

class sm_charge
{
public:
	sm_charge(){};
	~sm_charge(){};

	static bool run_sm( protobuf_charge* p_protobuf_charge );

protected:
private:
	
};


#endif//_STATE_MACHINE_CHARGE_WANGHONGTAO_20211230_
