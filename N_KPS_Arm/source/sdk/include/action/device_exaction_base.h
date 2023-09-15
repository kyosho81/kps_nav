#ifndef _DEVICE_EXACTION_BASE_KYOSHO_20180401_
#define _DEVICE_EXACTION_BASE_KYOSHO_20180401_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include "buffer_con.hpp"
#include "trans_dev/trans_dev.h"
#include "dispatching/act_trigger.h"
#include "Comm/TimerDiff.h"

#include "device/device_base.h"



class device_exaction_base : public device_base {

public:

	device_exaction_base();
	virtual ~device_exaction_base();

	virtual bool setPara( std::string name , std::string value );
	void set_mv_sta(const SRunStatus &sta);
	void set_run_path( std::string name,U8* data,U32 len );
	void set_heart_beat(const SHeartBeat &hb);

	bool setPara_list( std::string str_para);
	virtual std::string get_para();
	
	virtual bool init_sub_back( bool b_sim ) = 0;

private:


	bool fnc_init();
	bool onInit();
	
	bool toErr(U16 err_code);
	bool fnc_run();
	bool fnc_recovery() ;


protected:

	void set_action_name(std::string str_atcname);
	std::string get_action_nm();

	std::string str_atcname_;
	bool b_sim_;

private:

	THSafe<Enu_AState> th_act_sm_;
	void st_to_error(const U16 err_code);
	SActStatus act_state_;

private:
	bool sub_msg();
	bool s_act_para(const SAct_Para &action_para);
	
	int i_sub_act_para_;
	std::string str_sub_act_para_;

	
private:
	SAct_Base act_base_;
	bool set_para(std::string str_para);
	void pub_act_state();
	THSafe<SHeartBeat> th_hearbeat_;

private:
	act_trigger act_trigger_;
	cTimerDiff dt_;

private:
	virtual bool act_init();
	virtual int act_doing( F32 dt );
	virtual bool act_check();
};


#endif //_DEVICE_EXACTION_BASE_KYOSHO_20180401_