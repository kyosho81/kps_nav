#ifndef _DATA_SERVER_WANGHONGTAO_2015_12_10_
#define _DATA_SERVER_WANGHONGTAO_2015_12_10_

#include <string>
#include <boost/thread/mutex.hpp>
#include <boost/serialization/singleton.hpp>

#include "RobotStruct.h"
#include "Comm/buffer_con.hpp"

#include "global_path.h"
#include "local_map.h"
#include "Comm/file.h"
#include "protobuf_msg/protobuf_bag.h"
#include "protobuf_msg/protobuf_bag_ex.h"

class data_server
{
public:
	data_server();
	~data_server();

	void init( bool b_sim );
	
	void init_subcribe();
	void init_subcribe_play_back();
	void init_pipe();

	void get_all_ms();

	bool set_estimate_pos(const double &x,const double &y ,const double &th ,const double& para1,const double& para2,const double& para3,const double& para4);
	void set_target_pos(const double &x,const double &y ,const double &th );
	void set_sim_pos(const double &x,const double &y ,const double &th );
	void set_stop(const double &x,const double &y ,const double &th );
	void set_mapping_cmd(const std::string cmd);
	void set_map_cmd(const std::string str_cmd); //load map will set to SHARED_AMCL_MAP
	void set_map_lock(const bool &block);
	void set_map_fill(const int &value);
	void set_map_value(const int &gx,const int &gy,const int &value);
	void set_map_reflash();
	void set_amcl_run(const bool &run);
	void set_onboard_map(const std::string str_local_map);
	int set_log_cmd(const std::string str_cmd);
	int set_log_ex_cmd(const std::string str_cmd);
	void set_speed_cmd(const std::string str_cmd);
	void set_loop_clousure_cmd( const std::string str_cmd );

	void get_Laser_data(std::vector<double> &v_dist);
	void get_Used_Laser_data(std::vector<double> &v_dist,std::vector<double> &v_angle);
	void get_Ex_Laser_data(std::vector<double> &v_dist,std::vector<double> &v_angle);
	void get_Excab_Laser_data(std::vector<double> &v_x,std::vector<double> &v_y);
	void get_Sim_Laser_data(std::vector<double> &v_x,std::vector<double> &v_y);
	void get_robot_pos(double &x,double &y,double &th);
	void get_robot_odom(double &x,double &y,double &th,double &vx,double &vy,double &vw);

	void get_particles(std::vector<SparticleFAW> &v_particle);
	//bool upload_bag( SPUB_BAG &p_bag, const std::string file_path);

	void get_local_show(LocalShow& local_show);
	std::string get_para( const std::string name );
	void get_dev_status( std::map<int,SPubDevStatus> &dev_status);
	void get_dev_status( SPubDevStatus &dev_status , int dev_id);
	void get_file_list( std::vector<std::string> &v_str_name , const std::string str_path, const std::string &filename);
	int get_map(std::vector<int> &v_data, const std::string &str_map);
	int get_map(std::vector<int> &v_data, std::string str_cmd, const std::string &str_map);
	std::vector<int> v_map_data_;
	int i_map_data_index_;

	void pub_process_bar(const SProcess_Bar &pro_bar);
	void get_process_bar(SProcess_Bar &pro_bar);
	bool pub_bag( const SPUB_BAG &pro_bag );
	bool pub_bag_lc( const SPUB_BAG &pro_bag );
	bool get_bag(char* &data,int &len);
	void pub_ex_bag( const SPUB_BAG_EX &pro_bag );
	bool get_ex_bag(char* &data,int &len);
	
	bool get_laser_ex_ref(char* &data,int &len);
	void set_path(std::string str_path,std::vector<SOdomSpeed> path);
	void set_seg_path(char* data,int len);

	void test_set_laser(const std::vector<double> &v_dist);
	void test_set_amcl_pos(const double &x,const double &y ,const double &th);

	bool get_check_laser_range(const Range_type &range_type, char* &data,int &ilen);
	int get_check_laser_range_show(std::vector<int> &show_list);
	int get_remote_file(char* p_data, int &ilen , std::string str_cmd);
	void get_reflector(SReflector &ref);
	//bool get_reflector_pos(SPos &pos);
	bool get_ref_pos(SPOS_CONFIDENCE &pos_confi);
	bool get_loop_closure_pos(SLoopCLosurePos &c_pos);
	bool get_amcl_entropy(SAMCL_ENTROPY &amcl_entropy);
	bool get_amcl_confidence(SAMCL_CONFIDENCE &amcl_confidence);
	
	bool get_battery(SBattery &bt);
	bool set_bt_contact(const int &bt_contact);

	bool get_special_loc_conpos(SPOS_CONFIDENCE &conpos);
	bool get_special_landmark(SWorldLM &wlm);
	bool set_heart_beat(const SHeartBeat &hb);

	bool get_fork(SAct_Fork &fork_para);
	bool get_steering( std::vector<SSteering> &v_st );

	bool get_dio_bind( std::map<std::string, SDIO_NM_INDEX> &m_fnc_bind );
	bool get_dio_data( std::vector<SDIO_NM_INDEX> &v_data );

	bool download_file(std::string str_cmd,std::string str_file = "");
	bool download_file(char* p_data, int ilen);
	file download_file_;

	global_path global_path_;
	local_map laser_inf_map_;
	local_map path_map_;
	local_map goal_map_;

	local_map sim_path_;

	//sim agv
	bool set_sim_init_pos(const SPos init_pos );
	bool set_pause( int i_pause );


	bool get_qr_code(SQrCode &qr_code);

protected:
	
private:

	bool updata_laser(const SLaser &laser_data);
	bool updata_used_laser(const SLaser &used_laser_data);
	bool updata_laser_ex_ref(const SLaser_Ex_Ref &laser_ex_ref);
	bool updata_laser_ex_cab(const SLaserXYEx &laser_ex_cab);
	bool updata_sim_laser(const SLaserXYEx &sim_laser_data);
	bool update_odom(const SOdomSpeed &odomspeed);
	bool update_amcl_pos(const SPos &amcl_pos);

	bool update_particle(const SparticlePub &pub);
	bool update_local_show(const LocalShow &local_show);
	bool update_dev_status(const SPubDevStatus &dev_status);
	//void update_all_status(const SPubStatus &status);
	bool update_log_cmd(const SCmd &scmd);
	bool update_pro_bar(const SProcess_Bar &pro_bar);
	bool update_chk_laser_range(const SCHK_LASER_RANGE &chk_laser_range);
	bool update_laser_range_show(const Range_type &range_type);
	bool update_reflector(const SReflector &ref);
	//void update_reflector_pos(const SPos &ref_pos);
	bool updata_laser_ex(const SLaser_Ex &laser_ex);
	bool updata_loop_closure(const SLoopCLosurePos &c_pos);
	bool updata_amcl_entropy(const SAMCL_ENTROPY &amcl_entropy);
	bool updata_amcl_confidence(const SAMCL_CONFIDENCE &amcl_confidence);
	bool check_init_pos(const SPos &pos);
	bool updata_ref_pos( const SPOS_CONFIDENCE &confidence_pos );
	bool updata_battery(const SBattery &bt);
	bool updata_special_loc(const SPOS_CONFIDENCE &confidence_pos);
	bool updata_special_landmark(const SWorldLM &wlm);
	bool update_pipe_log(std::string name,U8* data,U32 len);

// 	bool update_bt_contactor_in(const int& bt_contact);
// 	bool update_bt_contactor_out(const int& bt_contact);
	bool update_steering(const SSteering& st);
	bool update_di_ai( const SDIAI &di_ai );
	bool update_do_ao( const SDOAO &do_ao );
	bool update_sdi( const SDI &sdi );
	bool update_sdo( const SDO &sdo );
	bool update_mv_status( const SRunStatus &sta );
	bool update_qr_code( const SQrCode &qr_code );
	bool update_priority_speed( const SDynamic_Speed &speed );

	boost::mutex laser_mu_;
	SLaser laser_data_;
	SLaser used_laser_data_;

	boost::mutex odom_mu_;
	SOdomSpeed odomspeed_;

	boost::mutex amcl_mu_;
	SPos amcl_pos_;
	SAMCL_RES res_;

	SparticlePub pub_;

	boost::mutex local_mu_;
	LocalShow local_show_;

	boost::mutex dev_status_mu_;
	std::map<int,SPubDevStatus> m_dev_status_;

// 	boost::mutex all_status_mu_;
// 	std::map<int,SPubStatus> m_all_status_;
	
	boost::mutex log_mu_;
	boost::mutex log_ex_mu_;

	THSafe<SProcess_Bar> th_process_bar_;

	SBuffer<SPUB_BAG> pub_bag_list_;
	SBuffer<SPUB_BAG_EX> pub_bag_ex_list_;
	//SBuffer<SCHK_LASER_RANGE> pub_chk_laser_range_;
	SBuffer<Range_type> pub_range_type_show_;
	
	boost::mutex mu_pub_ch_laser_range_;
	std::map<Range_type,SCHK_LASER_RANGE> m_pub_chk_laser_range_;

	THSafe<SReflector> pub_ref_;
	//CSBuffer<SPos,10> pub_reflector_pos_;

	CSBuffer<SLoopCLosurePos,1> pub_loop_closure_;
	CSBuffer<SAMCL_ENTROPY,1> pub_amcl_entropy_;
	CSBuffer<SAMCL_CONFIDENCE,1> pub_amcl_confidence_;
	CSBuffer<SPOS_CONFIDENCE,1> pub_ref_confidence_;
	CSBuffer<SBattery,1> battery_;

	CSBuffer<SLaserXYEx,1> pub_laser_ex_cab_;
	CSBuffer<SLaserXYEx,1> pub_laser_sim_;

	CSBuffer<SPOS_CONFIDENCE,1> pub_special_loc_con_pos_;
	CSBuffer<SWorldLM ,1> pub_special_loc_wlm_;

	THSafe<int> ths_contactor_in_;
	THSafe<int> ths_contactor_out_;

	file file_;

	protobuf_bag protobuf_bag_;
	protobuf_bag_ex protobuf_bag_ex_;

	boost::mutex mu_steering_;
	std::map<int,SSteering> m_steering_;

	SBuffer<SQrCode> thb_qr_code_;
	
	boost::mutex mu_priority_speed_;
	std::map<U8,SDynamic_Speed> m_priority_speed_;
	//simulation agv
private:
	bool b_sim_;

	void init_sim_sub_msg();

	bool s_robot_pos( const SPos &pos );
	int sub_id_sim_robot_pos_;
	int sub_id_odom_;

	bool s_fork_task( const SAct_Fork &fork_task );
	int sub_id_fork_task_;
	THSafe<SAct_Fork> th_act_fork_;

	bool s_fork_data( const SAct_Fork_DATA &fork_data );
	int sub_id_fork_data_;
	CSBuffer<SAct_Fork_DATA,1> pub_fork_data_;
};

typedef boost::serialization::singleton<data_server> Singleton_Data_Server;

#endif//_DATA_SERVER_WANGHONGTAO_2015_12_10_
