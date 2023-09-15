#include <cassert>
#include <iostream>

#include "Comm/PortDef.h"
#include "Comm/Comm.h"
#include "trans_dev/trans_dev.h"
#include "Comm/TimerDiff.h"
#include "Comm/PortDef.h"
#include "Log4cppArm.hpp"
#include "log/Log4cppMsgIndex.h"
#include "interpro_shared/sh_pool.hpp"

#include "log/log_server.h"

#define TCP_LOG_SERVER_WRITER_BUFFER_MAX 2000
#define TCP_LOG_SERVER_THREAD_POOL_MIN_SIZE 1
log_singleton_server::log_singleton_server()
	:circular_log_total_(TCP_LOG_SERVER_WRITER_BUFFER_MAX)
{
	ilisten_port_ = LOG_PORT;
	p_tcp_svr_monitor_ = 0;
	p_tcp_svr_set_ = 0;

	b_pub_db_log_ = false;
}


log_singleton_server::~log_singleton_server()
{

}

void log_singleton_server::init_listen()
{
	cConnPara conn_para;
	conn_para.m_iType = cConnPara::NETWORK;
	conn_para.m_nNetType = cConnPara::TCPSERVER;
	conn_para.n_listen_port = LOG_MONITOR_PORT;

	p_tcp_svr_monitor_ = cTransferDevice::GetInstance(conn_para);

	conn_para.m_iType = cConnPara::NETWORK;
	conn_para.m_nNetType = cConnPara::TCPSERVER;
	conn_para.n_listen_port = LOG_MONITOR_PORT_SET;

	p_tcp_svr_set_ = cTransferDevice::GetInstance(conn_para);


	pt_log_.size_controller().resize(2);
	pt_client_.size_controller().resize(TCP_LOG_SERVER_THREAD_POOL_MIN_SIZE);
	sp_service_ = boost::shared_ptr<boost::asio::io_service>(new boost::asio::io_service);
	boost::shared_ptr<boost::asio::ip::tcp::endpoint> ep( new boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), ilisten_port_)); // listen on 7700
	sp_acc_ = boost::shared_ptr<boost::asio::ip::tcp::acceptor>( new boost::asio::ip::tcp::acceptor(*sp_service_, *ep));
	
	init_th_log();
	schedule(pt_log_, boost::bind(&log_singleton_server::th_log_set, this));

	//schedule(pt_access_, boost::bind(&log_singleton_server::th_accept, this));
	
	b_pub_db_log_ = true;
	std::cout<<"log_pub_db:"<<int(b_pub_db_log_)<<std::endl;
	
}
void log_singleton_server::run_once(){
	socket_ptr np_sock;
	np_sock = socket_ptr(new boost::asio::ip::tcp::socket(*sp_service_));
	sp_acc_->accept(*np_sock);
	v_sock_.push_back(np_sock);
	bool b_full = schedule(pt_client_, boost::bind(&log_singleton_server::th_client_session, this, np_sock));
	std::cout<<"tcp accept size:"<<pt_client_.pending()<<std::endl;
	if(pt_client_.pending() > 0){
		int inew_pool_size = pt_client_.active() + pt_client_.pending();
		pt_client_.size_controller().resize(inew_pool_size);
		std::cout<<"inew_pool_size:"<<inew_pool_size<<std::endl;
	}
	
	//std::cout<<"thread schedule ok!"<<int(b_full)<<std::endl;
}

void log_singleton_server::destruct()
{
	cConnPara ConnPara;
	p_tcp_svr_monitor_->GetPara(ConnPara);
	if (cTransferDevice::DelInstance(ConnPara))
	{
		p_tcp_svr_monitor_= 0;
	}
	p_tcp_svr_set_->GetPara(ConnPara);
	if (cTransferDevice::DelInstance(ConnPara))
	{
		p_tcp_svr_set_= 0;
	}

	th_irun_ = 0;
	th_irun2_ = 0;
	circular_log_total_.put("destruct \n");
	{
		boost::mutex::scoped_lock lock(mu_v_sock_);
		std::list<socket_ptr>::iterator it = v_sock_.begin();
		for ( ;it != v_sock_.end() ; ++it )
		{
			socket_ptr p = *it;
			if (p->is_open())
			{
				p->close();
			}

		}
	}
	

	pt_client_.clear();
	pt_client_.wait();

	pt_log_.clear();
	pt_log_.wait();

	v_sock_.clear();
	sp_acc_->close();
	m_pronm_sock_.clear();
	

	std::cout<<"log_server destruct over!"<<std::endl;
}

void log_singleton_server::th_accept(){
	socket_ptr np_sock;

	while ( th_irun_() ) {

		np_sock = socket_ptr(new boost::asio::ip::tcp::socket(*sp_service_));
		sp_acc_->accept(*np_sock);
		
//		boost::thread( boost::bind(&log_singleton_server::th_client_session, this, np_sock));
		//schedule(pt_client_, boost::bind(&log_singleton_server::th_client_session, this, np_sock));
		bool b_full = pt_client_.schedule(boost::bind(&log_singleton_server::th_client_session, this, np_sock));
		std::cout<<"thread schedule ok!"<<int(b_full)<<std::endl;
	}

}
bool log_singleton_server::merge_data(std::string &str_log,char* p_data,const int &ilen){
	// 3 status
	// 1: <head insert
	// 2: >end merge
	// 3: mid data

	std::string str = "";
	if (ilen < 1)
	{
		return false;
	}
	if (p_data[0] == CH_LOG_HEAD)
	{
		//whole body
		if (p_data[ilen - 1] == CH_LOG_TAIL) //62 '>'
		{
			cComm::Char2String(str,(U8*)(p_data));
			str_log = str;
			return true;
		}else{//only head
			
			cComm::Char2String(str,(U8*)(p_data));
			str_log += str;
	
			return false;
		}
	//only tail
	}else if(p_data[ilen - 1] == CH_LOG_TAIL){
	
		cComm::Char2String(str,(U8*)(p_data));
		str_log += str;

		return true;
	}else{//only body
	
		cComm::Char2String(str,(U8*)(p_data));
		str_log += str;
		return false;
	}

}
void log_singleton_server::th_client_session(socket_ptr sock) {
 	//std::cout<<"th_client_session thread id:"<<boost::this_thread::get_id()<<std::endl;
 	//std::cout<<"tcp accept size:"<<pt_client_.active()<<std::endl;
	
	//first get process name and priority
	std::string str_cmd ="get_priority \n";
	S8 ch_send[100] = {0};
	int isend = cComm::String2Charlist(ch_send,100,str_cmd);

	if(sock->is_open()){
		sock->write_some(boost::asio::buffer(ch_send,isend));
	}


	std::string str_merge_str = "";
	std::string str_pro_nm = "";

	char data[MAX_TCP_LOG_DATA_SIZE] = {0};
	std::string str_log = "";
	while ( sock->is_open()) {

		boost::system::error_code ec;
		size_t len = sock->read_some(boost::asio::buffer(data),ec);

		if(ec){
			//std::cout<<boost::system::system_error(ec).what()<<std::endl;
			break;
		}
		if ( (len > 0 ) && (len < MAX_TCP_LOG_DATA_SIZE))
		{
			if (merge_data(str_log,data,len))
			{
				

				if ( "<#" == str_log.substr(0,2))
				{
					std::vector<std::string> v_str;
					cComm::SplitString(str_log,"#",v_str);

					int ipriority = log4cpp::Priority::INFO;
					

					cComm::ConvertToNum(ipriority,v_str[2].substr(0,v_str[2].find(">",0)));
					str_pro_nm = v_str[1];
					m_pronm_priority_[ str_pro_nm ] = ipriority;
					m_pronm_sock_[ str_pro_nm ] = sock;

				}
				else{
					circular_log_total_.put(str_log);
				}
				
				str_log = "";
			}
			memset(data,0,len);
		}

		//write(*sock, buffer("ok", 2));
	}
	boost::mutex::scoped_lock lock(mu_v_sock_);
	std::list<socket_ptr>::iterator it = std::find(v_sock_.begin(),v_sock_.end(),sock);
	if(it != v_sock_.end()){
		v_sock_.erase(it);
	}
	std::map<std::string,socket_ptr>::iterator it2 = m_pronm_sock_.find(str_pro_nm);
	if (it2 != m_pronm_sock_.end())
	{
		m_pronm_sock_.erase(it2);
	}
	
	//std::cout<<"log_singleton_server::th_client_session thread closed!!!"<<std::endl;
}

void log_singleton_server::th_log_pro()
{
	th_irun_ = 1;

	std::string str_log_name = cTimerDiff::get_file_now();
	str_log_name = ".//log_data//" + str_log_name + ".log";
	std::cout<<"create log file!"<<str_log_name<<std::endl;

	std::ofstream of(str_log_name,std::ios::trunc | std::ios::binary);
	if (!of.is_open())
	{
		std::cout<<">>>>>>>>>>>>>>>>>>>>create log file err!"<<str_log_name<<std::endl;
		
	}
	std::string str_log;
	U8* p_send = 0;//new U8[MAX_TCP_LOG_DATA_SIZE];
	//assert(p_send);
	int i_send = 0;
	
	while (th_irun_())
	{
		circular_log_total_.get(str_log);
		

		if (of.is_open()){
			of<<str_log<<std::endl;
		}
		pub_db_log(str_log);

		if(p_tcp_svr_monitor_ && p_tcp_svr_monitor_->m_Status.IsOpen())
		{
			cComm::String2Char(p_send,i_send,str_log);
			if (i_send > MAX_TCP_LOG_DATA_SIZE)
			{
				i_send = MAX_TCP_LOG_DATA_SIZE;
			}
			p_tcp_svr_monitor_->WriteData(p_send,i_send);
		}
		//std::cout<<str_log<<std::endl;
	}
	of.close();
	th_irun_ = -1;
	std::cout<<"th_log_pro end"<<std::endl;
}
void log_singleton_server::init_th_log()
{
	
	schedule(pt_log_, boost::bind(&log_singleton_server::th_log_pro, this));
}
void log_singleton_server::destruct_th_log(){
	th_irun_ = 0 ;
	circular_log_total_.put("destruct_th_log \n");
	while( th_irun_() != -1){
		SLEEP(100);
	}
	circular_log_total_.clear();
}
std::string log_singleton_server::get_all_priority(){
	std::stringstream ss;
	ss<<"#";
	std::map<std::string,log4cpp::Priority::Value>::iterator it2 = m_pronm_priority_.begin();
	for ( ; it2 != m_pronm_priority_.end() ; ++it2 )
	{
		ss<<it2->first<<" "<<log_msg_index::index_to_str_pri(it2->second)<<"#";
	}
	return ss.str();
}
void log_singleton_server::th_log_set()
{
	U8* p_rec = new U8[MAX_TCP_LOG_DATA_SIZE];
	memset(p_rec,0,MAX_TCP_LOG_DATA_SIZE);
	S8 ch_send[100] = {0};
	assert(p_rec);
	assert(ch_send);
	int i_rec = 0;
	int i_send = 0;

	std::cout<<"th_log_set() begin"<<std::endl;
	th_irun2_ = 1;

	std::string str_rec_cmd;
	std::string str_send_cmd;
	while (th_irun2_())
	{
		if(p_tcp_svr_set_ && p_tcp_svr_set_->m_Status.IsOpen())
		{
			
			p_tcp_svr_set_->ReadData(p_rec,i_rec,20,200);
			str_rec_cmd = (char*)p_rec;
			
			if ( i_rec < 1)
			{
				continue;
			}
			memset(p_rec,0,i_rec);
			
	
			std::vector<std::string> v_cmd;
			cComm::SplitString(str_rec_cmd," ",v_cmd);
			if (v_cmd.size() > 0)
			{
				str_rec_cmd = v_cmd[0]; 
			}
			
			if( "get_all_priority" == str_rec_cmd ){
				
				str_send_cmd = "get_priority \n";
				memset(ch_send,0,100);
				i_send = cComm::String2Charlist(ch_send,100,str_send_cmd);

				std::map<std::string,socket_ptr>::iterator it = m_pronm_sock_.begin();
				for ( ; it != m_pronm_sock_.end() ; ++it ){
					it->second->write_some(boost::asio::buffer(ch_send,i_send));
				}

				str_send_cmd = get_all_priority();
				memset(ch_send,0,100);
				i_send = cComm::String2Charlist(ch_send,100,str_send_cmd);
				if ( i_send > 0)
				{
					p_tcp_svr_set_->WriteData((U8*)ch_send,i_send);
				}
				

			}else if( "set_priority" == str_rec_cmd){

				if ( v_cmd.size() > 2)
				{
	

					std::stringstream ss;
					ss<<"set_priority "<<v_cmd[2];
					memset(ch_send,0,100);
					i_send = cComm::String2Charlist(ch_send,100,ss.str());

 					std::map<std::string,socket_ptr>::iterator it = m_pronm_sock_.find(v_cmd[1]);
 					if ( it != m_pronm_sock_.end() )
 					{
 						it->second->write_some(boost::asio::buffer(ch_send,i_send));
 					}

				}

			}else if( "save_log" == str_rec_cmd){
				std::cout<<"save_log"<<std::endl;
				destruct_th_log();
				init_th_log();
			}

		}else{
			SLEEP(200);
		}
	}
	th_irun2_ = -1;
}

bool log_singleton_server::pub_db_log(const std::string &str_log)
{
	if (!b_pub_db_log_){
		return false;
	}

	std::stringstream ss;
	ss<<cTimerDiff::total_ms();
	U8* data = 0; 
	int ilen = 0;
	cComm::String2Char(data,ilen,str_log);
	if ( !data || ilen < 1){
		delete[] data;
		data = 0;
		std::cout<<"log_singleton_server::pub_db_log err:"<<str_log<<std::endl;
		return false;
	}
	
	if(!pipe_shared_pool::push_back( PUB_PIPE_LOG, ss.str() , data, ilen ,false )){
		std::cout<<"pub_view_data pub  err!"<<std::endl;
		delete[] data;
		data = 0;
		return false;
	}
	delete[] data;
	data = 0;
	return true;
}






