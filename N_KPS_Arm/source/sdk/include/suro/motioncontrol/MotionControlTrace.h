/*
 * MotionControlTrace.h
 *
 *  Created on: 20190410
 *      Author: swordly
 */

#ifndef __MOTION_CONTROL_TRACE__
#define __MOTION_CONTROL_TRACE__

#include "motioncontrol/MotionControlBase.h"

class MotionControlTrace : public MotionControlBase
{
private:
    /* data */
    GTraceList trace_;   // 维护全局数据

    boost::mutex mut_trace_;    // trace_加锁

public:
    MotionControlTrace(boost::shared_ptr<ConfigFile> conf);
    
    ~MotionControlTrace();

    GTraceList::ExecuteStatus GetStatus();

    void Run();

    GTraceList PopTrace();

    void Push(GTraceList &new_trace);

private:
    // 4种状态处理
    int ProcessIdle();

    int ProcessTrace(GTraceList &trace);

    int ProcessFinish();

    int ProcessBlock();

    void MainLoop();

    bool GetTemporaryTarget(const GTraceList &trace, double &target_x, double &target_y, double &target_a);

};



#endif