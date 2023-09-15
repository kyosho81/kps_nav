#ifndef _PROTOBUF_MAP_WANGHONGTAO_20151230_
#define _PROTOBUF_MAP_WANGHONGTAO_20151230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"

#include "protobuf_msg/map.pb.h"

class GridMap;

class protobuf_map{


public:

	protobuf_map();
	~protobuf_map();

	bool set_map( const std::string &str_map_name , GridMap* g_map);
	//new grid map and return
	bool get_map(GridMap* &g_map);

	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

	KPS::mp_map proto_map_;

};

#endif//_PROTOBUF_MAP_WANGHONGTAO_20151230_
