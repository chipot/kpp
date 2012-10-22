#pragma once
#ifndef KLIB_9O1E4EZS
#define KLIB_9O1E4EZS

#include "types.h"

namespace kl {

template <typename T>
T *memcpy(T *dest, T *src, ulong n)
{
    for (ulong i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }
    return dest;
}

template <typename T, long _size>
class array
{
 public:
  long max_size() {return _size;};
  T &  operator[](int pos){return _array[pos];};

 private:
  T _array[_size];
};

}

#endif /* end of include guard: KLIB_9O1E4EZS */
