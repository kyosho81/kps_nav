include_directories(./)
 
#Transfer Lib
AUX_SOURCE_DIRECTORY(./ TRANSFER_SRC_LIS)
#FILE(GLOB_RECURSE SRC_LIST "*.cpp")

add_library(libtransfer ${TRANSFER_SRC_LIS})
target_link_libraries(libtransfer )
	
IF(BUILD_SDK)
	INSTALL(TARGETS libtransfer DESTINATION ${SDK_LIB_PATH})
ENDIF(BUILD_SDK)

