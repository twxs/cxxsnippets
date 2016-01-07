cmake_minimum_required(VERSION 2.8)

find_package(GTest )
# hack for system where gtest-main is not available 
if(NOT GTEST_LIBRARIES)
    _gtest_append_debugs(GTEST_LIBRARIES GTEST_LIBRARY)
    message(${GTEST_LIBRARIES})
endif()

find_package(Threads REQUIRED)

function(add_executable_and_tests EXECUTABLE)
	add_executable(${EXECUTABLE} ${ARGN})
	target_link_libraries(${EXECUTABLE} ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
	target_include_directories(${EXECUTABLE} PUBLIC ${GTEST_INCLUDE_DIR})
    target_compile_features(${EXECUTABLE} PRIVATE cxx_auto_type cxx_range_for)
	FOREACH(SRC ${ARGN})
		SET(TEST_REGEX "^[ \t]*(TEST|TEST_F)\\(([^,]*),[ \t]*([^\\)]*)\\).*$")
		FILE(STRINGS ${SRC} GTEST_LINES REGEX ${TEST_REGEX})
		FOREACH(GTEST_LINE ${GTEST_LINES})
			STRING(REGEX REPLACE ${TEST_REGEX} "\\2;\\3" GTEST_SPLIT_LINE ${GTEST_LINE})
			LIST(GET GTEST_SPLIT_LINE 0 GTEST_GROUP_NAME)
			LIST(GET GTEST_SPLIT_LINE 1 GTEST_TEST_NAME)
			ADD_TEST(${GTEST_GROUP_NAME}.${GTEST_TEST_NAME} ${EXECUTABLE} --gtest_filter=${GTEST_GROUP_NAME}.${GTEST_TEST_NAME})
		ENDFOREACH()
	ENDFOREACH()

endfunction(add_executable_and_tests)


include_directories(${GTEST_INCLUDE_DIRS})

add_executable_and_tests(algorithm main.cpp src/algorithm.cpp)


enable_testing()



