#ifndef _TASK_FLOW_DEFINE_WANGHONGTAO_20221210_
#define _TASK_FLOW_DEFINE_WANGHONGTAO_20221210_


#include <string>
#include <map>
#include <boost/thread.hpp>

#include "robot/RobotStruct.h"

#include "action/action_def.h"




typedef struct _SActDecribe
{
	int i_act_seq_;
	std::string str_act_;
	ACT_DEC act_dec_;

}SSActDecribe;

typedef struct _STaskFlow
{
	std::string str_tf_name_;
	int i_id_;
	std::string str_get_put_;
	std::string str_mv_seg_;
	std::vector<SSActDecribe> v_act_dec_;

}SSTaskFlow;


#endif //_TASK_FLOW_DEFINE_WANGHONGTAO_20221210_