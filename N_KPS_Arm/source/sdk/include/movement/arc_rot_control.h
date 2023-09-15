/***************************************************************************************************
* File name:    arc_rot_control.h
* Description:   
* Version:      0.0.1
* History: 
* (1) Author:   wanghongtao
*     Date:     2019-5-21
*     Operate:  Create
*     Version:  0.0.1
* Others: 
***************************************************************************************************/
#ifndef _ARC_ROT_CONTORL_CONTROL_WANGHONGTAO_H_
#define _ARC_ROT_CONTORL_CONTROL_WANGHONGTAO_H_

#include <boost/timer.hpp>
#include <boost/thread/mutex.hpp>
#include "MyDefine.h"
#include "RobotStruct.h"
// #include "interprocess_core/reg_msg.h"
// #include "interprocess/shared_pool.hpp"

#include "my_tf.h"
#include "buffer_con.hpp"

#include "task_path.h"
#include "protobuf_msg/protobuf_path.h"

typedef struct _SSRotSpeed_Para
{
	F32 normal_vx_;  //in normal distance speed vx
	F32 slow_vx_;    //in slow distance speed vx
	F32 rot_vx_;     //rot motion speed vx
	F32 rot_R_;      //rot Radius

}SRotSpeed_Para;

typedef struct _SSeg_path_dis
{
	F32 decrease_dis_; //normal speed to slow speed 
	F32 slow_dis_;     //before rot speed
	F32 rot_dis_;

	SPos normal_drop_pos_;
	SPos decrease_drop_pos_;
	SPos slow_drop_pos_;
	
	//current path
	Line ln_from_;
	//next path
	Line ln_to_;
	// 2 line intersection
	SPos ln_intersection_;
	//cal rot center by 2 path line and rot radius
	SPos rot_center_pos_;
	//rot drop on from path 
	SPos rot_drop_from_pos_;
	SPos rot_drop_to_pos_;

}SSeg_path_dis;

class arc_rot_para{
public:

	arc_rot_para();
	~arc_rot_para();

	void update_para();

	F32 k_dx_;
	F32 k_dy_;
	
	SRotSpeed_Para rot_para_;
};
class arc_rot_control
{
public:

	typedef enum{
		ARC_ROT_NORMAL = 0,
		ARC_ROT_DECREASE = 1,
		ARC_ROT_SLOW = 2,
		ARC_ROT_START = 3,
		ARC_ROT_ROTING = 4,
		ARC_ROT_END = 5
	}EARCCTL_status;

	arc_rot_control();
	~arc_rot_control();

	void init( );
	
	void reset();


	int cal_arc_rot_control(SPathData &pathAB,SPathData &pathBC,const SPos &c_robot_pos,const F32 &R,const F32 &normal_vx,const F32 &slow_vx);

	
public:
	bool cal_arc_rot( F32 &vx, F32 &vw, const F32 &t_vx, const F32 &R , SPos O_pos, const SPos &C_pos );

protected:
private:

	arc_rot_para para_;

	//state machine
private:
	EARCCTL_status status_;
	
	int slice_rot_path(SPathData &pathAB,SPathData &pathBC,const SPos &c_robot_pos,const F32 &R);

	//debug show
private:
	void set_show_pos(const SPos &pos);
	void publish_pos();

	SparticlePub pub_;

	std::list<SOdomSpeed> show_pos_;

	
};
#endif//_ARC_ROT_CONTORL_CONTROL_WANGHONGTAO_H_
