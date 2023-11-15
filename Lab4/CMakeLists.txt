cmake_minimum_required(VERSION 3.10)
project(Lab04)

include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)

add_executable(
    lab_04
    main.cpp
    figure.hpp
    triangle.hpp
    square.hpp
    array.hpp
    octagon.hpp)

add_executable(
    tests04
    tests.cpp
    figure.hpp
    triangle.hpp
    square.hpp
    array.hpp
    octagon.hpp)

 target_link_libraries(tests04 PRIVATE GTest::gtest_main)
 include(GoogleTest)
 gtest_discover_tests(tests04)
