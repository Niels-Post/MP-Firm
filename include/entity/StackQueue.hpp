#pragma once

#undef min
#undef max
#include <algorithm>

template<typename T, size_t max_size>
class StackQueue {
    size_t _front = 0;
    size_t _back  = 0;

    T data[max_size];


public:

    StackQueue() {}

    bool empty() {
        return _front == _back;
    }

    bool push(const T& el) {
        if(_back == (_front - 1) || (_back == (max_size - 1) && _front == 0)){
            return false;
        }
        data[_back] = el;
        _back = (_back + 1) % max_size;
        return true;
    }

    T pop() {
        T el = data[_front];
        _front = (_front + 1) % max_size;
        return std::move(el);
    }

    T front() {
        return data[_front];
    }


};