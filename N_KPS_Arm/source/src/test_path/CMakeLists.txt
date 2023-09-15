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

set(TEST_PATH_SRC
	main.cpp

)


if(WIN32)
set(TEST_PATH_LIB
	libtransfer
	libcom
	libprotobuf_msg
	libproject
	#librobot
	libshared_pool
	libxmlrpc
	#libchassis
	libinterface
	liblog4cpp
	liblog
	libdispatching
	libslam
	libscanmatcher
	libgridfastslam
	libgsensor

    libutils
	libmapserver
	libmovement
	libprotobuf
	
	libmsg_pump
	libdevice_base
	liboctomap

	${Boost_LIBRARIES}
	WS2_32.lib
	setupapi.lib 
)
else()

link_directories(/lib)

set(TEST_PATH_LIB
    libtransfer
    libcom
    libxmlrpc 
	libchassis
	libproject 	
	#librobot
	#libshared_pool
	protobuf
	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_path ${TEST_PATH_SRC})
target_link_libraries(test_path ${TEST_PATH_LIB})
