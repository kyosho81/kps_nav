#ifndef _PROTOBUF_LOG_BAG_WANGHONGTAO_20200617_
#define _PROTOBUF_LOG_BAG_WANGHONGTAO_20200617_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"

#include "protobuf_msg/log_bag.pb.h"


class protobuf_log_bag{
	
public:
	protobuf_log_bag();
	~protobuf_log_bag();

	void init();
	void destruct();
	
	bool put_odom( const SOdomSpeed &odom);
	bool put_laser(const SLaser &laser);
	bool put_amcl(const SPos &amcl_pos );

	bool open_write_file(const std::string file_path);
	bool close_write_file();

	bool file_save();

	//proto
private:
	void init_proto();
	KPS::mb_log_bag log_bag_;




private://file

	
	bool open_read_file(const std::string file_path);
	bool close_read_file();
	


	boost::thread* bag_th_;
	bool b_run_;

	std::ifstream fis_;
	std::ofstream fos_;
	
	std::string str_file_path_;

	SLaser_para para_;
	U64 time_stamp_begin_;
	U64 time_stamp_end_;

	int i_max_file_size_;
};

typedef boost::serialization::singleton<protobuf_log_bag> Singleton_ProtoBuf_Log_Bag;

#endif//_PROTOBUF_LOG_BAG_WANGHONGTAO_20200617_
