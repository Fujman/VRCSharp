#ifndef __YARRAY2_H
#define __YARRAY2_H
#include "YArray.h"

template <class T>
class YArray: public YDynamicArray<T>
{
public:
        YArray(int nSize, T* p=NULL) : YDynamicArray(nSize, (void*)p)
          {}
        YArray()
          {}
};

typedef YDynamicArray<YMemory::byte_t>  YByteArray; //byte non-resizable array

#endif//__YARRAY2_H
#pragma once
