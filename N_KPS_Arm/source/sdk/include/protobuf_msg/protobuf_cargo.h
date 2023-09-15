#ifndef _PROTOBUF_CARGO_WANGHONGTAO_20211230_
#define _PROTOBUF_CARGO_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
#include "meta_data/meta_data.h"

#include "protobuf_msg/protobuf_base.h"

#include "protobuf_msg/cargo.pb.h"


class protobuf_cargo : public protobuf_base {


public:

	protobuf_cargo();
	~protobuf_cargo();

	//void set_uuid();
	void update_cmd(std::string str_cmd);


public:


	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

private:

	void init();

	
public:

	std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	
	KPS::mp_cargo proto_data_;
};

#endif//_PROTOBUF_CARGO_WANGHONGTAO_20211230_
