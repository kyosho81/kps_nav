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


set(UUID_TEST_SRC
 
	main.cpp
)


if(WIN32)
set(UUID_TEST_LIB
	libcom 
	librobot
	libprotobuf_msg
	libproject
	libprotobuf
	liblog  
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(UUID_TEST_LIB
    libcom 
	librobot
	libprotobuf_msg
	libproject 
	protobuf
	liblog
	pthread
	rt 
#	${Boost_LIBRARIES}
)
endif()

add_executable(test_uuid ${UUID_TEST_SRC})
target_link_libraries(test_uuid ${UUID_TEST_LIB})
