include_directories(include)
IF(BUILD_SDK)

#ADD_SUBDIRECTORY(cordic_test)
#ADD_SUBDIRECTORY(shared_test)
#ADD_SUBDIRECTORY(xmlrpc_test)
#ADD_SUBDIRECTORY(test_astar)
#ADD_SUBDIRECTORY(test_angle_ctl)
#ADD_SUBDIRECTORY(test_configs)

#ADD_SUBDIRECTORY(interprocess_core)
#ADD_SUBDIRECTORY(interprocess_laser)
#ADD_SUBDIRECTORY(interprocess_urg)
#ADD_SUBDIRECTORY(interprocess_laser_sim)
#ADD_SUBDIRECTORY(interprocess_chassis)
#ADD_SUBDIRECTORY(interprocess_R2000)
#ADD_SUBDIRECTORY(interprocess_data_server)
#ADD_SUBDIRECTORY(interprocess_bag_player)
#ADD_SUBDIRECTORY(interprocess_keycontrol)
#ADD_SUBDIRECTORY(interprocess_remote)
#ADD_SUBDIRECTORY(interprocess_map_global_inf)
#ADD_SUBDIRECTORY(interprocess_map_laser_inf)
#ADD_SUBDIRECTORY(interprocess_pf)
#ADD_SUBDIRECTORY(interprocess_map_path)
#ADD_SUBDIRECTORY(interprocess_planner_tray)
#ADD_SUBDIRECTORY(interprocess_slam)
#ADD_SUBDIRECTORY(interprocess_motion_diff)
#ADD_SUBDIRECTORY(test_msg_pump)
#ADD_SUBDIRECTORY(test_msg_array_pump)
ADD_SUBDIRECTORY(test_transfer)
ADD_SUBDIRECTORY(kps_core)
#ADD_SUBDIRECTORY(kps_data_server)
#ADD_SUBDIRECTORY(kps_map_server)

#ADD_SUBDIRECTORY(kps_imu)
#ADD_SUBDIRECTORY(kps_movement)

#ADD_SUBDIRECTORY(protobuf_test)
#ADD_SUBDIRECTORY(project_test)
#ADD_SUBDIRECTORY(pca_test)
#ADD_SUBDIRECTORY(md5test)
#ADD_SUBDIRECTORY(file_test)
#ADD_SUBDIRECTORY(tcp_log_test)
#ADD_SUBDIRECTORY(test_boost_thread_pool)
#ADD_SUBDIRECTORY(test_r2000)
#ADD_SUBDIRECTORY(test_eigen)
#ADD_SUBDIRECTORY(test_sophus)
#ADD_SUBDIRECTORY(test_linear_least_squares)
#ADD_SUBDIRECTORY(test_transfer_matrix)
#ADD_SUBDIRECTORY(testOdomFilterbyLaser)
#ADD_SUBDIRECTORY(interprocess_ex_move)



#ADD_SUBDIRECTORY(kps_localization)
#ADD_SUBDIRECTORY(kps_ex_movement)
#ADD_SUBDIRECTORY(kps_loopclosure)
#ADD_SUBDIRECTORY(kps_msg_log)
#ADD_SUBDIRECTORY(kps_play_back)
#ADD_SUBDIRECTORY(kps_action_manage)
#ADD_SUBDIRECTORY(kps_dynamic_loc)
#ADD_SUBDIRECTORY(kps_dio)
#ADD_SUBDIRECTORY(kps_keygen)

#ADD_SUBDIRECTORY(test_transfer)
#ADD_SUBDIRECTORY(test_odom)
ADD_SUBDIRECTORY(test_can)
#ADD_SUBDIRECTORY(test_kegen)
ADD_SUBDIRECTORY(test_md5)

#ADD_SUBDIRECTORY(kps_task_tray)
#ADD_SUBDIRECTORY(kps_special_loc)
#ADD_SUBDIRECTORY(kps_reflected_pillar)
#ADD_SUBDIRECTORY(kps_health_examination)
#ADD_SUBDIRECTORY(kps_server_log)
#ADD_SUBDIRECTORY(kps_config_conver)
#ADD_SUBDIRECTORY(test_rpc_para_server)
#ADD_SUBDIRECTORY(test_octomap)
#ADD_SUBDIRECTORY(test_pub_view_data)
#ADD_SUBDIRECTORY(test_sqlite3)
#ADD_SUBDIRECTORY(test_zlib_file)

#ADD_SUBDIRECTORY(test_ping)
#ADD_SUBDIRECTORY(test_schedule)
#ADD_SUBDIRECTORY(test_broadcast)
#ADD_SUBDIRECTORY(test_ransac)
#ADD_SUBDIRECTORY(calib_odom_sensor)
#ADD_SUBDIRECTORY(test_skeleton)
#ADD_SUBDIRECTORY(test_ipa_nav)
#ADD_SUBDIRECTORY(test_uuid)
#ADD_SUBDIRECTORY(test_seg_path_against)
#ADD_SUBDIRECTORY(test_data_time)

#ADD_SUBDIRECTORY(test_modbus)
#ADD_SUBDIRECTORY(test_canopen)
#ADD_SUBDIRECTORY(test_path)
#ADD_SUBDIRECTORY(test_wj712)
#ADD_SUBDIRECTORY(test_pavo2)
#ADD_SUBDIRECTORY(test_big_map)

if(WIN32)
	#ADD_SUBDIRECTORY(driver_win)
	#ADD_SUBDIRECTORY(test_QtProperty)
	#ADD_SUBDIRECTORY(test_flirt)
	#ADD_SUBDIRECTORY(test_loop_closure)
	#ADD_SUBDIRECTORY(tutorial_slam2d)
	#ADD_SUBDIRECTORY(test_slam2d_pos_graph)
	#ADD_SUBDIRECTORY(test_3d2d)
	#ADD_SUBDIRECTORY(test_2d2d)
	#ADD_SUBDIRECTORY(test_find_contour)
	#ADD_SUBDIRECTORY(test_opencv_erode)
	#ADD_SUBDIRECTORY(test_opencv_subdiv)
	#ADD_SUBDIRECTORY(calib_odom_sensor)
	
endif(WIN32)

ENDIF(BUILD_SDK)

ADD_SUBDIRECTORY(test_shared_msg)
ADD_SUBDIRECTORY(test_shared_pipe)
ADD_SUBDIRECTORY(test_shared_block)
ADD_SUBDIRECTORY(test_shared_locker)

#ADD_SUBDIRECTORY(test_interface)
#ADD_SUBDIRECTORY(interface_xmlrpc)
#ADD_SUBDIRECTORY(test_k_means)
#ADD_SUBDIRECTORY(test_DBow3)
#ADD_SUBDIRECTORY(test_ch_72)
#ADD_SUBDIRECTORY(test_pavo_laser)
#ADD_SUBDIRECTORY(test_gn_scanmatch)
#ADD_SUBDIRECTORY(test_laser_interpolation)
#ADD_SUBDIRECTORY(test_protobuf)
#ADD_SUBDIRECTORY(test_merge_odom)
#ADD_SUBDIRECTORY(test_forbidden_line)
#ADD_SUBDIRECTORY(test_lsd)
#ADD_SUBDIRECTORY(test_gpio)
ADD_SUBDIRECTORY(test_timer)
ADD_SUBDIRECTORY(test_modbustcp)

IF(ARM)

	
	IF(SURO)
	#ADD_SUBDIRECTORY(suro_localization)
	#ADD_SUBDIRECTORY(suro_dynamic_nav)
	ENDIF(SURO)
	#ADD_SUBDIRECTORY(test_neon)
	
ELSE()

	IF(SURO)
	#ADD_SUBDIRECTORY(suro_localization)
	#ADD_SUBDIRECTORY(suro_dynamic_nav)
	ENDIF(SURO)
	
	
	if(WIN32)
	#ADD_SUBDIRECTORY(kps_monitor)
	#ADD_SUBDIRECTORY(kps_sim_agv_app)
	else(WIN32)
	endif(WIN32)
	
	
ENDIF(ARM)

IF(BUILD_SDK)
	INSTALL(PROGRAMS CMakeLists.txt DESTINATION source/src)
	
	INSTALL(DIRECTORY
			include
			test_transfer
			test_interface
			interface_xmlrpc
			kps_localization_app
			#interprocess_core
			#interprocess_laser
			#interprocess_chassis
			#interprocess_data_server
			#interprocess_keycontrol
			#interprocess_map_global_inf
			#interprocess_map_laser_inf
			#interprocess_map_path
			#interprocess_planner_tray

			
			  DESTINATION source/src
	          FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.inl" PATTERN "*.cpp" PATTERN "CMakeLists.txt"
	          PATTERN ".svn" EXCLUDE 
	          )
ENDIF(BUILD_SDK)
