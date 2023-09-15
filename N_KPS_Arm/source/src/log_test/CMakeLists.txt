set(LOG_TEST_SRC

	main.cpp
)


IF(CMAKE_BUILD_TYPE MATCHES "release")
add_executable(test_log ${LOG_TEST_SRC})
target_link_libraries(test_log libcom liblog4cpp ${Boost_LIBRARIES})
ELSE()
add_executable(test_logd ${LOG_TEST_SRC})
target_link_libraries(test_logd libcomd liblog4cppd ${Boost_LIBRARIES})
ENDIF()



