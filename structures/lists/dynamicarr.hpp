//
//  dynamicarr.hpp
//  Array
//
//  Created by Ming Kai Chen on 2014-05-09.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#pragma once
#ifndef __DYNAMIC_ARR__H
#define __DYNAMIC_ARR__H

#include <string>

template <class T>
using equality = bool (*)(const T&, const T&);

template <class T>
bool genericEquality(const T& o1, const T& o2) {
    return o1 == o2;
}

template <class T>
class dynamicarr
    {    
    private:
        T* array;
        size_t allocSize;
        void dynamicSize(size_t expand = 2); // handles the checking and expansion of the array
    public:
        dynamicarr();
        dynamicarr(const dynamicarr<T>& src);
        ~dynamicarr();
        dynamicarr<T>& operator = (const dynamicarr<T>& src);

        T& operator [] (size_t index);

        signed indexOf(T elem, equality<T> eqCb = genericEquality) const;
    };
    
#include "dynamicarr.cpp"

#endif /* __DYNAMIC_ARR__H */
