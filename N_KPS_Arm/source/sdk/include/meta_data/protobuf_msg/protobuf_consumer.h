#ifndef _PROTOBUF_CONSUMER_WANGHONGTAO_20211230_
#define _PROTOBUF_CONSUMER_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "meta_data/meta_data.h"
#include "protobuf_msg/consumer.pb.h"

#include "protobuf_msg/protobuf_base.h"

class GridMap;

class protobuf_consumer : public protobuf_base {


public:

	protobuf_consumer();
	~protobuf_consumer();

public:


	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

private:

	void init();

	
	void create_schedule_data(std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data);

public:
	std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	bool update_data(std::string str_group, std::string str_name ,std::string str_data);

	KPS::s_consumer proto_data_;

	int occupyed_node(std::vector<int> &v_res);

	//state machine used
public:


	bool enabled();
	bool check_on_schedule();

	void set_error( std::string str_error );
	
	void put_pallet(std::string str_uuid);
	int pallet_empty();

	void set_begin_consume();
	bool consume_cargo();
	void set_pallet(KPS::mp_pallet_cargo* p_pro_pallet_cargo);



	bool auto_destruct_pallet();
	void destruct_pallet();


	bool agv_get_pallet();
	bool get_pallet_over();

	bool agv_task_cancel();
	void set_agv_task_cencel(bool b_cancel);
	
	bool b_pause_;
	bool b_continue_;


	bool wait_put();
	bool wait_get();

	int put_get_pallet( int i_agv_id );

	std::string get_status();

	

private:
	

	bool b_cancel_book_;

	long long consume_begin_; 

	bool check_sche_date(std::string str_date);
	bool check_out_trigger();


private:
	int update_schedule(std::string str_group, std::string str_name ,std::string str_data);

	bool set_assign(int i_agv_id);
};

#endif//_PROTOBUF_CONSUMER_WANGHONGTAO_20211230_
