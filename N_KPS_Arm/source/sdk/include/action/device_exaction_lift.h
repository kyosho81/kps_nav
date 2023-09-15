#ifndef _DEVICE_EXACTION_LIFT_KYOSHO_20220711_
#define _DEVICE_EXACTION_LIFT_KYOSHO_20220711_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include "buffer_con.hpp"
#include "trans_dev/trans_dev.h"

#include "action/lift_control.h"

#include "action/device_exaction_base.h"

class device_exaction_lift : public device_exaction_base
{
public:

	device_exaction_lift();
	~device_exaction_lift();

	std::string get_para();

	bool init_sub_back( bool b_sim );

protected:
private:
	bool setPara( std::string name , std::string value );
	

	bool act_init();
	int act_doing( F32 dt );
	bool act_check();

// 	bool update_lift_level(const SFAI &fai);
// 	bool update_lift_zero(const SDI &di);
	
	

	int i_sub_lift_level_;
	std::string str_sub_lift_level_;
	int i_sub_lift_di_;
	std::string str_sub_lift_di_;
private:
	//task set
	F32 f_tar_lift_level_;
	F32 f_tar_lift_speed_;

	//current data
	F32 f_cur_lift_level_;
	F32 f_cur_lift_speed_;
	U8  u8_over_;
	U8  u8_zero_;
	U8  u8_emc_;

	F32 f_scale_;

// 	THSafe<F32> th_level_;
// 	THSafe<F32> th_speed_;
	//THSafe<int> th_set_zero_;
	bool b_set_zero_;
	//THSafe<int> th_over_;
	F32 level_zero_;
private:
	lift_control lift_control_;
public:
	bool pub_speed(F32 speed);
};

#endif //_DEVICE_EXACTION_LIFT_KYOSHO_20220711_