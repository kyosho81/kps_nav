#ifndef _PROTOBUF_PATH_WANGHONGTAO_20151230_
#define _PROTOBUF_PATH_WANGHONGTAO_20151230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"

#include "protobuf_msg/path.pb.h"


class protobuf_path{


public:

	protobuf_path();
	~protobuf_path();

	void set_name(const std::string str_nm);
	std::string get_name();
	void set_path( std::vector<SOdomSpeed> &v_list );
	int get_path( std::vector<SOdomSpeed> &v_list );

	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

	KPS::mp_path proto_path_;
	
};

#endif//_PROTOBUF_PATH_WANGHONGTAO_20151230_
