#ifndef _LOOP_CLOSURE_INTERFACE_KYOSHO_20200802_
#define _LOOP_CLOSURE_INTERFACE_KYOSHO_20200802_

#include "robot/RobotStruct.h"
#include "laser_filter/laser_filter.h"

#include "loop_closure/2dlaser_loop_closure.h"

class GridMap;

class loop_closure_interface
{
public:
	loop_closure_interface();
	~loop_closure_interface();

	void init();
	void init_shared_pool();
	void destroy();

	bool call_cmd( const SCmd& cmd );
	bool call_laser(SLaser used_laser);
	void pub_monitor_status( U8 status, U16 err_code);
	
	void spin();

protected:
private:
	
	void init_thread();
	void end_thread();

	void th_run();
	boost::thread* lc_th_;

	bool b_run_;
	laser2d_loop_closure* p_loop_closure_;
	CSBuffer<SLaser, 1> laser_buff_;
	THSafe<LC_State> g_lcs_;
	std::string gstr_load_file_;

	F32 laser_dx_ ;
	F32 laser_dy_ ;
	std::string map_path_;

	/////sim laser ref
private:
	F32 cal_laser_match( const SLaser &laser_data , const SPos &pos );
	
	laser_filter l_filter_;
	SimLaser_tf laser_tf_[LASER_COUNT];
	SLaser laser_sim_;
	bool b_first_laser_para_;
	F32 max_score_;
	GridMap* p_amcl_map_;
	std::string str_shape_;
	SPUB_BAG pub_bag_;

private:
	int i_show_particles_;
	void conver_laserRead2pubBag( SPUB_BAG &pub_bag , std::vector<SMatch_res> &v_res);
};

#endif//_LOOP_CLOSURE_INTERFACE_KYOSHO_20200802_
