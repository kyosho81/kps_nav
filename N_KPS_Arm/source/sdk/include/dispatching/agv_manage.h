#ifndef _AGV_MANAGE_WANGHONGTAO_KYOSHO_20200912_
#define _AGV_MANAGE_WANGHONGTAO_KYOSHO_20200912_

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <ctime>
#include <map>

#include <boost/lexical_cast.hpp>
#include <boost/serialization/singleton.hpp>
#include "boost/unordered/unordered_map.hpp"


#include "threadpool/threadpool.hpp"

#include "Comm/Comm.h"
#include "Comm/TimerDiff.h"
#include "Comm/configs.h"

#include "buffer_con.hpp"

#include "network.h"

class agv_base;


class agv_manage
{
public:
	agv_manage();
	~agv_manage();

	void init();
	void search_online_agv();

	void destruct();

	void do_agv_sm(int set_heartbeat , int set_sim_speed);
	int get_agv_status(std::map<int,SAGV_Info> &m_agv_status);
	int get_agv_info(std::map<int,SRobot_Inf> &m_robot_inf);
	int get_agv_run_path(std::map<int,std::list<SPathData>> &m_run_path);
	int get_agv_shape(std::map<int,std::vector<SVec>> &m_robot_shape);
	int get_agv_lock_pause(std::map<int,std::pair<int,int>> &m_lock_pause);
	int get_agv_ex_data(std::map<int,SAct_Fork> &m_ex_data);
	/////dispatch agv 
	int get_free_agv( std::map<int,SRobot_Inf> &m_robot_inf );
	bool get_free_agv( int i_agv_id );
	
	agv_base* get_agv(int id);
	agv_base* get_agv(std::string str_ip);

	bool set_agv_lock(  int i_id , int i_lock );
	bool check_agv_unlock( int i_id );
	
	int get_pack_agv(std::map<int,SRobot_Inf> &m_robot_inf);
	int get_charge_agv(std::map<int,SRobot_Inf> &m_robot_inf);

	bool offline_agv(const int &id);
	bool set_agv_init(const int &id);

private:

	std::map<int, SAGV_Info> m_agv_info_;
	std::map<int, SRobot_Inf> m_run_inf_;
	std::map<int,std::list<SPathData>> m_run_path_;
	std::map<int,std::vector<SVec>> m_robot_shape_;
	std::map<int,std::pair<int,int>> m_lock_pause_;
	std::map<int,SAct_Fork> m_ex_data_;

	net_work nw_;
	
	boost::threadpool::pool pt_regist_agv_;

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

	bool check_integrity(SAGV_Info &agv_info ,UData_buffer<U8,1024> &cmd_buffer, char* p_data,int ilen);

	THSafe<int> th_irun_;

private:
	agv_base* check_exist(std::string str_ip,int iport);
	agv_base* regist_agv(const SAGV_Info &agv_info);
	bool offline_agv(const SAGV_Info &agv_info);
	

	int i_agv_id_all_;

	boost::shared_mutex mu_read_write_agv_list_;
	typedef boost::shared_lock<boost::shared_mutex> read_lock;
	typedef boost::unique_lock<boost::shared_mutex> write_lock;

	std::map<int,agv_base*> m_id_agv_;
	std::map<std::string,agv_base*> m_ip_agv_;

private:
	
	bool get_agv_info(SAGV_Info &agv_inf, int id);
	bool get_robot_inf(SRobot_Inf &robot_inf, int id );
};

typedef boost::serialization::singleton<agv_manage> Singleton_Agv_Manage;
#define AGV_MANAGE Singleton_Agv_Manage::get_mutable_instance()

#endif //_AGV_MANAGE_WANGHONGTAO_KYOSHO_20200912_
