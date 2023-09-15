#ifndef _DEVICE_LASER_MATCHER_WANGHONGTAO_20200606_
#define _DEVICE_LASER_MATCHER_WANGHONGTAO_20200606_

#include <string>
#include <map>
#include <boost/thread.hpp>


#include "Comm/buffer_con.hpp"
#include "bag/bag.h"
#include "laser_filter/laser_filter.h"

#include "device/health_examination.h"

class device_laser_matcher : device_base
{
public:

	device_laser_matcher();
	~device_laser_matcher();

protected:

	bool setPara( std::string name , std::string value );

	bool fnc_run();
	
	bool fnc_init();

	bool fnc_recovery();

	bool fnc_to_err();

private:
	
	bool onInit();
	bool toErr(U16 err_code);

	//sub data source
private:
	void init_call_back();

	int sub_id_laser_;
	int sub_id_amcl_;
	int sub_id_ref_loc_;
	int sub_id_dynamic_loc_;

private:

	health_examination health_examination_;
};

#endif//_DEVICE_LASER_MATCHER_WANGHONGTAO_20200606_
