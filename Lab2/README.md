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
                std::cout << (number1 + number2) << std::endl;
                break;
            case '-':
                std::cout << (number1 - number2) << std::endl;
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
                std::cout << "Incorrect expression." << std::endl;
                break;
        }
    }
    catch (const std::invalid_argument& error)
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
#include <vector>
#include <stdexcept>
 
class Seven
{
    private:
        std::vector<unsigned char> s_array;
 
    public:
        Seven();
        Seven(const std::size_t & n, unsigned char);
        Seven(const std::initializer_list<unsigned char> &t);
        Seven(const std::string &t);
        Seven(const Seven& other);
        Seven(Seven&& other) noexcept;
        virtual ~Seven() noexcept;
 
        Seven operator + (const Seven&);
        Seven operator - (const Seven&);
        Seven operator = (const Seven&);
        bool operator < (const Seven&);
        bool operator > (const Seven&);
        bool operator == (const Seven&);
 
        std::string to_string() const noexcept;
        friend std::ostream& operator << (std::ostream&, const Seven&);
};
```

### seven.cpp
```
#include "seven.hpp"
#include <cmath>
 
// Constructors
 
Seven::Seven() : s_array(1, '0') {}
 
Seven::Seven(const size_t & n, unsigned char t = '0')
{
    if ((t > 54) || (t < 48)) throw std::invalid_argument("Character not from the working alphabet has been entered");
    s_array.resize(n, t);
}
 
Seven::Seven(const std::initializer_list<unsigned char> &t)
{
    s_array.resize(t.size());
    int i = t.size() - 1;
 
    for (unsigned char elem : t)
    {
        if ((elem > 54) || (elem < 48)) throw std::invalid_argument("Character not from the working alphabet has been entered");
 
        s_array[i--] = elem;
    }
}
 
Seven::Seven(const std::string &t)
{
    for (int i = t.size() - 1; i >= 0; --i)
    {
        if ((t[i] < 48) || (t[i] > 54)) throw std::invalid_argument("Character not from the working alphabet has been entered");
 
        s_array.push_back(t[i]);
    }
}
 
Seven::Seven(const Seven& other)
{
    s_array = other.s_array;
}
 
Seven::Seven(Seven&& other) noexcept
{
    s_array = other.s_array;
}
 
Seven::~Seven() noexcept 
{
 
}
 
// Operations
 
Seven Seven::operator + (const Seven& other)
{
    const std::vector<unsigned char> *f_value, *s_value;
    if (s_array.size() < other.s_array.size()) 
    {
        f_value = &other.s_array;
        s_value = &s_array;
    }
    else
    {
        f_value = &s_array;
        s_value = &other.s_array;
    }
 
    Seven result = Seven(f_value->size(), '0');
    int i_val = 0; 
    int i_position = 0, remnant = 0;
    for (int i = 0; i < s_value->size(); ++i)
    {
        i_val = ((*f_value)[i] - 48) + ((*s_value)[i] - 48) + remnant;
 
        remnant = i_val / 7;
        i_position = i_val % 7;
        result.s_array[i] = i_position + 48;
    }
    for (int i = s_value->size(); i < f_value->size(); ++i)
    {
        i_val = ((*f_value)[i] - 48) + remnant;
        remnant = i_val / 7;
        i_position = i_val % 7;
        result.s_array[i] = i_position + 48;
    }
 
    if (remnant > 0) result.s_array.push_back(remnant + 48);
 
    return result;
}
 
Seven Seven::operator - (const Seven& other)
{
    Seven result = *this;
 
    if (*this < other) throw std::underflow_error("A negative value will be received");
 
    int remnant = 0;
    int i_val = 0;
    for (int i = 0; i < other.s_array.size(); ++i)
    {
        i_val = (s_array[i] - 48) - (other.s_array[i] - 48) - remnant;
        result.s_array[i] = ((i_val % 7 + 7) % 7) + 48;
        remnant = i_val < 0 ? 1 : 0;
    }
 
    if (s_array.size() > other.s_array.size())  result.s_array[other.s_array.size()] = ((s_array[other.s_array.size()] - 48) - remnant) + 48;
    for (int i = result.s_array.size() - 1; i >= 0; --i)
    {
        if ((result.s_array[i] == '0') && (result.s_array.size() > 1)) 
            result.s_array.pop_back();
        else
            break;
    }
    return result;
}
 
Seven Seven::operator = (const Seven& other)
{
    s_array = other.s_array;
    return *this;
}
 
bool Seven::operator < (const Seven& other)
{
    if (s_array.size() < other.s_array.size())  return true;
 
    if (s_array.size() > other.s_array.size())  return false;
 
    for (int i = s_array.size() - 1; i >= 0; --i) 
    {
        if (s_array[i] < other.s_array[i])  return true;
 
        if (s_array[i] > other.s_array[i])  return false;
    }
 
    return false;
}
 
bool Seven::operator > (const Seven& other)
{
    if (s_array.size() > other.s_array.size())  return true;
 
    if (s_array.size() < other.s_array.size())  return false;
 
    for (int i = s_array.size() - 1; i >= 0; --i) 
    {
        if (s_array[i] > other.s_array[i])  return true;
 
        if (s_array[i] < other.s_array[i])  return false;
    }
 
    return false;
}
 
bool Seven::operator == (const Seven& other)
{
    if (s_array.size() != other.s_array.size()) return false;
 
    for (int i = s_array.size() - 1; i >= 0; --i) 
    {
        if (s_array[i] != other.s_array[i]) return false;
    }
 
    return true;
}
 
// Ostream
 
std::string Seven::to_string() const noexcept
{
    std::string result;
    for (int i = s_array.size() - 1; i >= 0; --i)
        result += s_array[i];
    return result;
}
 
std::ostream& operator << (std::ostream& cout, const Seven& value)
{
    return cout << value.to_string();
}
```

### CMakeLists.txt
```
cmake_minimum_required(VERSION 3.10)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(seven seven.hpp seven.cpp)

add_executable(lab_2 main.cpp seven.cpp)

```
