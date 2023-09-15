#include <cassert>
#include <iostream>

#include "Comm/PortDef.h"
#include "Comm/Comm.h"
#include "interface/cfg.hpp"
#include "trans_dev/trans_dev.h"
#include "Comm/TimerDiff.h"
#include "Log4cppArm.hpp"
#include "log/Log4cppMsgIndex.h"

#include "log/log_client.h"

#define CIRCLUAR_BUFFER_SEND 100

log_singleton_cinit::log_singleton_cinit():circular_send_(CIRCLUAR_BUFFER_SEND)
{
	str_ip_ = "127.0.0.1";
	str_prc_name_ = "default process name";
	p_tcp_client_ = 0;
	i_log_port_ = LOG_PORT;

	b_set_run_ = false;
	b_send_run_ = false;

}

log_singleton_cinit::~log_singleton_cinit()
{
	
}

bool log_singleton_cinit::init(int argc, char *argv[])
{
	str_prc_name_ = argv[0];
	str_prc_name_ = cComm::Get_FileName(str_prc_name_);

	return init(str_prc_name_);
}
bool log_singleton_cinit::init(std::string str_log_nm)
{

	log4cpp::Priority::Value priority = log4cpp::Priority::INFO;
	std::string str_config_nm =  str_log_nm + "_priority";
	Config::getConfig(str_config_nm,priority);
	set_priority(priority);

	LOG.bindFunction(boost::bind(&log_singleton_cinit::log_call,this,_1,_2,_3));

	cConnPara conn_para;
	conn_para.m_iType = cConnPara::NETWORK;
	conn_para.m_nNetType = cConnPara::TCPCLIENT;
	conn_para.m_nRemoteIP = str_ip_;
	conn_para.m_nRemotePort = i_log_port_;

	p_tcp_client_ = cTransferDevice::GetInstance(conn_para);

	if (p_tcp_client_)
	{
		for ( int i = 0 ; i < 10 ; ++i )
		{
			if(p_tcp_client_->m_Status.IsOpen()){

				init_send_th();
				init_set_th();
				return true;
			}else{
				SLEEP(100);
				std::cout<<"log:"<<str_prc_name_<<" tcp client open err!"<<std::endl;
			}

		}

	}


	return false;
}
void log_singleton_cinit::set_priority(log4cpp::Priority::Value priority){

	LOG.getLog(str_prc_name_).setPriority(priority);  //LOGS_PRIORITY_INFO("planner_tray");
}
log4cpp::Priority::Value log_singleton_cinit::get_priority()
{
	return LOG.getLog(str_prc_name_).getPriority();
}
void log_singleton_cinit::init_set_th(){

	boost::thread(boost::bind(&log_singleton_cinit::th_call_set,this));
}

void log_singleton_cinit::th_call_set()
{
	b_set_run_ = true;
	U8 p_data[1024];
	int ilen = 0;

	while(b_set_run_){

		if(p_tcp_client_->m_Status.IsOpen()){
		
			p_tcp_client_->ReadData(p_data,ilen,100,200);
			if (ilen > 0 )
			{
				std::string str;
				cComm::Char2String(str,p_data);
				std::vector<std::string> v_str;
				cComm::SplitString(str," ",v_str);
				if ( (v_str.size()> 1) && (v_str[0] == "set_priority"))
				{
					int priority = log4cpp::Priority::INFO;
					str = cComm::trim_n(v_str[1]);
					str = cComm::trim_cr(str);
					cComm::ConvertToNum(priority,str);
					std::cout<<str_prc_name_ << " set priority:"<<int(priority)<<std::endl;
					set_priority(priority);
				}else if ( (v_str.size()> 0) && (v_str[0] == "get_priority"))
				{
					int priority = get_priority();
					std::stringstream ss;
					ss<<"#"<<str_prc_name_<<"#"<<priority<<" \n";
					circular_send_.put(ss.str());
				}
			}
			

		}else{

			std::cout<<"log_singleton_cinit::th_call_set "<<str_prc_name_<<" tcp client err!"<<std::endl;
			SLEEP(1000);
		}

	
	}


}

void log_singleton_cinit::log_call( std::string str, Priority::Value val, TimeStamp time){
	
	std::stringstream ss;
	ss<<cTimerDiff::total_ms()<<" "<<str;

	if(!p_tcp_client_->m_Status.IsOpen()){
		std::cout<<"log_singleton_cinit::log_call tcp client is close!!!"<<ss.str();
		return;
	}
	
	
	circular_send_.put(ss.str());
	if (circular_send_.size() >= CIRCLUAR_BUFFER_SEND){
		std::cout<<"log circular buff overflow!"<<std::endl;
	}
	
	
	
}
void log_singleton_cinit::init_send_th(){

	boost::thread(boost::bind(&log_singleton_cinit::th_call_send,this));

}
int log_singleton_cinit::packet_send(U8* &p_data,int &ilen,std::string str)
{
	SDelete(p_data);
	//str = cComm::trim(str);
	str = str.substr(0 , str.length() - 2);
	ilen = str.length();
	if (ilen > 0)
	{
		p_data = new U8[ ilen + 2];
		if (p_data)
		{
			p_data[0] = CH_LOG_HEAD;
			memcpy( p_data + 1,str.c_str(),ilen);
			ilen += 2;
			p_data[ ilen - 1 ] = CH_LOG_TAIL;

		}else{
			ilen = 0;
		}

	}
	return ilen ;
}
void log_singleton_cinit::th_call_send()
{
	b_send_run_ = true;
	U8 p_data[1024];
	int ilen = 0;
	std::string str_send ;
	while(b_send_run_){


		if(p_tcp_client_->m_Status.IsOpen()){

			do{
				circular_send_.get(str_send);

				if ( (str_send.length() > 0) && ( str_send.length() < MAX_TCP_LOG_DATA_SIZE))
				{
					U8* p_data = 0;
					int ilen = 0;
					packet_send(p_data,ilen,str_send);
					p_tcp_client_->WriteData(p_data,ilen,false);
					delete[] p_data;
					p_data = 0;
					ilen = 0;
				}
			}while(circular_send_.size() > 0);

		}
		else{
			SLEEP(1000);
			//std::cout<<"th_call_send err tcp client:"<<str_send;
		}


	}

}
void log_singleton_cinit::destroy()
{
	b_set_run_ = false;
	b_send_run_ = false;
	SLEEP(100);
	circular_send_.put("");
	SLEEP(500);
	
	cConnPara ConnPara;
	p_tcp_client_->GetPara(ConnPara);
	cTransferDevice::DelInstance(ConnPara);
	p_tcp_client_ = 0;
}

CategoryStream log_singleton_cinit::get_log_info()
{
	return LOGS_INFO(str_prc_name_);
}
CategoryStream log_singleton_cinit::get_log_debug()
{
	return LOGS_DEBUG(str_prc_name_);
}

CategoryStream log_singleton_cinit::get_log_error()
{
	return LOGS_ERROR(str_prc_name_);
}
CategoryStream log_singleton_cinit::get_log_warn()
{
	return LOGS_WARN(str_prc_name_);
}