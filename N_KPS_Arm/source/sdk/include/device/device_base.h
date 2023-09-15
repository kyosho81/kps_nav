#ifndef _DEVICE_BASE_KYOSHO_20180401_
#define _DEVICE_BASE_KYOSHO_20180401_


#include <string>
#include <map>
#include <boost/thread.hpp>

#include "RobotStruct.h"
#include "Comm/buffer_con.hpp"
#include "TimerDiff.h"
#include "robot/dio_manage.h"

class device_base{
public:

	device_base();
	virtual ~device_base();

	//interface init
	bool init( std::string para  );
	int get_dev_ID(SDevStatus &sta);
	std::string get_dev_name();

	void setPara(std::string str_para);
	virtual std::string get_para();

	std::string prt_dev();

protected:
	U16 ms_loop_;

	virtual bool setPara(std::string name , std::string value);
	virtual bool fnc_init() = 0;
	virtual bool fnc_run()= 0;
	virtual bool fnc_recovery()= 0;

	bool fnc_to_err(U16 err_code);

	virtual bool onInit() = 0;
	//do err 
	virtual bool toErr(U16 err_code) = 0;

	void set_err_code(eDEV_ERR_CODE err_code);
	void clr_err_code(eDEV_ERR_CODE err_code);
	void clr_err_code();

	void stop();

private:

	

	void run(int ms_loop);
	
	void thread_loop();

private:

	U32  err_count_;
	U32  max_err_count_;

	void init_health();
	bool check_health();

private:
	bool thread_run_;
	
	cTimerDiff dt_;

	SDevStatus status_;

	void clear_err();
	void st_to_error(const U16 err_code);

private:
	std::string device_name_;
	static int device_id_;
	static boost::mutex mu_dev_id_;
	static int get_new_id();
	static void set_id( int device_id );
	THSafe<SDevStatus> th_status_;

protected:

	std::map<std::string, SDIAI> m_di_ai_;
	std::map<std::string, SAIF> m_fai_;
};

#endif //_DEVICE_BASE_KYOSHO_20180401_