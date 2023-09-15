#ifndef _DEVICE_EXACTION_REF_FORBIDDEN_KYOSHO_20220711_
#define _DEVICE_EXACTION_REF_FORBIDDEN_KYOSHO_20220711_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include "buffer_con.hpp"
#include "trans_dev/trans_dev.h"

#include "action/fork_control.h"

#include "action/device_exaction_base.h"

class device_exaction_ref_forbidden : public device_exaction_base
{
public:

	device_exaction_ref_forbidden();
	~device_exaction_ref_forbidden();

	std::string get_para();
	bool init_sub_back( bool b_sim );

protected:
	//from parent
private:
	bool setPara( std::string name , std::string value );

	bool act_init();
	int act_doing( F32 dt );
	bool act_check();

private:
	F32 cnt_time_;

	bool b_enable_;

	F32 forbidden_ref_begin_angle_; //ccw dir 
	F32 forbidden_ref_end_angle_;   //ccw dir 
};

#endif //_DEVICE_EXACTION_REF_FORBIDDEN_KYOSHO_20220711_