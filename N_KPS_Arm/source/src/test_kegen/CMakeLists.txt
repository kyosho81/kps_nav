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

set(TEST_KEYGEN_SRC
	main.cpp
)


if(WIN32)
set(TEST_KEYGEN_LIB
	libcom
	librobot
	libinterface
	libencryption
	libtransfer
	libxmlrpc
	libprotobuf_msg
	${Boost_LIBRARIES}
	WS2_32.lib
	setupapi.lib 
)
else()

link_directories(/lib)

set(TEST_KEYGEN_LIB
	#
	#
	#
	libcom
	libencryption
	libcom
	librobot
	libinterface
	libtransfer
	libinterface
	libxmlrpc
	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_keygen ${TEST_KEYGEN_SRC})
target_link_libraries(test_keygen ${TEST_KEYGEN_LIB})
