#ifndef _CHASSIS_STEERING_SINGLE_KYOSHO_2022_
#define _CHASSIS_STEERING_SINGLE_KYOSHO_2022_

#include "chassis_base.h"
#include "TimerDiff.h"

#include "chassis/steering_single.h"

class Chassis_steering_single : Chassis_base
{
public:

	Chassis_steering_single();
	~Chassis_steering_single();

private://virtual
	//
	void setPara(std::string name , std::string value);
	void pub_data(int id, steeing_single* p_steeing_single, F32 angle_action, F32 speed_action);
	
	bool initDriver(std::string para);

	//get odom in Base link (origin point is robot rotation center)
	void getOdomInBaseLink(F32 &dx,F32 &dy, F32 &th);
	void getOdomSpeed(F32 &vx,F32 &vy, F32 &th);

	void setOdomSpeed(F32 vx, F32 vy, F32 vw);

	

private:
	
	


	F32 ASpeed2RPM( F32 speed );
	F32 Angle2m2s( F32 speed );
	F32 Angle2RPM( F32 speed );

	void resolution(F32 &speed,F32 &angle, F32 vx, F32 vy, F32 vw);

protected:
private:

	cTimerDiff dt_;

	F32 vx_ ;
	F32 vy_ ;
	F32 th_ ;

	F32 wheel_a_dia_;
	F32 angle_zero_;

	F32 base_link_x_;
	F32 base_link_y_;
	F32 base_link_th_;

	F32 trans_matrix_x_;
	F32 trans_matrix_y_;
	F32 trans_matrix_th_;

	steeing_single steeing_single_;

	F32 cur_th_;
	F32 cur_speed_;
	F32 cur_th_zero_;
};



#endif//_CHASSIS_STEERING_SINGLE_KYOSHO_2022_
