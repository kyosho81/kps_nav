#ifndef _TASK_FLOW_DATA_WANGHONGTAO_20230426_
#define _TASK_FLOW_DATA_WANGHONGTAO_20230426_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
#include "robot/task_flow_def.h"





class task_flow_data
{
public:
	task_flow_data();
	~task_flow_data();

	std::string str_task_flow_nm_;

	int create_data();
	SSTaskFlow* create_data( int i_id );
	int insert_data(int i_id);

	bool del_data(int i_id);

	SSTaskFlow* get_data(int i_id);
	std::list<SSTaskFlow*> l_task_flow_;

protected:


private:
	

};


#endif//_TASK_FLOW_DATA_WANGHONGTAO_20230426_
