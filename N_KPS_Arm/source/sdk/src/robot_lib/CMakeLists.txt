#ROBOT Lib
AUX_SOURCE_DIRECTORY(./ ROBOT_SRC_LIS)
 
add_library(librobot ${ROBOT_SRC_LIS})

if(WIN32)
	target_link_libraries(librobot )
else()
	target_link_libraries(librobot rt)
endif()
 
IF(BUILD_SDK)
	INSTALL(TARGETS librobot DESTINATION ${SDK_LIB_PATH})
ENDIF(BUILD_SDK)
