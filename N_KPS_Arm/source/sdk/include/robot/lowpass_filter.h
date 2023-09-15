#ifndef _LOWPASS_FILTER_WANGHONGTAO_20200329_
#define _LOWPASS_FILTER_WANGHONGTAO_20200329_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include "Comm/buffer_con.hpp"


class GridMap;

class lowpass_filter
{
public:
	lowpass_filter();
	~lowpass_filter();

	bool set_data(const F32 &data);
	void set_para(const F32 &p1,const F32 &p2);
	void set_threshhold(const F32 &th);
	void clear();

protected:
private:
	F32 last_0_1_ ;
	F32 last_0_0_1_ ;

	F32 para_0_1_ ;
	F32 para_0_0_1_ ;

	F32 threshhold_;

	F32 lowpass_max_diff_;

	bool b_first_;
};


#endif//_LOWPASS_FILTER_WANGHONGTAO_20200329_
