ADD_SUBDIRECTORY(src)
 
IF(BUILD_SDK)

INSTALL(DIRECTORY include/ DESTINATION source/sdk/include
          FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.inl"
          PATTERN ".svn" EXCLUDE 
          PATTERN "Eigen" EXCLUDE)
INSTALL(DIRECTORY include/Eigen DESTINATION source/sdk/include/
          PATTERN ".svn" EXCLUDE)
ENDIF(BUILD_SDK)