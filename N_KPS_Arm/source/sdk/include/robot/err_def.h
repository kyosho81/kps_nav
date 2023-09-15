#ifndef _ERROR_DEF_WANGHONGTAO_20150831_
#define _ERROR_DEF_WANGHONGTAO_20150831_

#define ERROR_IO             1
#define ERROR_DEV            2
#define ERROR_NOTICE         5


//ERROR_IO
#define SUB_ERROR_IO_EMC_STOP  1
#define SUB_ERROR_IO_DIS_COLLI 2
#define SUB_ERROR_IO_COLLISION 3
#define SUB_ERROR_IO_DIO_DEV   4
#define SUB_ERROR_IO_OBS_STOP  5
#define SUB_ERROR_IO_AUTORUN   6

//ERROR_DEV
#define SUB_ERROR_DEV_ODOM       1
#define SUB_ERROR_DEV_LASER      2
#define SUB_ERROR_DEV_AMCL       3
#define SUB_ERROR_DEV_REF        4
#define SUB_ERROR_DEV_SUB_LOC    5
#define SUB_ERROR_DEV_MV_OUTLINE 6
#define SUB_ERROR_DEV_MV_ACTION  7

//ERROR_NOTICE
#define SUB_NOTICE_MV_RUN1       1
#define SUB_NOTICE_MV_RUN2       2
#define SUB_NOTICE_MV_RUN3       3
#define SUB_NOTICE_MV_RUN4       4

#define SUB_NOTICE_MV_STRAIGHT   5
#define SUB_NOTICE_MV_SLOW       6
#define SUB_NOTICE_MV_LOW        7
#define SUB_NOTICE_MV_CCW        8
#define SUB_NOTICE_MV_CW         9
#define SUB_NOTICE_MV_BACKWARD   10
#define SUB_NOTICE_MV_LEFTSHIFT  11
#define SUB_NOTICE_MV_RIGHTSHIFT 12

#endif//_ERROR_DEF_WANGHONGTAO_20150831_
