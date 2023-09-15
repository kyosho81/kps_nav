#ifndef _PROTOBUF_CHK_LASER_WANGHONGTAO_20190710_
#define _PROTOBUF_CHK_LASER_WANGHONGTAO_20190710_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"

#include "protobuf_msg/laser.pb.h"


#define PROTOBUF_2_3 1

class protobuf_chk_laser{


public:

	protobuf_chk_laser();
	~protobuf_chk_laser();
	
	static void init();

	static void set_chk_laser( const Range_type &type, const SLaser &laser_data);
	static void get_chk_laser( Range_type &type, SLaser &laser_data);

	static bool proto2byte(char* &data,int &len);
	static bool byte2proto(char* const data,const int len);

	static KPS::mp_chk_laser_range chk_laser_range_;
#ifdef PROTOBUF_2_3
	static KPS::mp_laser_para* p_laser_para_;
	static KPS::mp_laser_data* p_laser_data_;
#else
	static KPS::mp_laser_para laser_para_;
	static KPS::mp_laser_data laser_data_;
#endif

public:

	static bool bfirst_;
};

#endif//_PROTOBUF_CHK_LASER_WANGHONGTAO_20190710_
