#ifndef _DATA_TIME_KYOSHO_20110903_
#define _DATA_TIME_KYOSHO_20110903_


//#include <iostream>

#include <boost/date_time/posix_time/posix_time.hpp>
#include "TimerDiff.h"

class data_time
{
public:
	data_time();
	~data_time();

	std::string set_begin();
	std::string set_end();
	int get_diff_ms();
	int get_diff_sec();

protected:
private:
	boost::posix_time::ptime t_begin_;
	boost::posix_time::ptime t_end_;
};

#endif // _DATA_TIME_KYOSHO_20110903_
