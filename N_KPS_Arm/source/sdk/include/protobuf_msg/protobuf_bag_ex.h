#ifndef _PROTOBUF_BAG_EX_WANGHONGTAO_20151230_
#define _PROTOBUF_BAG_EX_WANGHONGTAO_20151230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
#include "protobuf_msg/bag_ex.pb.h"


typedef struct _SPROTOBUF_BAG_EX
{
	SOdomSpeed odom_;
	SLaser_Ex_Ref laser_ex_ref_;
	SPos amcl_pos_;

}SPROTOBUF_BAG_EX;


class protobuf_bag_ex{
	
public:
	protobuf_bag_ex();
	~protobuf_bag_ex();

	void init();
	void destruct();

	void put_odom( const SOdomSpeed &odom,const bool &force_input = false);
	void put_laser(const SLaser_Ex_Ref &laser_ex_ref);
	void put_reflector(const SReflector &ref);
	void put_laser(const SLaser_Ex &laser_ex);
	void get_laser(SLaser_Ex &laser_ex);
	bool get_laser(char* &data,int &len);
	void put_amcl(const SPos &amcl_pos );
	bool save_one(const SPROTOBUF_BAG_EX &bag_ex);

	bool begin_save_file(const std::string file_path);
	void stop_save_file();
	int begin_play_back(const std::string file_path);
	void stop_play_back();
	int continue_play();
	int continue_play_next();

	//bool upload_bag( SPUB_BAG &p_bag, const std::string file_path);

	//normal no thread
	bool init_normal_w(const std::string &file_path);
	bool save_one_normal(const SPROTOBUF_BAG_EX &bag);
	bool save_file_normal();

	bool init_normal_r();
	bool open_file_normal(const std::string &file_path);
	bool get_one_normal(SPUB_BAG_EX &pbag);
	void set_laser_para(const SLaser_para &para);
	void get_laser_para(SLaser_para &para);
	int get_total_size();

	SPubDevStatus get_pub_status();
	void bind_process_bar(boost::function<void(const SProcess_Bar &pro_bar)> fnc);
	void bind_pub_bag( boost::function<void(const SPUB_BAG_EX &pub_bag_ex)> fnc );
	void pub_process_bar(const std::string str_nm,const int &index, const int &imax);

	eBAG_STATUS get_estatus();
	std::string get_status();
private:
	static const int CNT_MAX_BAG_ = 500 ;
	CSBuffer<SPROTOBUF_BAG_EX,CNT_MAX_BAG_> bag_ex_buf_;

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
	
	bool get_one(SPUB_BAG_EX &pbag_ex);
	
	void clear_data();
	
	THSafe<SOdomSpeed> th_odom_;
	THSafe<SLaser_Ex_Ref> th_laser_ex_ref_;
	THSafe<SPos> th_amcl_pos_;
	bool begin_log_first_;

	boost::thread* bag_th_;
	bool b_run_;

	std::ifstream fis_;
	std::ofstream fos_;
///////////////////////////////
	KPS::mp_bag_ex probot_bag_ex_;
#ifdef PROTOBUF_2_3
	KPS::mp_laser_ex_para* p_laser_ex_para_;
	KPS::mp_laser_ex_data* p_laser_ex_data_;
	KPS::mp_laser_ref_data* p_reflector_data_;
	KPS::mp_pos_data* p_amcl_pos_;
	KPS::mp_odom_data* p_odom_;
#else
	KPS::mp_laser_ex_para laser_ex_para_;
	KPS::mp_laser_ex_data laser_ex_data_;
	KPS::mp_laser_ref_data reflector_data_;
	KPS::mp_pos_data amcl_pos_;
	KPS::mp_odom_data odom_;
#endif
//////////////////////////////////////////////////////////////////////////
	KPS::mp_bag_ex probot_laser_ex_ref_;
#ifdef PROTOBUF_2_3
	KPS::mp_laser_ex_para* lp_laser_ex_para_;
	KPS::mp_laser_ex_data* lp_laser_ex_data_;
	KPS::mp_laser_ref_data* lp_reflector_data_;
	KPS::mp_pos_data* lp_amcl_pos_;
	KPS::mp_odom_data* lp_odom_;
	bool b_para_filled_;
#endif
////////////////////////////////////
	std::string str_file_path_;
	int total_size_;
	int current_index_;
	int laser_beans_size_;
//state machine
	THSafe<eBAG_STATUS> bag_status_;
	
	

	boost::function<void(const SProcess_Bar &pro_bar)> fnc_probar;
	void pub_process_bar(SProcess_Bar &process_bar);

	boost::function<void(const SPUB_BAG_EX &pub_bag_ex)> fnc_pub_bag;
	void fpub_bag(SPUB_BAG_EX &pub_bag_ex);

public:
	bool buf2bag( SPUB_BAG_EX& pbag_ex, char* buf,int len );
	bool bag2buf( char* &buf,int &len,const SPUB_BAG_EX& bag_ex);

};

typedef boost::serialization::singleton<protobuf_bag_ex> Singleton_ProtoBuf_Bag_ex;

#endif//_PROTOBUF_BAG_EX_WANGHONGTAO_20151230_
