#ifndef _DEVICE_PAVO_LS20_WANGHONGTAO_20200520_
#define _DEVICE_PAVO_LS20_WANGHONGTAO_20200520_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include "sensor/laser_filter/laser_filter_ex.h"
#include "device/device_laser.h"

#include "sensor/pavo/pavo_driver.h"

class device_pavo_ls20 : protected device_laser
{
public:

	device_pavo_ls20();
	~device_pavo_ls20();

protected:

	bool setPara( std::string name , std::string value );
	
	bool fnc_run();

	bool fnc_recovery();

	bool fnc_to_err();

private:

	bool onInit();
	bool toErr(U16 err_code);

	
private:


	pavo::pavo_driver *driver_;
	std::vector<pavo_response_scan_t> scan_vec;

};

#endif//_DEVICE_PAVO_LS20_WANGHONGTAO_20200520_