#include <iostream>
#include "list.hpp"
#include "allocator.hpp"
 
int main()
{
    List <int, Allocator<int>> l(10, 1);
 
    std::cout << "Here are the elements of a list: " << std::endl;
    for (int elem : l)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
