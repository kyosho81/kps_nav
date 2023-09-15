#ifndef _DIO_ONBOARD_KYOSHO_20230210_
#define _DIO_ONBOARD_KYOSHO_20230210_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include "buffer_con.hpp"
#include "robot/dio_def.h"
#include "Comm/gpio.h"



class dio_onboard
{
public:
	dio_onboard();
	~dio_onboard();

	//load gpio pin
	bool init();
	
	bool do_in_out();

	bool get_di(SDI &sdi);


private:
	gpio gpio_;
};

#endif //_DIO_ONBOARD_KYOSHO_20230210_