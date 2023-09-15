#ifndef _CHASSIS_MY_DRIVER_OUTSIDE_
#define _CHASSIS_MY_DRIVER_OUTSIDE_

//#include "chassis/struct_driver.h"
#include "chassis/driver_base.h"
#include "TimerDiff.h"
class SerialPort;

class my_driver_outside : Driver_base
{
public:
	my_driver_outside();
	~my_driver_outside();

protected:

private://virtual
  
	
	void setPara(std::string name ,std::string value);
	bool open_transfer_device();
	bool init_driver();
	void close_driver();

	void setRPM(int id,F32 v);
	F32 getSpeed(int id);
	F32 getDiffAngle(int id);

 	void setAngle(int id,F32 rad_angle);
 	F32 getAngle(int id);

private:
	std::string port_;
	//SerialPort* sport_;
	cTransferDevice* pTransDevice_;
	F32 reduction_ratio_;
	U32 counts_;

	U32 one_wheel_counts_;


	bool first_odo_;

	//my chassis example, customer should not do like this
	void init_customer_para();


	bool SetSpeedLR();
	F32 GetDiffPos(U8 id );
	void GetSpeedLR();

	void SendData( U8* s_data,U16 len );
	void ReadData( U8* r_data,int &len,int need,int timeout );
	

	F32 left_speed_;	//RPM_left
	F32 right_speed_;   //RPM_right

	U8 address_;

	U8 left_status_;	
	U8 left_disable_;	
	U8 left_emergency_;	
	U8 left_over_load_;	
	U8 left_pwm_;		
	S8 left_direction_;	
	S32 left_pos_;
	S32 last_left_pos_;
	S32 deta_left_pos_;

	F32 left_set_v;	
	F32 left_current_v;
	F32 left_current;	

	U8 right_status_;	
	U8 right_disable_;	
	U8 right_emergency_;	
	U8 right_over_load_;	
	U8 right_pwm_;		
	S8 right_direction_;	
	S32 right_pos_;
	S32 last_right_pos_;
	S32 deta_right_pos_;

	F32 right_set_v;	
	F32 right_current_v;
	F32 right_current;	

	F32 c_left_;		
	F32 c_right_;		
	
	//////////////////
	U8 buf[32];
	S32 direction_left_;  //B
	S32 direction_right_;  //A
	S32 left_speed_ms_;	//RPMS_left  //B
	S32 right_speed_ms_;   //RPMS_right  //A

	////FSM
	enum State {StateA,StateB,StateC,StateD,StateE,StateF};
	State state;
	
	S32 direction_left_fsm;  //B
	S32 direction_right_fsm;  //A
	
	void FSM(char ch);

	////
	cTimerDiff dt_;
	F64 dt_last_;

};



#endif//_CHASSIS_MY_DRIVER_OUTSIDE_
