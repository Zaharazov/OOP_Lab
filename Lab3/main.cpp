#include <iostream>
#include <string>
#include "triangle.hpp"
#include "square.hpp"
#include "octagon.hpp"
class Array 
{
    private:
        Figure** arr;
        size_t _size;

    public:
        Array() 
        {
            arr = new Figure*[1];
            _size = 0;
        }

        Array(size_t len) 
        {
            arr = new Figure*[len];
            _size = 0;
        }

        ~Array() 
        {
            for (int i = 0; i < _size; ++i) 
            {
                delete arr[i];
            }
            delete[] arr;
            _size = 0;
        }

        void push_back(Figure* elem) 
        {
            arr[_size++] = elem;
        }

        void pop_back() 
        {
            --_size;
            delete arr[_size];
        }

        Figure* operator[](size_t ind) 
        {
            return arr[ind];
        }
        
        size_t get_size() const 
        {
            return _size;
        }
};

int main() 
{
    std::cout << "How many figures do you want to record: " << std::endl;
    size_t len;
    std::cin >> len;
    Array arr = Array(len);

    std::cout << "Enter the figure type and then the size of its side: " << std::endl;
    std::cout << "s - square, t - triangle, o - octagon" << std::endl;
    for (size_t i = 0; i < len; ++i)
    {
        char f_type;
        std::cin >> f_type;
        switch (f_type)
        {
            case 't':
                Triangle* t;
                t = new Triangle;
                std::cin >> *t;
                arr.push_back(t);
                break;
            case 's':
                Square* s;
                s = new Square;
                std::cin >> *s;
                arr.push_back(s);
                break;
            case 'o':
                Octagon* o; 
                o = new Octagon;
                std::cin >> *o;
                arr.push_back(o);
                break;
        }
        std::cout << "Data saved." << std::endl;
    }
    std::cout << std::endl << "Enter an action on the object: " << std::endl;
    std::cout << "fig_coords - print the coordinates of the figure by index." << std::endl;
    std::cout << "del_fig - remove the last figur from the array." << std::endl;
    std::cout << "center - print the center of the figure by index." << std::endl;
    std::cout << "square - print the square of the figure by index." << std::endl;
    std::cout << "compare - compare 2 figures. " << std::endl;
    std::cout << "total_square - print the total square of all figures." << std::endl;
    std::cout << "exit - finish the program." << std::endl << std::endl;

    std::string action;
    do {
        std::cin >> action;
        if (action == "fig_coords") 
        {
            size_t ind;
            std::cin >> ind;
            std::cout << std::endl << (*arr[ind - 1]) << std::endl;
        }
        else if (action == "del_fig") 
        {
            arr.pop_back();
        }
        else if (action == "center") 
        {
            size_t ind;
            std::cin >> ind;
            std::cout << arr[ind - 1]->center().first << " " << arr[ind - 1]->center().second << std::endl;
        }
        else if (action == "square") 
        {
            size_t ind;
            std::cin >> ind;
            std::cout << (double)(*arr[ind - 1]) << std::endl;
        }
        else if (action == "compare") 
        {
            size_t ind1, ind2;
            std::cin >> ind1 >> ind2;
            std::cout << (*arr[ind1 - 1] == *arr[ind2 - 1]) << std::endl;
        }
        else if (action == "total_square") 
        {
            double suma = 0;
            for (int i = 0; i < arr.get_size(); ++i) 
            {
                suma += (double)(*arr[i]);
            }
            std::cout << suma << std::endl;
        }
    } while (action != "exit");
}