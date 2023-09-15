#ifndef _CHASSIS_SPEED_WANGHONGTAO_20180401_
#define _CHASSIS_SPEED_WANGHONGTAO_20180401_


#include <string>
#include <map>
#include <boost/thread.hpp>


#include "Comm/TimerDiff.h"
#include "robot/RobotStruct.h"


class chassis_speed
{
public:

	chassis_speed();
	~chassis_speed();

	void init();
	
	bool call_back_priority_speed( const SDynamic_Speed &speed );

	bool get_priority_speed( SSpeed &speed );

private:

	void set_priority_speed( U8 id, SDynamic_Speed speed);

	std::map<U8,SDynamic_Speed> m_priority_speed_;
	cTimerDiff dt_priority_speed_;
	boost::mutex mu_speed_;
};

#endif //_CHASSIS_SPEED_WANGHONGTAO_20180401_