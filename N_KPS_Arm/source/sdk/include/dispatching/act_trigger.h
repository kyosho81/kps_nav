#ifndef _ACT_TRIGGER_KYOSHO_KYOSHO_20200912_
#define _ACT_TRIGGER_KYOSHO_KYOSHO_20200912_

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

#include "XmlRpc.h"

#include "Comm/Comm.h"
#include "Comm/TimerDiff.h"
#include "Comm/configs.h"
#include "interpro_shared/sh_pool.hpp"


#include "mapserver/MapServer.h"
#include "project/project_manage.h"

#include "project/task_manage.h"

#include "network.h"
#include "interface/rpc_bind.h"
#include "interface/rpc_task_server.h"
#include "movement/task_path.h"


class act_trigger
{
public:
	act_trigger();
	~act_trigger();

	bool init();
	
	typedef enum{
		ACT_TRIG_STA_NONE = 0,
		ACT_TRIG_STA_SEG_MATCH = 1,
		ACT_TRIG_STA_SEG_TRIG = 2,
		ACT_TRIG_STA_SEG_CHECK = 3
	}ACT_TRIG_STA;

	ACT_TRIG_STA check_state(SAct_Base act_do);
	
	void reset_match();

	bool update_mv_status( const SRunStatus &sta );
	bool s_run_path( std::string name,U8* data,U32 len );

protected:
private:

	
	
	//init msg call back
private:

	void init_msg_call_back();
	
	boost::mutex mu_data_;
	std::vector<SPathData> v_seg_path_;
	SRunStatus mv_run_sta_;

	
	int i_sub_seg_path_;

	
	int i_sub_id_runstatus_;

	ACT_TRIG_STA act_trig_sta_;

	bool b_match_;
	bool b_match_in3seg_;
};

#endif //_ACT_TRIGGER_KYOSHO_KYOSHO_20200912_
