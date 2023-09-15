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




set(TORORIAL_SLAM2D_SRC

	tutorial_slam2d.cpp
)

IF(CMAKE_BUILD_TYPE MATCHES "release")
#IF(CMAKE_DEBUG_POSTFIX)

if(WIN32)
set(TORORIAL_SLAM2D_LIB
	g2o_core
	g2o_solver_csparse
	g2o_stuff
	g2o_csparse_extension
	g2o_ext_csparse
	libg2o_slam
	WS2_32.lib  
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TORORIAL_SLAM2D_LIB
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
	libg2o_slam
	protobuf
	pthread
    rt  
	${Boost_LIBRARIES} 
	
)
endif()

add_executable(tutorial_slam2d ${TORORIAL_SLAM2D_SRC})
target_link_libraries(tutorial_slam2d ${TORORIAL_SLAM2D_LIB})

ELSE()

if(WIN32)
set(TORORIAL_SLAM2D_LIB
	
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

set(TORORIAL_SLAM2D_LIB
    libcomd
	libtransferd
	libmsg_pumpd
	libshared_poold
	libdevice_based
	libsensord
	librobotd
	libchassisd
	libpfd
	libxmlrpcd
	libldkd
	liblog4cppd
	libprojectd
	libreflected_pillar_locd
	libg2o_slamd
	protobuf
	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(tutorial_slam2 ${TORORIAL_SLAM2D_SRC})
target_link_libraries(tutorial_slam2 ${TORORIAL_SLAM2D_LIB})
ENDIF()




