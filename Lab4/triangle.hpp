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
