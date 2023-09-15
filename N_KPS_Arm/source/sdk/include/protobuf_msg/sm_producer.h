#ifndef _STATE_MACHINE_PRODUCER_WANGHONGTAO_20211230_
#define _STATE_MACHINE_PRODUCER_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "protobuf_msg/sm_def.h"

class protobuf_producer;

class sm_producer
{
public:
	sm_producer(){};
	~sm_producer(){};

	static bool run_sm(protobuf_producer* p_proto_producer);

protected:
private:
	
};


#endif//_STATE_MACHINE_PRODUCER_WANGHONGTAO_20211230_
