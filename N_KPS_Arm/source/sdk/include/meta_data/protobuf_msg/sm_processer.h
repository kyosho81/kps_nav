#ifndef _STATE_MACHINE_PROCESSER_WANGHONGTAO_20211230_
#define _STATE_MACHINE_PROCESSER_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "protobuf_msg/sm_def.h"

class sm_processer
{
public:
	sm_processer(){};
	~sm_processer(){};

	static bool run_sm(protobuf_processer* p_protobuf_processer);

protected:
private:
	
};


#endif//_STATE_MACHINE_PROCESSER_WANGHONGTAO_20211230_
