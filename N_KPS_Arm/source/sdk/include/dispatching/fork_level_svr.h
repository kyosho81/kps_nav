#ifndef _FORK_LEVEL_WANGHONGTAO_20220303_
#define _FORK_LEVEL_WANGHONGTAO_20220303_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"
#include "RobotStruct.h"


#define UNLOAD_FORK_LEVEL "unload_fork_level"
#define GET_BEFORE_LEVEL "get_before_level"
#define GET_OVER_LEVEL "get_over_level"
#define LOADING_FORK_LEVEL "loading_fork_level"
#define PUT_BEFORE_LEVEL "put_before_level"
#define PUT_OVER_LEVEL "put_over_level"

class fork_level_svr
{
public:
	fork_level_svr();
	~fork_level_svr();

	void init();

	std::string get_unload_level();
	std::string get_loading_level();
	std::string get_before_level();
	std::string get_over_level();
	std::string put_before_level();
	std::string put_over_level();

	std::string get_level(std::string str_type);

protected:
private:
	std::map<std::string,std::string> m_str_level_;
};

typedef boost::serialization::singleton<fork_level_svr> Singleton_Fork_Lev_Factory;
#define FORK_LEV_SVR Singleton_Fork_Lev_Factory::get_mutable_instance()

#endif//_FORK_LEVEL_WANGHONGTAO_20220303_
