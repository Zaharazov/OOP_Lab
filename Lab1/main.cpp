#include <iostream> 
#include "eliminate_unset_bits.hpp" 
using namespace std; 

int main() 
{ 
    string BinNumber; 
    cin >> BinNumber; 
    cout << eliminate_unset_bits(BinNumber) << endl; 

    return 0; 
}
