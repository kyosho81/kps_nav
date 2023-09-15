#ifndef _CHASSIS_STEERING_MULTI_KYOSHO_2022_
#define _CHASSIS_STEERING_MULTI_KYOSHO_2022_

#include "chassis_base.h"
#include "TimerDiff.h"

#include "chassis/steering_multi.h"

class Chassis_steering_multi : Chassis_base
{
public:

	Chassis_steering_multi();
	~Chassis_steering_multi();

private://virtual
	//
	void setPara(std::string name , std::string value);
	bool initDriver(std::string para);

	//get odom in Base link (origin point is robot rotation center)
	void getOdomInBaseLink(F32 &dx,F32 &dy, F32 &th);
	void getOdomSpeed(F32 &vx,F32 &vy, F32 &th);

	void setOdomSpeed(F32 vx, F32 vy, F32 vw);

	void pub_data(int id,  steeing_single* p_steeing_single, F32 angle_action, F32 speed_action);

private:


	F32 ASpeed2RPM( F32 speed );
	F32 Angle2m2s( F32 speed );

protected:
private:

	cTimerDiff dt_;

	F32 vx_ ;
	F32 vy_ ;
	F32 th_ ;

	F32 wheel_a_dia_;

	F32 trans_matrix_x_;
	F32 trans_matrix_y_;
	F32 trans_matrix_th_;

private:
	steering_multi steering_multi_;
	std::map<int,SPos> m_multi_pos_;
	std::map<int,SVec> m_cur_;

	bool load_steering(std::string str_para);
	bool add_steering(int i_id, std::string str_para);
	bool set_driver( int id , F32 angle_action, F32 speed_action );
	bool b_angle_fix_;

	bool set_check( F32 &max_projection, int id , F32 angle_action, F32 speed_action);
	std::map<int,SVec> m_set_angle_speed_;

	F32 diff_stop_angle_;
};

















#endif//_CHASSIS_STEERING_MULTI_KYOSHO_2022_
