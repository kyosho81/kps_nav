#ifndef _STATE_MACHINE_FACTORY_WANGHONGTAO_20211230_
#define _STATE_MACHINE_FACTORY_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "protobuf_msg/sm_def.h"
#include "protobuf_msg/sm_producer.h"

#include "Comm/pattern_thread.h"

class protobuf_base;

class sm_factory
{
public:
	sm_factory(){};
	~sm_factory(){};

	void init();
	void destruct();
	
	bool run_sm(std::multimap< std::string, protobuf_base*> &mm_roles);

protected:
private:

	
	pattern_thread pt_sm_;

	
};
typedef boost::serialization::singleton<sm_factory> Singleton_SM_Factory;
#define SM_FACTORY Singleton_SM_Factory::get_mutable_instance()

#endif//_STATE_MACHINE_FACTORY_WANGHONGTAO_20211230_
