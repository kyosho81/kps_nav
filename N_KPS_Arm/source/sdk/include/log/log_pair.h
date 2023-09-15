#ifndef _KPS_ARM_KYOSHO_LOG_PAIR_H_
#define _KPS_ARM_KYOSHO_LOG_PAIR_H_


#include "robot/RobotStruct.h"



class log_pair{
public:
	log_pair(){

		time_stamp_ = 0;
		msg_name_ = "";
		msg_type_ = "";
		ch_msg_ = 0;
		ilen_ = 0;
	};
	~log_pair(){
		if (ch_msg_){
			delete[] ch_msg_;
			ch_msg_ = 0;
		}
	};

	U64 time_stamp_;
	std::string msg_name_;
	std::string msg_type_;
	char* ch_msg_;
	int ilen_;
};

#endif//_KPS_ARM_KYOSHO_LOG_PAIR_H_
