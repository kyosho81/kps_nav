#ifndef _TIMERDIFF_KYOSHO_20110903_
#define _TIMERDIFF_KYOSHO_20110903_


//#include <iostream>

#include <boost/date_time/posix_time/posix_time.hpp>

class cTimerDiff
{

private:
	boost::posix_time::ptime beginTime;
	boost::posix_time::ptime endTime;

	void ms_begin();
	long long ms_end();
	boost::posix_time::ptime ms_beginTime;
	boost::posix_time::ptime ms_endTime;

public:
	cTimerDiff(void);
	~cTimerDiff(void);

	void Begin();
	long long End();

	long long GetTime() const;

	void ms_loop(int ms);


	void PrintString();
public:
	static std::string get_now();
	static std::string get_now_ut();
	static std::string get_file_now();
	static std::string get_now_ms();
	//universal_time microseconds 10-6 s
	static long long total_ms();
	static std::string time_to_string(const boost::posix_time::ptime& time);
	static boost::posix_time::ptime string_to_time(std::string str_time);
	static bool string_to_time(boost::posix_time::ptime &pt , std::string str_time);
	static bool string_to_lltime(long long &dt, std::string str_time );
	static bool lltime_to_string(std::string &str_time, long long dt);

	static long long diff_begin_end(const boost::posix_time::ptime& t_begin , const boost::posix_time::ptime& t_end);
	static long long diff_begin_end(std::string str_time_begin , std::string str_time_end);
	
};

#endif // _TIMERDIFF_KYOSHO_20110903_
