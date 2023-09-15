#ifndef _TASK_ACTION_WANGHOGNTAO_20220711_
#define _TASK_ACTION_WANGHOGNTAO_20220711_

#include <map>

#include "protobuf_msg/protobuf_seg_path.h"

#include "project/task_base.h"

class task_action : public task_base
{
public:
	task_action();
	~task_action();


protected:

//task_base 
private:

	bool check_init_para();
	int do_set_task();
	int do_check_set();
	int do_check_done();
	int do_force_done();
	

private:
	std::string str_act_name_;
	SAct_Para action_para_;
	int i_pub_cnt_;

private:

	void sub_msg();
	void pub_set_idle();

	THSafe<SActStatus> th_act_state_;
	bool s_act_state(const SActStatus &act_state);
	std::string str_sub_status_;
	int i_sub_status_ ;
};

#endif//_TASK_ACTION_WANGHOGNTAO_20220711_
