include_directories(${KPS_ARM_SDK_PATH}/include/protobuf_msg)

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



if(WIN32)
set(TEST_MODBUS_LIB
	libinterface
	libcom
	modbus
	${Boost_LIBRARIES}
	WS2_32.lib
	setupapi.lib 
	
)
else()

link_directories(/lib)

set(TEST_MODBUS_LIB
    libinterface
	libcom

	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_modbus_server unit-test-server.cpp)
target_link_libraries(test_modbus_server ${TEST_MODBUS_LIB})

add_executable(test_modbus_client unit-test-client.cpp)
target_link_libraries(test_modbus_client ${TEST_MODBUS_LIB})