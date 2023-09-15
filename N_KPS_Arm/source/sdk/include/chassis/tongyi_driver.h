#ifndef _CHASSIS_TONGYI_DRIVER_KYOSHO_2022_12_30_
#define _CHASSIS_TONGYI_DRIVER_KYOSHO_2022_12_30_

#include "TimerDiff.h"
#include "chassis/driver_base.h"

class can_base;


class tongyi_driver : Driver_base
{
public:
	tongyi_driver();
	~tongyi_driver();

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
	bool reset_driver();

	void setRPM(int id,F32 v);
	F32 getSpeed(int id);

	F32 getDiffAngle(int id);

	void setAngle( int id,F32 rad_angle );
	F32 getAngle( int id );

	bool set_wheel_pdo(int can_id);
	bool set_steer_pdo(int can_id);

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
	bool set_v(U8 can_id,F32 v );
	bool set_a( U8 can_id,F32 a );

	bool send_sdo( int can_id ,U8 op, U8 index_low, U8 index_high, U8 sub_index, S32 data);
	bool send_pdo( int can_id , S32 data1, S32 data2);
	bool sdo_read( S32 &date, int can_id , U8 index_low, U8 index_high, U8 sub_index );
	
	bool set_nmt_op();
	bool set_nmt_reset(int can_id);
	bool set_nmt_preop();
	bool set_nmt_op(int can_id);
	bool set_nmt_close();
	bool set_nmt_close(int can_id);
	bool set_nmt_700(int can_id);

	bool jump(int can_id);

	bool stop(int can_id);
	bool online(int can_id);
	bool faststop(int can_id);

	bool set_tpdo_syn(int can_id);
	bool set_tpdo_asyn(int can_id);
	bool set_prohibit_time(int can_id);
	bool set_event_time(int can_id);
	
	bool set_tpdo_wheel(int can_id);
	bool set_rpdo_wheel(int can_id);

	bool set_tpdo_steer(int can_id);
	bool set_rpdo_steer(int can_id);

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

	//bool clear_rpdo_size(int can_id);
	bool set_rpdo_size(int can_id, int i_size);

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
	bool set_rpdo1_steer(int can_id);
	bool set_rpdo2_steer(int can_id);
	bool enable_rpdo1(int can_id);

	bool set_heart(int can_id);
	bool set_pos_threshold(int can_id);

	bool set_troque(int can_id, bool b_charge);
	bool set_consumer_heartbeat(int can_id);
	bool cls_consumer_heartbeat(int can_id);
	bool set_pos_speed(int can_id , int i_rpm);
	bool set_wheel_speed(int can_id , int i_rpm);

	bool set_node_safe(int can_id);

	bool save_para(int can_id);

	bool clear_error(int can_id);


	
private:
	void parse_can_data();
	bool chk_node_safe();
	bool chk_node_701(int can_id);

	S64 i_time_stamp_;
	std::map<int,S64> m_node_701_;
	std::map<int,S32> m_node_safe_;
	std::map<int,S32> m_pos_;
	std::map<int,S32> m_last_pos_;
	std::map<int,F32> m_speed_;

	int i_nmt_701_;

};

#endif//_CHASSIS_TONGYI_DRIVER_KYOSHO_2022_12_30_
