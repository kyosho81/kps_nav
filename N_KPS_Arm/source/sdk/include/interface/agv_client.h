#ifndef _AGV_CLIENT_WANGHONGTAO_KYOSHO_20200912_
#define _AGV_CLIENT_WANGHONGTAO_KYOSHO_20200912_

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
#include "Comm/PortDef.h"

#include "network.h"



class agv_client
{
public:
	agv_client();
	~agv_client();

	void init( AGV_TYPE agv_type = AGV_TYPE::AGV_TYPE_2WD ,int i_rpc_port = RPC_DATA_SER_PORT, int i_action_rpc_port = RPC_TASK_SER_PORT);
	void destruct();

private:

	net_work nw_;
	SAGV_Info agv_client_info_;
	void th_regist();
	bool tcp_regist(const SCentralController_Info &cc_info);
	bool b_run_;
};



#endif //_AGV_CLIENT_WANGHONGTAO_KYOSHO_20200912_
