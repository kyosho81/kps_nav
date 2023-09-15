include_directories(
  ${KPS_ARM_THIRD_PARTY_PATH}/include/hasp/
)
IF(ARM)
link_directories(${KPS_ARM_THIRD_PARTY_PATH}/arm/hasp)
ENDIF(ARM)

set(TEST_LDK_SRC
	#main.cpp
	hasp_demo.cpp
	errorprinter.cpp
)

IF(CMAKE_BUILD_TYPE MATCHES "release")

if(WIN32)
set(TEST_LDK_LIB
	libtransfer
	libcom
	librobot
	libshared_pool
	${Boost_LIBRARIES}
	WS2_32.lib
	setupapi.lib 
)
else()

link_directories(/lib)

set(TEST_LDK_LIB
    libtransfer
    libcom 	
	librobot
	libshared_pool
	hasp_cpp_linux_armeabi-hf
	#hasp_linux_armeabi-hf
	hasp_linux_armhf_demo
	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_ldk ${TEST_LDK_SRC})
target_link_libraries(test_ldk ${TEST_LDK_LIB})

ELSE()

if(WIN32)
set(TEST_LDK_LIB
	libtransferd
	libcomd
	librobotd
	libshared_poold
	${Boost_LIBRARIES}
	WS2_32.lib
	setupapi.lib
)
else()

link_directories(/lib)

set(TEST_LDK_LIB
    libtransferd
    libcomd
	librobotd
	libshared_poold
	hasp_cpp_linux_armeabi-hf
	hasp_linux_armeabi-hf
	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_ldk ${TEST_LDK_SRC})
target_link_libraries(test_ldk ${TEST_LDK_LIB})
ENDIF()




