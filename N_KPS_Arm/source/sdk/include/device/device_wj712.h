#ifndef _DEVICE_WJ712_WANGHONGTAO_20191024_
#define _DEVICE_WJ712_WANGHONGTAO_20191024_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include "sensor/laser_filter/laser_filter_ex.h"
#include "device/device_laser.h"


#include "sensor/wj712/wj712_driver.h"

class device_wj712 : protected device_laser
{
public:

	device_wj712();
	~device_wj712();

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

	void pub_amcl_laser(float * range, float * intensity, int d_size);

	SReflector laser_ref_;
	SLaser_Ex_Ref laser_ex_ref_;

	laser_filter_ex filter_;
	//SLaser_Ex filter_min_range_;
	void filter_para_reset();
	F32 laser_amcl_resolution_;
	int laser_start_index_;
	int laser_step_;

	bool b_wj712_7200_;
	bool b_pub_laser_ex_;
	bool b_pub_laser_ex_ref_;
	bool b_pub_ref_;
	bool b_pub_amcl_ref_;

	int scan_frequency_ ;
	int samples_per_scan_ ;

private:
	//driver
	wj712_driver* p_wj712_driver_;
	int i_last_cnt_;
	int i_err_cnt_;
	THSafe<int> th_sig_cnt_;

	cTimerDiff dt_;

};

#endif//_DEVICE_WJ712_WANGHONGTAO_20191024_