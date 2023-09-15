#ifndef _DEVICE_LOG_WANGHONGTAO_20191201_
#define _DEVICE_LOG_WANGHONGTAO_20191201_

#include <string>
#include <map>
#include <boost/thread.hpp>


#include "Comm/buffer_con.hpp"
#include "bag/bag.h"
#include "laser_filter/laser_filter.h"

#include "device/device_laser.h"


class device_log : device_base
{
public:

	device_log();
	~device_log();

protected:

	bool setPara( std::string name , std::string value );

	bool fnc_run();
	
	bool fnc_init();

	bool fnc_recovery();

	bool fnc_to_err();

private:
	
	bool onInit();
	bool toErr(U16 err_code);

	SLaser laser_log_;
	SOdomSpeed odom_log_;
	std::string str_log_name_;
	cbag bag_;
	
	//0 : waiting for set pos
	//<100 send first frame
	//>=100 send one by one
	THSafe<int> th_i_flag_;
	SBAG one_bag_;

	laser_filter l_filter_;
private:
	void init_call_back();
	bool s_init_pos(const SInit_Pos &pos );
	int sub_id_estimate_;
};

#endif//_DEVICE_LOG_WANGHONGTAO_20191201_
