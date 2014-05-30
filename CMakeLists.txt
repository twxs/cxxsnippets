cmake_minimum_required(VERSION 2.8)

# http://www.guyrutenberg.com/2014/01/05/enabling-c11-c0x-in-cmake/
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

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



