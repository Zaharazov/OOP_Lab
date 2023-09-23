# ООП. Лабораторная работа 1.
## Автор: Епифанов Евгений, группа М8О-212Б-22
## Вариант: 8
Вам дана строка, представляющая собой число в двоичном виде. Ваша задача - удалить все 
нулевые биты в этой строке и вернуть соответствующее число (сохранив только "1"). 

На практике вы должны реализовать эту функцию: 
```
long eliminate_unset_bits(string number);
```
Реализация функции:
```
long eliminate_unset_bits(string BinNumber) 
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
        long DNumber; 
        DNumber = pow(2, NewBinNumber.size()) - 1; 
        return DNumber; 
    } 

}
```

Примеры:

eliminate_unset_bits("1101010101010101") -> 255 (= 11111111)

eliminate_unset_bits("111") -> 7 

eliminate_unset_bits("1000000") -> 1 

eliminate_unset_bits("000") -> 0
