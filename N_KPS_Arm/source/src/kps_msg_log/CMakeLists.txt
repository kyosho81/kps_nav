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




set(KPS_MSG_LOG_SRC

	main.cpp
)

if(WIN32)
set(KPS_MSG_LOG_LIB
	libcom
	liblog4cpp
	liblog
	libxmlrpc
	libprotobuf_msg
	libshared_pool
	libproject
	libsqlite3
	libtransfer
	libzlib
	libinterface
	librobot

	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(KPS_MSG_LOG_LIB

	
	liblog
	libzlib
	libcom
	libsqlite3
	libprotobuf_msg
	libshared_pool
	libinterface
	librobot
	libxmlrpc

	protobuf
	pthread
	rt
	dl 
	${Boost_LIBRARIES}
)
endif()

add_executable(kps_msg_log ${KPS_MSG_LOG_SRC})
target_link_libraries(kps_msg_log ${KPS_MSG_LOG_LIB})

