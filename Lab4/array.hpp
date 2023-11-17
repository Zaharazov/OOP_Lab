#pragma once
#include <iostream>
#include <memory>

template <class T>

class Array 
{
    private:
        std::shared_ptr<T[]> arr;
        size_t _size;

    public:
        Array() 
        {
            arr = std::shared_ptr<T[]>(new T[1]);
            _size = 0;
        }

        Array(size_t len) 
        {
            arr = std::shared_ptr<T[]>(new T[len]);
            _size = 0;
        }

        ~Array() 
        {
            _size = 0;
        }

        void push_back(T elem) 
        {
            arr[_size++] = elem;
        }

        void pop_back() 
        {
            --_size;
        }

        T& operator[](size_t& ind) const
        {
            if (ind >= _size) throw std::invalid_argument("Attempt to process a non-exist object.");
            return arr[ind];
        }
        
        size_t get_size() const 
        {
            return _size;
        }
};
