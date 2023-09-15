#ifndef _PROTOBUF_BAG_WANGHONGTAO_20151230_
#define _PROTOBUF_BAG_WANGHONGTAO_20151230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"

#include "protobuf_msg/bag.pb.h"

typedef struct _SPROTOBUF_BAG
{
	SOdomSpeed odom;
	SLaser laser;
	SPos amcl_pos;
	F32 confidence_;
}SPROTOBUF_BAG;



class protobuf_bag{
	
public:
	protobuf_bag();
	~protobuf_bag();

	void init();
	void destruct();
	//normal no thread
	bool init_normal(const std::string &file_path);
	bool save_one_normal(const SPROTOBUF_BAG &bag);
	bool save_file_normal();
	bool init_normal();
	//should init_normal() first
	bool open_file_normal(const std::string &file_path);
	bool get_one_normal(SPUB_BAG &pbag);
	void set_laser_para(const SLaser_para &para);
	void get_laser_para(SLaser_para &para);

	void put_odom( const SOdomSpeed &odom,const bool &force_input = false);
	void put_laser(const SLaser &laser);
	void put_amcl(const SPos &amcl_pos );

	bool begin_save_file(const std::string file_path);
	void stop_save_file();
	int begin_play_back(const std::string file_path);
	void stop_play_back();
	int continue_play();
	int continue_play_next();

	//bool upload_bag( SPUB_BAG &p_bag, const std::string file_path);

	SPubDevStatus get_pub_status();
	void bind_process_bar(boost::function<void(const SProcess_Bar &pro_bar)> fnc);
	void bind_pub_bag( boost::function<bool(const SPUB_BAG &pub_bag)> fnc );

	eBAG_STATUS get_estatus();
	std::string get_status();
private:
	static const int CNT_MAX_BAG_ = 500 ;
	CSBuffer<SPROTOBUF_BAG,CNT_MAX_BAG_> bag_buf_;

	static const int CNT_MAX_PLAY_ = 1 ;
	boost::mutex mu_max_play_back_;
	int max_play_back_;
	//thread
private:

	void init_thread();
	void end_thread();
	void th_run();
	bool open_write_file(const std::string file_path);
	bool close_write_file();
	bool open_read_file(const std::string file_path);
	bool close_read_file();
	bool save_one(const SPROTOBUF_BAG &bag);
	bool get_one(SPUB_BAG &pbag);
	
	void clear_data();
	
	THSafe<SOdomSpeed> th_odom_;
	THSafe<SLaser> th_laser_;
	THSafe<SPos> th_amcl_pos_;
	bool begin_log_first_;

	boost::thread* bag_th_;
	bool b_run_;

	std::ifstream fis_;
	std::ofstream fos_;
	KPS::mp_bag probot_bag_;
#ifdef PROTOBUF_2_3
	KPS::mp_laser_para* p_laser_para_;
	KPS::mp_laser_data* p_laser_data_;
	KPS::mp_pos* p_amcl_pos_;
	KPS::mp_odom* p_odom_;
#else
	KPS::mp_laser_para laser_para_;
	KPS::mp_laser_data laser_data_;
	KPS::mp_pos amcl_pos_;
	KPS::mp_odom odom_;
#endif
	std::string str_file_path_;
	int total_size_;
	int current_index_;
//state machine
	THSafe<eBAG_STATUS> bag_status_;
	
	

	boost::function<void(const SProcess_Bar &pro_bar)> fnc_probar;
	void pub_process_bar(SProcess_Bar &process_bar);

	boost::function<void(const SPUB_BAG &pub_bag)> fnc_pub_bag;
	void fpub_bag(SPUB_BAG &pub_bag);

	bool proto2buf( char* buf,int len,KPS::mp_bag &probot_bag );
	bool buf2proto( KPS::mp_bag &probot_bag , char* buf,int len );
public:
	bool buf2bag( SPUB_BAG& pbag,char* buf,int len );
	void bag2buf( char* &buf,int &len,const SPUB_BAG& bag );

};

typedef boost::serialization::singleton<protobuf_bag> Singleton_ProtoBuf_Bag;

#endif//_PROTOBUF_BAG_WANGHONGTAO_20151230_
