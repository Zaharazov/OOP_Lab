# ООП. Лабораторная работа 2.
## Автор: Епифанов Евгений, группа М8О-212Б-22
## Вариант: 8

Используя в качестве образца класс Array (см. ниже), реализовать динамические контейнеры с использова-
нием динамического массива.

- Каждый класс должен быть разделен на интерфейс и реализацию.
- Самостоятельно определить необходимые типы, поля и дополнительные методы.
- Реализовать генерацию исключений в конструкторах и методах при необходимости (использовать
стандартные исключения).
- Реализовать арифметические операции: сложение, вычитание, копирование
- Реализовать операции сравнения: (больше, меньше, равно).
- Арифметические операции с присваиванием должны быть реализованы как методы класса.

Создать класс Seven для работы с беззнаковыми целыми семеричными числами, используя для представления
числа массив из элементов типа unsigned char, каждый элемент которого является семиричной цифрой.
Младшая цифра имеет меньший индекс (единицы — в нулевом элементе массива).

## Программы

### main.cpp
```
#include <iostream>
#include "seven.hpp"
 
int main()
{
    try
    {
        std::string value1, value2;
        char op;
        std::cout << "Enter an expression like: <value operator value> (separated by a space)" << std::endl;
        std::cin >> value1 >> op >> value2; 
        Seven number1 = Seven(value1), number2 = Seven(value2);
        switch (op)
        {
            case '+':
                std::cout << (number1 + number2).to_string() << std::endl;
                break;
            case '-':
                std::cout << (number1 - number2).to_string() << std::endl;
                break; 
            case '>':
                std::cout << (number1 > number2) << std::endl;
                break;
            case '<':
                std::cout << (number1 < number2) << std::endl;
                break;
            case '=':
                std::cout << (number1 == number2) << std::endl;
                break;
            default:
                std::cout << "Incorrect expression" << std::endl;
                break;
        }
    }
    catch (const std::invalid_argument& error) // what() - вывод ошибки в виде строки
    {
        std::cout << "Invalid argument: " << error.what() << std::endl;
    }
    catch(const std::underflow_error& error)
    {
        std::cout << "Underflow error: " << error.what() << std::endl;
    }
 
    return 0;
}
```

### seven.hpp
```
#pragma once
#include <string>
 
class Seven
{
    private:
        unsigned char *s_array;
        std::size_t s_size;
        void resize_arr(const size_t);
 
    public:
        Seven();
        Seven(const std::size_t &, unsigned char);
        Seven(const std::initializer_list<unsigned char> &);
        Seven(const std::string &);
        Seven(const Seven&);
        Seven(Seven&& other) noexcept;
        ~Seven() noexcept;
 
        Seven operator + (const Seven&);
        Seven operator - (const Seven&);
        Seven operator = (const Seven&);
        bool operator < (const Seven&);
        bool operator > (const Seven&);
        bool operator == (const Seven&);
 
        std::string to_string() const;
};
```

### seven.cpp
```
#include "seven.hpp"
 
// Resize

void Seven::resize_arr(const size_t size) 
{
    unsigned char* new_s_array = new unsigned char[size];
    std::memcpy(new_s_array, s_array, size * sizeof(unsigned char));
    s_size = size;
    delete [] s_array;
    s_array = new_s_array;
}

// Constructors
 
Seven::Seven() 
{
    s_array = new unsigned char;
    *s_array = {'0'};
    s_size = 1;
}
 
Seven::Seven(const size_t & n, unsigned char t = '0')
{
    if ((t > 54) || (t < 48)) throw std::invalid_argument("Character not from the working alphabet has been entered");
    s_array = new unsigned char [n];
    s_size = n;
    for (int i = 0; i < s_size; ++i) s_array[i] = t;
}
 
Seven::Seven(const std::initializer_list<unsigned char> &t)
{
    s_array = new unsigned char[t.size()];
    s_size = t.size();
    int i = t.size() - 1;
 
    for (unsigned char elem : t)
    {
        if ((elem > 54) || (elem < 48)) throw std::invalid_argument("Character not from the working alphabet has been entered");
 
        s_array[i--] = elem;
    }
}
 
Seven::Seven(const std::string &t)
{
    s_array = new unsigned char[t.size()];
    s_size = t.size();
    int i = t.size() - 1;

    for (unsigned char elem : t)
    {
        if ((elem < 48) || (elem > 54)) throw std::invalid_argument("Character not from the working alphabet has been entered");
 
        s_array[i--] = elem;
    }
}
 
Seven::Seven(const Seven& other)
{
    s_array = new unsigned char[other.s_size];
    std::memcpy(s_array, other.s_array, other.s_size);
    s_size = other.s_size;
}
 
Seven::Seven(Seven&& other) noexcept
{
    s_array = other.s_array;
    s_size = other.s_size;
}
 
Seven::~Seven() noexcept 
{

}
 
// Operations
 
Seven Seven::operator + (const Seven& other)
{
    size_t size_f, size_s;
    
    if (s_size < other.s_size) 
    {
        size_f = other.s_size;
        size_s = s_size;
    }
    else
    {
        size_f = s_size;
        size_s = other.s_size;
    }
 
    Seven result = Seven(size_f, '0');
    int i_val = 0; 
    int i_position = 0, remnant = 0;
    for (int i = 0; i < size_s; ++i)
    {
        i_val = ((s_array)[i] - 48) + ((other.s_array)[i] - 48) + remnant;
        remnant = i_val / 7;
        i_position = i_val % 7;
        result.s_array[i] = i_position + 48;
    }
    
    for (int i = size_s; i < size_f; ++i)
    {
        i_val = (((s_size < other.s_size) ? other.s_array : s_array)[i] - 48) + remnant;
        remnant = i_val / 7;
        i_position = i_val % 7;
        result.s_array[i] = i_position + 48;
    }
    
    if (remnant > 0)
    {
        result.resize_arr(size_f + 1);
        result.s_array[result.s_size - 1] = remnant + 48;
    }
 
    return result;
}
 
Seven Seven::operator - (const Seven& other)
{
    Seven result = *this;
 
    if (result < other) throw std::underflow_error("A negative value will be received");
 
    int remnant = 0;
    int i_val = 0;

    for (int i = 0; i < other.s_size; ++i)
    {
        i_val = (s_array[i] - 48) - (other.s_array[i] - 48) - remnant;
        result.s_array[i] = ((i_val % 7 + 7) % 7) + 48;
        remnant = i_val < 0 ? 1 : 0;
    }

    size_t j = other.s_size;
    while (remnant == 1)
    {
        i_val = (s_array[j] - 48) - remnant;
        result.s_array[j] = ((i_val % 7 + 7) % 7) + 48;
        remnant = i_val < 0 ? 1 : 0;
        j++;
    }
    
    int pop_back = 0;

    for (int i = result.s_size - 1; i > 0; --i)
    {
        if (result.s_array[i] == '0') 
            ++pop_back;
        else
            break;
    }

    result.resize_arr(result.s_size - pop_back);
    return result;
}
 
Seven Seven::operator = (const Seven& other)
{
    resize_arr(other.s_size);
    for (int i = 0; i < s_size; ++i)
        s_array[i] = other.s_array[i];
        
    return *this;
}
 
bool Seven::operator < (const Seven& other)
{
    if (s_size < other.s_size)  return true;
 
    if (s_size > other.s_size)  return false;
 
    for (int i = s_size - 1; i >= 0; --i) 
    {
        if (s_array[i] < other.s_array[i])  return true;
 
        if (s_array[i] > other.s_array[i])  return false;
    }
 
    return false;
}
 
bool Seven::operator > (const Seven& other)
{
    if (s_size > other.s_size)  return true;
 
    if (s_size < other.s_size)  return false;
 
    for (int i = s_size - 1; i >= 0; --i) 
    {
        if (s_array[i] > other.s_array[i])  return true;
 
        if (s_array[i] < other.s_array[i])  return false;
    }
 
    return false;
}
 
bool Seven::operator == (const Seven& other)
{
    if (s_size != other.s_size) return false;
 
    for (int i = s_size - 1; i >= 0; --i) 
    {
        if (s_array[i] != other.s_array[i]) return false;
    }
 
    return true;
}
 
// To string

std::string Seven::to_string() const
{
    std::string result;
    for (int i = s_size - 1; i >= 0; --i)
        result += s_array[i];

    return result;
}
```

### CMakeLists.txt
```
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
```

### test.cpp
```
#include <gtest/gtest.h>
#include "seven.hpp"

TEST(test1, basic_test_set1)
{
    Seven number1, number2;

    ASSERT_TRUE(number1.to_string() == "0" && number2.to_string() == "0");

    number1 = {'2', '3'};
    number2 = {'1', '2'};
    number2 = number2 + number1;
    EXPECT_FALSE(number1 == number2);
    EXPECT_FALSE(number1 > number2);
    EXPECT_TRUE(number1 < number2);
}

TEST(test2, basic_test_set2)
{
    Seven number1 = {'2', '1', '2'};
    Seven number2 = {'3', '4'};
    Seven number3 = {'1', '0', '3'};

    ASSERT_TRUE(number1.to_string() == "212" && number2.to_string() == "34");

    number1 = number1 - number2; // 212 - 34 = 145
    EXPECT_TRUE(number1.to_string() == "145");

    number3 = number3 + number2; // 103 + 34 = 140
    EXPECT_TRUE(number3.to_string() == "140");
}

TEST(test3, basic_test_set3)
{
    Seven number1 = {'1', '0', '0'};
    Seven number2 = {'1'};
    Seven number3 = number1 - number2;

    EXPECT_TRUE(number3.to_string() == "66");

    number1 = {'3'};
    EXPECT_THROW(number2 - number1, std::underflow_error);
}

TEST(test4, basic_test_set4)
{
    Seven number1 = {'6', '6', '6'};
    Seven number2 = {'1'};
    Seven number3 = number1 + number2;
    
    EXPECT_TRUE(number3.to_string() == "1000");

    number3 = number2 + number1;
    EXPECT_TRUE(number3.to_string() == "1000");
}
```
