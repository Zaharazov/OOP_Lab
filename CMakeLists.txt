cmake_minimum_required(VERSION 3.10) 

# set the project name 
project(TestProject) 
 
include_directories(${GTEST_INCLUDE_DIRS}) 

set(CMAKE_CXX_STANDARD 20) 
# set(CMAKE_CXX_STANDARD_REQUIRED ON) 

add_subdirectory(googletest) 

# add the executable 
add_executable(tests tests.cpp func.cpp) 
add_executable(prog prog.cpp func.cpp) 

target_link_libraries(tests PRIVATE GTest::gtest_main) 

include(GoogleTest) 
gtest_discover_tests(tests) 