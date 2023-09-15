#ifndef _DEVICE_SPECIAL_LOCATION_WANGHONGTAO_20191205_
#define _DEVICE_SPECIAL_LOCATION_WANGHONGTAO_20191205_

#include <string>
#include <map>
#include <boost/thread.hpp>


#include "Comm/buffer_con.hpp"


#include "device/device_base.h"
#include "sub_map_loc/laser_special_loc.h"
//class special_loc_base;

class device_special_loc : device_base
{
public:

	device_special_loc();
	~device_special_loc();

	typedef enum{
		IDLE = 0,
		RUN = 1,
		ERR = 2
	}DSL_Status;

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
	void init_call_back();

	int sub_id_set_cmd_;
	bool s_set_cmd(const SCmd &set_cmd);

	THSafe<DSL_Status> th_dsl_status_;
	//sm 
private:
	bool create_sm_loc();
	void pub_loc_pos(SWorldLM wlm , SPOS_CONFIDENCE con_pos);
	special_loc_base* p_special_loc_base_;
};

#endif//_DEVICE_REFLECTOR_LOCATION_WANGHONGTAO_20191205_
