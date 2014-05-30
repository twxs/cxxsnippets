cmake_minimum_required(VERSION 2.8)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)


function(add_executable_and_tests EXECUTABLE)
	add_executable(${EXECUTABLE} ${ARGN})
	target_link_libraries(${EXECUTABLE} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

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

add_executable_and_tests(algorithm src/algorithm.cpp)


enable_testing()



