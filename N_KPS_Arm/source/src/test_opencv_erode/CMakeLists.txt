
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

set(TEST_OPENCV_ERODE_SRC
	main.cpp
)


if(WIN32)
set(TEST_OPENCV_ERODE_LIB
	libtransfer
	libcom
	librobot
	libshared_pool
	libxmlrpc
	libchassis
	${Boost_LIBRARIES}
	${OpenCV_LIBS}
	WS2_32.lib
	setupapi.lib 
)
else()

link_directories(/lib)

set(TEST_OPENCV_ERODE_LIB
    libtransfer
    libcom
    libxmlrpc 
	libchassis 	
	#librobot
	#libshared_pool
	pthread
	rt 
	${Boost_LIBRARIES}
	${OpenCV_LIBS}
)
endif()

add_executable(test_opencv_erode ${TEST_OPENCV_ERODE_SRC})
target_link_libraries(test_opencv_erode ${TEST_OPENCV_ERODE_LIB})
