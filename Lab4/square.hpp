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

