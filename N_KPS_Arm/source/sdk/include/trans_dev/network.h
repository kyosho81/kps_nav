#ifndef _NETWORK_WANGHONGTAO_KYOSHO_20200912_
#define _NETWORK_WANGHONGTAO_KYOSHO_20200912_

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <ctime>
#include <map>

#include <boost/asio.hpp>

#include "Comm/PortDef.h"
#include "robot/RobotStruct.h"

class UdpLinkServer;


class net_work
{
public:
	net_work();
	~net_work();

	bool init(bool b_boardcast , int i_bc_port = UPD_BOARDCAST_PORT);
	void set_agv_client_info(const SAGV_Info &agv_client_info);

	int get_active_ip();
	int get_local_ip();

	bool do_boardcast();
	bool do_activate(std::string str_sn);
	bool do_listen();

	bool get_cc_info(SCentralController_Info &cc_info);

	void destruct();

	SCentralController_Info get_pub_cc_info();

protected:
private:

	bool check_ip_active(std::string str_ip);
		std::vector<std::string> v_ip_;
	std::vector<std::string> v_active_ip_;

	void bc_callback(const boost::system::error_code& error,char *pData,int nDataLength,char *pPeerIp,unsigned short usPeerPort);
	
	UdpLinkServer* upd_bc_;
	boost::asio::io_service io_service_;

	SCentralController_Info cc_info_;
	std::vector<SCentralController_Info> vcc_rec_;

	SAGV_Info agv_client_info_;


};


#endif //_NETWORK_WANGHONGTAO_KYOSHO_20200912_
