#ifndef _PROTOBUF_ACTION_BASE_WANGHONGTAO_20220306_
#define _PROTOBUF_ACTION_BASE_WANGHONGTAO_20220306_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "meta_data/meta_data.h"
#include "protobuf_msg/action.pb.h"

#include "protobuf_msg/protobuf_base.h"


class protobuf_action_base : public protobuf_base {


public:

	protobuf_action_base();
	~protobuf_action_base();

public:


	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

private:

	void init();

	
public:
	std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	bool update_data(std::string str_group, std::string str_name ,std::string str_data);

	KPS::s_action proto_data_;

	//state machine used
public:


};

#endif//_PROTOBUF_ACTION_BASE_WANGHONGTAO_20220306_
