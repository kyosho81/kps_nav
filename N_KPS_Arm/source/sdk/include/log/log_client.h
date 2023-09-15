#ifndef _KPS_ARM_KYOSHO_LOG_CLIENT_SINGLETON_H_
#define _KPS_ARM_KYOSHO_LOG_CLIENT_SINGLETON_H_


#include <boost/serialization/singleton.hpp>

#include "Comm/MyDefine.h"
#include "buffer_con.hpp"
#include "log/LocalIp.hpp"
#include "Log4cppArm.hpp"

class cTransferDevice;

class log_singleton_cinit
{
public:
	log_singleton_cinit();
	~log_singleton_cinit();

	bool init(std::string str_log_nm);
	bool init(int argc, char *argv[]);
	void set_priority(log4cpp::Priority::Value priority);
	log4cpp::Priority::Value get_priority();

	void destroy();

	CategoryStream get_log_info();
	CategoryStream get_log_debug();
	CategoryStream get_log_error();
	CategoryStream get_log_warn();

protected:
private:

	std::string str_ip_;
	std::string str_prc_name_;
	int i_log_port_;
	void log_call( std::string str, Priority::Value val, TimeStamp time);
	cTransferDevice* p_tcp_client_;
	
	bool b_set_run_;
	void init_set_th();
	void th_call_set();


	bool b_send_run_;
	void init_send_th();
	int packet_send(U8* &p_data,int &ilen,std::string str);
	void th_call_send();

	CBuffer<std::string> circular_send_;

};




typedef boost::serialization::singleton<log_singleton_cinit> Singleton_Log_Client;
#define TCP_LOG Singleton_Log_Client::get_mutable_instance()
#define TCP_LOG_INFO Singleton_Log_Client::get_mutable_instance().get_log_info()
#define TCP_LOG_DEBUG Singleton_Log_Client::get_mutable_instance().get_log_debug ()
#define TCP_LOG_ERROR Singleton_Log_Client::get_mutable_instance().get_log_error()
#define TCP_LOG_WARN Singleton_Log_Client::get_mutable_instance().get_log_warn()

#endif//_KPS_ARM_KYOSHO_LOG_CLIENT_SINGLETON_H_
