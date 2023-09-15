
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


set(KPS_CORE_SRC
	#main_core.cpp
	main_core_new.cpp
	#main.cpp
)

if(WIN32)
set(KPS_CORE_LIB
	libcom 
	#librobot
	#liblog4cpp
	libinterface
	liblog
	libshared_pool
	libxmlrpc 
	libtransfer
	librobot 
	#WS2_32.lib
	#${Boost_LIBRARIES}
	
)
else()

link_directories(/lib)

set(KPS_CORE_LIB
	
	libinterface
	libcom
	liblog
	libshared_pool
	libtransfer
	libxmlrpc
	librobot
	libgeometry
	

	protobuf
	pthread 
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(kps_core ${KPS_CORE_SRC})
target_link_libraries(kps_core ${KPS_CORE_LIB})




