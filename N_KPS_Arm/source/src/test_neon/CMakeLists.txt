set(TEST_NEON_SRC
	main.cpp
)


if(WIN32)
set(TEST_NEON_LIB

	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_NEON_LIB

	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_neon ${TEST_NEON_SRC})
target_link_libraries(test_neon ${TEST_NEON_LIB})





