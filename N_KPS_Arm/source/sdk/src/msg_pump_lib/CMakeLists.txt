#msg_pump Lib
AUX_SOURCE_DIRECTORY(./ MSG_PUMP_SRC_LIS)
#FILE(GLOB_RECURSE SRC_LIST "*.cpp")
 
add_library(libmsg_pump ${MSG_PUMP_SRC_LIS})
target_link_libraries(libmsg_pump )

IF(BUILD_SDK)
	INSTALL(TARGETS libmsg_pump DESTINATION ${SDK_LIB_PATH})
ENDIF(BUILD_SDK)




