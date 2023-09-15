#ifndef _CHASSIS_MUSHINY_DRIVER_KYOSHO_2022_12_30_
#define _CHASSIS_MUSHINY_DRIVER_KYOSHO_2022_12_30_

#include "TimerDiff.h"
#include "chassis/driver_base.h"

class can_base;

typedef struct _Smushiny_bt
{

	U16 voltage_;
	U16 electricity_;
	U8  soc_;
	U8  soh_;
	U8  state_;
	U8  temperature_;

}Smushiny_bt;

class mushiny_driver : Driver_base
{
public:
	mushiny_driver();
	~mushiny_driver();

protected:

private:
	
	
	F32 reduction_ratio_;
	U32 counts_;

	U32 one_wheel_counts_;

	F32 rot_reduction_ratio_;
	F32 angle_reduction_ratio_;
	F32 lift_reduction_ratio_;
	F32 dis_reduction_ratio_;

	F32 rot_counts_;
	F32 lift_counts_;

	F32 liftspeed2rpm(F32 lift_speed);
	F32 rpm2liftspeed(F32 lift_rpm);
	F32 cnts2lift_level(S32 counts);
	S32 lift_level2cnts(F32 lift_level);

	F32 rotspeed2rpm(F32 rot_w_rad_s);
	F32 rpm2rotspeed(F32 rot_rpm);
	F32 cnts2rot_angle(S32 counts);
	S32 rot_angle2cnts(F32 rot_angle);

private://virtual customized :TODO
	void setPara(std::string name ,std::string value);

	bool init_driver();
	bool init_wheel();
	bool init_rot();
	bool init_lift();

	bool open_transfer_device();
	void close_driver();

	void setRPM(int id,F32 v);
	F32 getSpeed(int id);

	F32 getDiffAngle(int id);


	F32 getAngle( int id );


	bool set_can_init(int can_id, S32 ms_time );
	
	bool set_speed_mode(int can_id);
	bool set_pos_mode(int can_id);

private:

	F32 GetDiffPos(U8 id );
	

	can_base* p_can_base_;
	std::string str_type_;
	U32 i_baud_rate_;

	S32 a_v_;
	
	bool set_ctl_mode(U8 can_id, S16 state);
	bool set_ctl_word(U8 can_id, S16 state);
	bool set_v(U8 can_id,S32 v );
	bool set_rot(S32 a, S32 s );
	bool set_lift(S32 l, S32 s );
	
	bool check_sdo(int can_id);
	bool send_sdo( int can_id ,U8 op, U8 index_low, U8 index_high, U8 sub_index, S32 data);
	bool send_pdo( int can_id , S32 data1, S32 data2);
	bool sdo_read( S32 &date, int can_id , U8 index_low, U8 index_high, U8 sub_index );
	
	bool set_nmt_op();
	bool set_nmt_op(int can_id);
	bool set_nmt_close();
	bool set_nmt_close(int can_id);

	bool jump(int can_id);

	bool stop(int can_id);
	bool online(int can_id);
	bool faststop(int can_id);

	bool set_tpdo_syn(int can_id);
	bool set_tpdo_asyn(int can_id);
	bool set_prohibit_time(int can_id);
	bool set_event_time(int can_id,S32 ms_time);
	
	bool set_tpdo(int can_id,S32 ms_time);
	bool set_rpdo(int can_id);

	bool disable_tpdo1(int can_id);
	bool clear_tpdo1(int can_id);
	bool set_tpdo1_size(int can_id);
	bool set_tpdo1_01(int can_id);
	bool set_tpdo1_02(int can_id);
	bool set_tpdo1_03(int can_id);
	bool enable_tpdo1(int can_id);

	bool disable_tpdo2(int can_id);
	bool clear_tpdo2(int can_id);

	bool disable_tpdo3(int can_id);
	bool clear_tpdo3(int can_id);
	
	bool disable_tpdo4(int can_id);
	bool clear_tpdo4(int can_id);

	bool clear_rpdo_size(int can_id);
	bool set_rpdo_size(int can_id);

	bool disable_rpdo1(int can_id);
	bool clear_rpdo1(int can_id);
	bool disable_rpdo2(int can_id);
	bool clear_rpdo2(int can_id);
	bool disable_rpdo3(int can_id);
	bool clear_rpdo3(int can_id);
	bool disable_rpdo4(int can_id);
	bool clear_rpdo4(int can_id);

	bool set_rpdo_syn(int can_id);
	bool set_rpdo_asyn(int can_id);
	bool set_rpdo1_speed(int can_id);
	bool set_rpdo1_pos(int can_id);
	bool enable_rpdo1(int can_id);

	bool set_heart(int can_id);
	bool set_pos_threshold(int can_id);

	bool set_troque(int can_id, bool b_charge);
	bool set_consumer_heartbeat(int can_id);

	bool save_para(int can_id);

	
private:
	int i_do_battery_;
	int i_do_battery_cycle_;
	bool check_bt();
	bool send_bt();
	bool pub_bt();
	int i_send_;

public:
	bool pub_rot_lift();
	bool can_set_rot_lift();

private:
	void parse_can_data();
	std::map<int,S32> m_pos_;
	std::map<int,S32> m_last_pos_;
	std::map<int,F32> m_speed_;
	std::map<int,S16> m_state_;

	//battery
	Smushiny_bt battery_;
	THSafe<int> th_cnt_open_;

	std::string str_bt_cnt_out_;
	bool update_cnt_out(const int &bt_contact);

	
// 
// 	SBuffer<F32> th_rot_speed_;
// 	SBuffer<F32> th_rot_pos_;
// 	SBuffer<F32> th_level_speed_;
// 	SBuffer<F32> th_level_;

};

#endif//_CHASSIS_MUSHINY_DRIVER_KYOSHO_2022_12_30_
