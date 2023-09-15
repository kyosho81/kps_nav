#ifndef _PROTOBUF_NODE_WANGHONGTAO_20191122_
#define _PROTOBUF_NODE_WANGHONGTAO_20191122_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "meta_data/meta_data.h"

#include "protobuf_msg/node.pb.h"
#include "protobuf_msg/protobuf_base.h"

class GridMap;

class protobuf_node : public protobuf_base {


public:

	protobuf_node();
	~protobuf_node();

	void init();

	//void set_ref_node(const std::vector<int> &v_ref_node_id);
	void set_ref_edge(const std::vector<int> &v_ref_edge_id);

	//int get_ref_node(std::vector<int> &v_ref_node_id);
	int get_ref_edge(std::vector<int> &v_ref_edge_id);

	bool add_ref_edge(const int &ref_edge_id);
	bool remove_ref_edge(const int &ref_edge_id);

	void set_lab(const std::string str_lab);

	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

	KPS::mp_node proto_data_;

public:
	std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	bool update_data(std::string str_group, std::string str_name ,std::string str_data);

};

#endif//_PROTOBUF_NODE_WANGHONGTAO_20191122_
