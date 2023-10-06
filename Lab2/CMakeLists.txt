cmake_minimum_required(VERSION 3.10)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(seven seven.hpp seven.cpp)

add_executable(lab_2 main.cpp seven.cpp)
