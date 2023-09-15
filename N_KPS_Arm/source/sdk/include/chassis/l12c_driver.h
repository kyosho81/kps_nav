#ifndef _CHASSIS_L12C_DRIVER_KYOSHO_2023_07_30_
#define _CHASSIS_L12C_DRIVER_KYOSHO_2023_07_30_

#include "TimerDiff.h"
#include "chassis/driver_base.h"

class can_base;

class cnts_4bit{

public:
	cnts_4bit(){
		i_count_ = 0;
	};
	~cnts_4bit(){};

	U8 get_cnt(){
		i_count_ = (i_count_++) & 0x0f;
		return i_count_;
	};

	U8 i_count_;
};

class l12c_driver : Driver_base
{
public:
	l12c_driver();
	~l12c_driver();

protected:

private:
	
	F32 st_reduction_ratio_;
	F32 wh_reduction_ratio_;

	U32 counts_;

	U32 one_wheel_counts_;


private://virtual customized :TODO
	void setPara(std::string name ,std::string value);

	bool init_driver();
	bool reset();

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

		

	bool set_lift_lowering( S8 speed ); //10ms 0x195
	cnts_4bit cnts_lift_lowering_;

	F32 rpm2mph( F32 rpm );
	F32 angle_diff_limit(F32 a_rad);
	
	bool set_angle_speed( F32 a_rad, F32 rpm);
	cnts_4bit cnts_angle_speed_;       //10ms 0x295
	F32 last_angle_;

	bool set_agw_state();   //40ms 495

	bool send_sdo( int can_id ,U8 op, U8 index_low, U8 index_high, U8 sub_index, S32 data);
	bool send_pdo( int can_id , S32 data1, S32 data2);
	bool sdo_read( S32 &date, int can_id , U8 index_low, U8 index_high, U8 sub_index );
	

	bool set_nmt_715(); //40ms
	bool get_max_mast(F32 &max_mast );//0x781

	bool set_node_safe(int can_id);

private:
	void parse_can_data();
	bool chk_node_safe();
	bool chk_node_701(int can_id);
	bool set_frame(SCanframe &frame);
	std::vector<SCanframe> frame_list_;

	bool sleep_10ms();
	
	S32 i_10ms_cnt_;
	bool b_send_40ms_;

	std::map<int,S32> m_node_safe_;
	std::map<int,S16> m_angle_;
	std::map<int,S16> m_speed_;
	

	int i_nmt_701_;
	F32 f_diameter_;

private:
	F32 f_speed_;
	F32 f_max_lift_speed_;
	F32 f_min_lift_speed_;
	THSafe<F32> th_lift_speed_;

private:
	F32 cov2speed(U16 i_speed);
	F32 conv2angle( U16 i_angle );
	F32 conv2per(U8 i_per);
	F32 f_bat_percent_;
	F32 f_wheel_speed_;
	F32 f_wheel_last_speed_;

	cTimerDiff dt_;
};

#endif//_CHASSIS_L12C_DRIVER_KYOSHO_2023_07_30_
