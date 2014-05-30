cmake_minimum_required(VERSION 2.8)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(main main.cpp)

target_link_libraries(main ${GTEST_BOTH_LIBRARIES})

enable_testing()

add_test(A main)

