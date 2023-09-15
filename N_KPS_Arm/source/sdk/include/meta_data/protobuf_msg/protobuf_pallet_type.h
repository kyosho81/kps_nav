#ifndef _PROTOBUF_PALLET_TYPE_WANGHONGTAO_20211230_
#define _PROTOBUF_PALLET_TYPE_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "meta_data/meta_data.h"

#include "protobuf_msg/protobuf_base.h"

#include "protobuf_msg/pallet_type.pb.h"

class GridMap;

class protobuf_pallet_type : public protobuf_base {


public:

	protobuf_pallet_type();
	~protobuf_pallet_type();

	void set_uuid();
	void update_cmd(std::string str_cmd);
	void get_proto_data(KPS::mp_pallet_type &p_data);

public:


	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

private:

	void init();

	
public:

	std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	
	KPS::mp_pallet_type proto_data_;
};

#endif//_PROTOBUF_PALLET_TYPE_WANGHONGTAO_20211230_
