# Лабораторная работа 2. Классы
## Автор: Епифанов Евгений, группа М8О-212Б-22, вариант 8

Разработать программу на языке C++ согласно варианту задания. Программа на C++ должна собираться с помощью системы сборки CMake. Программа должна получать данные из стандартного ввода (std::cin) и выводить данные в стандартный вывод (std::cout).
Необходимо зарегистрироваться на GitHub и создать репозитарий для задания лабораторных работ.
Преподавателю необходимо предъявить ссылку на публичный репозиторий на Github. Необходимо реализовать функцию согласно варианту задания. Функция должна быть помещена в отдельный файл.

Разработать классы согласно варианту задания, классы должны наследоваться от базового класса Figure. Фигуры являются фигурами вращения.
Все классы должны поддерживать набор общих методов:
1. Вычисление геометрического центра фигуры вращения;
2. Вывод в стандартный поток вывода std::cout координат вершин фигуры через перегрузку оператора << для std::ostream;
3. Чтение из стандартного потока данных фигур через перегрузку оператора >> для std::istream
4. Вычисление площади фигуры через перегрузку оператора приведения к типу double;

Создать программу, которая позволяет:
- Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
- Сохранять созданные фигуры в динамический массив (по аналогии с предыдущей лабораторной работой Array) указатели на фигуру (Figure*)
- Фигуры должны иметь переопределенные операции копирования (=), перемещения (=) и сравнения (==)
- Вызывать для всего массива общие функции (1-3 см. выше).Т.е. распечатывать для каждой фигуры в массиве геометрический центр и площадь.
- Необходимо уметь вычислять общую площадь фигур в массиве. •Удалять из массива фигуру по индексу;

Вариант 8: 8-угольник, треугольник, квадрат.

## Программы

### main.cpp
```cpp
#include <iostream>
#include <string>
#include "triangle.hpp"
#include "square.hpp"
#include "octagon.hpp"
class Array 
{
    private:
        Figure** arr;
        size_t _size;

    public:
        Array() 
        {
            arr = new Figure*[1];
            _size = 0;
        }

        Array(size_t len) 
        {
            arr = new Figure*[len];
            _size = 0;
        }

        ~Array() 
        {
            for (int i = 0; i < _size; ++i) 
            {
                delete arr[i];
            }
            delete[] arr;
            _size = 0;
        }

        void push_back(Figure* elem) 
        {
            arr[_size++] = elem;
        }

        void pop_back() 
        {
            --_size;
            delete arr[_size];
        }

        Figure* operator[](size_t ind) 
        {
            return arr[ind];
        }
        
        size_t get_size() const 
        {
            return _size;
        }
};

int main() 
{
    std::cout << "How many figures do you want to record: " << std::endl;
    size_t len;
    std::cin >> len;
    Array arr = Array(len);

    std::cout << "Enter the figure type and then the size of its side: " << std::endl;
    std::cout << "s - square, t - triangle, o - octagon" << std::endl;
    for (size_t i = 0; i < len; ++i)
    {
        char f_type;
        std::cin >> f_type;
        switch (f_type)
        {
            case 't':
                Triangle* t;
                t = new Triangle;
                std::cin >> *t;
                arr.push_back(t);
                break;
            case 's':
                Square* s;
                s = new Square;
                std::cin >> *s;
                arr.push_back(s);
                break;
            case 'o':
                Octagon* o; 
                o = new Octagon;
                std::cin >> *o;
                arr.push_back(o);
                break;
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
            std::cout << std::endl << (*arr[ind - 1]) << std::endl;
        }
        else if (action == "del_fig") 
        {
            arr.pop_back();
        }
        else if (action == "center") 
        {
            size_t ind;
            std::cin >> ind;
            std::cout << arr[ind - 1]->center().first << " " << arr[ind - 1]->center().second << std::endl;
        }
        else if (action == "square") 
        {
            size_t ind;
            std::cin >> ind;
            std::cout << (double)(*arr[ind - 1]) << std::endl;
        }
        else if (action == "compare") 
        {
            size_t ind1, ind2;
            std::cin >> ind1 >> ind2;
            std::cout << (*arr[ind1 - 1] == *arr[ind2 - 1]) << std::endl;
        }
        else if (action == "total_square") 
        {
            double suma = 0;
            for (int i = 0; i < arr.get_size(); ++i) 
            {
                suma += (double)(*arr[i]);
            }
            std::cout << suma << std::endl;
        }
    } while (action != "exit");
}
```

### figure.hpp
```cpp
#pragma once
#include <iostream>
#include <vector>

class Figure 
{
    protected:
        std::vector<std::pair<double, double>> dots;

    public:
        Figure() noexcept;
        virtual ~Figure() = default;

        virtual std::pair<double, double> center() const = 0;
        virtual double f_square() const = 0;
        virtual operator double() const = 0;

        friend std::ostream& operator << (std::ostream&, const Figure&);
        friend std::istream& operator >> (std::istream&, Figure&);

        virtual bool operator == (const Figure&) const;
    };

inline std::ostream& operator << (std::ostream& out, const Figure& other) 
{
    for (size_t i = 0; i < other.dots.size(); ++i) 
    {
        out << other.dots[i].first << " " << other.dots[i].second << std::endl;
    }
    return out;
}
```

### figure.cpp
```cpp
#include "figure.hpp"

Figure::Figure() noexcept : dots(0) {}

bool Figure::operator == (const Figure& other) const  
{
    return dots == other.dots;
}

// Figure::~Figure() 
// {
//     dots.clear();
//     dots.shrink_to_fit();
// }
```

### octagon.hpp
```cpp
#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "figure.hpp"

class Octagon: public Figure 
{
    private:
        using Figure::dots;
        
    public:
        Octagon() noexcept;
        Octagon(const double&);
        ~Octagon();

        std::pair<double, double> center() const override;
        double f_square() const override;
        operator double() const override;

        friend std::istream& operator >> (std::istream&, Octagon&);

        using Figure::operator == ;

        Octagon& operator = (const Octagon&) noexcept;
        Octagon& operator = (Octagon&&) noexcept;
};

inline std::istream& operator >> (std::istream& cin, Octagon& other) 
{
    double length;
    cin >> length;
    other = Octagon(length);
    return cin;
}

```

### octagon.cpp
```cpp
#include "octagon.hpp"

Octagon::Octagon() noexcept 
{
    dots.resize(8, {0, 0});
}

Octagon::Octagon(const double& len) 
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

std::pair<double, double> Octagon::center() const 
{
    std::pair<double, double> _center;
    _center = {(std::sqrt(2)*(dots[1].first - dots[0].first) + (dots[1].first - dots[0].first)) / 2, (std::sqrt(2)*(dots[1].first - dots[0].first) + (dots[1].first - dots[0].first)) / 2};
    return _center;
}

double Octagon::f_square() const
{
    return 2 * (dots[1].first - dots[0].first) * (dots[1].first - dots[0].first) * (std::sqrt(2) + 1);
}

inline Octagon::operator double() const 
{
    return f_square();
}

Octagon& Octagon::operator = (const Octagon& other) noexcept 
{
    dots = other.dots;
    return *this;
}

Octagon& Octagon::operator = (Octagon&& other) noexcept 
{
    dots = other.dots;
    other.dots.clear();
    other.dots.shrink_to_fit();
    return *this;
}

Octagon::~Octagon() 
{
    dots.clear();
    dots.shrink_to_fit();
}
```

### triangle.hpp
```cpp
#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "figure.hpp"

class Triangle: public Figure 
{
    private:
        using Figure::dots;

    public:
        Triangle() noexcept;
        Triangle(const double&);
        ~Triangle();

        std::pair<double, double> center() const override;
        double f_square() const override;
        operator double() const override;

        friend std::ostream& operator << (std::ostream&, const Triangle&);
        friend std::istream& operator >> (std::istream&, Triangle&);

        using Figure::operator == ;

        Triangle& operator = (const Triangle&) noexcept;
        Triangle& operator = (Triangle&&) noexcept;
};

inline std::istream& operator >> (std::istream& cin, Triangle& other) 
{
    double length;
    cin >> length;
    other = Triangle(length);
    return cin;
}

```

### triangle.cpp
```cpp
#include "triangle.hpp"

Triangle::Triangle() noexcept 
{
    dots.resize(3, {0, 0});
}

Triangle::Triangle(const double& len) 
{
    dots.resize(3);
    dots[0] = {0, 0};
    dots[1] = {len, 0};
    dots[2] = {len / 2, len * std::sqrt(3)/2};
}

std::pair<double, double> Triangle::center() const 
{
    std::pair<double, double> _center;
    _center.first = (dots[1].first - dots[0].first) / 2;
    _center.second = (dots[1].first - dots[0].first) / (2*std::sqrt(3));
    return _center;
}

double Triangle::f_square() const 
{
    return (dots[1].first - dots[0].first)*(dots[2].second) / 2;
}

inline Triangle::operator double() const 
{
    return f_square();
}

Triangle& Triangle::operator = (const Triangle& other) noexcept 
{
    dots = other.dots;
    return *this;
}

Triangle& Triangle::operator = (Triangle&& other) noexcept 
{
    dots = other.dots;
    other.dots.clear();
    other.dots.shrink_to_fit();
    return *this;
}

Triangle::~Triangle() 
{
    dots.clear();
    dots.shrink_to_fit();
}
```

### square.hpp
```cpp
#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "figure.hpp"

class Square: public Figure 
{
    private:
        using Figure::dots;

    public:
        Square() noexcept;
        Square(const double&);
        ~Square();

        std::pair<double, double> center() const override;
        double f_square() const override;
        operator double() const override;

        friend std::istream& operator << (std::ostream&, const Square&);
        friend std::istream& operator >> (std::istream&, Square&);

        using Figure::operator == ;

        Square& operator = (const Square&) noexcept;
        Square& operator = (Square&&) noexcept;
};

inline std::istream& operator >> (std::istream& cin, Square& other) 
{
    double length;
    cin >> length;
    other = Square(length);
    return cin;
}
```

### square.cpp
```cpp
#include "square.hpp"

Square::Square() noexcept 
{
    dots.resize(4, {0, 0});
}

Square::Square(const double& len) 
{
    dots.resize(4);
    dots[0] = {0, 0};
    dots[1] = {len, 0};
    dots[2] = {len, len};
    dots[3] = {0, len};
}

std::pair<double, double> Square::center() const 
{
    std::pair<double, double> _center;
    _center = {dots[1].first / 2, dots[1].first / 2};
    return _center;
}

double Square::f_square() const 
{
    return dots[2].first * dots[2].second;
}

inline Square::operator double() const 
{
    return f_square();
}

Square& Square::operator = (const Square& other) noexcept 
{
    dots = other.dots;
    return *this;
}
Square& Square::operator = (Square&& other) noexcept 
{
    dots = other.dots;
    other.dots.clear();
    other.dots.shrink_to_fit();
    return *this;
}

Square::~Square() 
{
    dots.clear();
    dots.shrink_to_fit();
}
```

### CMakeLists.txt
```cpp
cmake_minimum_required(VERSION 3.10)
project(Lab03)

include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)

add_executable(
    lab_03
    main.cpp
    figure.cpp
    triangle.cpp
    square.cpp
    octagon.cpp)

add_executable(
    tests03
    tests.cpp
    figure.cpp
    triangle.cpp
    square.cpp
    octagon.cpp)

 target_link_libraries(tests03 PRIVATE GTest::gtest_main)
 include(GoogleTest)
 gtest_discover_tests(tests03)
```

### tests.cpp
```cpp
#include <gtest/gtest.h>
#include "triangle.hpp"
#include "square.hpp"
#include "octagon.hpp"

TEST(Group_1, basic_test_set) 
{
    Triangle t(2);
    Square s(2);
    Octagon o(2);

    EXPECT_FALSE(t == s);
    EXPECT_FALSE(s == o);
    EXPECT_FALSE(t == o);

    EXPECT_TRUE(t == t);

    EXPECT_EQ(s.center(), std::make_pair(1.0, 1.0));
}

TEST(Group_2, basic_test_set) 
{
    Square s(5);

    EXPECT_EQ((double)(s), 25);
    EXPECT_EQ(s.center(), std::make_pair(2.5, 2.5));
}

TEST(Group_3, basic_test_set) 
{
    Octagon o1;
    Octagon o2(4);
    EXPECT_FALSE(o1 == o2);
    o1 = o2;
    EXPECT_TRUE(o1 == o2);
}
```
