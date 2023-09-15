#ifndef _DEVICE_DIFF_COUNTS_WANGHONGTAO_20180401_
#define _DEVICE_DIFF_COUNTS_WANGHONGTAO_20180401_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include "buffer_con.hpp"

template<typename T>
class diff_counts
{
public:
	diff_counts(){
		b_first_ = true;
		last_counts_ = 0;
	};
	~diff_counts(){

	};
	T get_diff_counts(const T &t){
		if (b_first_)
		{
			last_counts_ = t;
			b_first_ = false;
		}
		T tmp = t - last_counts_;
		last_counts_ = t;
		
		return tmp;
	};

private:
	bool b_first_;
	T last_counts_;
};



#endif //_DEVICE_DIFF_COUNTS_WANGHONGTAO_20180401_