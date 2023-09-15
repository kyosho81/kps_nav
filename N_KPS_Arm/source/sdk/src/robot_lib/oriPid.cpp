#include "math.h"
#include "iostream"

#include "oriPid.h"

F32 oriPid::cal_pid(const F32 &setV,const F32 &actV){

	int index;

	err_ = setV - actV;

	if( actV > vmax_)
	{
		if( fabs( err_ ) > 200)
		{
			index=0;

		}else{

			index=1;

			if( err_ < 0)
			{
				integral_ += err_;
			}
		}
	}else if( actV < vmin_){
		if( fabs( err_ ) > 200)
		{
			index = 0;
		}else{
			index = 1;
			if( err_ > 0)
			{
				integral_ += err_;
			}
		}
	}else{
		if( fabs( err_ ) > 200)
		{
			index = 0;
		}else{
			index = 1;
			integral_ += err_;
		}
	}
	//std::cout<<"kp:"<<Kp_ * err_<<" ki:"<<Ki_ * integral_<<" kd:"<<Kd_ * ( err_ - err_last_)<<std::endl;
	out_ = Kp_ * err_ + index * Ki_ * integral_ + Kd_ * ( err_ - err_last_);
	
	err_last_ = err_;

	return out_;
}

void oriPid::init( const F32 &kp,const F32 &ki,const F32 &kd,const F32 &vmax,const F32 &vmin)
{
	Kp_ = kp;
	Ki_ = ki;
	Kd_ = kd;

	vmax_ = vmax;
	vmin_ = vmin;

	out_ = 0;

	err_ = 0;
	err_last_ = 0;

	integral_ = 0;

}
void oriPid::setP(const F32 &kp){
	Kp_ = kp;
}
void oriPid::setI(const F32 &ki){
	Ki_ = ki;
}
void oriPid::setD(const F32 &kd){
	Kd_ = kd;
}
void oriPid::reset(){
	err_ = 0;
	err_last_ = 0;

	integral_ = 0;
}
