#ifndef _CALIB_TOOLS_WANGHONGTAO_20210826_
#define _CALIB_TOOLS_WANGHONGTAO_20210826_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include "buffer_con.hpp"

#include "RobotStruct.h"
#include "sensor/laser_filter/laser_filter.h"

class calib_tools
{
public:
	calib_tools();
	~calib_tools();


	bool init(F32 wall_dx);
	void bind_pub_laser(boost::function< bool(const SLaser& laser)> fnc_show_laser);

	void stop_get_diff(F32 &dx , F32 &da);

protected:
private:
	std::string str_robot_shape_;
	SPos laser_in_base_link_;

	bool init_sub_msg();
	CALIB_SUB_TYPE calib_sub_type_;
	//sub
	int sub_id_laser_;
	bool updata_used_laser(const SLaser &new_laser);

	bool b_init_filter_;
	laser_filter l_filter_;

	boost::function< bool(const SLaser& laser)> fnc_show_laser_;

	bool cal_laser_diff( SPos &new_diff , std::vector<SLine2P> v_ln);
	F32 f_min_line_;
	F32 wall_dx_;

	boost::mutex mu_diff_;
	SPos new_diff_;
	THSafe<int> th_run_;

	filter<F32,30> diff_x_filter_;
	filter<F32,30> diff_a_filter_;
};




#endif//_CALIB_TOOLS_WANGHONGTAO_20210826_
