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

 
set(TEST_CH_72_SRC

	feature_extraction.cpp
)

IF(CMAKE_BUILD_TYPE MATCHES "release")


if(WIN32)
set(TEST_CH_72_LIB
	#g2o_core
	#g2o_solver_csparse
	#g2o_stuff
	#g2o_csparse_extension
	#g2o_ext_csparse
	#libg2o_slam
	WS2_32.lib
	${OpenCV_LIBS}  
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_CH_72_LIB
	#g2o_core
	#g2o_solver_csparse
	#g2o_stuff
	#g2o_csparse_extension
	#g2o_ext_csparse
	#libg2o_slam
	protobuf
	pthread
    	rt
 	${OpenCV_LIBS}   
	${Boost_LIBRARIES} 
	
)
endif()

add_executable(test_ch_72d ${TEST_CH_72_SRC})
target_link_libraries(test_ch_72d ${TEST_CH_72_LIB})

ELSE()

if(WIN32)
set(TEST_CH_72_LIB
	
	#g2o_core_d
	#g2o_solver_csparse_d
	#g2o_stuff_d
	#g2o_csparse_extension_d
	#g2o_ext_csparse_d
	#libg2o_slam
	WS2_32.lib
	${OpenCV_LIBS}   
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_CH_72_LIB
	#g2o_core_d
	#g2o_solver_csparse_d
	#g2o_stuff_d
	#g2o_csparse_extension_d
	#g2o_ext_csparse_d
	#libg2o_slam
	protobuf
	pthread
	rt
	${OpenCV_LIBS}  
	${Boost_LIBRARIES}
)
endif()

add_executable(test_ch_72 ${TEST_CH_72_SRC})
target_link_libraries(test_ch_72 ${TEST_CH_72_LIB})
ENDIF()




