/*
 * Copyright (c) 2021. Niels Post. AI Lab Vrije Universiteit Brussel.
 *
 * This file is part of MP-Firm.
 *
 * MP-Firm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MP-Firm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MP-Firm.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once


#include <cstddef>
#include <utility>

/**
 * Array-based implementation of a Queue that can be placed on the stack.
 *
 * @tparam T Type of objects put into the stack
 * @tparam max_size Maximum size of the stack
 */
template<typename T, size_t max_size>
class StackQueue {
    size_t _front = 0;
    size_t _back  = 0;

    T data[max_size];


public:

    StackQueue() {}

    /**
     * Check if the queue is empty
     * @return True if the queue is empty
     */
    bool empty() {
        return _front == _back;
    }

    /**
     * Push a value to the back of the queue
     * @param el Value to put on the queue
     * @return True if the push was successful, false if the queue was already full
     */
    bool push(const T& el) {
        if(_back == (_front - 1) || (_back == (max_size - 1) && _front == 0)){
            return false;
        }
        data[_back] = el;
        _back = (_back + 1) % max_size;
        return true;
    }

    /**
     * Pop the next value from the queue.
     *
     * Unsafe! call empty first to check if there is anything to pop.
     * @return
     */
    T pop() {
        T el = data[_front];
        _front = (_front + 1) % max_size;
        return std::move(el);
    }

    /**
     * Return the front of the queue without popping.
     *
     * Unsafe! call empty first to check if there is anything to pop.
     * @return A copy of the front of the queue
     */
    T front() {
        return data[_front];
    }


};