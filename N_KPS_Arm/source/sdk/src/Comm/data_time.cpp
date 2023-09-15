#include <boost/thread.hpp>
#include <ctime>

#include "Comm.h"
#include "TimerDiff.h"

#include "data_time.h"

data_time::data_time()
{

}

data_time::~data_time()
{

}

std::string data_time::set_begin()
{
	boost::posix_time::ptime t(
		boost::posix_time::microsec_clock::local_time());
	t_begin_ = t;
	return cTimerDiff::time_to_string(t_begin_);
}

std::string data_time::set_end()
{
	boost::posix_time::ptime t(
		boost::posix_time::microsec_clock::local_time());
	t_end_ = t;
	return cTimerDiff::time_to_string(t_end_);
}

int data_time::get_diff_ms()
{
	long long ldt = cTimerDiff::diff_begin_end(t_begin_,t_end_);
	return ldt / 1000;
}

int data_time::get_diff_sec()
{
	long long ldt = cTimerDiff::diff_begin_end(t_begin_,t_end_);
	return ldt / 1000000;
}
