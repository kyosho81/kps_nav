#ifndef _TASK_OPEN_CTL_KYOSHO_20150906_
#define _TASK_OPEN_CTL_KYOSHO_20150906_

#include <map>

#include "protobuf_msg/protobuf_seg_path.h"
#include "device/amcl_tf.h"

#include "project/task_base.h"

class task_open_ctl : public task_base
{
public:
	task_open_ctl();
	~task_open_ctl();

	

protected:

//task_base 
private:

	bool check_init_para();
	int do_set_task();
	int do_check_set();
	int do_check_done();
	int do_force_done();
	std::string get_para();

	//call back
private:
	bool update_mv_status( const SRunStatus &sta );
	bool s_update_odom(const SOdomSpeed& new_odom);
	bool s_update_bt_contactor_in(const int& bt_contact);

private:

	bool pub_speed(const SSpeed &speed);
	
	SPos target_pos_;
	SSpeed speed_;
	std::string str_obs_io_;

	THSafe<SRunStatus> th_mv_status_;
	THSafe<SPos> ths_open_pos_;
	THSafe<SOdomSpeed> ths_odom_;
	THSafe<int> ths_contactor_in_;
	amcl_tf merge_odom_tf_;
	
private:
	void init_max_do(int i_do_max);
	bool check_max_do();

	int i_do_cnt_;
	int i_do_max_;

private:
	bool check_close_to();
	bool check_contact();

private:
	int i_sub_id_runstatus_;
	int i_sub_id_odom_;
};

#endif//_TASK_OPEN_CTL_KYOSHO_20150906_
