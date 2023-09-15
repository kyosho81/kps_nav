#ifndef _PROTOBUF_EDGE_WANGHONGTAO_20191122_
#define _PROTOBUF_EDGE_WANGHONGTAO_20191122_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"

#include "protobuf_msg/edge.pb.h"
#include "protobuf_msg/protobuf_base.h"

class GridMap;

class protobuf_edge : public protobuf_base {


public:

	protobuf_edge();
	~protobuf_edge();

	void init();
	

	void set_nsrc_id(const int &nsrc_id);
	void set_ndst_id(const int &ndst_id);

	bool check_dir_ori(const int &src_id,const int &dst_id, U8 ori );

	int get_nsrc_id();
	int get_ndst_id();


	void set_forward(const DIRECTION &dir);
	void set_backward(const DIRECTION &dir);
	void set_leftshift(const DIRECTION &dir);
	void set_rightshift(const DIRECTION &dir);


	DIRECTION forward();
	DIRECTION backward();
	DIRECTION leftshift();
	DIRECTION rightshift();


	void set_forward_speed(const F32 &speed);
	void set_backward_speed(const F32 &speed);
	void set_leftshift_speed(const F32 &speed);
	void set_rightshift_speed(const F32 &speed);

	F32 forward_speed();
	F32 backward_speed();
	F32 leftshift_speed();
	F32 rightshift_speed();


	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

	KPS::mp_edge proto_data_;

public:

	std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	bool update_data(std::string str_group, std::string str_name ,std::string str_data);



};

#endif//_PROTOBUF_EDGE_WANGHONGTAO_20191122_
