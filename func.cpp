#include "func.hpp" 
#include <cmath>
using namespace std; 

int func(string BinNumber) 
{ 
    string NewBinNumber = ""; 
    for (int i = 0; i < BinNumber.size(); ++i) 
    { 
        if (BinNumber[i] == '1') NewBinNumber += BinNumber[i]; 
    } 

    if (NewBinNumber.size() == 0) 
        return 0; 
    else 
    { 
        int DNumber; 
        DNumber = pow(2, NewBinNumber.size()) - 1; 
        return DNumber; 
    } 

}