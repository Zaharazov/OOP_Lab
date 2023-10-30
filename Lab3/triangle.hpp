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
