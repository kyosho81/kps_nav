#ifndef _KPS_ACTION_DEFINE_MSG_H_
#define _KPS_ACTION_DEFINE_MSG_H_

#include "robot/RobotStruct.h"

// #define EXT_TRUN        "ext_turn"
// #define EXT_PASSING_BAY "ext_passing_bay"
// #define EXT_TASK_REPLAN "ext_task_replan"

#define ACT_PATH "act_path"
#define ACT_TASK "act_task"

#define ACT_FORK           "act_fork"
#define ACT_LIFT           "act_lift"
#define ACT_GET_OVER       "act_get_over"
#define ACT_PUT_SAFE       "act_put_safe"
#define ACT_PUT_OVER       "act_put_over"
#define ACT_PUT_ACCESS     "act_access"
#define ACT_GET_RELEASE    "act_get_release"
#define ACT_PUT_RELEASE    "act_put_release"
#define ACT_PUT_OCCUPY     "act_occupy"
#define ACT_REF_FB         "act_ref_forbidden"
#define ACT_DOOR           "act_door"
#define ACT_EVEVATOR       "act_elevator"
#define ACT_LOCAL_IO       "act_local_io"
#define ACT_REMOTE_IO      "act_remote_io"
#define ACT_QR_LOC         "act_qr_loc"
#define ACT_3D_LOC         "act_3d_loc"
#define ACT_CHARGE         "act_charge"
#define ACT_CHARGE_STATION "act_charge_station"

#define ACTION_ID_TURN           (Comm_Dev_Id::ID_EX_TASK_ID + 0)
#define ACTION_ID_FORK           (Comm_Dev_Id::ID_EX_TASK_ID + 1)
#define ACTION_ID_LIFT           (Comm_Dev_Id::ID_EX_TASK_ID + 2)
#define ACTION_ID_GET_OVER       (Comm_Dev_Id::ID_EX_TASK_ID + 3)
#define ACTION_ID_PUT_SAFE       (Comm_Dev_Id::ID_EX_TASK_ID + 4)
#define ACTION_ID_PUT_OVER       (Comm_Dev_Id::ID_EX_TASK_ID + 5)
#define ACTION_ID_ACCESS         (Comm_Dev_Id::ID_EX_TASK_ID + 6)
#define ACTION_ID_GET_RELEASE    (Comm_Dev_Id::ID_EX_TASK_ID + 7)
#define ACTION_ID_PUT_RELEASE    (Comm_Dev_Id::ID_EX_TASK_ID + 8)
#define ACTION_ID_OCCUPY         (Comm_Dev_Id::ID_EX_TASK_ID + 9)
#define ACTION_ID_REF_FORBIDDEN  (Comm_Dev_Id::ID_EX_TASK_ID + 10)
#define ACTION_ID_DOOR           (Comm_Dev_Id::ID_EX_TASK_ID + 11)
#define ACTION_ID_EVEVATOR       (Comm_Dev_Id::ID_EX_TASK_ID + 12)
#define ACTION_ID_LOCAL_IO       (Comm_Dev_Id::ID_EX_TASK_ID + 13)
#define ACTION_ID_REMOTE_IO      (Comm_Dev_Id::ID_EX_TASK_ID + 14)
#define ACTION_ID_QR_LOC         (Comm_Dev_Id::ID_EX_TASK_ID + 15)
#define ACTION_ID_3D_LOC         (Comm_Dev_Id::ID_EX_TASK_ID + 16)
#define ACTION_ID_CHARGE         (Comm_Dev_Id::ID_EX_TASK_ID + 17)
#define ACTION_ID_CHARGE_STATION (Comm_Dev_Id::ID_EX_TASK_ID + 18)

#define PUT_STAGE "put_stage"
#define GET_STAGE "get_stage"

#define MV_NONE ""
#define MV_ANY "mv_any"
#define MV_FORWARD1 "mv_forward_1"
#define MV_BACKWARD1 "mv_backward_1"
#define MV_FORWARD2 "mv_forward_2"
#define MV_BACKWARD2 "mv_backward_2"

#define MV_LEFTSHIFT1 "mv_leftshift_1"
#define MV_RIGHTSHIFT1 "mv_rightshift_1"
#define MV_LEFTSHIFT2 "mv_leftshift_2"
#define MV_RIGHTSHIFT2 "mv_rightshift_2"

#endif // _KPS_ACTION_DEFINE_MSG_H_
