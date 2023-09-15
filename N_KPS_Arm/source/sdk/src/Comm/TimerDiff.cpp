#include <boost/thread.hpp>
#include <ctime>

#include "Comm.h"
#include "TimerDiff.h"

cTimerDiff::cTimerDiff(void)
{
	Begin();
	End();

	
}

cTimerDiff::~cTimerDiff(void)
{
}

void cTimerDiff::Begin() {
	boost::posix_time::ptime t(
		boost::posix_time::microsec_clock::local_time());
	beginTime = t;
}

long long cTimerDiff::End() {
	boost::posix_time::ptime t(
		boost::posix_time::microsec_clock::local_time());
	endTime = t;

	boost::posix_time::time_duration t3 = (endTime - beginTime);

	return t3.total_microseconds();

}
void cTimerDiff::ms_begin() {
	boost::posix_time::ptime t(
		boost::posix_time::microsec_clock::local_time());
	ms_beginTime = t;
}

long long cTimerDiff::ms_end() {
	boost::posix_time::ptime t(
		boost::posix_time::microsec_clock::local_time());
	ms_endTime = t;

	boost::posix_time::time_duration t3 = (ms_endTime - ms_beginTime);

	return t3.total_microseconds();

}
long long cTimerDiff::GetTime() const{
	boost::posix_time::ptime t(
		boost::posix_time::microsec_clock::local_time());
	boost::posix_time::time_duration t3 = (t - beginTime);
	
	return t3.total_microseconds();
}
std::string cTimerDiff::get_now(){

		time_t tNowTime;
		time(&tNowTime);

		tm* tLocalTime = localtime(&tNowTime);

		std::stringstream ss;
		ss<<tLocalTime->tm_year+1900 <<"-"<<tLocalTime->tm_mon+1 <<"-"<<tLocalTime->tm_mday<<" "<<tLocalTime->tm_hour <<":"<< tLocalTime->tm_min <<":"<< tLocalTime->tm_sec;
		return ss.str();
}

std::string cTimerDiff::get_now_ut()
{
	boost::posix_time::ptime time(
		boost::posix_time::microsec_clock::universal_time());

	boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
	facet->format("%Y-%m-%d %H:%M:%S.%f");
	std::stringstream stream;
	stream.imbue(std::locale(std::locale::classic(), facet));
	stream << time;

	return stream.str();

}

std::string cTimerDiff::get_file_now(){

	time_t tNowTime;
	time(&tNowTime);

	tm* tLocalTime = localtime(&tNowTime);

	std::stringstream ss;
	ss<<tLocalTime->tm_year+1900 <<"-"<<tLocalTime->tm_mon+1 <<"-"<<tLocalTime->tm_mday<<"-"<<tLocalTime->tm_hour <<"-"<< tLocalTime->tm_min <<"-"<< tLocalTime->tm_sec;
	return ss.str();
}
std::string cTimerDiff::get_now_ms(){

	boost::posix_time::ptime time(
		boost::posix_time::microsec_clock::local_time());

	boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
	facet->format("%Y-%m-%d %H:%M:%S.%f");
	std::stringstream stream;
	stream.imbue(std::locale(std::locale::classic(), facet));
	stream << time;
	return stream.str();


}
void cTimerDiff::PrintString(){
	//printf("@Use Time = %f\n",GetTime());
}

void cTimerDiff::ms_loop( int ms )
{
	float do_time = ms_end() / 1e3;

	if (do_time > ms)
	{
		ms_begin();
		return;
	}else{
		do_time = ms - do_time;
		if ((do_time > 0)  && (do_time < 100000) )
		{
			//std::cout<<"sleep:"<<do_time<<std::endl;
			SLEEP(do_time);
		}
		else{
			std::cout<<" cTimerDiff::ms_loop time out !! "<<do_time<<std::endl;
		}
		
	}
	ms_begin();
}
//universal_time microseconds 10-6 s
long long cTimerDiff::total_ms()
{
	std::string s1 = "1970-01-01 00:00:00.000000";
	boost::posix_time::ptime epoch(boost::posix_time::time_from_string(s1));
	//boost::posix_time::ptime epoch(boost::gregorian::date(1970, boost::gregorian::Jan, 1));
	boost::posix_time::ptime t(
		boost::posix_time::microsec_clock::universal_time());

	boost::posix_time::time_duration time_from_epoch =
		t - epoch;
	long long dt = time_from_epoch.total_microseconds();

	return dt;

	//return time_from_epoch.total_seconds();

}
std::string cTimerDiff::time_to_string(const boost::posix_time::ptime& time)
{
	boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
	facet->format("%Y-%m-%d %H:%M:%S");
	std::stringstream stream;
	stream.imbue(std::locale(std::locale::classic(), facet));
	stream << time;
	return stream.str();
}
boost::posix_time::ptime cTimerDiff::string_to_time(std::string str_time)
{
	return boost::posix_time::time_from_string(str_time);
}
bool cTimerDiff::string_to_time(boost::posix_time::ptime &pt , std::string str_time)
{
	try
	{
		pt = boost::posix_time::time_from_string(str_time);
		return true;
	}
	catch(boost::bad_lexical_cast)
	{
		
	}
	return false;
}
long long cTimerDiff::diff_begin_end(const boost::posix_time::ptime& t_begin , const boost::posix_time::ptime& t_end){
	boost::posix_time::time_duration time_from_epoch = t_end - t_begin;
	long long dt = time_from_epoch.total_microseconds();
	return dt;
}
long long cTimerDiff::diff_begin_end(std::string str_time_begin , std::string str_time_end){
	boost::posix_time::ptime t_begin = string_to_time(str_time_begin);
	boost::posix_time::ptime t_end = string_to_time(str_time_end);
	return diff_begin_end(t_begin,t_end);
}

bool cTimerDiff::string_to_lltime(long long &dt, std::string str_time )
{
	try
	{
		boost::posix_time::ptime pt = boost::posix_time::time_from_string(str_time);

		std::string s1 = "1970-01-01 00:00:00.000000";
		boost::posix_time::ptime epoch(boost::posix_time::time_from_string(s1));

		boost::posix_time::time_duration time_from_epoch =
			pt - epoch;
		dt = time_from_epoch.total_microseconds();


		return true;
	}
	catch(boost::bad_lexical_cast)
	{

	}
	return false;
}

bool cTimerDiff::lltime_to_string(std::string &str_time, long long dt)
{
	try
	{
		std::string s1 = "1970-01-01 00:00:00.000000";
		boost::posix_time::ptime epoch(boost::posix_time::time_from_string(s1));

		boost::posix_time::time_duration time_dt = boost::posix_time::microseconds(dt);
		epoch += time_dt;

		boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
		facet->format("%Y-%m-%d %H:%M:%S.%f");
		std::stringstream stream;
		stream.imbue(std::locale(std::locale::classic(), facet));
		stream << epoch;
		str_time = stream.str();

		return true;
	}
	catch(boost::bad_lexical_cast)
	{

	}
	return false;
}
