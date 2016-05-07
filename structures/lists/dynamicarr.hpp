//
//  dynamicarr.hpp
//  Array
//
//  description: dynamically increasing array
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

// dynamically increasing array
template <class T>
class dynamicarr
    {    
    private:
        T* array;
        size_t allocSize;

        // handles the dynamic checking and expansion of the array
        // @param[in]   expand     expansion rate: next size = cur size * expand
        // @return      void
        void dynamicSize (size_t expand = 2); // 
    public:
        // allocates an array with default size of 128
        // @remark default constructor
        dynamicarr (void);

        // destroys self content, then copy src content to self
        // @remark copy constructor
        dynamicarr (const dynamicarr<T>& src);

        // destructor
        // @remark destructor
        virtual ~dynamicarr (void);

        // copy assignment operator
        // @param[in]   src     reference to dynamic object to copy from
        // @return      reference to this after copy assignment
        dynamicarr<T>& operator = (const dynamicarr<T>& src);

        // overloaded bracket reference operator
        // @param[in]   index     integer index of the accessing element in arr
        // @return      reference to data at index
        T& operator [] (size_t index);

        // finds the index of the first instance of element
        // determines equality using input function following signature: bool (*)(const T&, const T&);
        // @param[in]   elem     element to search for
        // @param[in]   eqCb     optional equality function (defaults to ==)
        // @return      index of the elem if found, -1 otherwise
        signed indexOf (T elem, equality<T> eqCb = genericEquality) const;
    };
    
#include "dynamicarr.cpp"

#endif /* __DYNAMIC_ARR__H */
