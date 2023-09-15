add_definitions(-DBOOST_NO_MEMBER_TEMPLATE_FRIENDS)
 
INCLUDE_DIRECTORIES("D:/lib/qwt-6.1.2/src")
link_directories("D:/lib/qwt-6.1.2/lib")

find_package(Qt4 COMPONENTS QtCore QtGui QtNetwork QtOpenGL REQUIRED )
include(${QT_USE_FILE})
INCLUDE_DIRECTORIES( ${QT_INCLUDE_DIR} )

#find_package(OpenCV REQUIRED )
#INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )
#link_directories(${OpenCV_LIBS})
#message(${OPENCV_INCLUDE_DIR})
#message(${OpenCV_LIBS})

include_directories(${KPS_ARM_THIRD_PARTY_PATH}/include)
#include_directories(${KPS_ARM_SDK_PATH}/include/protobuf_msg)

IF(ARM)
	IF(SURO)
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/lib)
	ELSE(SURO)
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/lib4418/lib)
	ENDIF(SURO)
ELSE(ARM)
	
	IF(CMAKE_BUILD_TYPE MATCHES "release")
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/x64/release)
	ELSE()
	link_directories(${KPS_ARM_THIRD_PARTY_PATH}/x64/debug)
	ENDIF()
	
ENDIF(ARM)

if(WIN32)
SET(OpenCV_DIR "D:/MyRobot/N_KPS_Arm/thirdparty/src/opencv/build/install")
endif(WIN32)

message("---------------OpenCV------------")
find_package(OpenCV 3.4.1 REQUIRED)

IF(OpenCV_FOUND)
include_directories(${OpenCV_INCLUDE_DIRS})
message(${OpenCV_INCLUDE_DIRS})
message(${OpenCV_LIBS})
ELSE(OpenCV_FOUND)
message("opencv not found")
ENDIF(OpenCV_FOUND)
#------------------Opencv---------------------

SET(TEST_LOOP_CLOSURE_MOC_SRCS
	#ADD QT OBJECT .h FILE HERE
	#FLIRTDemo.h
	
)


set(TEST_LOOP_CLOSURE_SRCS
	#FLIRTDemo.cpp
	RansacLoopClosureTest.cpp
)

set(TEST_LOOP_CLOSURE_UIS
	#ADD UIS FILE HERE ##

 )

set(TEST_LOOP_CLOSURE_QCCS 
	#ADD .qrc FILE HERE###
 
)
IF(CMAKE_BUILD_TYPE MATCHES "release")
set(TEST_LOOP_CLOSURE_LIBS
  #ADD LIB HERE###
  WS2_32.lib
  libflirtsensors
  libflirtfeature
  libflirtsesorsstream
  libflirtgui
  libdbow3
  qwt
  ${QT_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)
 
ELSE()
set(TEST_LOOP_CLOSURE_LIBS
  #ADD LIB HERE###
  WS2_32.lib
  librobot
  libflirtsensors
  libflirtfeature
  libflirtsensorsstream
  libflirtgui
  libdbow3
  glu32.lib
  opengl32.lib
  qwtd
  ${QT_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)
ENDIF()
  
qt4_automoc(${TEST_LOOP_CLOSURE_SRCS})

QT4_WRAP_CPP(TEST_LOOP_CLOSURE_MOC ${TEST_LOOP_CLOSURE_MOC_SRCS})

QT4_WRAP_UI(TEST_LOOP_CLOSURE_UIS_H ${TEST_LOOP_CLOSURE_UIS})

QT4_ADD_RESOURCES(TEST_LOOP_CLOSURE_QCCS_SRCS ${TEST_LOOP_CLOSURE_QCCS})

ADD_DEFINITIONS(-D_REENTRANT -DQT_NO_DEBUG -DQT_SQL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED )




IF(CMAKE_BUILD_TYPE MATCHES "release")
add_executable(test_loop_closure ${TEST_LOOP_CLOSURE_SRCS} ${TEST_LOOP_CLOSURE_MOC} ${TEST_LOOP_CLOSURE_UIS_H} ${TEST_LOOP_CLOSURE_QCCS_SRCS} )
message(${TEST_LOOP_CLOSURE_LIBS})
target_link_libraries(test_loop_closure ${TEST_LOOP_CLOSURE_LIBS} )
ADD_DEPENDENCIES(test_loop_closure ${TEST_LOOP_CLOSURE_LIBS})
ELSE()
add_executable(test_loop_closure ${TEST_LOOP_CLOSURE_SRCS} ${TEST_LOOP_CLOSURE_MOC} ${TEST_LOOP_CLOSURE_UIS_H} ${TEST_LOOP_CLOSURE_QCCS_SRCS} )
message(${TEST_LOOP_CLOSURE_LIBS})
target_link_libraries(test_loop_closure ${TEST_LOOP_CLOSURE_LIBS} )
ADD_DEPENDENCIES(test_loop_closure ${TEST_LOOP_CLOSURE_LIBS})
ENDIF()