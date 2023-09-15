#ifndef _DEVICE_TIM_WANGHONGTAO_20180401_
#define _DEVICE_TIM_WANGHONGTAO_20180401_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include <sick_tim/sick_tim_common_tcp.h>
#include <sick_tim/sick_tim551_2050001_parser.h>

#include "device/device_laser.h"



class device_tim : device_laser
{
public:

	device_tim();
	~device_tim();

protected:

	bool setPara( std::string name , std::string value );

	bool fnc_run();

	bool fnc_recovery();

	bool fnc_to_err();

private:

	bool onInit();
	bool toErr(U16 err_code);

	sick_tim::SickTim5512050001Parser* parser_;
	sick_tim::SickTimCommon* s_;
	int result_;
// 	LMS1xx* lms1xx_;
// 
// 	bool is_lms511_;
// 	scanData data_;
};

#endif//_DEVICE_TIM_WANGHONGTAO_20180401_