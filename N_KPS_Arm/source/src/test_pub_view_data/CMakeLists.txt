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



set(TEST_PUB_VIEW_DATA_SRC

	main.cpp
)

if(WIN32)
set(TEST_PUB_VIEW_DATA_LIB
	libcom
	libshared_pool
	libxmlrpc
	librobot
	libprotobuf_msg
	WS2_32.lib
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_PUB_VIEW_DATA_LIB
    libcom
	libshared_pool
	libmovement
	libprotobuf_msg
	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_pub_view_data ${TEST_PUB_VIEW_DATA_SRC})
target_link_libraries(test_pub_view_data ${TEST_PUB_VIEW_DATA_LIB})

