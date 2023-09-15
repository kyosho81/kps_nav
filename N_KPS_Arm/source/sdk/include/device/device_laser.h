#ifndef _DEVICE_LASER_WANGHONGTAO_20180401_
#define _DEVICE_LASER_WANGHONGTAO_20180401_


#include <string>
#include <map>
#include <boost/thread.hpp>

#include "laser_filter/laser_filter.h"
#include "laser_filter/laser_filter_ex.h"
#include "laser_filter/laser_filter_ex2.h"
#include "robot/laser_move_distortion_calib.h"
#include "device/device_base.h"


class device_laser : protected device_base
{
public:

	device_laser();
	virtual ~device_laser();

	void get_laser_para(SLaser_para &para);

protected:

	void pub_laser(const SLaser &laser);
	void pub_laser_ex(SLaser_Ex &laser_ex);

	virtual bool setPara( std::string name , std::string value );
	virtual bool fnc_run() = 0;
	virtual bool fnc_recovery() = 0;
	virtual bool onInit() = 0;
	virtual bool toErr(U16 err_code) = 0;
	
	void load_para();
	//laser para
	SLaser_para laser_para_;

	SLaser laser_data_;
	SLaser_Ex laser_data_ex_;
	SLaser_Ex2 laser_data_ex2_;

	cTimerDiff dt_;

	laser_filter l_filter_;
	laser_filter_ex filter_ex_;
	laser_filter_ex2 filter_ex2_;

	bool first_laser_;

	std::string pub_name_;

	bool b_used_laser_cab_;

private:

	bool fnc_init();

private://laser odom interpolation
	
	int sub_id_odom_;
	bool s_update_odom( const SOdomSpeed& new_odom );
	void init_call_back();
	
	laser_md_calib loi_;
	SLaserXYEx laser_calibInodom_;

};

#endif //_DEVICE_BASE_WANGHONGTAO_20180401_