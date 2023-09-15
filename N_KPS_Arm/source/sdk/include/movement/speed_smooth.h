#ifndef _SPEED_SMOOTH_KYOSHO_20181113_H
#define _SPEED_SMOOTH_KYOSHO_20181113_H

#include "Comm/Acc.h"
#include "Comm/TimerDiff.h"
#include "robot/Geometry.h"

class speed_smooth
{
public:
	speed_smooth();
	~speed_smooth();

	void init();

	F32 sm( F32 sv, F32 cv , F32 &out_cca );

	F32 get_acc(F32 s_acc, F32 c_acc);

protected:


//para
private:

	void init_para();
	//v ref
	F32 max_v_;
	F32 min_v_;
	F32 max_acc_v_;
	F32 acc_acc_v_;

	

private:
	F32 acc_;
	F32 last_cv_;
	F32 last_acc_;
	cTimerDiff dt_;
};

#endif // _AUTO_COVER_20181113_H
