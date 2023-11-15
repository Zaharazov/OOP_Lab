# Лабораторная работа 4
## Епифанов Евгений, М8О-212Б-22, Вариант 8

Разработать шаблоны классов согласно варианту задания. Параметром шаблона должен являться скалярный тип данных задающий тип данных для оси координат. Классы должны иметь только публичные поля. В классах не должно быть методов, только поля. Фигуры являются фигурами вращения (равнобедренными), за исключением трапеции и прямоугольника. Для хранения координат фигур необходимо использовать шаблон `std::pair` (или реализовать свой шаблон `template <class T> Point` в качестве параметра шаблона должен быть тип для переменных
координат).

Например:
```cpp
template <class T>
struct Square{
using vertex_t = std::pair<T,T>;
vertex_t a,b,c,d;
};
```
Создать программу, которая позволяет:
- Запрещается использовать сырые указатели
- Вводить из стандартного ввода `std::cin` фигуры, согласно варианту задания.
- Сохранять созданные фигуры в динамический массив (переиспользовать от предыдущей лабораторной работы) умных указатели на фигур (`std::smart_ptr<Figure*>`)
- Динамический массив должен быть сделан в виде шаблона (параметр шаблона – класс для хранения в массиве `template <class T> Array {...}`)
- Фигуры должны иметь переопределенные операции копирования, сравнения и приведение к типу `double` (вычисление площади)
- Вызывать для всего массива общие функции (1-3 см. выше).Т.е. распечатывать для каждой фигуры в массиве геометрический центр, координаты вершин и площадь.
- Необходимо уметь вычислять общую площадь фигур в массиве.
- Удалять из массива фигуру по индексу;

Вариант 8: 8-угольник, треугольник, квадрат.

## Программы

### main.cpp
```cpp
#include <iostream>
#include <string>
#include "triangle.hpp"
#include "square.hpp"
#include "octagon.hpp"
#include "array.hpp"
#include "figure.hpp"
#include <memory>

int main() 
{
    std::cout << "How many figures do you want to record: " << std::endl;
    size_t len;
    std::cin >> len;
    Array <std::shared_ptr <Figure<double>>> arr = Array <std::shared_ptr <Figure<double>>> (len);

    std::cout << "Enter the figure type and then the size of its side: " << std::endl;
    std::cout << "s - square, t - triangle, o - octagon" << std::endl;
    for (size_t i = 0; i < len; ++i)
    {
        char f_type;
        std::cin >> f_type;
        if (f_type == 't')
        {
            Triangle <double> t;
            std::cin >> t;
            std::shared_ptr<Figure<double>> t_ = std::make_shared <Triangle<double>>(t);
            arr.push_back(t_);
        }
        else if (f_type == 's') 
        {
            Square <double> s;
            std::cin >> s;
            std::shared_ptr<Figure<double>> s_ = std::make_shared <Square<double>>(s);
            arr.push_back(s_);  
        }
        else if (f_type == 'o')
        {
            Octagon<double> o; 
            std::cin >> o;
            std::shared_ptr<Figure<double>> o_ = std::make_shared <Octagon<double>>(o);
            arr.push_back(o_);
        }
               
        std::cout << "Data saved." << std::endl;
    }
    std::cout << std::endl << "Enter an action on the object: " << std::endl;
    std::cout << "fig_coords - print the coordinates of the figure by index." << std::endl;
    std::cout << "del_fig - remove the last figur from the array." << std::endl;
    std::cout << "center - print the center of the figure by index." << std::endl;
    std::cout << "square - print the square of the figure by index." << std::endl;
    std::cout << "compare - compare 2 figures. " << std::endl;
    std::cout << "total_square - print the total square of all figures." << std::endl;
    std::cout << "exit - finish the program." << std::endl << std::endl;

    std::string action;
    do {
        std::cin >> action;
        if (action == "fig_coords") 
        {
            size_t ind;
            std::cin >> ind;
            ind--;
            std::cout << std::endl << (*arr[ind]) << std::endl;
        }
        else if (action == "del_fig") 
        {
            arr.pop_back();
        }
        else if (action == "center") 
        {
            size_t ind;
            std::cin >> ind;
            ind--;
            std::cout << arr[ind]->center().first << " " << arr[ind]->center().second << std::endl;
        }
        else if (action == "square") 
        {
            size_t ind;
            std::cin >> ind;
            ind--;
            std::cout << (double)(*arr[ind]) << std::endl;
        }
        else if (action == "compare") 
        {
            size_t ind1, ind2;
            std::cin >> ind1 >> ind2;
            ind1--; ind2--;
            std::cout << (*arr[ind1] == *arr[ind2]) << std::endl;
        }
        else if (action == "total_square") 
        {
            double suma = 0;
            for (size_t i = 0; i < arr.get_size(); ++i) 
            {
                suma += (double)(*arr[i]);
            }
            std::cout << suma << std::endl;
        }
    } while (action != "exit");
}
```

### array.hpp
```cpp
#pragma once
#include <iostream>
#include <memory>

template <class T>

class Array 
{
    private:
        std::shared_ptr<T[]> arr;
        size_t _size;

    public:
        Array() 
        {
            arr = std::shared_ptr<T[]>(new T[1]);
            _size = 0;
        }

        Array(size_t len) 
        {
            arr = std::shared_ptr<T[]>(new T[len]);
            _size = 0;
        }

        ~Array() 
        {
            _size = 0;
        }

        void push_back(T elem) 
        {
            arr[_size++] = elem;
        }

        void pop_back() 
        {
            --_size;
        }

        T& operator[](size_t& ind) const
        {
            if (ind >= _size) throw std::invalid_argument("Attempt to process a non-exist object.");
            return arr[ind];
        }
        
        size_t get_size() const 
        {
            return _size;
        }
};
```

### figure.hpp
```cpp
#pragma once
#include <iostream>
#include <vector>
#include <concepts>

template <typename T>
concept Dot = (std::floating_point<T>);
template <Dot T>

class Figure 
{
    protected:
        std::vector<std::pair<T, T>> dots;

    public:
        Figure() noexcept = default;
        ~Figure() = default;

        virtual std::pair<T, T> center() const = 0;
        virtual double f_square() const = 0;
        virtual operator double() const = 0;

        friend std::ostream& operator << (std::ostream& out, const Figure<T>& other)
        {
            for (size_t i = 0; i < other.dots.size(); ++i) 
            {
                out << other.dots[i].first << " " << other.dots[i].second << std::endl;
            }
            return out;
        }

        virtual bool operator == (const Figure<T>& other) const
        {
            return dots == other.dots;
        }
    };
```

### octagon.hpp
```cpp
#pragma once
#include <iostream>
#include <cmath>
#include "figure.hpp"

template <Dot T>

class Octagon: public Figure<T> 
{
    private:
        using Figure<T>::dots;
        
    public:
        Octagon() noexcept
        {
            dots.resize(8, {0, 0});
        }

        Octagon(const double& len)
        {
            dots.resize(8);
            dots[0] = {len * std::sqrt(2) / 2, 0};
            dots[1] = {len + len * std::sqrt(2) / 2, 0};
            dots[2] = {std::sqrt(2) * len, len * std::sqrt(2) / 2};
            dots[3] = {std::sqrt(2) * len, len + len * std::sqrt(2) / 2};
            dots[4] = {len + len * std::sqrt(2) / 2, std::sqrt(2) * len};
            dots[5] = {len * std::sqrt(2) / 2, std::sqrt(2) * len};
            dots[6] = {0, len + len * std::sqrt(2) / 2};
            dots[7] = {0, len * std::sqrt(2) / 2};
        }

        Octagon(const Octagon<T>& other)
        {
            dots = other.dots;
        }

        ~Octagon()
        {
            dots.clear();
            dots.shrink_to_fit();
        }

        std::pair<T, T> center() const override
        {
            std::pair<T, T> _center;
            _center = {(std::sqrt(2)*(dots[1].first - dots[0].first) + (dots[1].first - dots[0].first)) / 2, (std::sqrt(2)*(dots[1].first - dots[0].first) + (dots[1].first - dots[0].first)) / 2};
            return _center;
        }

        double f_square() const override
        {
            return 2 * (dots[1].first - dots[0].first) * (dots[1].first - dots[0].first) * (std::sqrt(2) + 1);
        }

        operator double() const override
        {
            return f_square();
        }

        friend std::istream& operator >> (std::istream& cin, Octagon<T>& other)
        {
            T length;
            cin >> length;
            other = Octagon<T>(length);
            return cin;
        }

        using Figure<T>::operator == ;

        Octagon<T>& operator = (const Octagon<T>& other) noexcept
        {
            dots = other.dots;
            return *this;
        }

        Octagon<T>& operator = (Octagon<T>&& other) noexcept
        {
            dots = other.dots;
            other.dots.clear();
            other.dots.shrink_to_fit();
            return *this;
        }
};
```

### square.hpp
```cpp
#pragma once
#include <iostream>
#include <cmath>
#include "figure.hpp"

template <Dot T>

class Square: public Figure<T> 
{
    private:
        using Figure<T>::dots;

    public:
        Square() noexcept
        {
            dots.resize(4, {0, 0});
        }

        Square(const T& len)
        {
            dots.resize(4);
            dots[0] = {0, 0};
            dots[1] = {len, 0};
            dots[2] = {len, len};
            dots[3] = {0, len};
        }

        Square(const Square<T>& other)
        {
            dots = other.dots;
        }

        ~Square()
        {
            dots.clear();
            dots.shrink_to_fit();
        }

        std::pair<T, T> center() const override
        {
            std::pair<T, T> _center;
            _center = {dots[1].first / 2, dots[1].first / 2};
            return _center;
        }

        double f_square() const override
        {
            return dots[2].first * dots[2].second;
        }

        operator double() const override
        {
            return f_square();
        }

        friend std::istream& operator >> (std::istream& cin, Square<T>& other)
        {
            T length;
            cin >> length;
            other = Square<T>(length);
            return cin;
        }

        using Figure<T>::operator == ;

        Square<T>& operator = (const Square<T>& other) noexcept
        {
            dots = other.dots;
            return *this;
        }

        Square<T>& operator = (Square<T>&& other) noexcept
        {
            dots = other.dots;
            other.dots.clear();
            other.dots.shrink_to_fit();
            return *this;
        }
};
```

### triangle.hpp
```cpp
#pragma once
#include <iostream>
#include <cmath>
#include "figure.hpp"

template <Dot T>

class Triangle: public Figure<T> 
{
    private:
        using Figure<T>::dots;

    public:
        Triangle() noexcept
        {
            dots.resize(3, {0, 0});
        }

        Triangle(const double& len)
        {
            dots.resize(3);
            dots[0] = {0, 0};
            dots[1] = {len, 0};
            dots[2] = {len / 2, len * std::sqrt(3)/2};
        }

        Triangle(const Triangle<T>& other)
        {
            dots = other.dots;
        }

        ~Triangle()
        {
            dots.clear();
            dots.shrink_to_fit();
        }

        std::pair<T, T> center() const override
        {
            std::pair<T, T> _center;
            _center.first = (dots[1].first - dots[0].first) / 2;
            _center.second = (dots[1].first - dots[0].first) / (2*std::sqrt(3));
            return _center;
        }

        double f_square() const override
        {
            return (dots[1].first - dots[0].first)*(dots[2].second) / 2;
        }

        operator double() const override
        {
            return f_square();
        }

        friend std::istream& operator >> (std::istream& cin, Triangle<T>& other)
        {
            T length;
            cin >> length;
            other = Triangle<T>(length);
            return cin;
        }

        using Figure<T>::operator == ;

        Triangle<T>& operator = (const Triangle<T>& other) noexcept
        {
            dots = other.dots;
            return *this;
        }

        Triangle<T>& operator = (Triangle<T>&& other) noexcept
        {
            dots = other.dots;
            other.dots.clear();
            other.dots.shrink_to_fit();
            return *this;
        }
};
```

### tests.cpp
```cpp
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
```

### CMakeLists.txt
```cpp
#include <gtest/gtest.h>
#include "triangle.hpp"
#include "square.hpp"
#include "octagon.hpp"

TEST(Group_1, basic_test_set) 
{
    Triangle <double> t(2);
    Square <double> s(2);
    Octagon <double> o(2);

    EXPECT_FALSE(t == s);
    EXPECT_FALSE(s == o);
    EXPECT_FALSE(t == o);

    EXPECT_TRUE(t == t);

    EXPECT_EQ(s.center(), std::make_pair(1.0, 1.0));
}

TEST(Group_2, basic_test_set) 
{
    Square <double> s(5);

    EXPECT_EQ((double)(s), 25);
    EXPECT_EQ(s.center(), std::make_pair(2.5, 2.5));
}

TEST(Group_3, basic_test_set) 
{
    Octagon <double> o1;
    Octagon <double> o2(4);
    EXPECT_FALSE(o1 == o2);
    o1 = o2;
    EXPECT_TRUE(o1 == o2);
}
```
