IF(WIN32)
ELSE(WIN32)

ENDIF()

include_directories(${KPS_ARM_SDK_PATH}/include/protobuf_msg)


IF(ARM)
	IF(SURO)
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/lib)
	ELSE(SURO)
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/lib4418/lib)
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/hasp)
	ENDIF(SURO)
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



set(TEST_R2000_SRC

	main.cpp
)

IF(CMAKE_BUILD_TYPE MATCHES "release")

if(WIN32)
set(TEST_R2000_LIB
	libcom
	#libldk
	libmovement
	libsensor
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_R2000_LIB
    libcom
	#libldk
	libmovement
	libsensor
	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_r2000 ${TEST_R2000_SRC})
target_link_libraries(test_r2000 ${TEST_R2000_LIB})

ELSE()

if(WIN32)
set(TEST_R2000_LIB
	libcomd
	#libldkd
	libmovementd
	libsensord
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_R2000_LIB
    libcomd
	#libldkd
	libmovementd
	libsensord
	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_r2000d ${TEST_R2000_SRC})
target_link_libraries(test_r2000d ${TEST_R2000_LIB})


ENDIF()



