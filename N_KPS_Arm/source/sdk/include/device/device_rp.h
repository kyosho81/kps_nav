#ifndef _DEVICE_RP_WANGHONGTAO_20180401_
#define _DEVICE_RP_WANGHONGTAO_20180401_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include "rplidar/rplidar.h" //RPLIDAR standard sdk, all-in-one header

#include "device/device_laser.h"



class device_rp : device_laser
{
public:

	device_rp();
	~device_rp();

protected:

	bool setPara( std::string name , std::string value );

	bool fnc_run();

	bool fnc_recovery();

	bool fnc_to_err();

private:

	bool onInit();
	bool toErr(U16 err_code);
	
	bool getRPLIDARDeviceInfo(rp::standalone::rplidar::RPlidarDriver * drv);
	bool checkRPLIDARHealth(rp::standalone::rplidar::RPlidarDriver * drv);
	bool getData(SLaser& used_laser,rplidar_response_measurement_node_t* nodes,size_t count);

	rp::standalone::rplidar::RPlidarDriver * rp_ ;
	rplidar_response_measurement_node_t* nodes_;
	size_t   count_;
};

#endif//_DEVICE_RP_WANGHONGTAO_20180401_