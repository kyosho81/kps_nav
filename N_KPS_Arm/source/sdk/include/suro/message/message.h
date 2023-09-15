#ifndef __AGV_NAVIGATE_MESSAGE_H__
#define __AGV_NAVIGATE_MESSAGE_H__
#include "SerializationInterface.h"
#include "message/GLaserScan.pb.h"

USE_GOOGLE_TYPE(GBeam);
USE_GOOGLE_TYPE(GEcho);
USE_GOOGLE_TYPE(GLaserScan);

#include "message/GChassic.pb.h"

USE_GOOGLE_TYPE(GMotorSet);
USE_GOOGLE_TYPE(GRobotSpeed);
USE_GOOGLE_TYPE(GRobotPWM);
USE_GOOGLE_TYPE(GRobotSpeedControl);
USE_GOOGLE_TYPE(GOdometer);
USE_GOOGLE_TYPE(GChassicData);

USE_GOOGLE_TYPE(GMotorDebugMessage);
USE_GOOGLE_TYPE(GChassicDebugMessage);


#include "message/GErrorCode.pb.h"
USE_GOOGLE_TYPE(GErrorCode);

#include "message/GTraceList.pb.h"
USE_GOOGLE_TYPE(GTracePoint);
USE_GOOGLE_TYPE(GTraceSeg);
USE_GOOGLE_TYPE(GTraceList);

#include "message/GRobPosFind.pb.h"
USE_GOOGLE_TYPE(GRobPosQuality);
USE_GOOGLE_TYPE(GFindRobPos);
USE_GOOGLE_TYPE(GFindRobPosStatus);
USE_GOOGLE_TYPE(GWandererCmd);

#endif
