#include <string.h>
#include <iostream>

#include "Comm.h"
#include "log/log_client.h"
#include "robot/lowpass_filter.h"

lowpass_filter::lowpass_filter()
{
	last_0_1_ = 0;
	last_0_0_1_ = 0;

	para_0_1_ = 0.2;
	para_0_0_1_ = 0.02;
	threshhold_ = 800;


	lowpass_max_diff_ = ( para_0_1_ - para_0_0_1_)*threshhold_;

	b_first_ = true;
}

lowpass_filter::~lowpass_filter()
{

}

bool lowpass_filter::set_data(const F32 &data)
{
	if(b_first_){

		last_0_1_  = data;
		last_0_0_1_  = data;
		b_first_ = false;
	}

	last_0_1_  = last_0_1_* para_0_1_ + data * (1.0 - para_0_1_);
	last_0_0_1_  = last_0_0_1_* para_0_0_1_ + data * (1.0 - para_0_0_1_);
	F32 diff = fabs(last_0_1_ - last_0_0_1_);
	//TCP_LOG_DEBUG<<"lowpass_filter:"<<diff;
	if ( diff > lowpass_max_diff_)
	{
		return false;
	}
	return true;
}


void lowpass_filter::set_para(const F32 &p1,const F32 &p2)
{
	para_0_1_ = p1;
	para_0_0_1_ = p2;
	lowpass_max_diff_ = ( para_0_1_ - para_0_0_1_)*threshhold_;
}

void lowpass_filter::set_threshhold(const F32 &th)
{
	threshhold_ = th;
	lowpass_max_diff_ = ( para_0_1_ - para_0_0_1_)*threshhold_;
}

void lowpass_filter::clear()
{
	b_first_ = true;
}
