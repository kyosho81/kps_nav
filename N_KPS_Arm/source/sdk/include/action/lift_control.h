#ifndef _LIFT_CONTROL_KYOSHO_20220711_
#define _LIFT_CONTROL_KYOSHO_20220711_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include "buffer_con.hpp"
#include "trans_dev/trans_dev.h"



typedef enum 
{
	LIFT_ACT_IDLE        = 0,
	LIFT_ACT_DOING       = 1,
	LIFT_ACT_DONE        = 2,
	LIFT_ACT_CHECK       = 3,
	LIFT_ACT_ERROR   	 = 4,
	LIFT_ACT_EMC     	 = 5
}Enu_LiftState;

class lift_control
{
public:
	lift_control();
	~lift_control();


	bool init( F32 f_tar_lift_level, F32 f_tar_lift_speed );

	int ctl_loop( F32 dt, F32 f_cur_lift_level, F32 f_cur_lift_speed, U8 u8_emc_);
	bool bind_pub(boost::function<bool(F32 speed)> fnc_pub);

	F32 f_level_sim_;
	F32 f_speed_sim_;

	F32 f_level_min_err_;

protected:
private:
	//task set
	F32 f_tar_lift_level_;
	F32 f_tar_lift_speed_;

	F32 f_max_speed_;
	F32 f_min_speed_;

	F32 f_max_level_;
	F32 f_min_level_;

	
	

	F32 area_b_;            //speed cut area
	F32 area_c_;            //speed slow area

	F32 v_acc_;
	F32 v_dec_;

	Enu_LiftState state_;

	F32 doing_total_time_;

private:
	boost::function<bool(F32 speed)> fnc_pub_;

	F32 set_speed( F32 dt, F32 set_v ,F32 cur_v );

	void set_sta( Enu_LiftState sta );
	
	int i_cnt_do_;

	F32 get_tar_speed( F32 f_cur_lift_level );

	void sim_level(  F32 dt, F32 set_v );
	
};

#endif //_LIFT_CONTROL_KYOSHO_20220711_