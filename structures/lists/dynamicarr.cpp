//
//  dynamicarr.cpp
//  Array
//
//  description: dynamically increasing array
//
//  Created by Ming Kai Chen on 2014-05-09.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __DYNAMIC_ARR__H

#include <algorithm>

#define DEFAULT_SIZE 128

// handles the dynamic checking and expansion of the array
// @param[in]   expand     expansion rate: next size = cur size * expand
// @return      void

template <class T>
void dynamicarr<T>::dynamicSize (size_t expand)
    {
    size_t newSize = allocSize*expand;
    T* newarray = new T[newSize];
    std::fill(newarray+newSize-allocSize, newarray+newSize, defaultval);
    for (size_t i = 0; i < newSize; i++)
        {
        newarray[i] = array[i];
        }
    delete[] array;
    array = newarray;
    allocSize = newSize;
    }

// allocates an array with default size of 128
// @remark default constructor

template <class T>
dynamicarr<T>::dynamicarr (void) : allocSize(DEFAULT_SIZE)
    {
    array = new T[allocSize];
    std::fill(array, array+allocSize, defaultval);
    }

// allocates an array with default size of 128
// fills this with default value
// @remark constructor

template <class T>
dynamicarr<T>::dynamicarr (T defaultval) : allocSize(DEFAULT_SIZE), defaultval(defaultval)
    {
    array = new T[allocSize];
    std::fill(array, array+allocSize, defaultval);
    }

// destroys self content, then copy src content to self
// @remark copy constructor

template <class T>
dynamicarr<T>::dynamicarr (const dynamicarr &src) : 
    allocSize(src.allocSize), defaultval(src.defaultval), comparator<T>(src)
    {
    array = new T[allocSize];
    for (size_t i = 0; i < allocSize; i++)
        {
        array[i] = src.array[i];
        }
    }

// destructor
// @remark destructor

template <class T>
dynamicarr<T>::~dynamicarr (void)
    {
    delete[] array;
    }

// copy assignment operator
// @param[in]   src     reference to dynamic object to copy from
// @return      reference to this after copy assignment

template <class T>
dynamicarr<T>& dynamicarr<T>::operator = (const dynamicarr<T>& src)
    {
    comparator<T>::operator = (src);
    if (&src != this)
        {
        delete[] array;
        allocSize = src.allocSize;
        defaultval = src.defaultval;
        array = new T[allocSize];
        for (size_t i = 0; i < allocSize; i++)
            {
            array[i] = src.array[i];
            }
        }
    return *this;
    }

// overloaded bracket reference operator
// @param[in]   index     integer index of the accessing element in arr
// @return      reference to data at index
    
template <class T>
T& dynamicarr<T>::operator [] (size_t index)
    {
    if (index > allocSize)
        {
        dynamicSize(index);
        }
        
    return array[index];
    }

// overloaded constant bracket reference operator
// @param[in]   index     integer index of the accessing element in arr
// @return      reference to data at index

template <class T>
T dynamicarr<T>::operator [] (size_t index) const
    {
    if (index > allocSize)
        {
        throw std::runtime_error("index out of bounds");
        }

    return array[index];
    }

// finds the index of the first instance of element
// determines equality using input function following signature: bool (*)(const T&, const T&);
// @param[in]   elem     element to search for
// @param[in]   eqCb     optional equality function (defaults to ==)
// @return      index of the elem if found, -1 otherwise

template <class T>
signed dynamicarr<T>::indexOf (T elem) const
    {
    signed index = 0;
    while (index < allocSize && false == this->equals(array[index], elem))
        {
        index++;
        }
    if (index == allocSize)
        {
        index = -1;
        }
    return index;
    }

#endif /* __DYNAMIC_ARR__H */