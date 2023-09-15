#ifndef _DEVICE_LASER_SIM_WANGHONGTAO_20180401_
#define _DEVICE_LASER_SIM_WANGHONGTAO_20180401_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include "rplidar/rplidar.h" //RPLIDAR standard sdk, all-in-one header

#include "Comm/buffer_con.hpp"
#include "sim_obstacle.h"

#include "device/device_laser.h"

class GridMap;

class device_laser_sim : device_laser
{
public:

	device_laser_sim();
	~device_laser_sim();

protected:

	bool setPara( std::string name , std::string value );

	bool fnc_run();

	bool fnc_recovery();

	bool fnc_to_err();

private:
	
	bool onInit();
	bool toErr(U16 err_code);
	void sim_laser_bin(SLaser &laser_data);
	void init_laser_th(const SLaser &laser_data);
	
	GridMap* shared_amcl_map_;

	

	typedef struct _SimLaser_tf
	{
		F32 base_laser_cos_;
		F32 base_laser_sin_;

	}SimLaser_tf;
	SimLaser_tf laser_tf_[LASER_COUNT];

private:
	void init_call_back();
	bool update_odom( const SOdomSpeed& new_odom );
	int sub_id_odom_;
	THSafe<SOdomSpeed> th_odom_;

	void do_sim_obstacle();
	sim_obstacle sim_obstacle_;
};

#endif//_DEVICE_LASER_SIM_WANGHONGTAO_20180401_
