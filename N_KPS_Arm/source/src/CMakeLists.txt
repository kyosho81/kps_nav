include_directories(include)
IF(BUILD_SDK)

ADD_SUBDIRECTORY(test_transfer)

if(WIN32)
	
	
endif(WIN32)

ENDIF(BUILD_SDK)

ADD_SUBDIRECTORY(test_shared_msg)
ADD_SUBDIRECTORY(test_shared_pipe)
ADD_SUBDIRECTORY(test_shared_block)
ADD_SUBDIRECTORY(test_shared_locker)

ADD_SUBDIRECTORY(test_timer)


IF(BUILD_SDK)
	INSTALL(PROGRAMS CMakeLists.txt DESTINATION source/src)
	
	INSTALL(DIRECTORY
			include
			test_transfer
			

			
			  DESTINATION source/src
	          FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.inl" PATTERN "*.cpp" PATTERN "CMakeLists.txt"
	          PATTERN ".svn" EXCLUDE 
	          )
ENDIF(BUILD_SDK)
