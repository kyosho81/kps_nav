add_definitions(-DBOOST_NO_MEMBER_TEMPLATE_FRIENDS)

INCLUDE_DIRECTORIES("D:/lib/qwt-6.1.2/src")
link_directories("D:/lib/qwt-6.1.2/lib")

set(CMAKE_PREFIX_PATH "D:/Qt/4.8.6/bin")
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
INCLUDE_DIRECTORIES( ${QT_INCLUDE_DIR} )

#find_package(OpenCV REQUIRED )
#INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )
#link_directories(${OpenCV_LIBS})
#message(${OPENCV_INCLUDE_DIR})
#message(${OpenCV_LIBS})

include_directories(${KPS_ARM_THIRD_PARTY_PATH}/include)
include_directories(${KPS_ARM_SDK_PATH}/include/protobuf_msg)

IF(ARM)
	IF(SURO)
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/lib)
	ELSE(SURO)
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/lib4418/lib)
	ENDIF(SURO)
ELSE(ARM)
	
	IF(CMAKE_BUILD_TYPE MATCHES "release")
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/x64/release)
	ELSE()
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/x64/debug)
	ENDIF()
	
ENDIF(ARM)


SET(KPS_MONITOR_APP_MOC_SRCS
	#ADD QT OBJECT .h FILE HERE
	
	kps_main_win.h
	action_data_model.h
	action_monitor_dlg.h
	action_monitor_table.h
	dev_data_model.h
	dev_monitor_dlg.h

	action.h
	file_list_dlg.h
	ip_list_dlg.h
	item_collection.h
	calib_dlg.h
	log_priority_dlg.h
	para_dlg.h
	agv_manage_model.h
	agv_manage_dlg.h
	agv_manage_table.h
	data_manage_dlg.h
	data_edit_dlg.h
	data_tree.h
	path_search_dlg.h
	order_dlg.h
	role_model.h
	role_table.h
	order_model.h
	order_table.h
	interface_dlg.h
	interface_table.h
	interface_model.h
	interface_delegate.h

	checkbox_delegate.h
	combox_delegate.h
	data_delegate.h
	dbline_delegate.h
	progress_delegate.h
	readonly_delegate.h
	spinbox_delegate.h
	time_delegate.h
	manual_model.h
	manual_table.h
	strategy_dlg.h
	strategy_model.h
	strategy_table.h
	manual_ctl_dlg.h
	shape_dlg.h
	dio_dlg.h
	dio_model.h
	dio_table.h
	task_flow_dlg.h
	task_flow_para_dlg.h
	task_flow_edit_dlg.h
	flow_main_para_tab.h
	flow_extern_para_tab.h
	task_flow_table.h
	task_flow_model.h
	#CustomButton.h
	#mouse_event.h
)


set(KPS_MONITOR_APP_SRCS
	
	main.cpp
	kps_main_win.cpp
	action_data_model.cpp
	action_monitor_table.cpp
	action_monitor_dlg.cpp
	dev_monitor_dlg.cpp
	dev_data_model.cpp

	action.cpp
	file_list_dlg.cpp
	ip_list_dlg.cpp
	item_collection.cpp
	auto_cover.cpp
	calib_dlg.cpp
	log_priority_dlg.cpp
	para_dlg.cpp
	area.cpp
	sep_block.cpp
	block_path.cpp
	#CustomButton.cpp
	#mouse_event.cpp
	agv_manage_model.cpp
	agv_manage_dlg.cpp
	agv_manage_table.cpp
	data_manage_dlg.cpp
	data_edit_dlg.cpp
	data_tree.cpp
	path_search_dlg.cpp
	order_dlg.cpp
	role_model.cpp
	role_table.cpp
	order_model.cpp
	order_table.cpp
	interface_dlg.cpp
	interface_table.cpp
	interface_model.cpp
	interface_delegate.cpp

	checkbox_delegate.cpp
	combox_delegate.cpp
	data_delegate.cpp
	dbline_delegate.cpp
	progress_delegate.cpp
	spinbox_delegate.cpp
	time_delegate.cpp
	manual_model.cpp
	manual_table.cpp
	strategy_dlg.cpp

	strategy_model.cpp
	strategy_table.cpp
	action_permission.cpp

	manual_ctl_dlg.cpp
	shape_dlg.cpp
	dio_dlg.cpp
	dio_model.cpp
	dio_table.cpp
	task_flow_dlg.cpp
	task_flow_model.cpp

	task_flow_para_dlg.cpp
	task_flow_edit_dlg.cpp
	flow_main_para_tab.cpp
	flow_extern_para_tab.cpp
	task_flow_table.cpp
)

set(KPS_MONITOR_APP_UIS
	#ADD UIS FILE HERE ##

 )

set(KPS_MONITOR_APP_QCCS 
	#ADD .qrc FILE HERE###
 
)
IF(CMAKE_BUILD_TYPE MATCHES "release")
set(KPS_MONITOR_APP_LIBS
  #ADD LIB HERE###
  WS2_32.lib
  libcom
  libmapserver
  libtransfer
  libmsg_pump
  libdevice_base
  libsensor
  librobot
  libchassis
  libplot
  qwt
  libpf
  libxmlrpc
  libscene
  libproject
  libslam
  libscanmatcher
  libgridfastslam
  libpngx
  libprotobuf_msg
  libbag
  libgsensor
  libshared_pool
  libgridfastslam
  libutils
  libdevice_base
  libplot
  libreflected_pillar_loc
  liblog4cpp
  liblog
  libslam
  libaction

  g2o_core
  g2o_solver_csparse
  g2o_stuff
  g2o_csparse_extension
  g2o_ext_csparse
  libg2o_slam
  libgeometry

  libflirtutils
  libflirtsensors
  libflirtfeature
  libflirtsensorsstream
  libflirtgui

  libdbow3
  liblaser2d_loopclosure
  libgn_scanmatch
  liboctomap
  libopencv_cus
  libproject
  libsub_map_localization
  libcalib
  libdispatching
  libmovement
  libinterface
  libdynamic_loc
  libpolarscanmatcher

  libprotobuf
  QtPropertyBrowser
  ${QT_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)
 
ELSE()
set(KPS_MONITOR_APP_LIBS
  #ADD LIB HERE###
  WS2_32.lib
  libcom
  libmapserver
  libtransfer
  libmsg_pump
  libdevice_base
  libsensor
  librobot
  libchassis
  libplot
  qwt
  libpf
  libxmlrpc
  libscene
  libproject
  libslam
  libscanmatcher
  libgridfastslam
  libpngx
  libprotobuf_msg
  libbag
  libgsensor
  libshared_pool
  libgridfastslam
  libutils
  libdevice_base
  libplot
  libreflected_pillar_loc
  liblog4cpp
  liblog
  libslam
  libaction

  g2o_core_d
  g2o_solver_csparse_d
  g2o_stuff_d
  g2o_csparse_extension_d
  g2o_ext_csparse_d
  libg2o_slam
  libgeometry

  libflirtutils
  libflirtsensors
  libflirtfeature
  libflirtsensorsstream
  libflirtgui

  libdbow3
  liblaser2d_loopclosure
  libgn_scanmatch
  liboctomap
  libopencv_cus
  libproject
  libsub_map_localization
  libcalib
  libdispatching
  libmovement
  libinterface
  libdynamic_loc
  libpolarscanmatcher

  libprotobuf
  QtPropertyBrowser
  ${QT_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)
ENDIF()
  
qt4_automoc(${KPS_MONITOR_APP_SRCS})

QT4_WRAP_CPP(KPS_MONITOR_APP_MOC ${KPS_MONITOR_APP_MOC_SRCS})

QT4_WRAP_UI(KPS_MONITOR_APP_UIS_H ${KPS_MONITOR_APP_UIS})

QT4_ADD_RESOURCES(KPS_MONITOR_APP_QCCS_SRCS ${KPS_MONITOR_APP_QCCS})

ADD_DEFINITIONS(-D_REENTRANT -DQT_NO_DEBUG -DQT_SQL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED )

add_definitions(-DBOOST_NO_MEMBER_TEMPLATE_FRIENDS)


IF(CMAKE_BUILD_TYPE MATCHES "release")
add_executable(kps_monitor ${KPS_MONITOR_APP_SRCS} ${KPS_MONITOR_APP_MOC} ${KPS_MONITOR_APP_UIS_H} ${KPS_MONITOR_APP_QCCS_SRCS} )
message(${KPS_MONITOR_APP_LIBS})
target_link_libraries(kps_monitor ${KPS_MONITOR_APP_LIBS} )
ADD_DEPENDENCIES(kps_monitor libplot)
ELSE()
add_executable(kps_monitor ${KPS_MONITOR_APP_SRCS} ${KPS_MONITOR_APP_MOC} ${KPS_MONITOR_APP_UIS_H} ${KPS_MONITOR_APP_QCCS_SRCS} )
message(${KPS_MONITOR_APP_LIBS})
target_link_libraries(kps_monitor ${KPS_MONITOR_APP_LIBS} )
ADD_DEPENDENCIES(kps_monitor libplotd)
ENDIF()
