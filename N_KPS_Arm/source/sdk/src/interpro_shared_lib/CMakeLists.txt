#Shared_pool Lib 
AUX_SOURCE_DIRECTORY(./ SHARED_POOL_SRC_LIS)

add_library(libshared_pool ${SHARED_POOL_SRC_LIS})
target_link_libraries(libshared_pool )

IF(BUILD_SDK)
	INSTALL(TARGETS libshared_pool DESTINATION ${SDK_LIB_PATH})
ENDIF(BUILD_SDK)