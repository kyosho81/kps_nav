#ifndef _DEVICE_EXACTION_CHARGE_KYOSHO_20220711_
#define _DEVICE_EXACTION_CHARGE_KYOSHO_20220711_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include "buffer_con.hpp"
#include "trans_dev/trans_dev.h"

#include "action/fork_control.h"

#include "action/device_exaction_base.h"

class device_exaction_charge : public device_exaction_base
{
public:

	device_exaction_charge();
	~device_exaction_charge();

	std::string get_para();
	bool init_sub_back( bool b_sim );

protected:
	//from parent
private:
	bool setPara( std::string name , std::string value );

	bool act_init();
	int act_doing( F32 dt );
	bool act_check();

private:
	bool update_bt_state(const SBattery &bt_state);
	int i_sub_battery_;
	SBuffer<SBattery> th_bt_state_;

	int i_error_;
	F32 cnt_time_;
	bool pub_set_charge_out( int i_charge_out );
private://sim value

	U8 v_bt_con_in_;
};

#endif //_DEVICE_EXACTION_CHARGE_KYOSHO_20220711_