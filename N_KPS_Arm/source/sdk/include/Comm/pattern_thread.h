#ifndef _WANGHONGTAO_PATTERN_THREAD_2020_04_20_H_
#define _WANGHONGTAO_PATTERN_THREAD_2020_04_20_H_

#include "Comm/buffer_con.hpp"
#include <boost/thread.hpp>

class pattern_thread
{
public:

	pattern_thread();
	~pattern_thread();

	
	void run_thread(boost::function<bool ()> fnc);
	void bind_func(boost::function<bool ()> fnc);
	bool destory_thread();

protected:
private:
	void th_run();
	THSafe<bool> th_b_run_;
	CSBuffer<int,1> th_over_sig_;
	boost::function<bool ()> fnc_run_;
};

#endif//_WANGHONGTAO_PATTERN_THREAD_2020_04_20_H_
