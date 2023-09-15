#include "Comm.h"
#include "TimerDiff.h"

#include "angle_ctl.h"


angle_ctl::angle_ctl()
{

}

angle_ctl::~angle_ctl()
{

}

void angle_ctl::Init_pid(F32 p,F32 i)
{
	
	pid_.Init_pid(p,i);
}

void angle_ctl::Cal_vw( F32 &out,const F32& ca,const F32& sa )
{

	dt_.End();
	
	F32 t = dt_.GetTime();
	t = t / 1e6;

	pid_.Cal_Pid(t,sa,ca,out);

	dt_.Begin();

}
