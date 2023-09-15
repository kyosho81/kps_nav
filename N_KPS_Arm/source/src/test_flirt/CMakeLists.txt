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


SET(KPS_MONITOR_APP_MOC_SRCS
	#ADD QT OBJECT .h FILE HERE
	FLIRTDemo.h
	
)


set(KPS_MONITOR_APP_SRCS
	FLIRTDemo.cpp
)

set(KPS_MONITOR_APP_UIS
	#ADD UIS FILE HERE ##

 )

set(KPS_MONITOR_APP_QCCS 
	#ADD .qrc FILE HERE###
 
)
IF(CMAKE_BUILD_TYPE MATCHES "release")
set(KPS_MONITOR_APP_LIBS
  #ADD LIB HERE###
  WS2_32.lib
  libflirtsensors
  libflirtfeature
  libflirtsesorsstream
  libflirtgui
  qwt
  ${QT_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)
 
ELSE()
set(KPS_MONITOR_APP_LIBS
  #ADD LIB HERE###
  WS2_32.lib
  librobot
  libflirtsensors
  libflirtfeature
  libflirtsensorsstream
  libflirtgui

  glu32.lib
  opengl32.lib
  qwtd
  ${QT_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)
ENDIF()
  
qt4_automoc(${KPS_MONITOR_APP_SRCS})

QT4_WRAP_CPP(KPS_MONITOR_APP_MOC ${KPS_MONITOR_APP_MOC_SRCS})

QT4_WRAP_UI(KPS_MONITOR_APP_UIS_H ${KPS_MONITOR_APP_UIS})

QT4_ADD_RESOURCES(KPS_MONITOR_APP_QCCS_SRCS ${KPS_MONITOR_APP_QCCS})

ADD_DEFINITIONS(-D_REENTRANT -DQT_NO_DEBUG -DQT_SQL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED )




IF(CMAKE_BUILD_TYPE MATCHES "release")
add_executable(test_flirt_demo ${KPS_MONITOR_APP_SRCS} ${KPS_MONITOR_APP_MOC} ${KPS_MONITOR_APP_UIS_H} ${KPS_MONITOR_APP_QCCS_SRCS} )
message(${KPS_MONITOR_APP_LIBS})
target_link_libraries(test_flirt_demo ${KPS_MONITOR_APP_LIBS} )
ADD_DEPENDENCIES(test_flirt_demo ${KPS_MONITOR_APP_LIBS})
ELSE()
add_executable(test_flirt_demo ${KPS_MONITOR_APP_SRCS} ${KPS_MONITOR_APP_MOC} ${KPS_MONITOR_APP_UIS_H} ${KPS_MONITOR_APP_QCCS_SRCS} )
message(${KPS_MONITOR_APP_LIBS})
target_link_libraries(test_flirt_demo ${KPS_MONITOR_APP_LIBS} )
ADD_DEPENDENCIES(test_flirt_demo ${KPS_MONITOR_APP_LIBS})
ENDIF()