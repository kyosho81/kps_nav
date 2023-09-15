set(SHARED_TEST_SRC

	main.cpp
)

IF(CMAKE_BUILD_TYPE MATCHES "release")

if(WIN32)
set(SHARED_TEST_LIB
	libcom 
	librobot
#	libsensor  
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(SHARED_TEST_LIB
    libcom 
	librobot
#	libsensor 
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(shared_test ${SHARED_TEST_SRC})
target_link_libraries(shared_test ${SHARED_TEST_LIB})

ELSE()

if(WIN32)
set(SHARED_TEST_LIB
	libcomd 
	librobotd
#	libsensord  
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(SHARED_TEST_LIB
    libcomd 
	librobotd
#	libsensord 
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(shared_testd ${SHARED_TEST_SRC})
target_link_libraries(shared_testd ${SHARED_TEST_LIB})


ENDIF()



