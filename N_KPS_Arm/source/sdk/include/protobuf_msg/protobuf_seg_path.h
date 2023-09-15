#ifndef _PROTOBUF_SEG_PATH_WANGHONGTAO_20190710_
#define _PROTOBUF_SEG_PATH_WANGHONGTAO_20190710_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"

#include "protobuf_msg/seg_path.pb.h"

class protobuf_seg_path{


public:

	protobuf_seg_path();
	~protobuf_seg_path();


	void set_name(const std::string str_nm);
	std::string get_name();
	
	void set_seg_path( const std::vector<SOdomSpeed> &seg_data);
	void get_seg_path( std::vector<SPathData> &seg_path);

	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

	KPS::mp_seg_path seg_path_;


public:
	std::string str_nm_;

};

#endif//_PROTOBUF_SEG_PATH_WANGHONGTAO_20190710_
