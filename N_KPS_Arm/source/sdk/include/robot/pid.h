#ifndef _PID_KYOSHO_20160316_
#define _PID_KYOSHO_20160316_

#include "MyDefine.h"

typedef struct{

	F32 kp;
	F32 ti;

	F32 last_err;
	F32 last_out;

	F32 w_max_;
	F32 w_min_;

}PID_Para;



class pid
{
public:
	pid();
	~pid();

	void Init_pid(F32 p,F32 i);
	void Cal_Pid(F32 dt,F32 sv,F32 cv,F32 &out);
	void Clear_pid();

protected:
private:

	PID_Para pid_v_;

};





#endif//_PID_KYOSHO_20160316_
