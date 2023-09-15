#ifndef _PROTOBUF_PRODUCER_WANGHONGTAO_20211230_
#define _PROTOBUF_PRODUCER_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "meta_data/meta_data.h"
#include "protobuf_msg/producer.pb.h"

#include "protobuf_msg/protobuf_base.h"

class GridMap;

class protobuf_producer : public protobuf_base {


public:

	protobuf_producer();
	~protobuf_producer();

public:


	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

private:

	void init();

	
	void create_schedule_data(std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data);

public:
	std::string get_data( std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data );
	bool update_data(std::string str_group, std::string str_name ,std::string str_data);

	KPS::s_producer proto_data_;

	int occupyed_node( std::vector<int> &v_res );
	
	//state machine used
public:
	bool get_pallet_cargo(KPS::mp_pallet_cargo *p_pallet_cargo);
	bool enabled();
	bool check_on_schedule();
	void set_error( std::string str_error );

	//if auto create pallet , create pallet self
	bool auto_create_pallet();
	bool check_pallet_ready();
	

	void put_pallet(std::string str_uuid);

	void set_begin_produce();
	bool produce_cargo();
	void set_pallet(KPS::mp_pallet_cargo* p_pro_pallet_cargo, bool b_full = true);

	int put_get_pallet( int i_agv_id );

	bool get_pallet_over();

	bool b_pause_;
	bool b_continue_;

	bool wait_get();
	bool wait_put();

	

	std::string get_status();

	int i_pallet_state_;//0 empt 1 pallet on 2 full pallet

private:
	bool b_book_pt_;
	

	long long produce_begin_; 

	bool check_sche_date(std::string str_date);
	bool check_out_trigger();


private:
	int update_schedule(std::string str_group, std::string str_name ,std::string str_data);

	bool set_assign(int i_agv_id);

	
};

#endif//_PROTOBUF_PRODUCER_WANGHONGTAO_20211230_
