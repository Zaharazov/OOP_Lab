cmake_minimum_required(VERSION 3.10)
project(Lab03)

# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    lab_03
    main.cpp
    figure.cpp
    triangle.cpp
    square.cpp
    octagon.cpp)


# enable_testing()
# add_executable(
#    tests03
#    tests.cpp
#    figure.cpp
#    triangle.cpp
#    square.cpp
#    octagon.cpp)

# target_link_libraries(tests03 ${GTEST_LIBRARIES})

# add_test(NAME BASIC COMMAND tests03)