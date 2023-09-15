#ifndef _DEVICE_REFLECTOR_SIM_WANGHONGTAO_20191205_
#define _DEVICE_REFLECTOR_SIM_WANGHONGTAO_20191205_

#include <string>
#include <map>
#include <boost/thread.hpp>


#include "Comm/buffer_con.hpp"

#include "device/device_laser.h"

class GridMap;

class device_reflector_sim : device_base
{
public:

	device_reflector_sim();
	~device_reflector_sim();

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
	bool update_odom( const SOdomSpeed& new_odom );
	int sub_id_odom_;
	THSafe<SOdomSpeed> th_odom_;

};

#endif//_DEVICE_REFLECTOR_SIM_WANGHONGTAO_20191205_
