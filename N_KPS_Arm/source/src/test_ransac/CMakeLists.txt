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

set(TEST_RANSAC_SRC
	main.cpp
)


if(WIN32)
set(TEST_RANSAC_LIB
	libcom
    librobot
	libgeometry
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_RANSAC_LIB
	libcom
    librobot
	libgeometry
	protobuf
	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_ransac ${TEST_RANSAC_SRC})
target_link_libraries(test_ransac ${TEST_RANSAC_LIB})





