#ifndef _KPS_ARM_KYOSHO_MSG_PLAY_BACK_SINGLETON_H_
#define _KPS_ARM_KYOSHO_MSG_PLAY_BACK_SINGLETON_H_

#include <fstream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "robot/RobotStruct.h"
#include "buffer_con.hpp"
#include "Comm/pattern_thread.h"
#include "Comm/TimerDiff.h"

#include "log/log_pair.h"

class sqlite3;

class msg_play_back
{
public:
	msg_play_back();
	~msg_play_back();

	bool init();

	bool play_db(const std::string &str_db);
	bool load_map(const std::string &str_map);
	bool load_cfg(const std::string &str_map);

	bool destruct();
	bool th_run();

private:
	pattern_thread pattern_thread_;
	THSafe<bool> th_pub_;

protected:
private:
	std::string str_path_;

	bool b_play_;

	bool open_db(const std::string &str_db);
	bool close_db();

	bool find_time_stamp_head();
	bool find_total_rows();
	bool pub_all();
	bool bind_pub_data(log_pair &log_p);
	U64 time_select_begin_;

	U64 time_stamp_first_;
	U64 time_diff_;

	U64 total_rows_;

	cTimerDiff dt_;
	F32 time_coefficient_;

	sqlite3* db_;

private:

	bool get_laser_ex_para();
	SLaser_para laser_para_;

private:
	
	MtBuffer< U64, boost::function<void (void)> > pub_func_list_;
	void pub_spos( std::string str_msg_nm, const SPos pos);
	void pub_sodom( std::string str_msg_nm, const SOdomSpeed odom);
	void pub_laser( std::string str_msg_nm, const SLaser laser);
	void pub_laser_ex( std::string str_msg_nm, const SLaser_Ex laser_ex);
	void pub_dev_status( std::string str_msg_nm, const SPubDevStatus dev_status);
	void pub_loc_conf( std::string str_msg_nm, const SAMCL_CONFIDENCE amcl_conf, const SAMCL_ENTROPY amcl_entropy);
	void pub_log(const std::string str_msg_nm, const std::string str_log);
	void pub_refs( std::string str_msg_nm, const SReflector refs);
	void pub_view_data( std::string str_msg_nm, U8* p_data,int ilen);
	void pub_ref_pos( std::string str_msg_nm, const SPOS_CONFIDENCE conf_ref_pos);
	void pub_sdi( std::string str_msg_nm, const SDI &sdi );
	void pub_sdo( std::string str_msg_nm, const SDO &sdo );
	void pub_fai( std::string str_msg_nm, const SFAI &sfai);
	void pub_fao( std::string str_msg_nm, const SFAO &sfao);
};


typedef boost::serialization::singleton<msg_play_back> Singleton_Msg_Play_Back;
#define MSG_PLAY_BACK Singleton_Msg_Play_Back::get_mutable_instance()

#endif//_KPS_ARM_KYOSHO_MSG_PLAY_BACK_SINGLETON_H_
