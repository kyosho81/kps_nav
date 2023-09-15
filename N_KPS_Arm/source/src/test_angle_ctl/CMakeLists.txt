set(TEST_ANGLE_CTL_SRC

	main.cpp
)

IF(CMAKE_BUILD_TYPE MATCHES "release")

if(WIN32)
set(TEST_ANGLE_CTL_LIB
	libcom
	librobot
	libmovement
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_ANGLE_CTL_LIB
    libcom
	librobot
	libmovement
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_angle_ctl ${TEST_ANGLE_CTL_SRC})
target_link_libraries(test_angle_ctl ${TEST_ANGLE_CTL_LIB})

ELSE()

if(WIN32)
set(TEST_ANGLE_CTL_LIB
	libcomd
	librobotd
	libmovementd
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_ANGLE_CTL_LIB
    libcomd
	librobotd
	libmovementd
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_angle_ctl ${TEST_ANGLE_CTL_SRC})
target_link_libraries(test_angle_ctl ${TEST_ANGLE_CTL_LIB})


ENDIF()



