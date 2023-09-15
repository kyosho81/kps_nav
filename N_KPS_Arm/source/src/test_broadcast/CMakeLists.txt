

set(TEST_BOARDCAST_SRC
	main.cpp

)

if(WIN32)
set(TEST_BOARDCAST_LIB
	libtransfer
	${Boost_LIBRARIES}
	WS2_32.lib
	setupapi.lib 
)
else()

link_directories(/lib)

set(TEST_BOARDCAST_LIB
	libtransfer
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_boardcast ${TEST_BOARDCAST_SRC})
target_link_libraries(test_boardcast ${TEST_BOARDCAST_LIB})
