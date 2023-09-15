#ifndef _PROTOBUF_STATION_WANGHONGTAO_20211230_
#define _PROTOBUF_STATION_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "meta_data/meta_data.h"
#include "protobuf_msg/station.pb.h"

#include "protobuf_msg/station.pb.h"

#include "protobuf_msg/protobuf_base.h"
#include "protobuf_msg/sm_def.h"

class GridMap;

class protobuf_station : public protobuf_base {


public:

	protobuf_station();
	~protobuf_station();

public:


	virtual bool proto2byte(char* &data,int &len) = 0;
	virtual bool byte2proto(char* const data,const int len) = 0;

protected:

	void init(std::string str_type);
	
	
public:
	
	std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	bool update_data(std::string str_group, std::string str_name ,std::string str_data);

	KPS::s_station* proto_data_;



private:

	virtual void get_sub_data(std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data) = 0;
	virtual int update_sub_data(std::string str_group, std::string str_name ,std::string str_data) = 0;
};

#endif//_PROTOBUF_CONSUMER_WANGHONGTAO_20211230_
