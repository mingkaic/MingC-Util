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

#define DEFAULT_SIZE 128

// handles the dynamic checking and expansion of the array
// @param[in]   expand     expansion rate: next size = cur size * expand
// @return      void

template <class T>
void dynamicarr<T>::dynamicSize (size_t expand)
    {
    size_t newSize = allocSize*expand;
    T* newarray = new T[newSize];
    memset(newarray+newSize-allocSize, 0, sizeof(T)*(newSize-allocSize));
    memcpy(newarray, array, sizeof(T)*newSize);
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
    memset(array, 0, sizeof(T)*allocSize);
    }

// destroys self content, then copy src content to self
// @remark copy constructor

template <class T>
dynamicarr<T>::dynamicarr (const dynamicarr &src) : allocSize(src.allocSize)
    {
    array = new T[allocSize];
    memcpy(array, src.array, sizeof(T)*allocSize);
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
        array = new T[allocSize];
        memcpy(array, src.array, sizeof(T)*allocSize);
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