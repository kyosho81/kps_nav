#ifndef _MSG_DEF_KYOSHO_20150831_
#define _MSG_DEF_KYOSHO_20150831_

#define PUB_INIT_POS ("init_pos")
#define PUB_LASER_EX ("laser_ex")
#define PUB_LASER_EX2 ("laser_ex2")
#define PUB_AMCL_LASER ("amcl_laser")
#define PUB_LASER_EX_CAB ("laser_ex_cab")
#define PUB_DY_SIM_LASER ("dynamic_sim_laser")
#define PUB_DEVICE_STATUS ("device_status")
#define PUB_DEVICE_STATUS_ERR ("device_status_err")
#define PUB_CHASSIS_ODOM_SPEED ("chassis_odom_speed")
#define PUB_CHASSIS_SET_SPEED ("chassis_set_speed")
#define PUB_REMOTE_SET_SPEED ("remote_set_speed")
#define PUB_AMCL_POS ("amcl_pos")
#define PUB_AMCL_PARTICLES ("amcl_particles")
#define PUB_REFLECTOR_LIST ("reflector_list")
#define PUB_REFLECTOR_POS ("reflector_pos")
#define PUB_REFLECTOR_LASER_POS ("reflector_laser_pos")
#define PUB_LASER_EX_REFLECTOR ("laser_ex_reflector")
#define PUB_LASER_EX_REFLECTOR2 ("laser_ex_reflector2")
#define PUB_AMCL_CONFIDENCE ("amcl_confidence")
#define PUB_AMCL_POS_CONFIDENCE ("amcl_pos_confidence")
#define PUB_SET_MAP_CMD ("set_map_cmd")
#define PUB_REF_LOCAL_POS ("ref_local_pos")

#define PUB_LOG_PLAYBACK ("log_playback")
#define PUB_AMCL_CONF_PLAYBACK ("amcl_confidence_playback")
#define PUB_AMCL_ENTROPY_PLAYBACK ("amcl_entropy_playback")
#define PUB_VIEW_DATA_PLAYBACK ("view_data_playback")
#define PUB_PLAYBACK "_PLAYBACK"

#define PUB_SPECIAL_LOC_POS     ("special_loc_pos")
#define PUB_SPECIAL_LANDMARK_POS ("special_landmark_pos")
#define TH_PUB_SPECIAL_LOC_SET_CMD ("set_special_cmd")


#define PUB_RUN_STATUS ("mv_run_status")
#define PUB_REFLASH_MAP_OVER ("reflash_map_over")

#define TH_PUB_SEG_PATH ("msg_seg_path")
#define TH_PUB_HEART_BEAT ("msg_heart_beat")
#define TH_PUB_PAUSE ("pause")


#define PUB_ACT_STATE_HEAD ("actstate_") //extask action msg head
#define PUB_ACT_PARA_HEAD ("actpara_") //extask action para head

#define PUB_TASK_FORK ("task_fork")//task_fork to sim_agv_fork
#define PUB_ACT_FORK_STATE ("act_fork_state") //sim_agv_fork to task_fork
#define PUB_ACT_FORK_DATA ("act_fork_data")   //sim_agv_fork to data server

#define PUB_ACT_SEG_PATH ("act_seg_path")   //sim_agv_move to act

#define PUB_SET_DYNAMIC_SPEED ("set_dynamic_speed")   //pub dynamic speed, action check done should pause
#define PUB_PRIORITY_SPEED ("priority_speed") 
#define PUB_DYNAMIC_LOC_SCAN ("dynamic_loc_scan")
#define PUB_DYNAMIC_LOCACTION ("dynamic_location")

#define PUB_BATTERY_CNT_OUT ("battery_contactor_out")
#define PUB_BATTERY_CNT_IN ("battery_contactor_in")
#define PUB_BATTERY_STATE ("battery_state")

#define PUB_ROTATION_POS "rotation_pos"
#define PUB_LIFT_POS "lift_pos"
#define PUB_DI_AI "di_ai_"
#define PUB_DO_AO "do_ao_"
#define PUB_DI "di"
#define PUB_AI "ai"
#define PUB_FNC_DI "fnc_di_"
#define PUB_FNC_DO "fnc_do_"
#define PUB_AO "ao"
#define PUB_FAI "fai"
#define PUB_AIF "fai_"
#define PUB_FAO "fao"
#define PUB_AOF "fao_"
#define PUB_FNC_FAI "fnc_fai_"
#define PUB_FNC_FAO "fnc_fao_"

#define PUB_QR_CODE "qrcode"
#define PUB_ERR_MSG ("error_msg")
#define PUB_REF_FORBIDDEN ("ref_forbidden_range")

#define TH_PUB_DI_AI "di_ai_"
#define TH_PUB_DO_AO "do_ao_"
#define TH_PUB_FNC_DO "fnc_do"
#define TH_PUB_AO "ao"
#define TH_PUB_DI "di"
#define TH_PUB_AI "ai"
#define TH_PUB_FAI "fai"
#define TH_PUB_AIF "fai_"
#define TH_PUB_FAO "fao"
#define TH_PUB_AOF "fao_"

#define TH_PUB_QR_CODE "qrcode"
#define TH_PUB_IMU     "imu"
#define TH_PUB_REF_LOCAL_POS ("ref_local_pos")
#define TH_PUB_DYNAMIC_LOCACTION ("dynamic_location")

#define TH_PUB_ERR_MSG ("error_msg")

#define TH_PUB_BATTERY_CNT_OUT ("battery_contactor_out")
#define TH_PUB_BATTERY_CNT_IN ("battery_contactor_in")
#define TH_PUB_BATTERY_STATE ("battery_state")


#define DYNAMIC_SPEED_EMERGENCY 0
#define DYNAMIC_SPEED_COLLISION 1
#define DYNAMIC_SPEED_OBS_SLOW 2
#define DYNAMIC_SPEED_OBS_STOP 3
#define DYNAMIC_SPEED_MSG_CYCLYE 4
#define DYNAMIC_SPEED_TASK_SYN 100

#endif//_MSG_DEF_KYOSHO_20150831_

