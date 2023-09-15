

set(TEST_SQLITE3_SRC
	shell.c

)


if(WIN32)
set(TEST_SQLITE3_LIB
	libsqlite3
	${Boost_LIBRARIES}
	WS2_32.lib
	setupapi.lib 
)
else()

link_directories(/lib)

set(TEST_SQLITE3_LIB
    libsqlite3
	pthread
	rt 
	dl
	${Boost_LIBRARIES}
)
endif()

add_executable(test_sqlite3 ${TEST_SQLITE3_SRC})
target_link_libraries(test_sqlite3 ${TEST_SQLITE3_LIB})
