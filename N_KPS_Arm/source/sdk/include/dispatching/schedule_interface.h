#ifndef _SCHEDULE_INTERFACE_WANGHONGTAO_20151230_
#define _SCHEDULE_INTERFACE_WANGHONGTAO_20151230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>
#include "buffer_con.hpp"

#include "RobotStruct.h"

#include "schedule_interface_data.h"

class schedule_interface
{
public:
	schedule_interface();
	~schedule_interface();

	void init();
	schedule_interface_data* new_schedule_rules();
	bool insert_schedule_rules(std::vector<schedule_interface_data*> &v_si_data);

	bool del_schedule_rules(int i_index);

	void clear();

	schedule_interface_data* load_test();

	bool load_file(std::string str_file);
	bool save_file(std::string str_file);

	std::map<int,schedule_interface_data*> get_schedule_list();

	std::string match_carry_type(std::string type1,std::string type2);

	
	//


protected:
private:
	int get_rule_index();
	std::map<int,schedule_interface_data*> m_schedule_list_;

	boost::shared_mutex mu_read_write_sch_list_;
	typedef boost::shared_lock<boost::shared_mutex> read_lock;
	typedef boost::unique_lock<boost::shared_mutex> write_lock;
};

typedef boost::serialization::singleton<schedule_interface> Singleton_Sche_Factory;
#define STRATEGY_FACTORY Singleton_Sche_Factory::get_mutable_instance()


#endif//_SCHEDULE_INTERFACE_WANGHONGTAO_20151230_
