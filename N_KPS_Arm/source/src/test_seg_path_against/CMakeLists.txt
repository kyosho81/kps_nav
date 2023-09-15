add_definitions(-DBOOST_NO_MEMBER_TEMPLATE_FRIENDS)

INCLUDE_DIRECTORIES("D:/lib/qwt-6.1.2/src")
link_directories("D:/lib/qwt-6.1.2/lib")

set(CMAKE_PREFIX_PATH "D:/Qt/4.8.6/bin")
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


SET(TEST_SEG_PATH_AGAINST_MOC_SRCS
	#ADD QT OBJECT .h FILE HERE
	
	#kps_main_win.h
	
)

set(TEST_SEG_PATH_AGAINST_SRCS

	main.cpp
	
)

set(TEST_SEG_PATH_AGAINST_UIS
	#ADD UIS FILE HERE ##

 )

set(TEST_SEG_PATH_AGAINST_QCCS 
	#ADD .qrc FILE HERE###
 
)
IF(CMAKE_BUILD_TYPE MATCHES "release")
set(TEST_SEG_PATH_AGAINST_LIBS
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
  libdevice_base
  libplot
  libreflected_pillar_loc
  liblog4cpp
  liblog
  g2o_core
  g2o_solver_csparse
  g2o_stuff
  g2o_csparse_extension
  g2o_ext_csparse
  libg2o_slam
  libgeometry

  libflirtsensors
  libflirtfeature
  libflirtsensorsstream
  libflirtgui

  libdbow3
  liblaser2d_loopclosure
  libgn_scanmatch
  liboctomap
  libopencv_cus
  libproject
  libsub_map_localization
  libcalib
  libdispatching
  libinterface
  libmovement

  libprotobuf
  QtPropertyBrowser
  ${QT_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)
 
ELSE()
set(TEST_SEG_PATH_AGAINST_LIBS
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
  libdevice_base
  libplot
  libreflected_pillar_loc
  liblog4cpp
  liblog
  g2o_core_d
  g2o_solver_csparse_d
  g2o_stuff_d
  g2o_csparse_extension_d
  g2o_ext_csparse_d
  libg2o_slam
  libgeometry

  libflirtsensors
  libflirtfeature
  libflirtsensorsstream
  libflirtgui

  libdbow3
  liblaser2d_loopclosure
  libgn_scanmatch
  liboctomap
  libopencv_cus
  libproject
  libsub_map_localization
  libcalib
  libdispatching
  libinterface
  libmovement

  libprotobuf
  QtPropertyBrowser
  ${QT_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)
ENDIF()
  
qt4_automoc(${TEST_SEG_PATH_AGAINST_SRCS})

QT4_WRAP_CPP(TEST_SEG_PATH_AGAINST_MOC ${TEST_SEG_PATH_AGAINST_MOC_SRCS})

QT4_WRAP_UI(TEST_SEG_PATH_AGAINST_UIS_H ${TEST_SEG_PATH_AGAINST_UIS})

QT4_ADD_RESOURCES(TEST_SEG_PATH_AGAINST_QCCS_SRCS ${TEST_SEG_PATH_AGAINST_QCCS})

ADD_DEFINITIONS(-D_REENTRANT -DQT_NO_DEBUG -DQT_SQL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED )

add_definitions(-DBOOST_NO_MEMBER_TEMPLATE_FRIENDS)


IF(CMAKE_BUILD_TYPE MATCHES "release")
add_executable(test_seg_path_against ${TEST_SEG_PATH_AGAINST_SRCS} ${TEST_SEG_PATH_AGAINST_MOC} ${TEST_SEG_PATH_AGAINST_UIS_H} ${TEST_SEG_PATH_AGAINST_QCCS_SRCS} )
message(${TEST_SEG_PATH_AGAINST_LIBS})
target_link_libraries(test_seg_path_against ${TEST_SEG_PATH_AGAINST_LIBS} )
ADD_DEPENDENCIES(test_seg_path_against libplot)
ELSE()
add_executable(test_seg_path_against ${TEST_SEG_PATH_AGAINST_SRCS} ${TEST_SEG_PATH_AGAINST_MOC} ${TEST_SEG_PATH_AGAINST_UIS_H} ${TEST_SEG_PATH_AGAINST_QCCS_SRCS} )
message(${TEST_SEG_PATH_AGAINST_LIBS})
target_link_libraries(test_seg_path_against ${TEST_SEG_PATH_AGAINST_LIBS} )
ADD_DEPENDENCIES(test_seg_path_against libplotd)
ENDIF()