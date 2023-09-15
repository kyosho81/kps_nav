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


set(testOdomFilterbyLaser_SRCS
    main.cpp
)

IF(CMAKE_BUILD_TYPE MATCHES "release")

add_executable(testOdomFilterbyLaser  ${testOdomFilterbyLaser_SRCS})

if(WIN32)
target_link_libraries(testOdomFilterbyLaser  libcom libbag librobot libpolarscanmatcher libsensor ${Boost_LIBRARIES})
else()
target_link_libraries(testOdomFilterbyLaser  libcom libbag librobot libpolarscanmatcher libsensor pthread rt ${Boost_LIBRARIES})
endif()

ELSE()

add_executable(testOdomFilterbyLaserd  ${testOdomFilterbyLaser_SRCS})
if(WIN32)
target_link_libraries(testOdomFilterbyLaserd libcom libbag librobot libpolarscanmatcher libsensor libxmlrpc WS2_32.lib ${Boost_LIBRARIES})
else()
target_link_libraries(testOdomFilterbyLaserd libcom libbag librobot libpolarscanmatcher libsensor pthread rt ${Boost_LIBRARIES})
endif()

ENDIF()

