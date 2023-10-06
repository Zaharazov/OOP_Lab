#include "seven.hpp"
#include <cmath>
 
// Constructors
 
Seven::Seven() : s_array(1, '0') {}
 
Seven::Seven(const size_t & n, unsigned char t = '0')
{
    if ((t > 54) || (t < 48)) throw std::invalid_argument("Character not from the working alphabet has been entered");
    s_array.resize(n, t);
}
 
Seven::Seven(const std::initializer_list<unsigned char> &t)
{
    s_array.resize(t.size());
    int i = t.size() - 1;
 
    for (unsigned char elem : t)
    {
        if ((elem > 54) || (elem < 48)) throw std::invalid_argument("Character not from the working alphabet has been entered");
 
        s_array[i--] = elem;
    }
}
 
Seven::Seven(const std::string &t)
{
    for (int i = t.size() - 1; i >= 0; --i)
    {
        if ((t[i] < 48) || (t[i] > 54)) throw std::invalid_argument("Character not from the working alphabet has been entered");
 
        s_array.push_back(t[i]);
    }
}
 
Seven::Seven(const Seven& other)
{
    s_array = other.s_array;
}
 
Seven::Seven(Seven&& other) noexcept
{
    s_array = other.s_array;
}
 
Seven::~Seven() noexcept 
{
 
}
 
// Operations
 
Seven Seven::operator + (const Seven& other)
{
    const std::vector<unsigned char> *f_value, *s_value;
    if (s_array.size() < other.s_array.size()) 
    {
        f_value = &other.s_array;
        s_value = &s_array;
    }
    else
    {
        f_value = &s_array;
        s_value = &other.s_array;
    }
 
    Seven result = Seven(f_value->size(), '0');
    int i_val = 0; 
    int i_position = 0, remnant = 0;
    for (int i = 0; i < s_value->size(); ++i)
    {
        i_val = ((*f_value)[i] - 48) + ((*s_value)[i] - 48) + remnant;
 
        remnant = i_val / 7;
        i_position = i_val % 7;
        result.s_array[i] = i_position + 48;
    }
    for (int i = s_value->size(); i < f_value->size(); ++i)
    {
        i_val = ((*f_value)[i] - 48) + remnant;
        remnant = i_val / 7;
        i_position = i_val % 7;
        result.s_array[i] = i_position + 48;
    }
 
    if (remnant > 0) result.s_array.push_back(remnant + 48);
 
    return result;
}
 
Seven Seven::operator - (const Seven& other)
{
    Seven result = *this;
 
    if (*this < other) throw std::underflow_error("A negative value will be received");
 
    int remnant = 0;
    int i_val = 0;
    for (int i = 0; i < other.s_array.size(); ++i)
    {
        i_val = (s_array[i] - 48) - (other.s_array[i] - 48) - remnant;
        result.s_array[i] = ((i_val % 7 + 7) % 7) + 48;
        remnant = i_val < 0 ? 1 : 0;
    }
 
    if (s_array.size() > other.s_array.size())  result.s_array[other.s_array.size()] = ((s_array[other.s_array.size()] - 48) - remnant) + 48;
    for (int i = result.s_array.size() - 1; i >= 0; --i)
    {
        if ((result.s_array[i] == '0') && (result.s_array.size() > 1)) 
            result.s_array.pop_back();
        else
            break;
    }
    return result;
}
 
Seven Seven::operator = (const Seven& other)
{
    s_array = other.s_array;
    return *this;
}
 
bool Seven::operator < (const Seven& other)
{
    if (s_array.size() < other.s_array.size())  return true;
 
    if (s_array.size() > other.s_array.size())  return false;
 
    for (int i = s_array.size() - 1; i >= 0; --i) 
    {
        if (s_array[i] < other.s_array[i])  return true;
 
        if (s_array[i] > other.s_array[i])  return false;
    }
 
    return false;
}
 
bool Seven::operator > (const Seven& other)
{
    if (s_array.size() > other.s_array.size())  return true;
 
    if (s_array.size() < other.s_array.size())  return false;
 
    for (int i = s_array.size() - 1; i >= 0; --i) 
    {
        if (s_array[i] > other.s_array[i])  return true;
 
        if (s_array[i] < other.s_array[i])  return false;
    }
 
    return false;
}
 
bool Seven::operator == (const Seven& other)
{
    if (s_array.size() != other.s_array.size()) return false;
 
    for (int i = s_array.size() - 1; i >= 0; --i) 
    {
        if (s_array[i] != other.s_array[i]) return false;
    }
 
    return true;
}
 
// Ostream
 
std::string Seven::to_string() const noexcept
{
    std::string result;
    for (int i = s_array.size() - 1; i >= 0; --i)
        result += s_array[i];
    return result;
}
 
std::ostream& operator << (std::ostream& cout, const Seven& value)
{
    return cout << value.to_string();
}
