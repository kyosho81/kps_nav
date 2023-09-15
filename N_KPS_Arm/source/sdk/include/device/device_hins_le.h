#ifndef _DEVICE_HINS_LE_KYOSHO_20221027_
#define _DEVICE_HINS_LE_KYOSHO_20221027_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include "sensor/laser_filter/laser_filter_ex2.h"
#include "device/device_laser.h"

class hins_le_driver;

class device_hins_le : protected device_laser
{
public:

	device_hins_le();
	~device_hins_le();

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
	void fill_pub_data(float * range, unsigned int* intensity, int d_size);

	void pub_laser_ex2(SLaser_Ex2 &laser_ex2);
	void pub_ref(SReflector &laser_ref);
	void pub_laser_ex_ref(SLaser_Ex_Ref &laser_ex_ref);

	void pub_amcl_laser(float * range, unsigned int* intensity, int d_size);

	SReflector laser_ref_;
	SLaser_Ex_Ref laser_ex_ref_;


	//SLaser_Ex filter_min_range_;
	void filter_para_reset();
	F32 laser_amcl_resolution_;
	int laser_start_index_;
	int laser_step_;

	bool b_pub_laser_ex_;

	int scan_frequency_ ;
	int samples_per_scan_ ;

private:
	//driver
	hins_le_driver* p_hins_le_driver_;

	int i_last_cnt_;
	int i_err_cnt_;
	THSafe<int> th_sig_cnt_;
};

#endif//_DEVICE_HINS_LE_KYOSHO_20221027_