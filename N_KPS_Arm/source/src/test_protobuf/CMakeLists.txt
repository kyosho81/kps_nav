set(TEST_PROTOBUF_SRC
	main.cpp
)


if(WIN32)
set(TEST_PROTOBUF_LIB
	libprotobuf_msg
	librobot
	libxmlrpc
	WS2_32.lib
	${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(TEST_PROTOBUF_LIB
	libprotobuf_msg
	librobot
	libxmlrpc
	pthread
	rt 
	${Boost_LIBRARIES}
)
endif()

add_executable(test_protobuf ${TEST_PROTOBUF_SRC})
target_link_libraries(test_protobuf ${TEST_PROTOBUF_LIB})





