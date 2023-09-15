#ifndef _DEVICE_LOG_BAG_WANGHONGTAO_20200617_
#define _DEVICE_LOG_BAG_WANGHONGTAO_20200617_

#include <string>
#include <map>
#include <boost/thread.hpp>


#include "Comm/buffer_con.hpp"
#include "bag/bag.h"
#include "laser_filter/laser_filter.h"

#include "protobuf_msg/protobuf_log_bag.h"

#include "device/device_log_bag.h"


class device_log_bag : device_base
{
public:

	device_log_bag();
	~device_log_bag();

protected:

	bool setPara( std::string name , std::string value );

	bool fnc_run();
	
	bool fnc_init();

	bool fnc_recovery();

	bool fnc_to_err();

private:
	
	bool onInit();
	bool toErr(U16 err_code);


	protobuf_log_bag* protobuf_log_bag_;

private:

	void init_call_back();
	int sub_id_laser_;
	int sub_id_odom_;
	int sub_id_amcl_;
};

#endif//_DEVICE_LOG_BAG_WANGHONGTAO_20200617_
