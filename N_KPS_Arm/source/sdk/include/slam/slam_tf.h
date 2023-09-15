#ifndef _MY_TF_KYOSHO_20150906_
#define _MY_TF_KYOSHO_20150906_

#include "MyDefine.h"
#include "RobotStruct.h"

class slam_tf
{
public:
	slam_tf();
	~slam_tf();

	void setLaserInBaselink(F32 x ,F32 y ,F32 th);
	void getLaserInBaselink(F32 &x ,F32 &y ,F32 &th);

	void getDLaserInBaselink(F32 &x, F32 &y);
	void getDLaserInBaseOdom(F32 &x,F32 &y,F32 ox,F32 oy,F32 oth);

	SPos getLaserPos2OdomPos(const SPos& laser_pos);

protected:
private:

	SPos pos_;	//base_laer in base link
};

#endif//_MY_TF_KYOSHO_20150906_
