cmake_minimum_required(VERSION 3.10)
project(Lab2)

include_directories(${GTEST_INCLUDE_DIRS}) 

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest) 

add_executable(lab_2 main.cpp seven.cpp)

add_executable(test test.cpp seven.cpp)

target_link_libraries(test PRIVATE GTest::gtest_main) 
include(GoogleTest) 
gtest_discover_tests(test) 
