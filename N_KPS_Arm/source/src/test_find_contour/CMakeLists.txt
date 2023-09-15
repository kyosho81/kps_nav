add_definitions(-DBOOST_NO_MEMBER_TEMPLATE_FRIENDS)
 
INCLUDE_DIRECTORIES("D:/lib/qwt-6.1.2/src")
link_directories("D:/lib/qwt-6.1.2/lib")

find_package(Qt4 COMPONENTS QtCore QtGui QtNetwork QtOpenGL REQUIRED )
include(${QT_USE_FILE})
INCLUDE_DIRECTORIES( ${QT_INCLUDE_DIR} )

include_directories(${KPS_ARM_THIRD_PARTY_PATH}/include)

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

SET(TEST_FIND_CONTOUR_MOC_SRCS
	#ADD QT OBJECT .h FILE HERE
	#FLIRTDemo.h
	
)


set(TEST_FIND_CONTOUR_SRCS

	main.cpp
)

set(TEST_FIND_CONTOUR_UIS
	#ADD UIS FILE HERE ##

 )

set(TEST_FIND_CONTOUR_QCCS 
	#ADD .qrc FILE HERE###
 
)
IF(CMAKE_BUILD_TYPE MATCHES "release")
set(TEST_FIND_CONTOUR_LIBS
  #ADD LIB HERE###
  WS2_32.lib
  libdbow3
  qwt
  ${QT_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)
 
ELSE()
set(TEST_FIND_CONTOUR_LIBS
  #ADD LIB HERE###
  WS2_32.lib
  librobot
  libdbow3
  glu32.lib
  opengl32.lib
  qwtd
  ${QT_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)
ENDIF()
  
qt4_automoc(${TEST_FIND_CONTOUR_SRCS})

QT4_WRAP_CPP(TEST_FIND_CONTOUR_MOC ${TEST_FIND_CONTOUR_MOC_SRCS})

QT4_WRAP_UI(TEST_FIND_CONTOUR_UIS_H ${TEST_FIND_CONTOUR_UIS})

QT4_ADD_RESOURCES(TEST_FIND_CONTOUR_QCCS_SRCS ${TEST_FIND_CONTOUR_QCCS})

ADD_DEFINITIONS(-D_REENTRANT -DQT_NO_DEBUG -DQT_SQL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED )




IF(CMAKE_BUILD_TYPE MATCHES "release")
add_executable(test_findcontour ${TEST_FIND_CONTOUR_SRCS} ${TEST_FIND_CONTOUR_MOC} ${TEST_FIND_CONTOUR_UIS_H} ${TEST_FIND_CONTOUR_QCCS_SRCS} )
message(${TEST_FIND_CONTOUR_LIBS})
target_link_libraries(test_findcontour ${TEST_FIND_CONTOUR_LIBS} )
ADD_DEPENDENCIES(test_findcontour ${TEST_FIND_CONTOUR_LIBS})
ELSE()
add_executable(test_findcontour ${TEST_FIND_CONTOUR_SRCS} ${TEST_FIND_CONTOUR_MOC} ${TEST_FIND_CONTOUR_UIS_H} ${TEST_FIND_CONTOUR_QCCS_SRCS} )
message(${TEST_FIND_CONTOUR_LIBS})
target_link_libraries(test_findcontour ${TEST_FIND_CONTOUR_LIBS} )
ADD_DEPENDENCIES(test_findcontour ${TEST_FIND_CONTOUR_LIBS})
ENDIF()