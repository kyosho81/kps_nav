include_directories(${KPS_ARM_SDK_PATH}/include/protobuf_msg)

IF(ARM)
	IF(SURO)
		link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/lib)
	ELSE(SURO)
		link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/lib4418/lib)
		link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/lib4418/lib/g2o)
	ENDIF(SURO)
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/canalyst2)
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/hasp)
ELSE(ARM)
	IF(WIN32)
		IF(CMAKE_BUILD_TYPE MATCHES "release")
		link_directories(${KPS_ARM_THIRD_PARTY_PATH}/x64/release)
		ELSE()
		link_directories(${KPS_ARM_THIRD_PARTY_PATH}/x64/debug)
		ENDIF()
	ELSE(WIN32)

	    #include_directories(${KPS_ARM_THIRD_PARTY_PATH}/include/EXTERNAL)
		
		find_package(PkgConfig)
		pkg_check_modules(Protobuf REQUIRED protobuf)
		message("protobuf include ${Protobuf_INCLUDE_DIRS}")
		message("protobuf lib dirs ${Protobuf_LIBRARY_DIRS}")
		message("protobuf lib names ${Protobuf_LIBRARIES}")
		INCLUDE_DIRECTORIES(${Protobuf_INCLUDE_DIRS})
		LINK_DIRECTORIES(${Protobuf_LIBRARY_DIRS})

		#LIST(APPEND CMAKE_MODULE_PATH ${KPS_ARM_THIRD_PARTY_PATH}/cmake_modules)

		#FIND_PACKAGE(CSparse)
		#message("CSparse include ${CSPARSE_LIBRARY}")
		#IF(CSPARSE_FOUND)
		#message("22222222222222222")
		#ENDIF()

		link_directories(${KPS_ARM_THIRD_PARTY_PATH}/x64/)
		link_directories(${KPS_ARM_THIRD_PARTY_PATH}/x64/canalyst2/)
		link_directories(${KPS_ARM_THIRD_PARTY_PATH}/x64/g2o/)
	ENDIF(WIN32)
ENDIF(ARM)


set(TEST_ODOM_SRC
	main_kps.cpp

)


if(WIN32)
set(TEST_ODOM_LIB
	libtransfer
	libcom
	librobot
	libshared_pool
	libxmlrpc
	libchassis
	libinterface
	liblog4cpp
	liblog
	${Boost_LIBRARIES}
	WS2_32.lib
	setupapi.lib 
)
else()

link_directories(/lib)

set(TEST_ODOM_LIB
	
	libinterface
	liblog
	liblog4cpp
	libshared_pool
	libcom
	librobot
	libchassis
	libxmlrpc
	libtransfer
	librobot
	libcom

	controlcan

	protobuf
	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_odom ${TEST_ODOM_SRC})
target_link_libraries(test_odom ${TEST_ODOM_LIB})
