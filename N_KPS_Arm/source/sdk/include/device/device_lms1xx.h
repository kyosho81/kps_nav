#ifndef _DEVICE_LMS1XX_WANGHONGTAO_20180401_
#define _DEVICE_LMS1XX_WANGHONGTAO_20180401_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include "sensor/sick/lms111.h"
#include "device/device_laser.h"


class LMS1xx;

class device_lms1xx : protected device_laser
{
public:

	device_lms1xx();
	~device_lms1xx();

protected:

	bool setPara( std::string name , std::string value );

	bool fnc_run();

	bool fnc_recovery();

	bool fnc_to_err();

private:

	bool onInit();
	bool toErr(U16 err_code);

	LMS1xx* lms1xx_;

	bool is_lms511_;
	scanData data_;
};

#endif//_DEVICE_LMS1XX_WANGHONGTAO_20180401_