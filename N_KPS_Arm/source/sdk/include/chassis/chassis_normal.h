#ifndef _CHASSIS_NORMAL_KYOSHO_20190911_H_
#define _CHASSIS_NORMAL_KYOSHO_20190911_H_

#include "chassis_base.h"

class Chassis_normal : Chassis_base
{
public:

	Chassis_normal();
	~Chassis_normal();

private://virtual
	//
	void setPara(std::string name , std::string value);
	bool initDriver(std::string para);

	//get odom in Base link (origin point is robot rotation center)
	void getOdomInBaseLink(F32 &dx,F32 &dy, F32 &th);
	void getOdomSpeed(F32 &vx,F32 &vy, F32 &th);

	void setOdomSpeed(F32 vx, F32 vy, F32 vw);

	

private:

	F32 wheel_dia_;	
	F32 axle_;		

protected:
private:
};



#endif//_CHASSIS_NORMAL_KYOSHO_20190911_H_
