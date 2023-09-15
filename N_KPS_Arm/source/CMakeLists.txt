#cmake example for eclipse
#cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j8 ../source
#cmake example for vs2008
#cmake -G "Visual Studio 9 2008" -DCMAKE_BUILD_TYPE="release" -DBUILD_SDK=1 ../source
#cmake -G "Visual Studio 9 2008" ../source

cmake_minimum_required(VERSION 2.8.3)
project(kps_arm)


# Configuration types
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
IF(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
  SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS  ${CMAKE_CONFIGURATION_TYPES})
ENDIF()

#SET(${PROJ_NAME}_PATH_INSTALL     "/opt/project"                     CACHE PATH "This directory contains installation Path")
SET(CMAKE_DEBUG_POSTFIX "d")

SET( BUILD_SDK ON CACHE BOOL ON )

IF(SURO)
#############SURO_DIR#############################################################
STRING( REGEX REPLACE "\\\\" "/"  SURO_DIR  "$ENV{SURODIR}")
message("#### SURODIR: ${SURODIR}")

set(CMAKE_MODULE_PATH   ${SURO_DIR}/cmake/ ) 
message("1 #### SURODIR: ${CMAKE_MODULE_PATH}")


include(${SURO_DIR}/cmake/LinkOS.cmake) 
#############FIND SURO PACKAGE################# 
message("before FIND_PACKAGE suro")
FIND_PACKAGE(SURO REQUIRED)
message("after FIND_PACKAGE suro")
LINK_DIRECTORIES(${SURO_DIR}/lib) 
INCLUDE_DIRECTORIES(${SURO_DIR}/include)
INCLUDE_DIRECTORIES(${SURO_DIR}/../include) 
LINK_DIRECTORIES(${SURO_DIR}/../lib)


#SET(CMAKE_VERBOSE_MAKEFILE on)
#############SURO_DIR#############################################################
ENDIF(SURO)


INSTALL(PROGRAMS CMakeLists.txt DESTINATION source/)
INSTALL(PROGRAMS CMakeX64_Boost.txt DESTINATION source/)
INSTALL(PROGRAMS CMakeARM_Boost.txt DESTINATION source/)
INSTALL(PROGRAMS ReadMe.txt DESTINATION source/)

#################
## output path ##
#################

#message(${CMAKE_BINARY_DIR})
#SET_TARGET_PROPERTIES(core PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../bin)
IF(ARM)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BINARY_DIR}/../lib/arm)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BINARY_DIR}/../lib/arm)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BINARY_DIR}/../bin/arm)
set(SDK_LIB_PATH "lib/arm")
ELSE()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BINARY_DIR}/../lib/x64)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BINARY_DIR}/../lib/x64)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BINARY_DIR}/../bin/x64)
set(SDK_LIB_PATH "lib/x64")
ENDIF(ARM)
message("SDK_LIB_PATH")
message(${SDK_LIB_PATH})

###########
## Build ##
###########
IF(CMAKE_BUILD_TYPE MATCHES "release")

if(WIN32)
add_link_options("/DEBUG")
add_compile_options("/Zi")
endif(WIN32)

ENDIF()

set(KPS_ARM_SDK_PATH ${${PROJECT_NAME}_SOURCE_DIR}/sdk/)
message(${KPS_ARM_SDK_PATH})

set(KPS_ARM_THIRD_PARTY_PATH ${${PROJECT_NAME}_SOURCE_DIR}/../thirdparty/)
message(${KPS_ARM_THIRD_PARTY_PATH})

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(${KPS_ARM_THIRD_PARTY_PATH}/include)

IF(ARM)
	IF(SURO)
	include("CMakeARM64_Boost.txt")
	ELSE(SURO)
	include("CMakeARM_Boost.txt")
	ENDIF(SURO)
ELSE(ARM)
include("CMakeX64_Boost.txt")
ENDIF(ARM)

IF(OPENCV)
include("CMakeOpenCV.txt")
ENDIF(OPENCV)
 
include_directories(
  ${Boost_INCLUDE_DIRS}
  
  ${KPS_ARM_SDK_PATH}/include/
  ${KPS_ARM_SDK_PATH}/include/Comm
  ${KPS_ARM_SDK_PATH}/include/robot
  ${KPS_ARM_SDK_PATH}/include/trans_dev
  ${KPS_ARM_SDK_PATH}/include/xmlrpc
  ${KPS_ARM_SDK_PATH}/include/sensor
  ${KPS_ARM_SDK_PATH}/include/scanmatch
  ${KPS_ARM_SDK_PATH}/include/log4cpp
  ${KPS_ARM_SDK_PATH}/include/log
  
)

link_directories(${Boost_LIBRARY_DIRS})

IF(BUILD_SDK)
ELSE(BUILD_SDK)
	IF(ARM)
	link_directories( ${${PROJECT_NAME}_SOURCE_DIR}/../lib/arm )
	message(${${PROJECT_NAME}_SOURCE_DIR}/../lib/arm)
	ELSE(ARM)
	link_directories( ${${PROJECT_NAME}_SOURCE_DIR}/../lib/x64 )
	message(${${PROJECT_NAME}_SOURCE_DIR}/../lib/x64)
	ENDIF(ARM)
ENDIF(BUILD_SDK)

ADD_SUBDIRECTORY(src)
IF(BUILD_SDK)
ADD_SUBDIRECTORY(sdk)

INSTALL(DIRECTORY

			../thirdparty
			DESTINATION ./
	          FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.inl" PATTERN "*.cpp" PATTERN "CMakeLists.txt" PATTERN "*.a" PATTERN "*.lib"
	          PATTERN ".svn" EXCLUDE 
	          )
ENDIF(BUILD_SDK)
#add_link_options("/DEBUG")
#add_compile_options("/Zi")
