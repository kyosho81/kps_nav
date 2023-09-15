#ifndef _PROTOBUF_REFLECTOR_WANGHONGTAO_20191122_
#define _PROTOBUF_REFLECTOR_WANGHONGTAO_20191122_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"

#include "protobuf_msg/reflector.pb.h"

class GridMap;

class protobuf_reflector{


public:

	protobuf_reflector();
	~protobuf_reflector();

	void set_id();
	void set_id(const int &id);
	int get_id();
	void set_pos(const F32 &x,const F32 &y);
	void get_pos(F32 &x, F32 &y);
	void get_pos(SVec &vp);
	void set_lab_id(const int &lab_id);
	int get_lab_id();

	void set_ref_list(const std::vector<std::pair<int,F32>> &ref_list);
	void set_ref(const int &ref_id, const F32 &dis);
	int get_ref(std::vector<std::pair<int,F32>> &ref_list);


	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

	KPS::mp_refector proto_reflector_;

public:

	std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	bool update_data(std::string str_group, std::string str_name ,std::string str_data);

private:
	static int max_id_;

};

#endif//_PROTOBUF_REFLECTOR_WANGHONGTAO_20191122_
