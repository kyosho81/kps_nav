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

set(PROTOBUF_TEST_SRC

	main.cpp
)

IF(CMAKE_BUILD_TYPE MATCHES "release")

if(WIN32)
set(PROTOBUF_TEST_LIB
	libcom 
	librobot
	libprotobuf_msg
	libprotobuf  
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(PROTOBUF_TEST_LIB
    libcom 
	librobot
	libprotobuf_msg
	protobuf.a 
	rt 
#	${Boost_LIBRARIES}
)
endif()

add_executable(protobuf_test ${PROTOBUF_TEST_SRC})
target_link_libraries(protobuf_test ${PROTOBUF_TEST_LIB})

ELSE()

if(WIN32)
set(PROTOBUF_TEST_LIB
	libcomd 
	librobotd
	libprotobuf_msgd
	libprotobuf  
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(PROTOBUF_TEST_LIB
	libcomd 
	librobotd
	libprotobuf_msgd
	protobuf.a 
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(protobuf_testd ${PROTOBUF_TEST_SRC})
target_link_libraries(protobuf_testd ${PROTOBUF_TEST_LIB})


ENDIF()



