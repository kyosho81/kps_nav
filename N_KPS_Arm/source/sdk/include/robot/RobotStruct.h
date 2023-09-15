#ifndef _ROBOT_STRUCT_WANGHONGTAO_20150831_
#define _ROBOT_STRUCT_WANGHONGTAO_20150831_


#include <vector>
#include <string>
#include "Comm/MyDefine.h"

#define LASER_COUNT 541
#define FPGA_LASER_BIN_CNT 512

#define LASER_COUNT_EX 8400
#define LASER_COUNT_EX_WJ 7200
#define LASER_COUNT_EX_WJ2 10800
#define LASER_COUNT_EX_WJ3 1081
#define LASER_COUNT_EX2 LASER_COUNT_EX_WJ2
#define REFLECTOR_COUNT 100

#define PROTOBUF_2_3 1
#define TYPE_DELIMITER_ID "_"
//#define FPGA_LASER_BIN_CNT_256 256
//#define FPGA_LASER_BIN_CNT_512 512

//#define LASER_DIFF ((LASER_COUNT - FPGA_LASER_BIN_CNT) / 2)


#define LASER_COUNT_URG 1081

typedef enum{
	IDLE = 0,
	PLAN = 1,
	MOVE = 2,
	RECOVERY = 3,
	ERR = 4
}Status;

typedef enum{
	FRONT = 1,
	BACK = 2,
	LEFT = 3,
	RIGHT = 4
}Direction;

typedef enum
{
	dynamic = 1,
	fix = 2
}MODEL_TYPE;

typedef enum{
	NONE_ERR = 0,
	GLOBAL_PLANNER_ERR = 1,
	LOCAL_PLANNER_ERR = 2,
	OBSTACLE_DETECT = 3,
	AMCL_ERR = 4,
	OUT_OF_LINE_ERR = 5,
	STOPPING_ERR = 6,
	OBSTACLE_STOP = 7,
	COMMAND_STOP = 8,
	COLLISION_STOP = 9,
	SERVER_STOP = 10,
	FORK_ACT_MOVE = 11,
	FORK_ACT_TIME_OUT = 12,
	EX_TASK_ACTION_ERR = 10000
}ERR_CODE;

typedef enum{
	DIFF2WD = 0,
	FORK_STEER = 1,
	FORK_DIFF = 2,
	SINGLE = 4,
	MULIT = 8,
	OMNI = 16,
	TYPE1 = 32,
	TYPE2 = 64
}Motion_type;

typedef enum{
	FIX_SLOW = 0, 
	FIX_STOP_IN = 1,
	FIX_STOP_OUT = 2,
	DY_ROT = 3,
	DY_ROTGO = 4
}Range_type;

typedef enum{
	SICK_LMS = 0, 
	SICK_TIM = 1,
	HOKUYO = 2,
	SAMTEC = 3,
	P_F_R2000 = 4,
	PAVO_LS20 = 5,
	WJ_712 = 6,
	WJ_719 = 7,
	WJ_718MINI = 8,
	PAVO2_LS50H = 9,
	HINS_LE = 10,
	SIM = 11
}Laser_type;

typedef enum{
	ID_MAP_SERVER = 100,
	ID_EX_TASK_ID = 150,
	ID_LOG_BAG = 200,
	ID_LOG_BAG_EX = 201,
	ID_LOOP_CLOSURE = 212,
	ID_MOVE_MENT = 213,
	ID_MSG_LOG = 214,
	ID_DYNAMIC_LOC = 215,
	ID_EASYWAY = 216,
	ID_CFY_MCU = 217,
	ID_BATTERY = 218,
	ID_DIO = 220
	//ID_DIO1 = 221
	//ID_DIO2 = 222
}Comm_Dev_Id;


typedef enum{
	AGV_TYPE_2WD = 0,
	AGV_TYPE_FORK_LIFT = 1,
	AGV_TYPE_SIM = 2
}AGV_TYPE;

typedef enum 
{
	AGV_SM_NONE         = 0,//none
	AGV_SM_IDLE         = 1,//free
	AGV_SM_INIT			= 2,//load map and para
	AGV_SM_PACK			= 3,//pack agv
	AGV_SM_CHARGE		= 4,//agv charge
	AGV_SM_PACKING		= 5,//packing agv 
	AGV_SM_CHARGING	    = 6,//charging agv 
	AGV_SM_WANDER		= 7,//agv wander
	AGV_SM_AWAYFROM_CH  = 8,//agv away from charge pos
	AGV_SM_RESCUE		= 9,//agv rescue : 1 go open area (no obstacle around) 2 relocate 
	AGV_SM_ERROR		= 10,//agv err
	AGV_SM_CLOSE		= 11, //agv close
	AGV_SM_TASK_INIT	= 12,//agv task init
	AGV_SM_TASK_DO		= 13,//agv task do
}AGV_SM;


typedef enum{
	CALIB_RUNTIME = 0,
	CALIB_PLAYBACK = 1,
	CALIB_DEVICE = 2
}CALIB_SUB_TYPE;

// typedef enum{
// 	ORI_FORWARD = 1<<0,
// 	ORI_BACKWARD = 1<<1,
// 	ORI_LEFTSHIFT = 1<<2,
// 	ORI_RIGHTSHIFT = 1<<3
// }ORIENTATION;

typedef enum{
	DIR_NONE = 0,
	DIR_SRC2DST = 1,
	DIR_DST2SRC = 2,
	DIR_BOTH = 3
}DIRECTION;

typedef enum{
	ORI_FORWARD = 0,
	ORI_BACKWARD = 1,
	ORI_LEFTSHIFT = 2,
	ORI_RIGHTSHIFT = 3
}ORIENTAION;

typedef enum{
	BIND_NONE = 0,
	BIND_OPT = 1,
	BIND_REQ = 2
}BIND_SEL;

typedef enum{
	ACT_REQUIRE = 0,
	ACT_OPTIONAL = 1,
	ACT_DISABLE = 2
}ACT_DEC;

typedef enum{
	MENU_PER_SHOW = 0,
	MENU_PER_HIDE = 1,
	MENU_PER_ENABLE = 2,
	MENU_PER_DISENABLE = 3
}MENU_PER;

typedef enum 
{
	BATTERY_FUL         = 0,
	BATTERY_RUN         = 1,
	BATTERY_LOW         = 2,
	BATTERY_CHA			= 3,
	BATTERY_SHUT 		= 4

}eBatSta;

typedef struct _SEdge_Ori_Dir
{
	DIRECTION forward_;
	DIRECTION backward_;
	DIRECTION leftshift_;
	DIRECTION rightshift_;

}SSEdge_Ori_Dir;

typedef struct _SSerialNum
{

	U32 serial_num;
	U32 motion_type;
	U32 d1;
	U32 d2;
	U8 main_v;
	U8 sub_v;
	U8 c1;
	U8 c2;
}SSerialNum;

typedef struct _SGridXY
{
	U16 x_;
	U16 y_;
	S8 value_;

	S8 dir_;
	S8 speed_;
	S8 ptype_;

}SGridXY;

typedef struct _SLaser
{
	U64 stamp_;
	F32 start_angle_;
	F32 resolution_;	//
	F32 range_max_;
	F32 range_min_;

	F32 data_[LASER_COUNT];
	U8  seg_[LASER_COUNT];
	U32 used_;

} SLaser;

typedef struct _SLaser_Ex
{
	U64 stamp_;
	F32 dx_;
	F32 dy_;
	F32 start_angle_;
	F32 resolution_;	//
	F32 range_max_;
	F32 range_min_;
	F32 bean_dt_;
	F64 time_stamp_;

	F32 data_[LASER_COUNT_EX];
	U32 intensities_[LASER_COUNT_EX];
	U8  seg_[LASER_COUNT_EX];
	U32 used_ray_;

} SLaser_Ex;

typedef struct _SLaser_Ex2
{
	U64 stamp_;
	F32 dx_;
	F32 dy_;
	F32 start_angle_;
	F32 resolution_;	//
	F32 range_max_;
	F32 range_min_;
	F32 bean_dt_;
	F64 time_stamp_;

	F32 data_[LASER_COUNT_EX2];
	U32 intensities_[LASER_COUNT_EX2];
	U8  seg_[LASER_COUNT_EX2];
	U32 used_ray_;

} SLaser_Ex2;

typedef struct _SLaser_para
{
	char ch_laser_ip_[500];
	bool reverse_;
	F32 laser_start_angle_;
	F32 laser_range_max_;
	F32 laser_range_min_;
	F32 laser_dx_;
	F32 laser_dy_;
	F32 laser_resolution_;

} SLaser_para;


typedef struct _SLaserXY
{

	F32 x_[LASER_COUNT];
	F32 y_[LASER_COUNT];
	U8 used_[LASER_COUNT];

} SLaserXY;

typedef struct _SLaserXYEx
{

	F32 x_[LASER_COUNT_EX];
	F32 y_[LASER_COUNT_EX];
	U32 used_cnt_;

} SLaserXYEx;

typedef struct _SPos
{
	F32 x_;
	F32 y_;
	F32 th_;

}SPos;

typedef struct _SSpeed
{
	F32 vx_;	//speed vx_
	F32 vy_;	//speed vy_
	F32 vw_;	//speed vw_

}SSpeed;

typedef struct _SOdomSpeed
{
	F32 x_;
	F32 y_;
	F32 th_;

	F32 vx_;	//speed vx_
	F32 vy_;	//speed vy_
	F32 vw_;	//speed vw_

}SOdomSpeed;

typedef struct _SOdomSpeedEx
{
	F64 time_stamp_;

	F32 x_;
	F32 y_;
	F32 th_;

	F32 vx_;	//speed vx_
	F32 vy_;	//speed vy_
	F32 vw_;	//speed vw_

}SOdomSpeedEx;

typedef struct _Sxy
{
	F32 x_;
	F32 y_;

}Sxy;

typedef struct _S16xy
{
	S16 x_;
	S16 y_;

}S16xy;

typedef struct _SLaser_xy
{
	Sxy xy_[LASER_COUNT];
	U32 used_size_;

}SLaser_xy;


typedef struct _SPair_Odo_Laser
{

	SPos pos_;
	SLaser laser_;

}SPair_Odo_Laser;

typedef struct _SInit_Pos
{
	SPos pos_;

	U32 psize_;

	F32 para1_;
	F32 para2_;
	F32 para3_;
	F32 para4_;

}SInit_Pos;

typedef struct _STarget_Pos
{
	U8 model_;
	U8  stop_;
	U16 tmp2_;

	F32 x_;
	F32 y_;
	F32 th_;

}STarget_Pos;

typedef struct _SAMCL_RES
{

	F32 entropy_;
	F32 hz_;
	S32 stamp_;

}SAMCL_RES;

typedef struct _SparticleFAW
{

	F32 x;
	F32 y;
	F32 th;
	F32 aw;

}SparticleFAW;

typedef struct _SparticlePub
{
	U32 pwsize_;
	SparticleFAW data_w_[8192];

}SparticlePub;

typedef struct _Srecoder
{

	char cmd_file_[200];

}Srecoder;

typedef enum 
{
	EX_M_IDLE         = 0,
	EX_M_PLAN         = 1,
	EX_M_DY_MOVING    = 2,
	EX_M_FX_MOVING    = 3,
	EX_M_STOPPING     = 4,
	EX_M_ERROR   	  = 5,
	EX_M_toIDLE       = 6,
	EX_M_toPLAN       = 7,
	EX_M_toMOVING     = 8,
	EX_M_toSTOPPING   = 9,
	EX_M_toERROR 	  = 10
}EX_MState;

typedef enum 
{
	ACT_IDLE         = 0,
	ACT_INIT         = 1,
	ACT_DOING		 = 2,
	ACT_CHECK		 = 3,
	ACT_DONE         = 4,
	ACT_ERROR   	 = 5

}Enu_AState;


typedef enum 
{
	SPEED_DIR_STOP		   = 0,
	SPEED_DIR_FORWARD      = 1,
	SPEED_DIR_BACKWARD     = 2,
	SPEED_DIR_LEFT         = 3,
	SPEED_DIR_RIGHT        = 4,
	SPEED_DIR_CW		   = 5,     //clockwise  turn left
	SPEED_DIR_CCW	       = 6,      //counter clockwise turn right
	SPEED_DIR_INP_R		   = 7,     //inplace rotation
	SPEED_DIR_TURN_R       = 8,     //circle run
	SPEED_DIR_SLOW         = 9,
	SPEED_DIR_NORMAL       = 10,
	SPEED_DIR_FAST         = 11

}Enu_Dir;

typedef struct _SRunStatus
{

	EX_MState status_;
	U8 err_code_;
	U8 arrived_;
	U8 back_;

}SRunStatus;

typedef struct _SVec
{
	F32 x_;
	F32 y_;

}SVec;

typedef struct _SLine2P
{
	SVec p1_;
	SVec p2_;

}SLine2P;

typedef struct _SLinePA
{
	SVec p_;
	F32 angle_;

}SLinePA;

typedef struct _SCircle
{
	SVec p_;
	F32 radius_;

}SCircle;

typedef struct _SLocalShow
{
	SVec C_;
	SVec L_;
	SVec H_;

	F32 v_;
	F32 w_;

	SLinePA line_;

}LocalShow;

#define MAX_DI 32
#define MAX_DO 24
#define MAX_AI 12
#define MAX_AO 12

typedef struct _SDIAI
{
	U64 time_stamp_;
	U8 di_[MAX_DI];
	S32 ai_[MAX_AI];

}SDIAI;

typedef struct _SAIF
{
	U64 time_stamp_;
	F32 fai_[MAX_AI];

}SAIF;

typedef struct _SAOF
{
	U64 time_stamp_;
	F32 fao_[MAX_AO];

}SAOF;

typedef struct _SDOAO
{
	U64 time_stamp_;
	U8 do_[MAX_DO];
	S32 ao_[MAX_AO];

}SDOAO;

typedef struct _SDO
{
	U32 used_;
	U8 id_[MAX_DO];
	U8 do_[MAX_DO];

}SDO;

typedef struct _SFNC_DO
{
	U32 used_;
	S8 ch_fnc_nm_[MAX_DO][100];
	U8 do_[MAX_DO];

}SFNC_DO;

typedef struct _SFNC_FAI
{
	U32 used_;
	S8 ch_fnc_nm_[MAX_AI][100];
	F32 ai_[MAX_AI];

}SFNC_FAI;

typedef struct _SAO
{
	U32 used_;
	U8 id_[MAX_AO];
	S32 ao_[MAX_AO];

}SAO;

typedef struct _SDI
{
	U32 used_;
	U8 id_[MAX_DI];
	S32 di_[MAX_DI];

}SDI;

typedef struct _SAI
{
	U32 used_;
	U8 id_[MAX_AI];
	S32 ai_[MAX_AI];

}SAI;

typedef struct _SFAI
{
	U32 used_;
	U8 id_[MAX_AI];
	F32 fai_[MAX_AI];

}SFAI;

typedef struct _SFAO
{
	U32 used_;
	U8 id_[MAX_AO];
	F32 fao_[MAX_AO];

}SFAO;


typedef struct _SA_D_PARA
{

	U8 id_ai_[MAX_AI];
	F32 fai_[MAX_AI];
	F32 fai_max_[MAX_AI];
	F32 fai_min_[MAX_AI];
	S8 fai_para_[MAX_AI][200];

	U8 id_ao_[MAX_AO];
	F32 fao_[MAX_AO];
	F32 fao_max_[MAX_AO];
	F32 fao_min_[MAX_AO];
	S8 fao_para_[MAX_AO][200];

	U8 id_di_[MAX_DI];
	F32 di_[MAX_DI];
	F32 di_max_[MAX_DI];
	F32 di_min_[MAX_DI];

	U8 id_do_[MAX_DO];
	F32 do_[MAX_DO];
	F32 do_max_[MAX_DO];
	F32 do_min_[MAX_DO];

}SA_D_PARA;

typedef struct _SSub_task_upload
{
	U32 agv_id_;

	U32 sub_task_index_;
	U32 prority_;
	int current_step_;
	int max_step_;

	std::vector<SGridXY> run_path_;

}SSub_task_upload;

typedef struct _SSub_task_path
{
	U32 agv_id_;

	U32 sub_task_index_;
	U32 prority_;

	std::vector<SGridXY> run_path_;

}SSub_task_path;

typedef struct _SSub_task_path_aux
{
	U32 agv_id_;

	U32 sub_task_index_;
	U32 prority_;
	U32 max_step_;
}SSub_task_path_aux;


typedef struct _SSub_task_fnc
{
	U32 agv_id_;

	U32 sub_task_index_;
	U32 prority_;
	U32 function_code_; // 0 fork down 1 fork up  3 pos

	int current_step_;
	int max_step_;

}SSub_task_fnc;

// typedef struct _SFork_state
// {
// 	U32 fnc_code_;
// 	S32 para_;               //0 - 10000    mm
// 	S32 current_status_;     //0:action 1:finished
// 
// }SFork_state;


typedef struct _SControl
{
	U32 agv_id_;
	F32 max_speed_;
	int pause_run_slow;

}SControl;

#define THREAD_COUNTS   10

typedef struct _Health_Status
{
	F32 frequency[THREAD_COUNTS] ;     //unit :  Hz
	int error_code[THREAD_COUNTS];     //flag,  0:not work   1:low   2: normal
}Health_Status;


typedef enum{
	DEV_IDLE = 0,
	DEV_INIT = 1,
	DEV_RUN = 2,
	DEV_ERR = 3,
	DEV_toERR = 4
}eDEV_STATUS;

typedef enum{
	DEV_ERR_NONE = 0,
	DEV_ERR_INIT = 1,
	DEV_ERR_COMMUNICATE = 2,
	DEV_ERR_HZ = 3,
	DEV_ERR_INIT_POS =  4,
	DEV_ERR_REFLECTOR_IN = 5,
	DEV_ERR_REFLECTOR_NO_MATCH = 6,
	DEV_ERR_REFLECTOR_LS = 7,
	DEV_ERR_REFLECTOR_MTI_FOUND = 8,
	DEV_ERR_REFLECTOR_ZERO = 9,
	DEV_ERR_LC_FRAME_INIT_ERR = 10,
	DEV_ERR_LC_FRAME_RN_ERR = 11,

	DEV_ERR_MV_LOCATION_ERR = 12,
	DEV_ERR_MV_SEG_PATH_ERR = 13,
	DEV_ERR_MV_OUTOFF_TARGET_ERR = 14,
	DEV_ERR_MV_OUTOFF_LINE_ERR = 15,

}eDEV_ERR_CODE;

typedef struct _SDevStatus
{
	U8 device_id_;
	U8 status_;
	U16 err_code_;
	
	F32 cycle_ms_;
	F32 run_ms_;

}SDevStatus;

typedef struct _SPubDevStatus
{
	SDevStatus dev_status_;
	char name_[200];

}SPubDevStatus;

typedef struct _SCmd
{
	char cmd_str_[200];
}SCmd;

typedef struct _SPara
{
	char para_str_[5000];

}SPara;

typedef struct _SLaser_used
{
	F32 angle_;
	F32 dis_;

}SLaser_used;


typedef struct _SReflash_map
{
	
	typedef enum{
		AMCL_RUN,
		AMCL_STOP,
		AMCL_REFLASH
	}REF_TYPE;

	REF_TYPE ref_type_;

}SReflash_map;

typedef struct _STriangle {

	F32 x;
	F32 y;
	F32 angle;
	F32 weight;

	SVec points[3];
	S32 color;

} STriangle;

typedef struct _SRemote_data{

	U8 key1_;
	U8 key2_;
	U8 key3_;
	U16 new_ad1_;
	U16 new_ad2_;
	S32 sequence_;

}SRemote_data;

typedef enum{

	BAG_IDLE = 200,
	BAG_LOGGING = 201,
	BAG_PLAYBACK = 202,
	BAG_PLAYBACK_WAIT = 203,
	BAG_IDLE_LOGGING = 204,
	BAG_IDLE_PLAYBACK = 205,
  //BAG_IDLE_UPLOAD = 6,
	BAG_LOGGING_IDLE = 207,
	BAG_PLAYBACK_IDLE = 208,
	BAG_UPLOAD = 209,
	BAG_ERR = 210

}eBAG_STATUS;

typedef struct _SPUB_BAG
{
	SOdomSpeed odom_;
	SLaser laser_;
	SPos amcl_pos_;
	SLaser_para laser_para_;
	char robot_shape_[500];
	F32 confidence_;
}SPUB_BAG;

typedef enum{

	MAP_IDLE = 100,
	MAP_RUN_MAPPING = 101,
	MAP_BAG_MAPPING = 102,
	MAP_IDLE_RUN_MAPPING = 103,
	MAP_IDLE_BAG_MAPPING = 104,
	MAP_RUN_MAPPING_IDLE = 105,
	MAP_BAG_MAPPING_IDLE = 106,
	MAP_SAVE_MAP = 107,
	MAP_SHOW_MAP = 108

}eMAP_STATUS;

typedef enum 
{
	LC_IDLE         = 230,
	LC_LOAD         = 231,
	LC_INIT		    = 232,
	LC_RUN		    = 233,
	LC_ERR		    = 234

}LC_State;

typedef enum 
{
	LOG_IDLE         = 240,
	LOG_RUN		    = 241,
	LOG_PKG		    = 242,

}LOG_State;
// typedef struct _SPubStatus
// {
// 	
// 	U8 device_id_;
// 	U8 status_;
// 	U16 err_code_;
// 
// 	char name_[200];
// 	char ms_str_[200];
// 
// }SPubStatus;

typedef struct _SProcess_Bar
{
	U32 max_step_;
	U32 current_step_;

	char name_[200];

}SProcess_Bar;

typedef struct _SDynamic_Speed
{
	U8 id_;			   //id stand for one kind of speed limit type
	U16 control_time_;  //10 means speed limit continue in 10 seconds
	U8 priority_;

	F32 vx_;
	F32 vy_;
	F32 vw_;


}SDynamic_Speed;

typedef struct _SRunPath
{
	U8 replan_;
	U8 backward_;
	U8 tmp1_;
	U8 tmp2_;
	char path_name_[200];

}SRunPath;

typedef enum{
	PATH_STATUS_IDLE = 0,
	PATH_STATUS_ERR = 1,
	PATH_STATUS_AWAY = 2,
	PATH_STATUS_CLOSE = 3
}EPath_status;

typedef enum{
	PATH_SEG = 0,
	PATH_ROT = 1,
	PATH_ARC = 2
}EPath_type;

typedef struct _SPathData
{
	SPos tn_from_;
	SPos tn_to_;
	EPath_type p_type_;
	F32 complete_pre_;
	F32 speed_from_;
	F32 speed_;
	F32 orientation_;
	S32 node_from_;
	S32 node_to_;
	char desc_from_[500];
	char desc_to_[500];

}SPathData;


typedef struct _SAct_Base
{
	int node_from_;
	int node_to_;
	F32 trig_per_;
	F32 check_per_;

	U8 init_;
	U8 force_done_;
	U8 force_error_;
	U8 redo_;
	

}SAct_Base;

typedef struct _SAct_Fork_DATA
{

	F32 level_;
	F32 speed_;

}SAct_Fork_DATA;

typedef struct _SAct_Fork
{
	SAct_Base act_base_;

	SAct_Fork_DATA act_data_;

}SAct_Fork;

typedef struct _SAct_Para
{
	SAct_Base act_base_;
	char ch_name_[20];
	char ch_para_[500];

}SAct_Para;

typedef struct _SActStatus
{

	Enu_AState status_;
	U8 err_code_;
	U8 done_;
	U8 back_;

	char msg_nm_[50];

}SActStatus;

typedef struct _SCHK_LASER_RANGE
{
	SLaser laser_;
	Range_type type_;

}SCHK_LASER_RANGE;

typedef struct _SIMURION
{
	U64 time_stamp_;
	F32 acc_;
	F32 w_;
	F32 th_;

}SIMURION;

typedef struct _SLaser_Landmark
{
	U8 numbers;
	F32 Position_x[LASER_COUNT];
	F32 Position_y[LASER_COUNT];
	F32 orient[LASER_COUNT];
	S32 ID[LASER_COUNT];
} SLaser_Landmark;

typedef struct _SPair_SVec
{
	bool b_selected_;
	int id_from_;
	int id_to_;
	int bind_global_id_;
	F32 dis_;

	void clear(){
		b_selected_ = false;
		id_from_ = 0;
		id_to_ = 0;
		bind_global_id_ = 0;
		dis_ = 0;
	};
}SPair_SVec;

typedef struct _SReflector
{
	int id_[REFLECTOR_COUNT];
	SVec pos_[REFLECTOR_COUNT];
	U8 used_;
}SReflector;

typedef struct _SLaser_Ex_Ref
{
	SLaser_Ex laser_ex_;
	SReflector laser_reflector_;

} SLaser_Ex_Ref;

typedef struct _SLaser_Ex_Ref2
{
	SLaser_Ex2 laser_ex2_;
	SReflector laser_reflector_;

} SLaser_Ex_Ref2;

typedef struct _SReflectorPos
{
	int id_;
	SVec pos_;

}SReflectorPos;

typedef struct _SPUB_BAG_EX
{
	SOdomSpeed odom_;
	SLaser_Ex_Ref laser_ex_ref_;
	SPos amcl_pos_;
	SLaser_para laser_para_;
	char robot_shape_[500];
}SPUB_BAG_EX;


typedef struct _SLoopCLosurePos
{
	SPos pos_;
	F32 confidence_;

}SLoopCLosurePos;


typedef struct _SAMCL_CONFIDENCE
{
	
	bool b_amcl_confidence_;
	F32 amcl_confidence_;

}SAMCL_CONFIDENCE;

typedef struct _SAMCL_ENTROPY
{

	bool b_amcl_entropy_;
	F32 amcl_xy_entropy_;
	F32 amcl_theta_entropy_;
	F32 amcl_entropy_;

}SAMCL_ENTROPY;


typedef struct _SLOG_BAG
{
	SPUB_BAG pub_bag_;
	SAMCL_CONFIDENCE amcl_confidence_;

}SLOG_BAG;

typedef struct _SScan_Frame
{
	int i_frame_id_;
	long long time_stamp_;
	SOdomSpeed odom_;
	SPos calib_diff_;
	int i_ref_frame_id_;

	SLaser laser_;
	SPos amcl_pos_;
	SAMCL_CONFIDENCE amcl_conf_;
	SLaser_para laser_para_;

	int i_match_err_;
	bool b_match_ok_;

}Scan_Frame;

typedef struct _SimLaser_tf
{
	F32 base_laser_cos_;
	F32 base_laser_sin_;

}SimLaser_tf;

typedef struct _SPOS_CONFIDENCE
{

	SAMCL_CONFIDENCE confidence_;
	SPos pos_;

}SPOS_CONFIDENCE;

typedef struct _SView_Data
{

	char name_[200];

	U32 ilen_;
	U8* uc_data_;

}SView_Data;

typedef struct  _KPS_VERSION
{
	U8 v_main_;
	U8 v_sub_1_;
	U8 v_sub_2_;
	U8 temp_;

}KPS_VERSION;

typedef struct _STASK_STA
{

	typedef enum{
		TASK_IDLE,
		TASK_SET,
		TASK_CHECK_SET,
		TASK_DOING,
		TASK_DONE,
		TASK_ERR
	}ETask_Sta;
	U64 err_code_;
	S32 sub_err_code_;
	ETask_Sta task_sta_;

}STASK_STA;

typedef struct _SBattery
{
	U64 time_stamp_;
	F32 percent_;
	F32 voltage_;
	F32 charge_current_;
	F32 run_current_;
	int set_contactor_out_;
	int get_contactor_in_;
}SBattery;

typedef struct _SRobot_Inf
{
	SOdomSpeed odom_;
	SPos amcl_pos_;
	SPOS_CONFIDENCE ref_pos_;
	SBattery bat_;
	char group_[100];
	char carry_type_[100];

}SRobot_Inf;

typedef struct _SCentralController_Info
{
	char ch_ip_[20];
	int regist_port_;

	KPS_VERSION ver_;
	char key_[200];
	char back_[300];

}SCentralController_Info;


typedef struct _SAGV_Info
{
	KPS_VERSION ver_;
	
	int id_;
	char ch_ip_[20];
	int rpc_port_;
	int action_rpc_port_;

	int status_;
	AGV_TYPE agv_type_;
	
	char ch_msg_[200];
	char back_[100];

	//int i_lock_; //0:off line 1:lock 2:unlock 

}SAGV_Info;


typedef struct _SWorldLM
{
	SPos robot_in_world_;
	SPos landmark_in_robot_;
	SPos landmark_in_world_;
}SWorldLM;

typedef struct _SHeartBeat
{
	int i_heart_beat_;
	int i_sim_speed_;

}SHeartBeat;

typedef struct _SSteering
{
	int id_;
	SPos pos_;

	F32 set_speed_;
	F32 set_angle_;

	F32 cur_speed_;
	F32 cur_angle_;

	F32 max_angle_;
	F32 min_angle_;

	F32 zero_angle_;

}SSteering;

typedef struct _SCanframe
{
	int can_id_;
	U8 len_;
	U8 data_[64];

}SCanframe;

typedef struct
{
	int start_node_id_;
	int end_node_id_;
	ORIENTAION orientation_;

}SEdge_ori;

typedef struct _SMenu_permission
{
	std::string str_user_;
	int i_permission_;
	bool b_available_;

}SMenu_permission;
//have string in
typedef struct _SDIO_NM_INDEX
{
	std::string str_fnc_nm_;
	std::string str_dev_nm_;
	std::string str_type_;

	int i_dio_index_;

	std::string str_value_;


} SDIO_NM_INDEX;

typedef struct _SSQrCode
{

	U32 qr_id_;
	U64 time_stemp_;
	SPos pos_;

	char ch_des_[200];

}SQrCode;

typedef struct _SSEncoder
{

	S32 total_counts_;
	S16 single_counts_;
	S16 rot_num_;
	U8  dir_;
	S16  rpm_;
	U8  back_[1];
}SEncoder;

typedef struct _SSRefForbidden
{
	U64 time_stemp_;
	U16 cnt_time_;
	F32 forbidden_begin_;
	F32 forbidden_end_;

}SRefForbidden;

typedef struct _SSTPos
{
	U64 time_stemp_;
	SPos pos_;

}STPos;

#define BASE_LASER "base_laser"  //laser in base link
#define BASE_CAMERA "base_camera" //camera in base link
#define BASE_LINK  "base_link" //center of robot rotation 
#define BASE_ODOM  "base_odom" //pos relative to init pos by odom

#define PRODUCER  "producer" 
#define CONSUMER  "consumer" 
#define STORAGE   "storage" 

#endif//_ROBOT_STRUCT_WANGHONGTAO_20150831_

