
#ifndef _XML_RPC_CLIENT_H_
#define _XML_RPC_CLIENT_H_

#include <vector>
#include <boost/serialization/singleton.hpp>
#include <boost/thread.hpp>

#include <RobotStruct.h>

#include "XmlRpc.h"


using namespace XmlRpc;

class protobuf_path;
class protobuf_bag;
class protobuf_bag_ex;

class xml_rpc_client
{
public:
	xml_rpc_client();
	~xml_rpc_client();

	void init(std::string ip, int port);
	void init_conn( std::string ip, int port );
	bool is_connected();

	bool get_dev_status( std::vector<SPubDevStatus> &v_dev_status );
	bool get_dev_status( SPubDevStatus &dev_status,int dev_id );
	bool get_file_list( std::vector<std::string> &v_file_list ,const std::string str_path, const std::string &filename = "*.*" );
	bool get_map(std::vector<int> &v_map_date, const std::string &map_nm);
	bool get_map_separate(std::vector<int> &v_map_date, const std::string &map_nm);
	int i_map_data_size_;

	bool set_map(const std::vector<int> v_map_date);
	bool do_set_onboard_map( const std::string str_map_name );
	bool set_est_pos(const SPos &pos,const bool &b_descrete = true);

	bool do_download_file(std::string pc_file,std::string arm_file);

	bool get_robot_pos(SPos &pos);
	bool get_robot_pos_hb(SPos &pos, int set_heartbeat , int set_sim_speed );//get robot pos with heart beat
	bool get_laser(std::vector<SLaser_used> &v_laser_data);
	bool get_ex_laser(std::vector<SLaser_used> &v_laser_data);
	bool get_ex_cab_laser(SLaserXYEx &laser_ex);
	bool get_sim_laser(SLaserXYEx &laser_sim);
	bool get_odom_speed(SOdomSpeed &odom);
	bool get_para(std::string &str_value ,const std::string &str_para);
	bool get_particles(std::vector<STriangle>& v_particles);

	bool do_begin_bag_mapping();
	bool do_end_bag_mapping();
	bool do_begin_gmapping();
	bool do_stop_gmapping();
	bool do_show_gmapping();
	bool do_save_gmapping(std::string file_nm);
	
	bool do_load_map(std::string map_nm);
	bool do_save_onboard_map( std::string map_nm );

	bool do_begin_log(std::string file_nm);
	bool do_end_log();
	bool do_play_back_log(std::string file_nm);
	bool do_end_play_back_log();
	bool do_continue_play_log();


	bool do_begin_log_ex(std::string file_nm);
	bool do_end_log_ex();

	bool do_cmd_speed(std::string speed_cmd);
	bool do_set_loop_clusure_cmd( std::string speed_cmd );
	bool do_get_process_bar( SProcess_Bar &pro_bar, const std::string &str_name );
	bool get_pub_bag(SPUB_BAG & pub_bag);
	bool get_pub_bag_ex(SPUB_BAG_EX & pub_bag_ex);
	bool get_pub_laser_ex_ref(SLaser_Ex_Ref &laser_ex_ref);
	bool set_seg_path(const std::vector<SOdomSpeed> &v_run_path);
	bool get_check_laser_range(const Range_type &range_type, SCHK_LASER_RANGE &chk_laser_range);
	bool get_chk_laser_show(std::vector<Range_type> &v_show_list);

	bool get_sim_path(std::vector<STriangle> &v_show_list);
	bool get_remote_file(const std::string &file_path, const std::string &new_file_path);
	bool get_scan_reflector(SReflector &ref);
	bool get_reflector_pos(SPOS_CONFIDENCE &pos_confi);
	bool get_loop_closure_pos(SLoopCLosurePos &cpos);
	bool get_amcl_entropy(SAMCL_ENTROPY &ae);
	bool get_amcl_confidence(SAMCL_CONFIDENCE &ac);
	bool get_view_data(std::vector<SView_Data> &v_data);

	bool get_battery(SBattery &bat);
	bool set_bt_contact(const int &bt_contact);


	bool get_special_loc_conpos( SPOS_CONFIDENCE &con_pos );
	bool get_special_landmark(SWorldLM &wlm);

	bool set_pause( bool b_pause );
	bool get_fork(SAct_Fork &fork_para);

	bool get_steering( std::vector<SSteering> &v_st);
	bool get_dio_bind(std::map<std::string, SDIO_NM_INDEX> &m_data);
	bool get_dio_data(std::vector<SDIO_NM_INDEX> &v_data);

	bool get_qr_code(SQrCode &qr_code);

private:

	XmlRpcClient* client_;

	protobuf_path* pub_path_;
	protobuf_bag* protobuf_bag_;
	protobuf_bag_ex* protobuf_bag_ex_;

	//sim agv
public:
	bool set_sim_init_pos(const SPos &pos);

	boost::mutex mu_rpc_;
	bool execute(const char* method, XmlRpcValue const& params, XmlRpcValue& result);
};


typedef boost::serialization::singleton<xml_rpc_client> Singleton_XML_Client;
#define DATASERVER_XML_CLIENT Singleton_XML_Client::get_mutable_instance() 
#endif // _XML_RPC_CLIENT_H_
