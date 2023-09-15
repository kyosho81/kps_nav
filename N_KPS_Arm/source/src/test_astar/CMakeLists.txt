set(TEST_ASTAR_SRC

	main.cpp
)

IF(CMAKE_BUILD_TYPE MATCHES "release")

if(WIN32)
set(TEST_ASTAR_LIB
	libcom
	libbag 
	librobot
	libmapserver
#	libsensor  
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_ASTAR_LIB
    libcom
    libbag 
	librobot
	libmapserver
#	libsensor 
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_astar ${TEST_ASTAR_SRC})
target_link_libraries(test_astar ${TEST_ASTAR_LIB})

ELSE()

if(WIN32)
set(TEST_ASTAR_LIB
	libcomd
	libbagd 
	librobotd
	libmapserverd
#	libsensord  
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_ASTAR_LIB
    libcomd
    libbagd 
	librobotd
	libmapserverd
#	libsensord 
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_astard ${TEST_ASTAR_SRC})
target_link_libraries(test_astard ${TEST_ASTAR_LIB})


ENDIF()



