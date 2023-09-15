/*
 * MotionControlBase.h
 *
 *  Created on: 20190410
 *      Author: swordly
 */

#ifndef __MOTION_CONTROL_BASE__
#define __MOTION_CONTROL_BASE__

#include <ConfigFile.hpp>
#include "message/message.h"
#include <boost/thread/pthread/mutex.hpp>

class MotionControlBase
{
private:
    /* data */
    double curr_vel_x_; // 当前速度 (m/s, rad/s)， 当前实际下发之速度值
	double curr_vel_y_;
	double curr_rot_;
    double max_vel_x_;  // 默认最大速度 (m/s, rad/s)
    double max_vel_y_;
    double max_vel_rot_;
    double max_accl_x_; // 默认最大加速度 (m/s^2, rad/s^2)
    double max_accl_y_;
    double max_accl_rot_;
    GLaserScan scan_0_; // 激光计算碰撞时间
    long timestamp_;    // (ms)
    double p_angle_;    // 角速度比例控制系数

    double stop_rotate_thrs_upper_; //  停止原地旋转 死区阈值，消除不必要震荡
    double stop_rotate_thrs_lower_; //  大于upper则原地转，直到与相对目标角小于lower才开始边走边调整

    vector<GLaserScan> scans_;   // index, scan 扩展有多个激光

    double loc_x_;
    double loc_y_;
    double loc_a_;

    boost::mutex mut_sensor_;

public:
    MotionControlBase(boost::shared_ptr<ConfigFile> conf);
    
    virtual ~MotionControlBase();
    
    // 派生去实现，const GTraceList &trace 在本函数内不允许修改, 返回临时目标点的全局坐标
    virtual bool GetTemporaryTarget(const GTraceList &trace, double &target_x, double &target_y, double &target_a) = 0;

    // 计算控制量
    bool DoAction(double target_x, double target_y, double target_a, 
                    double &vx_best , double &vy_best , double &w_best);

    // 激光数据管理
    void SetScan(GLaserScan scan, int index = 0);

    GLaserScan GetScan(int index = 0);

    void SetLoc(double loc_x, double loc_y, double loc_a);

    // 计算碰撞时间
    double CollisionTime(double v, double w);

};



#endif 