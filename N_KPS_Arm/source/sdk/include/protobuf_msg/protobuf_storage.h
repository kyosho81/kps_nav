#ifndef _PROTOBUF_STORAGE_WANGHONGTAO_20211230_
#define _PROTOBUF_STORAGE_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "meta_data/meta_data.h"
#include "protobuf_msg/storage.pb.h"
#include "protobuf_msg/sm_def.h"

#include "protobuf_msg/protobuf_base.h"

class GridMap;

class protobuf_storage : public protobuf_base {


public:

	protobuf_storage();
	~protobuf_storage();

public:


	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

private:

	void init();

	
	void create_schedule_data(std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data);

public:
	std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	bool update_data(std::string str_group, std::string str_name ,std::string str_data);


	KPS::s_storage proto_data_;

	int occupyed_node(std::vector<int> &v_res);

	//state machine used
public:


	bool enabled();
	bool check_on_schedule();

	void set_error( std::string str_error );
	
	bool is_empty();
	bool trigger_io();

	bool set_assign(int i_agv_id);

	int pallet_empty();


	bool agv_get_pallet(const int& agv_id);
	bool get_pallet_over();

	bool agv_task_cancel();
	void set_agv_task_cencel(bool b_cancel);
	
	bool b_pause_;
	bool b_continue_;


	bool wait_put();
	bool wait_get();

	bool put_get_pallet( int i_agv_id );

	std::string get_status();

	sm_def::ST_STA state_;

private:
	
	

	bool b_cancel_book_;


	bool check_sche_date(std::string str_date);
	bool check_out_trigger();


private:
	int update_schedule(std::string str_group, std::string str_name ,std::string str_data);

};

#endif//_PROTOBUF_STORAGE_WANGHONGTAO_20211230_
