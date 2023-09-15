#ifndef _DIO_DEFINE_WANGHONGTAO_20221210_
#define _DIO_DEFINE_WANGHONGTAO_20221210_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include "buffer_con.hpp"


// #define AI_BAT_VOLTAGE 0//"batttery_voltage"
// #define AI_BAT_PERCENT 1//"batttery_percent"
// #define DI_BAT_ONCHARGE 0//"batttery_good_contact"
// 
// #define DO_BAT_CP_READY 0//"batttery_charging_plate_ready"


#define DIO_IO_TYPE          "dio_io_type"

#define DIO_TYPE_DI          "dio_type_di"     
#define DIO_TYPE_DO          "dio_type_do" 
#define DIO_TYPE_AI          "dio_type_ai" 
#define DIO_TYPE_AO          "dio_type_ao" 
#define DIO_TYPE_FAI         "dio_type_fai" 
#define DIO_TYPE_FAO         "dio_type_fao"

#define DIO_DEV_TYPE         "dio_dev_type"

#define DIO_DEV_ONBOARD      "onboard_dio"
#define DIO_DEV_PLCLUJIE     "plclujie_dio"
#define DIO_DEV_EASYWAY      "easywaytec_encoder"
#define DIO_DEV_MUSHINY      "mushiny_driver_dio"
#define DIO_DEV_ACTION_DO    "action_do"

#define DI_00                0
#define DI_01                1
#define DI_02                2
#define DI_03                3
#define DI_04                4
#define DI_05                5
#define DI_06                6
#define DI_07                7
#define DI_08                8
#define DI_09                9
#define DI_10                10
#define DI_11                11
#define DI_12                12
#define DI_13                13
#define DI_14                14
#define DI_15                15
#define DI_16                16
#define DI_17                17
#define DI_18                18
#define DI_19                19
#define DI_20                20
#define DI_21                21
#define DI_22                22
#define DI_23                23

#define DO_00                0
#define DO_01                1
#define DO_02                2
#define DO_03                3
#define DO_04                4
#define DO_05                5
#define DO_06                6
#define DO_07                7
#define DO_08                8
#define DO_09                9
#define DO_10                10
#define DO_11                11
#define DO_12                12
#define DO_13                13
#define DO_14                14
#define DO_15                15
#define DO_16                16
#define DO_17                17
#define DO_18                18
#define DO_19                19
#define DO_20                20
#define DO_21                21
#define DO_22                22
#define DO_23                23

#define AIF_00                0
#define AIF_01                1
#define AIF_02                2
#define AIF_03                3
#define AIF_04                4
#define AIF_05                5
#define AIF_06                6
#define AIF_07                7

#define AOF_00                0
#define AOF_01                1
#define AOF_02                2
#define AOF_03                3
#define AOF_04                4
#define AOF_05                5
#define AOF_06                6
#define AOF_07                7


#define DI_FNC_TYPE             "di_fnc_type"

#define DI_FNC_EMERGENCY        "di_fnc_emergency"
#define DI_FNC_CLEAR_ERROR      "di_fnc_clear_error"
#define DI_FNC_AUTO_MANUAL      "di_fnc_auto_manual"
#define DI_FNC_EN_DESH_PROOF    "di_fnc_en_dash_proof"
#define DI_FNC_DASH_PROOF_1     "di_fnc_dash_proof_1"   
#define DI_FNC_DASH_PROOF_2     "di_fnc_dash_proof_2"  
#define DI_FNC_DASH_PROOF_3     "di_fnc_dash_proof_3"  
#define DI_FNC_DASH_PROOF_4     "di_fnc_dash_proof_4"  
#define DI_FNC_FNC_PAYLOADS     "di_fnc_payloads"  
#define DI_FNC_FNC_LIFT_ZERO    "di_fnc_lift_zero"  
#define DI_FNC_FNC_LIFT_OVER    "di_fnc_lift_over"  

#define DI_FNC_STOP_FORKLEFT     "di_fnc_stop_forkleft"  
#define DI_FNC_STOP_FORKRIGHT    "di_fnc_stop_forkringht"  

// #define DI_FNC_STOP_FORWARD     "di_fnc_stop_forward"  
// #define DI_FNC_SLOW_FORWARD     "di_fnc_slow_forward"  
// 
// #define DI_FNC_STOP_BACKWARD    "di_fnc_stop_backward"  
// #define DI_FNC_SLOW_BACKWARD    "di_fnc_slow_backward"  
// 
// #define DI_FNC_STOP_LIFT        "di_fnc_stop_lift"  
// #define DI_FNC_SLOW_LIFT        "di_fnc_slow_lift"  
// 
// #define DI_FNC_STOP_RIGHT       "di_fnc_stop_right"  
// #define DI_FNC_SLOW_RIGHT       "di_fnc_slow_right"

#define DI_FNC_LS_LOW           "di_fnc_stop_ls_low_speed" 
#define DI_FNC_LS_SLOW          "di_fnc_stop_ls_slow_speed" 
#define DI_FNC_LS_STOP          "di_fnc_stop_ls_stop" 

#define DI_FNC_TURN_CW_INP      "di_fnc_turn_cw_inp"  
#define DI_FNC_TURN_CCW_INP     "di_fnc_turn_ccw_inp"  
#define DI_FNC_TURN_CW          "di_fnc_turn_cw"  
#define DI_FNC_TURN_CCW         "di_fnc_turn_ccw"  
#define DI_FNC_BT_CONNECT       "di_fnc_battery_connect" 

#define DO_FNC_TYPE             "do_fnc_type"

#define DO_FNC_DRV_ENABLE       "do_fnc_driver_enable"
#define DO_FNC_ERROR_LIHGT      "do_fnc_error_light"
#define DO_FNC_LEFT_LIHGT       "do_fnc_left_light"
#define DO_FNC_RIGHT_LIHGT      "do_fnc_right_light"
#define DO_FNC_AUTO_MANUAL      "do_fnc_auto_manual"
#define DO_FNC_ONLINE           "do_fnc_online"
#define DO_FNC_LOADING          "do_fnc_loading"
#define DO_FNC_BT_CHARGE        "do_fnc_bt_charge"


#define DO_FNC_FAST_FORWARD     "do_fnc_fast_forward"
//define DO_FNC_SLOW_FORWARD     "do_fnc_slow_forward"

#define DO_FNC_FAST_BACKWARD    "do_fnc_fast_backward"
//#define DO_FNC_SLOW_BACKWARD    "do_fnc_slow_backward"

#define DO_FNC_FAST_LEFT        "do_fnc_fast_left"
//#define DO_FNC_SLOW_LEFT        "do_fnc_slow_left"

#define DO_FNC_FAST_RIGHT       "do_fnc_fast_right"
//#define DO_FNC_SLOW_RIGHT       "do_fnc_slow_right"

#define DO_FNC_TURN_CW_INP      "do_fnc_turn_cw_imp"
#define DO_FNC_TURN_CCW_INP     "do_fnc_turn_ccw_imp"

#define DO_FNC_TURN_CW          "do_fnc_turn_cw"
#define DO_FNC_TURN_CCW         "do_fnc_turn_ccw"

#define AIF_FNC_TYPE            "ai_fnc_type"

#define AIF_FNC_LIFT_POS        "ai_fnc_lift_pos"
#define AIF_FNC_ROT_POS         "ai_fnc_rot_pos"
#define AIF_FNC_LIFT_SPEED      "ai_fnc_lift_speed"
#define AIF_FNC_ROT_SPEED       "ai_fnc_rot_speed"

#define AOF_FNC_TYPE            "ao_fnc_type"

#define AOF_FNC_LIFT_POS        "ao_fnc_lift_pos"
#define AOF_FNC_ROT_POS         "ao_fnc_rot_pos"
#define AOF_FNC_LIFT_SPEED      "ao_fnc_lift_speed"
#define AOF_FNC_ROT_SPEED       "ao_fnc_rot_speed"

#define AO_LIFT_SPEED 1   //ao 0
#define AO_LIFT_POS   2   //ao 1

#define AO_ROT_SPEED  2   //ao 2
#define AO_ROT_POS    3   //ao 3

#define AI_LIFT_POS   1   //ai 0
#define AI_LIFT_SPEED 2   //ai 1

#define DI_HL_EMERGENCY 0 //di emergency hight low activate

#endif //_DIO_DEFINE_WANGHONGTAO_20221210_