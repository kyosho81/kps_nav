#include <boost/thread.hpp>

#include "Comm.h"

#include "interface/rpc_bind.h"

rpc_bind::rpc_bind(){



}

rpc_bind::~rpc_bind(){


	SDelete(get_laser_);
	SDelete(get_used_laser_);
	SDelete(get_ex_laser_);
	SDelete(get_pub_laser_ex_cab_);
	SDelete(get_sim_laser_);
	SDelete(get_particle_);

	SDelete(set_extimate_pos_);
	SDelete(get_robot_pos_);
	SDelete(get_robot_pos_hb_);
	SDelete(get_robot_odom_);
	SDelete(get_para_);

	SDelete(set_target_pos_);
	SDelete(set_stop_);

	SDelete(get_global_path_);
	SDelete(get_local_map_);

	SDelete(get_local_show_);

	
	SDelete(get_status_);
	SDelete(get_laser_filter_);
	SDelete(get_dev_status_);
	SDelete(set_mapping_cmd_);
	SDelete(get_file_list_);
	SDelete(get_map_);
	SDelete(get_map_separate_);
	SDelete(set_map_cmd_);
	SDelete(set_map_);
	SDelete(set_log_cmd_);
	SDelete(set_log_ex_cmd_);
	SDelete(set_speed_cmd_);
	SDelete(set_loop_closure_cmd_);
	SDelete(get_process_bar_);
	SDelete(get_pub_bag_);
	SDelete(get_pub_bag_ex_);
	SDelete(get_pub_laser_ex_ref_);
	SDelete(set_path_);
	SDelete(set_seg_path_);
	SDelete(get_check_laser_range_);
	SDelete(get_chk_laser_show_);
	SDelete(get_sim_path_);
	SDelete(get_remote_file_);
	SDelete(set_onboard_map_);
	SDelete(get_scan_reflector_);
	SDelete(get_reflector_pos_);
	SDelete(get_loop_closure_);
	SDelete(get_amcl_entropy_);
	SDelete(get_amcl_confidence_);
	SDelete(do_download_file_);
	SDelete(get_view_data_);
	SDelete(get_battery_);
	SDelete(set_bt_contact_);
	SDelete(get_special_loc_conpos_);
	SDelete(get_special_landmark_);

	SDelete(set_sim_init_pos_);
	SDelete(set_pause_);
	SDelete(get_fork_);
	SDelete(get_steering_);
	SDelete(get_dio_bind_);
	SDelete(get_dio_data_);
	SDelete(get_qr_code_);

	SDelete(hello_);
}


void rpc_bind::init_s(){
	get_laser_ = new getLaser(&s_);
	get_used_laser_ = new getUsedLaser(&s_);
	get_ex_laser_ = new getExLaser(&s_);
	get_pub_laser_ex_cab_ = new get_pub_laser_ex_cab(&s_);
	get_sim_laser_ = new get_sim_laser(&s_);
	get_particle_ = new getParticles(&s_);

	set_extimate_pos_ = new setEstimate_pos(&s_);
	get_robot_pos_ = new get_robot_pos(&s_);
	get_robot_pos_hb_= new get_robot_pos_hb(&s_);
	get_robot_odom_ = new get_robot_odom(&s_);
	get_para_ = new get_para(&s_);
	set_sim_pos_ = new setSim_pos(&s_);

	set_target_pos_ = new setTarget_pos(&s_);
	set_stop_ = new setStop(&s_);

	get_global_path_ = new getGlobalPath(&s_);
	get_local_map_ = new getLocalMap(&s_);

	get_local_show_ = new getLocal_show(&s_);

	get_status_ = new getStatus(&s_);
	get_laser_filter_ = new getLaserfilter(&s_);
	get_dev_status_ = new getDevStatus(&s_);

	set_mapping_cmd_ = new setMappingCmd(&s_);
	get_file_list_ = new get_file_list(&s_);
	get_map_ = new get_map(&s_);
	get_map_separate_ = new get_map_separate(&s_);
	set_map_cmd_ = new set_map_cmd(&s_);
	set_map_ = new set_map(&s_);
	set_log_cmd_ = new set_log_cmd(&s_);
	set_log_ex_cmd_ = new set_log_ex_cmd(&s_);
	set_speed_cmd_ = new set_speed_cmd(&s_);
	set_loop_closure_cmd_ = new set_loop_closure_cmd(&s_);
	get_process_bar_ = new get_process_bar(&s_);
	get_pub_bag_ = new get_pub_bag(&s_);
	get_pub_bag_ex_ = new get_pub_bag_ex(&s_);
	get_pub_laser_ex_ref_ = new get_pub_laser_ex_ref(&s_);
	set_path_ = new set_path(&s_);
	set_seg_path_ = new set_seg_path(&s_);
	get_check_laser_range_ = new get_check_laser_range(&s_);
	get_chk_laser_show_ = new get_chk_laser_show(&s_);
	get_sim_path_ = new get_sim_path(&s_);
	get_remote_file_ = new get_remote_file(&s_);
	set_onboard_map_ = new set_onboard_map(&s_);
	get_scan_reflector_ = new get_scan_reflector(&s_);
	get_reflector_pos_ = new get_reflector_pos(&s_);
	get_loop_closure_ = new get_loop_closure(&s_);
	get_amcl_entropy_ = new get_amcl_entropy(&s_);
	get_amcl_confidence_ = new get_amcl_confidence(&s_);

	do_download_file_ = new do_download_file(&s_);
	get_view_data_ = new get_view_data(&s_);
	get_battery_ = new get_battery(&s_);
	set_bt_contact_ = new set_bt_contact(&s_);

	get_special_loc_conpos_ = new get_special_loc_conpos(&s_);
	get_special_landmark_ = new get_special_landmark(&s_);


	set_sim_init_pos_ = new set_sim_init_pos(&s_);
	set_pause_ = new set_pause(&s_);
	get_fork_  = new get_fork(&s_);
	get_steering_ = new get_steering(&s_);
	get_dio_bind_ = new get_dio_bind(&s_);
	get_dio_data_ = new get_dio_data(&s_);

	get_qr_code_ = new get_qr_code(&s_);

	hello_ = new Hello(&s_);

}
void rpc_bind::init(int port  ){

	init_s();

	//XmlRpc::setVerbosity(0);

	if (s_.bindAndListen(port))
	{
		// Enable introspection
		s_.enableIntrospection(true);
		// Wait for requests indefinitely
		boost::thread th(boost::bind(&rpc_bind::th_rpc_,this));
	}else{
		std::cout<<"xmlrpc init err !!!!port:"<<port<<std::endl;
		return;
	}

	

}

void rpc_bind::th_rpc_(void){

	std::cout<<"data server thread run!"<<std::endl;
	s_.work(-1.0);
	std::cout<<"data server thread end!"<<std::endl;
}

void rpc_bind::destruct()
{
	s_.close();
}
