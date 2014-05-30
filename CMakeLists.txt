cmake_minimum_required(VERSION 2.8)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)


add_executable(main main.cpp)

target_include_directories(main PRIVATE ${GTEST_INCLUDE_DIRS})

target_link_libraries(main ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

enable_testing()

add_test(A main)

