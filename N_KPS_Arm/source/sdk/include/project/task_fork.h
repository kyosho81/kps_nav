#ifndef _TASK_FORK_KYOSHO_20150906_
#define _TASK_FORK_KYOSHO_20150906_

#include <map>

#include "protobuf_msg/protobuf_seg_path.h"

#include "project/task_base.h"

class task_fork : public task_base
{
public:
	task_fork();
	~task_fork();


protected:

//task_base 
private:

	bool check_init_para();
	int do_set_task();
	int do_check_set();
	int do_check_done();
	int do_force_done();
	

private:

	SAct_Fork fork_para_;
	int i_pub_cnt_;

private:
	THSafe<SActStatus> th_act_state_;
	bool s_fork_state(const SActStatus &act_state);
	int i_sub_forkstatus_;
};

#endif//_TASK_FORK_KYOSHO_20150906_
