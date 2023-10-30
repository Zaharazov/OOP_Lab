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