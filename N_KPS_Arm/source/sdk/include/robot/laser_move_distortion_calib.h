#ifndef _LASER_MOVEMENT_DISTORTION_CALIBRATION_WANGHONGTAO_2020_07_21_
#define _LASER_MOVEMENT_DISTORTION_CALIBRATION_WANGHONGTAO_2020_07_21_

#include <map>

#include "MyDefine.h"
#include <boost/thread.hpp>

#include "TimerDiff.h"
#include "RobotStruct.h"
#include "buffer_con.hpp"

class laser_md_calib
{
public:
	laser_md_calib();
	~laser_md_calib();

	void set_odom(const SOdomSpeed& new_odom);
	void set_odom(const SOdomSpeedEx& new_odom);
	bool get_odom_interpolation(SOdomSpeedEx &odom, F64 time_now);
	F32 laser_calib( SLaserXYEx &laser_calibInodom, SLaser_Ex &laser_ex);

protected:

private:
	int cal_odom_covariance( boost::circular_buffer<SOdomSpeedEx> odom_tmp);
	bool cal_fit(boost::circular_buffer<SOdomSpeedEx> odom_tmp);

	THSafe<SOdomSpeedEx> cur_odom_;

	boost::circular_buffer<SOdomSpeedEx> buffer_odom_;
	boost::mutex mu_;
	int th_poly_type_;
	F64 st_;
	std::vector<F64> v_x_poly_;
	std::vector<F64> v_y_poly_;
	F64 point_slope_k_;
	F64 point_slope_x_;
	F64 point_slope_y_;
};


#endif//_LASER_MOVEMENT_DISTORTION_CALIBRATION_WANGHONGTAO_2020_07_21_
