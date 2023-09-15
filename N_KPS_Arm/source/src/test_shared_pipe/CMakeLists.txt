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



set(TEST_SHARED_PIPE_SRC

	main.cpp
)

if(WIN32)
set(TEST_SHARED_PIPE_LIB
	libcom
	libshared_pool

	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_SHARED_PIPE_LIB
    libcom
	libshared_pool

	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_shared_pipe ${TEST_SHARED_PIPE_SRC})
target_link_libraries(test_shared_pipe ${TEST_SHARED_PIPE_LIB})

