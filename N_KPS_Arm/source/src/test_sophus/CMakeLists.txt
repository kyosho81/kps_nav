set(TEST_SOPHUS_SRC
	main.cpp
	#test_se3.cpp
)


if(WIN32)
set(TEST_SOPHUS_LIB
	libsophus
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_SOPHUS_LIB
    	libsophus
	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_sophus ${TEST_SOPHUS_SRC})
target_link_libraries(test_sophus ${TEST_SOPHUS_LIB})





