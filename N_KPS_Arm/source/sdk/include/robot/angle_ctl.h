#ifndef _ANGLE_CTL_20160518_
#define _ANGLE_CTL_20160518_

#include "RobotStruct.h"

#include "pid.h"

class angle_ctl
{
public:
	angle_ctl();
	~angle_ctl();

	void Init_pid(F32 p,F32 i);

	void Cal_vw(F32 &out,const F32& ca,const F32& sa);

protected:
private:


	pid pid_;

	cTimerDiff dt_;

	
};



#endif//_ANGLE_CTL_20160518_
