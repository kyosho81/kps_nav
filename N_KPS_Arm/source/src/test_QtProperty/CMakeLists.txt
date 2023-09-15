add_definitions(-DBOOST_NO_MEMBER_TEMPLATE_FRIENDS)
 
INCLUDE_DIRECTORIES("D:/lib/qwt-6.1.2/src")
link_directories("D:/lib/qwt-6.1.2/lib")

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
INCLUDE_DIRECTORIES( ${QT_INCLUDE_DIR} )

#find_package(OpenCV REQUIRED )
#INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )
#link_directories(${OpenCV_LIBS})
#message(${OPENCV_INCLUDE_DIR})
#message(${OpenCV_LIBS})

include_directories(${KPS_ARM_THIRD_PARTY_PATH}/include)
include_directories(${KPS_ARM_SDK_PATH}/include/protobuf_msg)

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


SET(TEST_QTPTOPERTY_MOC_SRCS
	#ADD QT OBJECT .h FILE HERE
	
	
)


set(TEST_QTPTOPERTY_SRCS
	
	main.cpp
	
)

set(TEST_QTPTOPERTY_UIS
	#ADD UIS FILE HERE ##

 )

set(TEST_QTPTOPERTY_QCCS 
	#ADD .qrc FILE HERE###
 
)

set(TEST_QTPTOPERTY_LIBS
  #ADD LIB HERE###
  WS2_32.lib
  libcom
  libmapserver
  libtransfer
  libmsg_pump
  libdevice_base
  libsensor
  librobot
  libchassis
  libplot
  qwt
  libpf
  libxmlrpc
  libscene
  libproject
  libslam
  libscanmatcher
  libgridfastslam
  libpngx
  libprotobuf_msg
  libbag
  libgsensor
  libshared_pool
  libgridfastslam
  libutils
  libprotobuf
  QtPropertyBrowser
  ${QT_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)
 

  
qt4_automoc(${TEST_QTPTOPERTY_SRCS})

QT4_WRAP_CPP(TEST_QTPTOPERTY_MOC ${TEST_QTPTOPERTY_MOC_SRCS})

QT4_WRAP_UI(TEST_QTPTOPERTY_UIS_H ${TEST_QTPTOPERTY_UIS})

QT4_ADD_RESOURCES(TEST_QTPTOPERTY_QCCS_SRCS ${TEST_QTPTOPERTY_QCCS})

ADD_DEFINITIONS(-D_REENTRANT -DQT_NO_DEBUG -DQT_SQL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED )




IF(CMAKE_BUILD_TYPE MATCHES "release")
add_executable(test_QtProperty ${TEST_QTPTOPERTY_SRCS} ${TEST_QTPTOPERTY_MOC} ${TEST_QTPTOPERTY_UIS_H} ${TEST_QTPTOPERTY_QCCS_SRCS} )
message(${TEST_QTPTOPERTY_LIBS})
target_link_libraries(test_QtProperty ${TEST_QTPTOPERTY_LIBS} )
ADD_DEPENDENCIES(test_QtProperty libplot)
ELSE()
add_executable(test_QtProperty ${TEST_QTPTOPERTY_SRCS} ${TEST_QTPTOPERTY_MOC} ${TEST_QTPTOPERTY_UIS_H} ${TEST_QTPTOPERTY_QCCS_SRCS} )
message(${TEST_QTPTOPERTY_LIBS})
target_link_libraries(test_QtProperty ${TEST_QTPTOPERTY_LIBS} )
ADD_DEPENDENCIES(test_QtProperty libplot)
ENDIF()