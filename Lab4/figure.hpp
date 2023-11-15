#pragma once
#include <iostream>
#include <vector>
#include <concepts>

template <typename T>
concept Dot = (std::floating_point<T>);
template <Dot T>

class Figure 
{
    protected:
        std::vector<std::pair<T, T>> dots;

    public:
        Figure() noexcept = default;
        ~Figure() = default;

        virtual std::pair<T, T> center() const = 0;
        virtual double f_square() const = 0;
        virtual operator double() const = 0;

        friend std::ostream& operator << (std::ostream& out, const Figure<T>& other)
        {
            for (size_t i = 0; i < other.dots.size(); ++i) 
            {
                out << other.dots[i].first << " " << other.dots[i].second << std::endl;
            }
            return out;
        }

        virtual bool operator == (const Figure<T>& other) const
        {
            return dots == other.dots;
        }
    };
