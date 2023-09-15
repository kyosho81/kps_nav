#ifndef _DEVICE_EXACTION_FORK_KYOSHO_20220711_
#define _DEVICE_EXACTION_FORK_KYOSHO_20220711_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include "buffer_con.hpp"
#include "trans_dev/trans_dev.h"

#include "action/fork_control.h"

#include "action/device_exaction_base.h"

class device_exaction_fork : public device_exaction_base
{
public:

	device_exaction_fork();
	~device_exaction_fork();

	std::string get_para();
	bool init_sub_back( bool b_sim );

protected:
private:
	bool setPara( std::string name , std::string value );

	bool act_init();
	int act_doing( F32 dt );
	bool act_check();

private:
	//task set
	F32 f_tar_fork_level_;
	F32 f_tar_fork_speed_;

	//current data
	F32 f_cur_fork_level_;
	F32 f_cur_fork_speed_;

private:
	fork_control fork_control_;
	U8 u8_emc_;
};

#endif //_DEVICE_EXACTION_FORK_KYOSHO_20220711_