#ifndef _CHASSIS_VSY27X_DRIVER_KYOSHO_2022_05_30_
#define _CHASSIS_VSY27X_DRIVER_KYOSHO_2022_05_30_

#include "TimerDiff.h"
#include "chassis/driver_base.h"

class can_base;

class vsy27x_driver : Driver_base
{
public:
	vsy27x_driver();
	~vsy27x_driver();

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

	void setRPM(int id,F32 v);
	F32 getSpeed(int id);

	F32 getDiffAngle(int id);

	void setAngle( int id,F32 rad_angle );
	F32 getAngle( int id );

private:

	F32 GetDiffPos(U8 id );
	

	can_base* p_can_base_;
	std::string str_type_;
	U32 i_baud_rate_;

	S32 a_v_;

	bool set_clear(U8 can_id);
	bool set_ctl_mode(U8 can_id, S16 state);
	bool set_ctl_word(U8 can_id, S16 state);
	bool set_v(U8 can_id,S32 v );
	bool set_a(U8 can_id,S32 a );


	bool send_sdo( int can_id ,U8 op, U8 index_low, U8 index_high, U8 sub_index, S32 data);
	bool send_pdo( int can_id , S32 data1, S32 data2);
	bool set_nmt_op();

private:
	void parse_can_data();
	std::map<int,S32> m_pos_;
	std::map<int,S32> m_last_pos_;
	std::map<int,F32> m_speed_;

	void print_can(SCanframe frame);
};

#endif//_CHASSIS_VSY27X_DRIVER_KYOSHO_2022_05_30_
