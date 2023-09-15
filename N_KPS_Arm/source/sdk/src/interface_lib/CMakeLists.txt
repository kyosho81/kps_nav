#interface Lib
#AUX_SOURCE_DIRECTORY(./ INTERFACE_SRC_LIS)

include_directories(${KPS_ARM_THIRD_PARTY_PATH}/include)
include_directories(${KPS_ARM_SDK_PATH}/include/protobuf_msg)


set(INTERFACE_SRC_LIS

	rpc_task_server.cpp
	rpc_bind.cpp
	data_server.cpp
	global_path.cpp
	local_map.cpp
	agv_client.cpp
	view_data.cpp
	xml_rpc_client.cpp
	rpc_config_client.cpp
	rpc_config_server.cpp
)


if(WIN32)
set(INTERFACE_LIB

	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(INTERFACE_LIB

	rt 
)
message(${INTERFACE_LIB})
endif()

add_library(libinterface ${INTERFACE_SRC_LIS})
target_link_libraries(libinterface ${INTERFACE_LIB})

IF(BUILD_SDK)
	INSTALL(TARGETS libinterface DESTINATION ${SDK_LIB_PATH})
ENDIF(BUILD_SDK)
	
