#ifndef _DEVICE_AMCL_WANGHONGTAO_20180401_
#define _DEVICE_AMCL_WANGHONGTAO_20180401_


#include <string>
#include <map>
#include <boost/thread.hpp>

#include "Comm/TimerDiff.h"
#include "robot/lowpass_filter.h"

#include "pf/pf_simulation.h"

#include "device/device_base.h"

class GridMap;
class gn_scan_match;

class device_amcl : device_base
{
public:

	device_amcl();
	virtual ~device_amcl();

	bool reflash_map(const SReflash_map &ref);

protected:
	//void pub_laser(const SLaser &laser);

	virtual bool setPara( std::string name , std::string value );
	
	bool fnc_recovery();
	bool toErr(U16 err_code);


private:

	bool fnc_init();
	bool fnc_run() ;
	bool onInit();
	
	std::string get_map_name();
	void load_para();

	
	bool load_map( std::string path );
	//GridMap* amcl_map_;
	bool s_init_pos(const SInit_Pos &pos );

	THSafe<bool> th_run_stop_;

	pf_simulation pf_;

	void init_call_back();
	

	int sub_id_laser_;
	int sub_id_odom_;
	int sub_id_estimate_;
	int sub_id_laser_ex_cab_;
	int sub_id_amcl_confidence_;
	int sub_id_dynamic_loc_;

	bool b_pub_;
	void publish_pos(const SPos &pos);
	void publish_entropy( const SAMCL_ENTROPY &amcl_entropy);
	void publish_particle();
	bool get_pub_particle();
	SPos get_resample_center_pos();

	lowpass_filter lowpass_filter_;
	F32 amcl_entropy_health_;
	SAMCL_ENTROPY ae_;

	bool b_used_laser_cab_;
	bool b_gn_amcl_;

	//hyper location ,merge odom and amcl
	merge_tf location_tf_;
	bool b_merge_odom_;
	bool b_force_merge_;
	SBuffer<SPOS_CONFIDENCE> th_dy_confidence_pos_;
	THSafe<SAMCL_CONFIDENCE> th_amcl_confidence_;

	//call back when interprocess_chassis (20hz)
	THSafe<SOdomSpeed> th_odom_new_;
	void update_odom(const SOdomSpeed& new_odom);
	bool s_update_odom( const SOdomSpeed& new_odom );
	bool s_update_confidence(const SAMCL_CONFIDENCE &amcl_confidence);
	bool s_update_dy_pos( const SPOS_CONFIDENCE &confidence_pos );

private://global plan shared map
	GridMap* sh_shared_global_;
	F32 amcl_map_inf_;

protected:

	gn_scan_match* p_gn_;
};

#endif //_DEVICE_AMCL_WANGHONGTAO_20180401_
