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

 
set(TEST_DBOW3_SRC

	#demo_general.cpp
	feature_training.cpp
)

IF(CMAKE_BUILD_TYPE MATCHES "release")

if(WIN32)
set(TEST_DBOW3_LIB
	#g2o_core
	#g2o_solver_csparse
	#g2o_stuff
	#g2o_csparse_extension
	#g2o_ext_csparse
	#libg2o_slam
	libdbow3
	WS2_32.lib
	${OpenCV_LIBS}  
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_DBOW3_LIB
	#g2o_core
	#g2o_solver_csparse
	#g2o_stuff
	#g2o_csparse_extension
	#g2o_ext_csparse
	#libg2o_slam
	libdbow3
	protobuf
	pthread
    rt
	${OpenCV_LIBS}   
	${Boost_LIBRARIES} 
	
)
endif()

add_executable(test_dbow3d ${TEST_DBOW3_SRC})
target_link_libraries(test_dbow3d ${TEST_DBOW3_LIB})

ELSE()

if(WIN32)
set(TEST_DBOW3_LIB
	
	#g2o_core_d
	#g2o_solver_csparse_d
	#g2o_stuff_d
	#g2o_csparse_extension_d
	#g2o_ext_csparse_d
	#libg2o_slam
	libcom
	libdbow3
	WS2_32.lib
	${OpenCV_LIBS}   
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_DBOW3_LIB

	libshared_pool
	librobot
	liblog4cpp
	liblaser2d_loopclosure
	libdbow3
	libprotobuf_msg
	protobuf
	pthread
    rt
    ${OpenCV_LIBS} 
	${Boost_LIBRARIES} 
	
)
endif()

add_executable(test_dbow3 ${TEST_DBOW3_SRC})
target_link_libraries(test_dbow3 ${TEST_DBOW3_LIB})
ENDIF()




