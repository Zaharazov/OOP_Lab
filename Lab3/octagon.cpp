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