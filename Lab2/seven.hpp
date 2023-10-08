#pragma once
#include <string>
 
class Seven
{
    private:
        unsigned char *s_array;
        std::size_t s_size;
        void resize_arr(const size_t);
 
    public:
        Seven();
        Seven(const std::size_t &, unsigned char);
        Seven(const std::initializer_list<unsigned char> &);
        Seven(const std::string &);
        Seven(const Seven&);
        Seven(Seven&& other) noexcept;
        ~Seven() noexcept;
 
        Seven operator + (const Seven&);
        Seven operator - (const Seven&);
        Seven operator = (const Seven&);
        bool operator < (const Seven&);
        bool operator > (const Seven&);
        bool operator == (const Seven&);
 
        std::string to_string() const;
};
