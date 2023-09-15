#ifndef _CHASSIS_IT_SERVO_DRIVER_WANGHONGTAO_2018_08_26_
#define _CHASSIS_IT_SERVO_DRIVER_WANGHONGTAO_2018_08_26_

#include "TimerDiff.h"
#include "chassis/driver_base.h"

class cTransferDevice;

class it_servo_driver : Driver_base
{
public:
	it_servo_driver();
	~it_servo_driver();

protected:

private:
	
	
	F32 reduction_ratio_;
	U32 counts_;
	
	U32 one_wheel_counts_;

private://virtual customized :TODO
	void setPara(std::string name ,std::string value);

	bool init_driver();


	bool open_transfer_device();
	void close_driver();
	void SendData( U8* s_data,U16 len );
	void ReadData( U8* r_data,int &len,int need,int timeout );
	cTransferDevice* pTransDevice_;
	std::string port_;

	void setRPM(int id,F32 v);
	F32 getSpeed(int id);

	F32 getDiffAngle(int id);

private:
	F32 RPM2CMD(const F32 &speed);
	F32 GetDiffPos(U8 id );
	

	
	cTimerDiff left_dt_;
	cTimerDiff right_dt_;

	F32 left_speed_;
	F32 right_speed_;

	F32 c_left_;
	F32 c_right_;

private:
	void init_cmd();
	U8 ch_cmd_left_stop_[8];
	U8 ch_cmd_right_stop_[8];

	U8 ch_cmd_left_begin_[8];
	U8 ch_cmd_right_begin_[8];

	U8 ch_cmd_left_model_[8];
	U8 ch_cmd_right_model_[8];

	U8 ch_cmd_left_speed_[13];
	U8 ch_cmd_right_speed_[13];

	U8 ch_cmd_left_counts_[8];
	U8 ch_cmd_right_counts_[8];

	bool b_first_counts_;
	S32 left_pos_;
	S32 right_pos_;

	S32 last_left_pos_;
	S32 last_right_pos_;

	S32 deta_left_pos_;
	S32 deta_right_pos_;

	void set_stop();
	void set_begin();
	void set_model();
	void set_rpm(const S32 &left_rpm,const S32 &right_rpm);
	void get_counts(U8 id);
	S32 parse_counts(U8* data);
	U8 ch_read[1024];
};



#endif//_CHASSIS_IT_SERVO_DRIVER_WANGHONGTAO_2018_08_26_
