#Comm Lib 
AUX_SOURCE_DIRECTORY(./ COM_SRC_LIS)
#FILE(GLOB_RECURSE SRC_LIST "*.cpp")

add_library(libcom ${COM_SRC_LIS})
target_link_libraries(libcom  )

IF(BUILD_SDK)
	INSTALL(TARGETS libcom DESTINATION ${SDK_LIB_PATH})
ENDIF(BUILD_SDK)


