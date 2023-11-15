#include <iostream>
#include <string>
#include "triangle.hpp"
#include "square.hpp"
#include "octagon.hpp"
#include "array.hpp"
#include "figure.hpp"
#include <memory>

int main() 
{
    std::cout << "How many figures do you want to record: " << std::endl;
    size_t len;
    std::cin >> len;
    Array <std::shared_ptr <Figure<double>>> arr = Array <std::shared_ptr <Figure<double>>> (len);

    std::cout << "Enter the figure type and then the size of its side: " << std::endl;
    std::cout << "s - square, t - triangle, o - octagon" << std::endl;
    for (size_t i = 0; i < len; ++i)
    {
        char f_type;
        std::cin >> f_type;
        if (f_type == 't')
        {
            Triangle <double> t;
            std::cin >> t;
            std::shared_ptr<Figure<double>> t_ = std::make_shared <Triangle<double>>(t);
            arr.push_back(t_);
        }
        else if (f_type == 's') 
        {
            Square <double> s;
            std::cin >> s;
            std::shared_ptr<Figure<double>> s_ = std::make_shared <Square<double>>(s);
            arr.push_back(s_);  
        }
        else if (f_type == 'o')
        {
            Octagon<double> o; 
            std::cin >> o;
            std::shared_ptr<Figure<double>> o_ = std::make_shared <Octagon<double>>(o);
            arr.push_back(o_);
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
            ind--;
            std::cout << std::endl << (*arr[ind]) << std::endl;
        }
        else if (action == "del_fig") 
        {
            arr.pop_back();
        }
        else if (action == "center") 
        {
            size_t ind;
            std::cin >> ind;
            ind--;
            std::cout << arr[ind]->center().first << " " << arr[ind]->center().second << std::endl;
        }
        else if (action == "square") 
        {
            size_t ind;
            std::cin >> ind;
            ind--;
            std::cout << (double)(*arr[ind]) << std::endl;
        }
        else if (action == "compare") 
        {
            size_t ind1, ind2;
            std::cin >> ind1 >> ind2;
            ind1--; ind2--;
            std::cout << (*arr[ind1] == *arr[ind2]) << std::endl;
        }
        else if (action == "total_square") 
        {
            double suma = 0;
            for (size_t i = 0; i < arr.get_size(); ++i) 
            {
                suma += (double)(*arr[i]);
            }
            std::cout << suma << std::endl;
        }
    } while (action != "exit");
}

