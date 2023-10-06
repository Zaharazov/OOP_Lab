#pragma once
#include <string>
#include <vector>

class Seven
{
    private:
        std::vector<unsigned char> s_array;

    public:
        Seven();
        Seven(const std::size_t & n, unsigned char);
        Seven(const std::initializer_list<unsigned char> &t);
        Seven(const std::string &t);
        Seven(const Seven& other);
        Seven(Seven&& other) noexcept;
        virtual ~Seven() noexcept;

        Seven operator + (const Seven&);
        Seven operator - (const Seven&);
        Seven operator = (const Seven&);
        bool operator < (const Seven&);
        bool operator > (const Seven&);
        bool operator == (const Seven&);

        std::string to_string() const noexcept;
        friend std::ostream& operator << (std::ostream&, const Seven&);
};
