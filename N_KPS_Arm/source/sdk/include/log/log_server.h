#ifndef _KPS_ARM_KYOSHO_LOG_SERVER_SINGLETON_H_
#define _KPS_ARM_KYOSHO_LOG_SERVER_SINGLETON_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"
#include "threadpool/threadpool.hpp"

#include "Log4cppArm.hpp"



class cTransferDevice;

class log_singleton_server
{
public:
	log_singleton_server();
	~log_singleton_server();

	void init_listen();
	void run_once();
	void destruct();
	//tcp server
private:

	typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
	boost::shared_ptr<boost::asio::io_service> sp_service_;
	boost::shared_ptr<boost::asio::ip::tcp::acceptor> sp_acc_;
	boost::mutex mu_v_sock_;
	std::list<socket_ptr> v_sock_;

private:
	void th_accept();
	void th_client_session(socket_ptr sock);
	void th_log_pro();
	void th_log_set();
	void init_th_log();
	void destruct_th_log();

	bool merge_data(std::string &str_log,char* p_data,const int &ilen);
	std::string get_all_priority();
	
	bool pub_db_log(const std::string &str_log);
	bool b_pub_db_log_;

	cTransferDevice* p_tcp_svr_monitor_;
	cTransferDevice* p_tcp_svr_set_;

	int ilisten_port_;
	boost::threadpool::pool pt_log_;
	boost::threadpool::pool pt_client_;

	CBuffer<std::string> circular_log_total_;
	THSafe<int> th_irun_;
	THSafe<int> th_irun2_;

	//process name priority
	std::map<std::string,log4cpp::Priority::Value> m_pronm_priority_;
	std::map<std::string,socket_ptr> m_pronm_sock_;
};



typedef boost::serialization::singleton<log_singleton_server> Singleton_Log_Server;
#define TCP_LOG_SERVER Singleton_Log_Server::get_mutable_instance()

#endif//_KPS_ARM_KYOSHO_LOG_SERVER_SINGLETON_H_
