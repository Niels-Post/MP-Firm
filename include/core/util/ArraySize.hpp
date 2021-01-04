#include <cstddef>

#pragma once
template<typename T, unsigned int sz>
inline size_t lengthof(T (&)[sz]) { return sz; }