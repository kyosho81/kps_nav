#include <assert.h>

#include "Comm/PortDef.h"
#include "Comm/configs.h"

#include "trans_dev/trans_dev.h"
#include "interface/cfg.hpp"
#include "interface/agv_client.h"


agv_client::agv_client(){

	
}

agv_client::~agv_client(){

}

void agv_client::init(AGV_TYPE agv_type ,int i_rpc_port , int i_action_rpc_port)
{
	memset(&agv_client_info_,0,sizeof(SAGV_Info));
	std::string str_local_ip = "127.0.0.1";
	Config::getConfig("agv_ip",str_local_ip);

	int i_agv_id = 1;
	Config::getConfig("agv_id",i_agv_id);

	cComm::String2Charlist( (S8*)agv_client_info_.ch_ip_,20,str_local_ip);
	agv_client_info_.ver_ = cComm::getVersion();
	agv_client_info_.agv_type_ = agv_type;
	agv_client_info_.rpc_port_ = i_rpc_port;
	agv_client_info_.action_rpc_port_ = i_action_rpc_port;
	agv_client_info_.id_ = i_agv_id;
	cComm::String2Charlist((S8*)agv_client_info_.ch_msg_,200,std::string("regist"));

	boost::thread th(boost::bind(&agv_client::th_regist,this));
}

void agv_client::th_regist()
{
	b_run_ = true;
	nw_.init(false);
	nw_.set_agv_client_info(agv_client_info_);
	
	while (b_run_){
		nw_.do_listen();
		SCentralController_Info cc_info;
		if (nw_.get_cc_info(cc_info)){
			tcp_regist(cc_info);
		}
		SLEEP(200);
	}
	std::cout<<"agv_client regist over!"<<std::endl;
}
bool agv_client::tcp_regist(const SCentralController_Info &cc_info){

	std::string str_ip = "127.0.0.1";
	cComm::Char2String(str_ip,(U8*)&(cc_info.ch_ip_));

	cConnPara conn_para;
	conn_para.m_iType = cConnPara::NETWORK;
	conn_para.m_nNetType = cConnPara::TCPCLIENT;
	conn_para.m_nRemoteIP = str_ip;
	conn_para.m_nRemotePort = cc_info.regist_port_;


	cTransferDevice* pTcp = cTransferDevice::GetInstance(conn_para);

	if (pTcp)
	{
		for ( int i = 0 ; i < 100 ; ++i){
			if(!pTcp->m_Status.IsOpen()){
				SLEEP(100);
				std::cout<<"wait connect to regist server!!!"<<std::endl;
			}else{
				break;
			}
		}

		if( pTcp->WriteData((U8*)&agv_client_info_,sizeof(SAGV_Info)) ){
			
			std::cout<<"send agv client info to regist server !!!"<<std::endl;

			SCentralController_Info cc_info;

			int irec_len = 0;
			pTcp->ReadData((U8*)&cc_info,irec_len, sizeof(SCentralController_Info),60000);
			
			cTransferDevice::DelInstance(conn_para);

			if (irec_len == sizeof(SCentralController_Info)){
				return true;
			}
		}else{
			std::cout<<"send agv client info to regist server Error!!!"<<std::endl;
		}
	}
	return false;
}
void agv_client::destruct()
{
	b_run_ = false;
	nw_.destruct();
}


