# OOP_Labs
Лабораторные работы по курсу ООП.

В репозитории хранятся файлы для лабораторных работ по курсу ООП. 
Лабораторная N находится в папке LabN. 

Главный файл лабораторной работы - main.cpp, необходимые для работы функции описываются в отдельных файлах .cpp, которые дополняются заголовочными файлами .hpp.

Лабораторные работы выполняются с использованием CMake и GTest.

Пример простейшего файла с тестами:
```
#include <gtest/gtest.h> 
#include "eliminate_unset_bits.hpp" 

TEST(test1, basic_test_set1) 
{ 
    ASSERT_TRUE(eliminate_unset_bits("0")==0); 
} 
```
Пример простейшего CMake файла:
```
cmake_minimum_required(VERSION 3.10) 

# set the project name 
project(Lab1) 
 
include_directories(${GTEST_INCLUDE_DIRS}) 

set(CMAKE_CXX_STANDARD 20) 

add_subdirectory(googletest) 

# add the executable 
add_executable(tests tests.cpp eliminate_unset_bits.cpp) 
add_executable(main main.cpp eliminate_unset_bits.cpp) 

target_link_libraries(tests PRIVATE GTest::gtest_main) 

include(GoogleTest)

gtest_discover_tests(tests) 
```
>[!NOTE]
>Примеры CMake и GTest файлов основаны на данных из первой лабораторной работы.
