#ifndef _DEVICE_DYNAMIC_LOCATION_WANGHONGTAO_20191205_
#define _DEVICE_DYNAMIC_LOCATION_WANGHONGTAO_20191205_

#include <string>
#include <map>
#include <boost/thread.hpp>


#include "Comm/buffer_con.hpp"
#include "pf/merge_tf.h"

#include "device/device_base.h"

class dynamic_loc;

class device_dynamic_loc : device_base
{
public:

	device_dynamic_loc();
	~device_dynamic_loc();

protected:

	bool setPara( std::string name , std::string value );

	bool fnc_run();

	bool fnc_recovery();

	bool fnc_to_err();

	bool fnc_init();

private:
	
	bool onInit();
	
	bool toErr(U16 err_code);

	



private:
	dynamic_loc* dynamic_loc_;
	
	bool init_sub_msg();

	int sub_id_set_map_cmd_;
	std::string sub_nm_set_map_cmd_;
	bool s_set_map_cmd(const SCmd &map_cmd);

	void set_map_cmd(const std::string &str_map_cmd);
	bool get_map_cmd(std::string &str_cmd );

	boost::mutex m_reset_map_;
	std::string str_map_cmd_;
};

#endif//_DEVICE_DYNAMIC_LOCATION_WANGHONGTAO_20191205_
