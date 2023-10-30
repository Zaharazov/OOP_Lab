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
