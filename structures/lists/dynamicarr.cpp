//
//  dynamicarr.cpp
//  Array
//
//  Created by Ming Kai Chen on 2014-05-09.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __DYNAMIC_ARR__H

template <class T>
dynamicarr<T>::dynamicarr() : allocSize(128)
    {
    array = new T[allocSize];
    memset(array, 0, sizeof(T)*allocSize);
    }

template <class T>
dynamicarr<T>::dynamicarr(const dynamicarr &src) : allocSize(src.allocSize)
    {
    array = new T[allocSize];
    memcpy(array, src.array, sizeof(T)*allocSize);
    }

template <class T>
dynamicarr<T>::~dynamicarr()
    {
    delete[] array;
    }

template <class T>
dynamicarr<T>& dynamicarr<T>::operator = (const dynamicarr<T>& src)
    {
    if (&src != this)
        {
        delete[] array;
        allocSize = src.allocSize;
        array = new T[allocSize];
        memcpy(array, src.array, sizeof(T)*allocSize);
        }
    return *this;
    }

template <class T>
void dynamicarr<T>::dynamicSize(size_t expand)
    {
    size_t newSize = allocSize*expand;
    T* newarray = new T[newSize];
    memset(newarray+newSize-allocSize, 0, sizeof(T)*(newSize-allocSize));
    memcpy(newarray, array, sizeof(T)*newSize);
    delete[] array;
    array = newarray;
    allocSize = newSize;
    }
    
template <class T>
T& dynamicarr<T>::operator [] (size_t index)
    {
    if (index > allocSize)
        {
        dynamicSize(index);
        }
        
    return array[index];
    }

template <class T>
signed dynamicarr<T>::indexOf(T elem, equality<T> eqCb) const
    {
    signed index = 0;
    while (index < allocSize && false == eqCb(array[index], elem))
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