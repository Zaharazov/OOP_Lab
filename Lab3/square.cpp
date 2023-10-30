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