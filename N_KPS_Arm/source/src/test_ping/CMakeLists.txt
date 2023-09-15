include_directories(${KPS_ARM_SDK_PATH}/include/protobuf_msg)


IF(ARM)
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/lib)
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

set(TEST_PING_SRC
	main.cpp
)


if(WIN32)
set(TEST_PING_LIB
	libtransfer
	libxmlrpc
	libprotobuf_msg
	${Boost_LIBRARIES}
	WS2_32.lib
	setupapi.lib 
)
else()

link_directories(/lib)

set(TEST_PING_LIB
	libcom
	libtransfer
	libxmlrpc
	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_ping ${TEST_PING_SRC})
target_link_libraries(test_ping ${TEST_PING_LIB})
