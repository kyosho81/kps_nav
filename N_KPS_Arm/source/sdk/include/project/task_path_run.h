#ifndef _TASK_RUN_PATH_KYOSHO_20150906_
#define _TASK_RUN_PATH_KYOSHO_20150906_

#include <map>

#include "protobuf_msg/protobuf_seg_path.h"

#include "project/task_base.h"

class task_path_run : public task_base
{
public:
	task_path_run();
	~task_path_run();

	bool update_mv_status( const SRunStatus &sta );
	
	//void set_sub_id_runstatus( const int &runstatus );


protected:

//task_base 
private:

	bool check_init_para();
	int do_set_task();
	int do_check_set();
	int do_check_done();
	int do_force_done();
	std::string get_para();

private:
	void pnt_paht_data(const SPathData &pdata);
	bool pub_path_run();
	
	//protobuf_seg_path p_seg_path_;
	std::vector<SPathData> seg_path_;

	THSafe<SRunStatus> th_mv_status_;

	int i_pub_cnt_;

private:
	int i_sub_id_runstatus_;
};

#endif//_TASK_RUN_PATH_KYOSHO_20150906_
