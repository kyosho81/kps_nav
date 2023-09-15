#Xmlrpc Lib
AUX_SOURCE_DIRECTORY(./ XMLRPC_SRC_LIS)

add_library(libxmlrpc ${XMLRPC_SRC_LIS})
target_link_libraries(libxmlrpc)
	
IF(BUILD_SDK)
	INSTALL(TARGETS libxmlrpc DESTINATION ${SDK_LIB_PATH})
ENDIF(BUILD_SDK)
