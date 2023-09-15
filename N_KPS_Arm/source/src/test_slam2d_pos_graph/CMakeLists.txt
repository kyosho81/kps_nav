include_directories(${KPS_ARM_SDK_PATH}/include/g2o_slam)
include_directories(${KPS_ARM_THIRD_PARTY_PATH}/include)

IF(ARM)
	IF(SURO)
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/lib)
	ELSE(SURO)
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/lib4418/lib)
	ENDIF(SURO)
	
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/hasp)
ELSE(ARM)
	IF(WIN32)
		IF(CMAKE_BUILD_TYPE MATCHES "release")
		link_directories(${KPS_ARM_THIRD_PARTY_PATH}/x64/release)
		ELSE()
		link_directories(${KPS_ARM_THIRD_PARTY_PATH}/x64/debug)
		ENDIF()
	ELSE(WIN32)
		link_directories(${KPS_ARM_THIRD_PARTY_PATH}/x64/)
	ENDIF(WIN32)
ENDIF(ARM)




set(TEST_SLAM2D_POS_GRAPH_SRC

	main.cpp
)

IF(CMAKE_BUILD_TYPE MATCHES "release")

if(WIN32)
set(TEST_SLAM2D_POS_GRAPH_LIB
	libcom
	libtransfer
	libmsg_pump
	libshared_pool
	libdevice_base
	libsensor
	librobot
	libchassis
	libpf
	libxmlrpc
	liblog4cpp
	libproject
	libreflected_pillar_loc
	libpolarscanmatcher
	libg2o_slam
	g2o_core
	g2o_solver_csparse
	g2o_stuff
	g2o_csparse_extension
	g2o_ext_csparse
	WS2_32.lib  
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_SLAM2D_POS_GRAPH_LIB
    libcom
	libtransfer
	libmsg_pump
	libshared_pool
	libdevice_base
	libsensor
	librobot
	libchassis
	libpf
	libxmlrpc
	#libldk
	liblog4cpp
	libproject
	libreflected_pillar_loc
	libpolarscanmatcher
	libg2o_slam
	protobuf
	pthread
    rt  
	${Boost_LIBRARIES} 
	
)
endif()

add_executable(test_slam2d_pos_graphd ${TEST_SLAM2D_POS_GRAPH_SRC})
target_link_libraries(test_slam2d_pos_graphd ${TEST_SLAM2D_POS_GRAPH_LIB})

ELSE()

if(WIN32)
set(TEST_SLAM2D_POS_GRAPH_LIB
	libpolarscanmatcher
	libgridfastslam
    libscanmatcher
    libgsensor
   	libutils
	libsensor
	libgsensor
	libslam
	g2o_core_d
	g2o_solver_csparse_d
	g2o_stuff_d
	g2o_csparse_extension_d
	g2o_ext_csparse_d
	libg2o_slam
	WS2_32.lib  
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_SLAM2D_POS_GRAPH_LIB
    
	libcom
	libtransfer
	libmsg_pump
	libshared_pool
	libdevice_base
	libsensor
	librobot
	libchassis
	libpf
	libxmlrpc
	libldk
	liblog4cpp
	libproject
	libreflected_pillar_loc
	libpolarscanmatcher
	libg2o_slam
	protobuf
	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_slam2d_pos_graphd ${TEST_SLAM2D_POS_GRAPH_SRC})
target_link_libraries(test_slam2d_pos_graphd ${TEST_SLAM2D_POS_GRAPH_LIB})
ENDIF()




