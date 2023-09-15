#ifndef _DEVICE_R2000_WANGHONGTAO_20191024_
#define _DEVICE_R2000_WANGHONGTAO_20191024_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include "sensor/laser_filter/laser_filter_ex.h"
#include "device/device_laser.h"

#include "sensor/R2000/r2000_driver.h"

class device_r2000 : protected device_laser
{
public:

	device_r2000();
	~device_r2000();

protected:

	bool setPara( std::string name , std::string value );

	
	bool fnc_run();

	bool fnc_recovery();

	bool fnc_to_err();

private:

	bool onInit();
	bool toErr(U16 err_code);

	
private:
	void init_filter();
	void fill_pub_data();
	void pub_laser_ex(SLaser_Ex &laser_ex);
	void pub_ref(SReflector &laser_ref);
	void pub_laser_ex_ref(SLaser_Ex_Ref &laser_ex_ref);

	pepperl_fuchs::R2000Driver* driver_;

	int i_8400_7200_720_;
	bool b_pub_laser_ex_;
	bool b_pub_ref_;
	bool b_pub_amcl_ref_;
	bool b_pub_laser_ex_ref_;

	int scan_frequency_ ;
	int samples_per_scan_ ;

	//SLaser_Ex laser_ex_;
	SReflector laser_ref_;
	SLaser_Ex_Ref laser_ex_ref_;

	laser_filter_ex filter_;
	//SLaser_Ex filter_min_range_;
	void filter_para_reset();
	F32 laser_amcl_resolution_;
	int laser_start_index_;
	int laser_step_;
};

#endif//_DEVICE_R2000_WANGHONGTAO_20191024_