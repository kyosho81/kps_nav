
//#include <cstdlib> //std::system
//#include <sstream>

// #include <iostream>
// #include <fstream>
#include <string>
#include <signal.h>



#include "Comm.h"
#include "TimerDiff.h"
#include "buffer_con.hpp"
#include "mapserver/map_def.h"


#include "interprocess_core/reg_msg.h"
//#include "interprocess_core/process.h"

#include "Comm/KHConfig.h"
#include "log/log_server.h"
#include "Comm/rpc_config_server.h"

bool brun = true;
bool gb_suro = false;

rpc_config_server rpc_cfg_svr;

void Reg_Data_Msg(){

	shared_pool::Reg_sh_map(SHARED_AMCL_MAP,GLOBAL_MAP_SIZE);
	shared_pool::Reg_sh_map(SHARED_GLOBAL_INF_MAP,GLOBAL_MAP_SIZE);
	shared_pool::Reg_sh_map(SHARED_LASER_INF_MAP,LOCAL_MAP_SIZE);
	shared_pool::Reg_sh_map(SHARED_GLOBAL_PROHIBIT_INF_MAP,GLOBAL_MAP_SIZE);

	shared_pool::Reg_sh_map(SHARED_PROHIBIT_MAP,GLOBAL_MAP_SIZE);

	shared_pool::Reg_msg("kps_localization","kps_data_server","odom",SOdomSpeed());
	shared_pool::Reg_msg("kps_localization","kps_data_server","laser",SLaser());
	shared_pool::Reg_msg("kps_localization","kps_data_server","particles",SparticlePub());
	shared_pool::Reg_msg("kps_localization","kps_data_server","amcl_pos",SPos());
	shared_pool::Reg_msg("kps_localization","kps_data_server","device_status",SPubDevStatus());
	shared_pool::Reg_msg("kps_localization","kps_data_server","laser_ex",SLaser_Ex());
	shared_pool::Reg_msg("kps_localization","kps_data_server","laser_ex_ref",SLaser_Ex_Ref());
	shared_pool::Reg_msg("kps_localization","kps_data_server","laser_ex_cab",SLaserXYEx());
	shared_pool::Reg_msg("kps_localization","kps_data_server","reflector_pos",SPOS_CONFIDENCE());


	shared_pool::Reg_msg("kps_localization","kps_health_examination","laser",SLaser());
	shared_pool::Reg_msg("kps_localization","kps_health_examination","amcl_pos",SPos());
	shared_pool::Reg_msg("kps_health_examination","kps_data_server","amcl_confidence",SAMCL_CONFIDENCE());
	
	shared_pool::Reg_msg("kps_data_server","kps_localization","set_estimate_pos",SInit_Pos());
	shared_pool::Reg_msg("kps_data_server","kps_localization","reflash_map",SReflash_map());
	shared_pool::Reg_msg("kps_data_server","kps_mapserver","mapping_cmd",SCmd());
	shared_pool::Reg_msg("kps_data_server","kps_localization","set_speed_cmd",SCmd());
	shared_pool::Reg_msg("kps_data_server","kps_localization","set_map_cmd",SCmd());

	shared_pool::Reg_msg("kps_localization","kps_mapserver","odom",SOdomSpeed());
	shared_pool::Reg_msg("kps_localization","kps_mapserver","laser",SLaser());

	shared_pool::Reg_msg("kps_mapserver","kps_data_server","log_cmd",SCmd());
	shared_pool::Reg_msg("kps_mapserver","kps_data_server","process_bar",SProcess_Bar());
	shared_pool::Reg_msg("kps_mapserver","kps_data_server","device_status",SPubDevStatus());
	
	shared_pool::Reg_msg("kps_data_server","kps_mapserver","process_bar",SProcess_Bar());
	shared_pool::Reg_msg("kps_data_server","kps_mapserver","pub_bag",SPUB_BAG());
	//movement
	shared_pool::Reg_msg("kps_localization","kps_ex_move_ment","laser",SLaser());
	shared_pool::Reg_msg("kps_localization","kps_ex_move_ment","amcl_pos",SPos());
	shared_pool::Reg_msg("kps_localization","kps_ex_move_ment","odom",SOdomSpeed());
	shared_pool::Reg_msg("kps_data_server","kps_ex_move_ment","set_path",SRunPath());
	shared_pool::Reg_msg("kps_data_server","kps_localization","setspeed",SSpeed());

	shared_pool::Reg_msg("kps_localization","kps_data_server","reflectors",SReflector());
	shared_pool::Reg_msg("kps_localization","kps_data_server","reflector_pos",SPos());
	shared_pool::Reg_msg("kps_localization","kps_data_server","amcl_confidence",SAMCL_CONFIDENCE());


	shared_pool::Reg_msg("kps_loopclosure","kps_data_server","process_bar",SProcess_Bar());
	shared_pool::Reg_msg("kps_loopclosure","kps_data_server","device_status",SPubDevStatus());
	shared_pool::Reg_msg("kps_loopclosure","kps_data_server","loop_closure",SLoopCLosurePos());
	//shared_pool::Reg_msg("kps_loopclosure","kps_data_server","lc_particles_bag",SPUB_BAG());

if(gb_suro){

	shared_pool::Reg_msg("suro_localization","kps_data_server","amcl_pos",SPos());
	shared_pool::Reg_msg("suro_localization","suro_dynamic_nav","amcl_pos",SPos());
	shared_pool::Reg_msg("suro_localization","kps_data_server","laser",SLaser());
	shared_pool::Reg_msg("suro_localization","kps_data_server","odom",SOdomSpeed());
	shared_pool::Reg_msg("suro_localization","kps_data_server","amcl_entropy",SAMCL_ENTROPY());

	//kps_loopclosure ref
	shared_pool::Reg_msg("suro_localization","kps_loopclosure","laser",SLaser());
	shared_pool::Reg_msg("suro_localization","kps_loopclosure","loop_closure_cmd",SCmd());
	shared_pool::Reg_msg("kps_loopclosure","suro_localization","loop_closure",SLoopCLosurePos());


	shared_pool::Reg_msg("suro_dynamic_nav","kps_data_server","setspeed",SSpeed());
	shared_pool::Reg_msg("suro_dynamic_nav","kps_data_server","laser",SLaser());
	shared_pool::Reg_msg("suro_dynamic_nav","kps_data_server","odom",SOdomSpeed());
	shared_pool::Reg_msg("suro_dynamic_nav","kps_data_server","run_status",Status());
	shared_pool::Reg_msg("suro_dynamic_nav","kps_data_server","particles",SparticlePub());

	shared_pool::Reg_msg("suro_dynamic_nav","kps_data_server","pub_laser_range",SCHK_LASER_RANGE());
	shared_pool::Reg_msg("suro_dynamic_nav","kps_data_server","pub_laser_range_show",Range_type());
	shared_pool::Reg_msg("suro_dynamic_nav","kps_data_server","run_status",Status());
	//can remove
	shared_pool::Reg_msg("kps_data_server","kps_loopclosure","loop_closure_cmd",SCmd());

	shared_pool::Reg_sh_pipe("suro_dynamic_nav","kps_data_server","sim_path");

	std::cout<<"---------------------suro trans monite data!"<<std::endl;
}else{
	shared_pool::Reg_msg("kps_localization","kps_data_server","amcl_entropy",SAMCL_ENTROPY());

	shared_pool::Reg_msg("kps_ex_move_ment","kps_data_server","particles",SparticlePub());
	shared_pool::Reg_msg("kps_ex_move_ment","kps_localization","setspeed",SSpeed());
	shared_pool::Reg_msg("kps_ex_move_ment","kps_data_server","pub_laser_range",SCHK_LASER_RANGE());
	shared_pool::Reg_msg("kps_ex_move_ment","kps_data_server","pub_laser_range_show",Range_type());
	shared_pool::Reg_msg("kps_ex_move_ment","kps_localization","pub_laser_range_show",Range_type());
	shared_pool::Reg_msg("kps_ex_move_ment","kps_data_server","run_status",Status());

	shared_pool::Reg_sh_pipe("kps_data_server","kps_ex_move_ment","seg_path");
	shared_pool::Reg_sh_pipe("kps_ex_move_ment","kps_data_server","sim_path");

	shared_pool::Reg_sh_pipe("kps_ex_move_ment","kps_data_server","global_path");
	shared_pool::Reg_sh_pipe("kps_localization","kps_data_server","shared_laser_inf_map");
	shared_pool::Reg_sh_pipe("kps_localization","kps_data_server","local_path");


	//kps_loopclosure ref
	shared_pool::Reg_msg("kps_localization","kps_loopclosure","laser",SLaser());
	shared_pool::Reg_msg("kps_data_server","kps_loopclosure","loop_closure_cmd",SCmd());



}
	//laser inf
//	shared_pool::Reg_msg("kps_localization","kps_map_laser_inf","laser",SLaser());
//	shared_pool::Reg_msg("kps_localization","kps_map_laser_inf","amcl_pos",SPos());

	



}

void shutdown(int sig)
{

	std::cout<<"shutdown child process"<<std::endl;

	sclose cl;
	cl.over = 1;
	shared_pool::Publish(shared_pool::name(),"shutdown",cl);


	SLEEP(1000);
	std::cout<<"core shutdown all over!!!"<<std::endl;
	shared_pool::destructor();

	brun = false;
	TCP_LOG_SERVER.destruct();
	
	
	return;
}





int main(int argc, char *argv[])
{

	shared_pool::init(argv);

	::signal(SIGINT, shutdown);

	if(argc > 1){
		gb_suro = true;
	}

	Reg_Data_Msg();

#if KH_CONFIG
	rpc_cfg_svr.init();
#else
	KHConfig kh_cfg_;
#endif

	shared_pool::reg_close_msg();
	shared_pool::save_msg("reg_msg.txt");
	shared_pool::save_sh("reg_sh.txt");
	shared_pool::save_lock("reg_lock.txt");
	shared_pool::save_pipe("reg_pipe.txt");

	TCP_LOG_SERVER.init_listen();

	SLEEP(100);

	while(brun){

		TCP_LOG_SERVER.run_once();

	}
	
	std::cout<<"core main thread destruct!"<<std::endl;

	

	shared_pool::destructor();
#if KH_CONFIG
	rpc_cfg_svr.destruct();
#endif

	return 0;
}
