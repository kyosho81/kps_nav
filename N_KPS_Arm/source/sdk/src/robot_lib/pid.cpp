#include "math.h"
#include <iostream>

#include "pid.h"

pid::pid()
{
	pid_v_.kp = 0;
	pid_v_.ti = 0;

	pid_v_.last_err = 0;
	pid_v_.last_out = 0;

	pid_v_.w_max_ = 1;
	pid_v_.w_min_ = -1;
}

pid::~pid()
{
	
}

void pid::Init_pid(F32 p,F32 i){
	pid_v_.kp = p;
	pid_v_.ti = i;

	pid_v_.last_err = 0;
	pid_v_.last_out = 0;	
}
void pid::Cal_Pid(F32 dt,F32 sv,F32 cv,F32 &out){

	F32 err = 0;
	F32 A = 0.0;
	F32 B = 0.0;
	F32 uk = 0.0;

	F32 tmp = 0;
	//	F32 acc = 0;

	
	
	if( (fabs(dt) < 1e-6) || (dt > 3.0)){
		return;
	}

	if(pid_v_.ti == 0){
		A = pid_v_.kp;
	}else{
		A = pid_v_.kp * (1 + dt / pid_v_.ti);
	}

	B = pid_v_.kp ;

	err = sv - cv;

	//std::cout<<"err:"<<err<<std::endl;

	uk = A*err - B * pid_v_.last_err;


	if(fabs(err) < 0.01){
		tmp= 0;
	}
	else{
		tmp = pid_v_.last_out + uk;	
	}


	if(tmp > pid_v_.w_max_){
		tmp = pid_v_.w_max_;
	}
	if(tmp < pid_v_.w_min_){
		tmp = pid_v_.w_min_;
	}

	pid_v_.last_out	= tmp;
	pid_v_.last_err = err;

	out = tmp;

}
void pid::Clear_pid(){

	pid_v_.last_err = 0;
	pid_v_.last_out = 0;	
}


