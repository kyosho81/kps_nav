#ifndef _DEVICE_PAVO2_LS50_KYOSHO_20200520_
#define _DEVICE_PAVO2_LS50_KYOSHO_20200520_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include "sensor/laser_filter/laser_filter_ex.h"
#include "device/device_laser.h"

#include "sensor/pavo2/pavo2_driver.h"

class device_pavo2_ls50 : protected device_laser
{
public:

	device_pavo2_ls50();
	~device_pavo2_ls50();

protected:

	bool setPara( std::string name , std::string value );
	
	bool fnc_run();

	
	
	bool fnc_recovery();

	bool fnc_to_err();

private:

	bool onInit();
	bool toErr(U16 err_code);

	
	
private:
	void filter_para_reset();
	void init_filter();
	void fill_pub_data();
	void pub_laser_ex(SLaser_Ex &laser_ex);
	bool b_pub_laser_ex_;

	pavo2::pavo2_driver *driver_;
	std::vector<pavo_response_scan_t> scan_vec;
	
	F32 laser_amcl_resolution_;
	int laser_start_index_;
	int laser_step_;

	int scan_frequency_ ;
	int samples_per_scan_ ;

	laser_filter_ex filter_;
};

#endif//_DEVICE_PAVO2_LS50_KYOSHO_20200520_