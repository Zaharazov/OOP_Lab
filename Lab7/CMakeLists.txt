cmake_minimum_required(VERSION 3.10)
project(OOP7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app main.cpp npc.cpp druid.cpp squirrel.cpp werewolf.cpp)

enable_testing()
add_subdirectory(googletest)

add_executable(tests tests.cpp npc.cpp druid.cpp squirrel.cpp werewolf.cpp)

target_link_libraries(tests PRIVATE GTest::gtest_main)
include(GoogleTest)
