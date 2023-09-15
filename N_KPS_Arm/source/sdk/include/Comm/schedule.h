#ifndef _SCHEDULE_KYOSHO_20110903_
#define _SCHEDULE_KYOSHO_20110903_


#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

class rpc_config_client;

typedef struct _SDT 
{

	std::string str_time_from_;
	std::string str_time_to_;
	int i_week_;

}SDT;

class pschedule
{
public:
	pschedule();
	~pschedule();


	typedef enum{
		WEEK_SUN = 0,
		WEEK_MON,
		WEEK_TUE,
		WEEK_WEN,
		WEEK_THU,
		WEEK_FIR,
		WEEK_STA
	}eWEEK;

	typedef enum{
		SCHE_NONE,
		SCHE_PARK,
		SCHE_CHARGE,	
		SCHE_WANDER,
	}eTASK;

	void init(rpc_config_client* cfg_rpc);
	bool check_schedule(eTASK task_type);

private:
	std::multimap<eTASK,SDT> mt_sdt_;
	void set_week_bit(int &i_week, eWEEK week);
	void cls_week_bit(int &i_week, eWEEK week);
	bool chk_week_bit(int i_week, eWEEK week);

	bool check_on_duty( int i_week, boost::posix_time::ptime pt, const SDT &sdt);
	bool insert_schedule( eTASK task_type , SDT sdt );

	bool decode(std::string str);
};

#endif // _SCHEDULE_KYOSHO_20110903_
