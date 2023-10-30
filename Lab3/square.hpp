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
