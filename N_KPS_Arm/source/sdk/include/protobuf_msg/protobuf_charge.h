#ifndef _PROTOBUF_CHARGE_WANGHONGTAO_20211230_
#define _PROTOBUF_CHARGE_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
#include "TimerDiff.h"
//#include "mapserver/GridMap.h"
#include "meta_data/meta_data.h"
#include "protobuf_msg/station.pb.h"

#include "protobuf_msg/charge.pb.h"

#include "protobuf_msg/protobuf_base.h"
#include "protobuf_msg/sm_def.h"

class GridMap;

class protobuf_charge : public protobuf_station {


public:

	protobuf_charge();
	~protobuf_charge();

	sm_def::CH_STA state_;

	bool enabled();

	bool is_charge_station();
	bool is_charge_action();
	bool is_free();
	bool is_assigned();
	bool is_occupy();
	bool free_for_charge();
	int on_charging();

	bool set_assign( int i_agv_id );
	int set_occupy(int i_agv_id);
	bool set_free(int i_agv_id);
	int set_charge(int i_agv_id);
// 	bool set_charge_over();
// 	bool set_pack_over();
	void set_error( std::string str_error );

	bool check_pos_ok(F32 dm , F32 dth);
	int check_charge_begin();
	int check_charge_over();
	int check_full();

	std::string str_error_msg_;

	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

	std::string get_status();

	int occupyed_node(std::vector<int> &v_res);

	bool get_bt_state(SBattery &battery_state);
	bool get_robot_pos(SPos &pos);

private:

	void init();

	

	void get_sub_data(std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> &m_data);
	int update_sub_data(std::string str_group, std::string str_name ,std::string str_data);
	



	cTimerDiff dt_;
	int i_check_timeout_;

	KPS::s_charge s_charge_;
private:
	
	int i_error_;
	SBattery bt_state_;
};

#endif//_PROTOBUF_CHARGE_WANGHONGTAO_20211230_
