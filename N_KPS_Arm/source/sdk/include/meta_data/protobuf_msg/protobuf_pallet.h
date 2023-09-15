#ifndef _PROTOBUF_PALLET_WANGHONGTAO_20211230_
#define _PROTOBUF_PALLET_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
#include "meta_data/meta_data.h"

#include "protobuf_msg/protobuf_base.h"

#include "protobuf_msg/pallet.pb.h"


class protobuf_pallet : public protobuf_base {


public:

	protobuf_pallet();
	~protobuf_pallet();

	//void set_uuid();
	void update_cmd(std::string str_cmd);
	void set_pallet_type_uuid(std::string str_uuid);
	void set_pallet_cargo(KPS::mp_pallet_cargo* p_pallet_cargo);
	void set_full(bool b_full);
	void set_empty(bool b_empty);
	bool is_full();
	int get_cargo_size();
	std::string get_cargo_uuid();

	bool consume_cargo();

public:


	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

private:

	void init();

	
public:

	std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	
	KPS::mp_pallet proto_data_;
};

#endif//_PROTOBUF_PALLET_WANGHONGTAO_20211230_
