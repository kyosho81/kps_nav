#ifndef _WANGHONGTAO_CMD2SPEED_2017_04_05_H_
#define _WANGHONGTAO_CMD2SPEED_2017_04_05_H_

#include "buffer_con.hpp"
#include "robot/RobotStruct.h"

class cmd2speed{

public:
	cmd2speed();
	~cmd2speed();
	
	void parse_cmd(const std::string str_cmd);

	void init();

private:

	F32 vx_max_;
	F32 vx_min_;

	F32 vw_max_;
	F32 vw_min_;

	void set_vx(const F32 &target_vx);
	void set_vy(const F32 &target_vy);
	void set_vw(const F32 &target_vw);

	F32 target_vx_;
	F32 target_vy_;
	F32 target_vw_;

	SBuffer<F32> vx_list_;
	SBuffer<F32> vy_list_;
	SBuffer<F32> vw_list_;
	//thread
private:
	void init_thread();
	void end_thread();
	void th_run();

	boost::thread* cmd_th_;
	bool b_run_;
};


#endif//_WANGHONGTAO_CMD2SPEED_2017_04_05_H_
