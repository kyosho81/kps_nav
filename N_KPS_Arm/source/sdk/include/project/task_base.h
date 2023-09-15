#ifndef _TASK_BASE_KYOSHO_20150906_
#define _TASK_BASE_KYOSHO_20150906_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "XmlRpc.h"
#include "Comm/TimerDiff.h"

#include "log/log_client.h"

#include "project/task_errcode.h"



class task_feadback
{
public:
	task_feadback();
	~task_feadback();

	void set_id(const int &task_id);
	void set_init_para(std::string str_init_para);
	void set_status(int status, std::string str_status);
	void set_uuid(std::string str_uuid);

	int get_task_id();
	std::string get_init_para();
	std::string get_str_status();
	int get_status();
	std::string get_str_uuid();

protected:
private:
	int task_id_;
	std::string str_init_para_;
	std::string str_status_;
	int status_;
	std::string str_uuid_;
};

class task_base
{
public:
	task_base();
	virtual ~task_base();

	void set_sim_module(bool b_sim_module);
	bool init( XmlRpc::XmlRpcValue& params , F32 do_time_diff_ms = 20);
	bool run_state_mechine();

	STASK_STA get_status();
	std::string get_str_status();

	
	void set_id(const int &i_id);
	int get_id();

	void get_feadback(task_feadback &task_fb);
	void force_complete();
	void redo();

	typedef enum{
		RES_CONTINUE = 0,
		RES_ERR = 1,
		RES_DONE = 2
	}TASK_RES;

protected:

	virtual bool check_init_para() = 0;
	virtual int do_set_task() = 0;
	virtual int do_check_set() = 0;
	virtual int do_check_done() = 0;
	virtual int do_force_done() = 0;
	virtual std::string get_para();

	XmlRpc::XmlRpcValue params_;
	XmlRpc::XmlRpcValue result_;

	

	STASK_STA task_status_;


	U64 set_error_code(const int &err_bit);
	U64 cls_error_code(const int &err_bit = -1);

	void set_sub_err_codde( const S32 &i_err_code);

	THSafe<bool> th_complete_;
	THSafe<bool> th_redo_;

	bool b_sim_module_;

private:
	int i_id_;
	std::string str_uuid_;
	//call sleep
private:

	F32 do_time_diff_ms_;
	cTimerDiff dt_;

	bool call_sleep();

protected:
	bool set_act_para(std::string str_name, std::string str_value);
	SAct_Base act_base_;
};

#endif//_TASK_BASE_KYOSHO_20150906_
