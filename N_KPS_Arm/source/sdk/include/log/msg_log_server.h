#ifndef _KPS_ARM_KYOSHO_MSG_LOG_SERVER_SINGLETON_H_
#define _KPS_ARM_KYOSHO_MSG_LOG_SERVER_SINGLETON_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "robot/RobotStruct.h"
#include "buffer_con.hpp"
#include "Comm/pattern_thread.h"

#include "protobuf_msg/pos.pb.h"
#include "protobuf_msg/base.pb.h"
#include "protobuf_msg/laser_ex.pb.h"
#include "protobuf_msg/dev_status.pb.h"
#include "protobuf_msg/loc_confidence.pb.h"
#include "protobuf_msg/reflector.pb.h"
#include "protobuf_msg/conf_ref_pos.pb.h"
#include "protobuf_msg/dio.pb.h"

#include "log/log_pair.h"

class sqlite3;

class msg_log_server
{
public:

	msg_log_server();
	~msg_log_server();

	bool init();
	bool destruct();

	

// 	bool put_data( U64 time_stamp , const std::string &msg_name, const SPos& pos);
// 	bool put_data( U64 time_stamp , const std::string &msg_name, const SOdomSpeed &odom_pos);
	bool put_data( U64 time_stamp , const std::string &msg_name, const std::string &msg_type , char* const ch_msg, int ilen);
	bool put_laser_para( U64 time_stamp , char* const ch_msg, int ilen);
	bool put_log( U64 time_stamp , U8* const ch_msg, int ilen);

	bool get_save_db(std::string &db_name);

private:
	bool open_db();
	bool close_db();

	std::string get_db_name();
	std::string str_db_;
	std::string str_path_;
	sqlite3* db_;

	bool create_table(const std::string &table_name);


private:
	boost::mutex mu_msg_pair_;
	boost::circular_buffer<log_pair*> l_msg_pair_;

	pattern_thread pattern_thread_;
	bool th_run();

	bool b_record_;
	typedef enum{
		IDLE = 0,
		OPEN = 1,
		RECORD = 2,
		CLOSE = 3
	}MSG_LOG_Status;

	THSafe<MSG_LOG_Status> th_status_;
	
	

	bool check_db_size_save();
	bool save_one(log_pair* log);
	int get_rec(std::vector<log_pair*> &v_log);

	//sub log data
	void sub_log_msg();

	void sub_spos(const std::string &sub_msg_name);
	bool update_pos(const SPos &pos,boost::shared_ptr<KPS::s_pos> pk_pos,std::string sub_msg_name, char* ch_data);

	void sub_sodom_pos(const std::string &sub_msg_name);
	bool update_odomspeed(const SOdomSpeed &odom_pos,boost::shared_ptr<KPS::mp_odom_data> pk_odom_pos,std::string sub_msg_name, char* ch_data);

	void sub_laser(const std::string &sub_msg_name);
	bool update_laser(const SLaser &laser,boost::shared_ptr<KPS::mp_laser_ex_data> pk_laser,std::string sub_msg_name, char* ch_data);

	void sub_laser_ex(const std::string &sub_msg_name);
	bool update_laser_ex(const SLaser_Ex &laser_ex,boost::shared_ptr<KPS::mp_laser_ex_data> pk_laser,std::string sub_msg_name, char* ch_data);

	void sub_dev_status(const std::string &sub_msg_name);
	bool update_dev_status(const SPubDevStatus &dev_status,boost::shared_ptr<KPS::mp_dev_status> pk_dev_status,std::string sub_msg_name, char* ch_data);
	boost::mutex mu_dev_;

	void sub_amcl_conf(const std::string &sub_msg_name);
	bool update_amcl_conf(const SAMCL_CONFIDENCE &amcl_confidence,boost::shared_ptr<KPS::mp_loc_confidence> pk_loc_conf,std::string sub_msg_name, char* ch_data);
	bool updata_amcl_entropy(const SAMCL_ENTROPY &amcl_entropy);
	THSafe<SAMCL_ENTROPY> th_amcl_entropy_;

	void sub_reflector(const std::string &sub_msg_name);
	bool update_reflector(const SReflector &refs,boost::shared_ptr<KPS::mp_refs> pk_refs,std::string sub_msg_name, char* ch_data);

	void sub_reflector_pos(const std::string &sub_msg_name);
	bool update_reflector_pos(const SPOS_CONFIDENCE &confidence_pos,boost::shared_ptr<KPS::mp_conf_ref_pos> pk_ref_pos,std::string sub_msg_name, char* ch_data);

	bool call_view_data_pipe(std::string name,U8* data,U32 len);

	boost::shared_ptr<KPS::mp_laser_ex_para> pk_laser_ex_para_;

	bool b_laser_para_;
	void update_laser_para(const SLaser &laser);
	bool b_laser_ex_para_;
	void update_laser_ex_para(const SLaser_Ex &laser_ex);


	void sub_DIO(std::string str_sub_dev, std::string str_pub_dev);
	bool call_fnc_sdi(std::string str_dev, const SDI &sdi,boost::shared_ptr<KPS::mp_sdi> pk_dis,std::string sub_msg_name, char* ch_data);
	bool call_fnc_sdo(std::string str_dev, const SDO &sdo,boost::shared_ptr<KPS::mp_sdo> pk_dos,std::string sub_msg_name, char* ch_data);
	bool call_fnc_sfai(std::string str_dev, const SFAI &sfai,boost::shared_ptr<KPS::mp_sfai> pk_fais,std::string sub_msg_name, char* ch_data);
	bool call_fnc_sfao(std::string str_dev, const SFAO &sfao,boost::shared_ptr<KPS::mp_sfao> pk_faos,std::string sub_msg_name, char* ch_data);
	std::map<std::string,int> m_sub_dev_sdi_;
	std::map<std::string,int> m_sub_dev_sdo_;
	std::map<std::string,int> m_sub_dev_fai_;
	std::map<std::string,int> m_sub_dev_fao_;

	//pipe 
	bool update_pipe_log(std::string name,U8* data,U32 len);

	CBuffer<std::string> v_save_db_;

private:
	THSafe<int> th_save_cnt_;
	bool check_save_data();
	

};



typedef boost::serialization::singleton<msg_log_server> Singleton_Msg_Log;
#define MSG_LOG_SERVER Singleton_Msg_Log::get_mutable_instance()

#endif//_KPS_ARM_KYOSHO_MSG_LOG_SERVER_SINGLETON_H_
