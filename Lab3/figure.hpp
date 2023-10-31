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
