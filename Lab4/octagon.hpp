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

