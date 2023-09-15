#include <assert.h>
#include "Comm/Comm.h"
#include "interface/cfg.hpp"

#include "trans_dev/pinger.h"
#include "trans_dev/udp_server.h"


#include "network.h"



net_work::net_work()
{
	upd_bc_ = 0;

	memset(&cc_info_,0,sizeof(SCentralController_Info));
	cc_info_.regist_port_ = CLIENT_REGIST_PORT;
	cc_info_.ver_ = cComm::getVersion();
	std::string str_ip = "127.0.0.1";
	cComm::String2Charlist((S8*)cc_info_.ch_ip_,20,str_ip);

	
}

net_work::~net_work()
{
	SDelete(upd_bc_);
}

int net_work::get_local_ip()
{
	v_ip_.clear();

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::resolver resolver(io_service);
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
	boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
	boost::asio::ip::tcp::resolver::iterator end; // End marker.

	while (iter != end)
	{
		boost::asio::ip::tcp::endpoint ep = *iter++;
		std::string str_ip = ep.address().to_string();
		if(cComm::Check_ip(str_ip)){
			v_ip_.push_back(str_ip);
			std::cout << ep << std::endl;
		}
		
	}

	return v_ip_.size();

}

int net_work::get_active_ip()
{

	v_active_ip_.clear();
	get_local_ip();

	std::vector<std::string>::iterator it = v_ip_.begin();
	for ( ; it != v_ip_.end() ; ++it ){
		if (check_ip_active(*it)){
			v_active_ip_.push_back(*it);
		}
	}
	
	return v_active_ip_.size();
}

bool net_work::check_ip_active(std::string str_ip)
{
	boost::asio::io_service io_service;
	pinger p(io_service, str_ip.c_str());
	io_service.run();


	return p.ping_ok();
}

bool net_work::do_boardcast()
{
	if (!upd_bc_){
		
	}

	upd_bc_->SendData((char*)&cc_info_,sizeof(SCentralController_Info),true);
	io_service_.poll();

	return true;
}



bool net_work::do_activate(std::string str_sn)
{
	if (!upd_bc_){

	}

	cComm::String2Charlist((S8*)cc_info_.key_,200,str_sn);

	upd_bc_->SendData((char*)&cc_info_,sizeof(SCentralController_Info),true);
	io_service_.poll();

	return true;
}

bool net_work::init(bool b_boardcast , int i_bc_port /*= UPD_BOARDCAST_PORT */)
{


	std::string str_ip = "127.0.0.1";
	Config::getConfig("server_ip",str_ip);
	cComm::String2Charlist((S8*)cc_info_.ch_ip_,20,str_ip);

	if (upd_bc_){
		upd_bc_->Stop();
		io_service_.stop();
		SDelete(upd_bc_);
	}

	upd_bc_ = new UdpLinkServer(i_bc_port,b_boardcast);//true，为广播模式；false，监听模式
	if (!b_boardcast){
		upd_bc_->SetRecvDataCallback( true, boost::bind(&net_work::bc_callback,this,_1,_2,_3,_4,_5) );
	}

	return upd_bc_->Start(io_service_);
}

void net_work::bc_callback(const boost::system::error_code& error,char *pData,int nDataLength,char *pPeerIp,unsigned short usPeerPort){
	if ( nDataLength == sizeof(SCentralController_Info) ){
		
		vcc_rec_.clear();
		
		SCentralController_Info cc_rec;
		memcpy(&cc_rec,&cc_info_,sizeof(SCentralController_Info));
		memcpy(&cc_rec,pData,nDataLength);
		vcc_rec_.push_back(cc_rec);

		std::cout<<"central controller ip:"<<cc_rec.ch_ip_<<" upd ip:"<<pPeerIp<<" port:"<<usPeerPort<<std::endl;

// 		upd_bc_->SendData((char*)&agv_client_info_,sizeof(SAGV_Info),false);
// 

	}
}
bool net_work::do_listen()
{
	
	io_service_.poll();
	return true ;
}

void net_work::set_agv_client_info(const SAGV_Info &agv_client_info)
{
	agv_client_info_ = agv_client_info;
}
void net_work::destruct(){
	if (upd_bc_){
		upd_bc_->Stop();
		io_service_.stop();
		SDelete(upd_bc_);
	}
}

bool net_work::get_cc_info(SCentralController_Info &cc_info)
{
	if (vcc_rec_.size() > 0){
		cc_info = vcc_rec_.front();
		vcc_rec_.clear();
		return true;
	}
	return false;
	

}

SCentralController_Info net_work::get_pub_cc_info()
{
	return cc_info_;
}
