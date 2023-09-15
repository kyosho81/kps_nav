#ifndef _PROTOBUF_RANGE_WANGHONGTAO_20151230_
#define _PROTOBUF_RANGE_WANGHONGTAO_20151230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
#include "meta_data/meta_data.h"

#include "protobuf_msg/range.pb.h"

class GridMap;

class protobuf_range{


public:

	protobuf_range();
	~protobuf_range();


	void set_name(const std::string str_nm);
	std::string get_name();
	void set_range( std::vector<Sxy> &v_list );
	int get_range( std::vector<Sxy> &v_list );
	void set_start_pos(const SPos &pos);
	SPos get_start_pos();

	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

	KPS::mp_range proto_range_;
	int i_plan_type_;
	SPos start_pos_;

	std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	bool update_data(std::string str_group, std::string str_name ,std::string str_data);

public:
	static int max_id_;

};

#endif//_PROTOBUF_RANGE_WANGHONGTAO_20151230_
