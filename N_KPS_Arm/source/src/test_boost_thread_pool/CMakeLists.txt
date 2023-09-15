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


set(BOOST_THREAD_POOL_SRC
 
	main.cpp
)


if(WIN32)
set(BOOST_THREAD_POOL_LIB
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

set(BOOST_THREAD_POOL_LIB
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

add_executable(test_boost_thread_pool ${BOOST_THREAD_POOL_SRC})
target_link_libraries(test_boost_thread_pool ${BOOST_THREAD_POOL_LIB})
