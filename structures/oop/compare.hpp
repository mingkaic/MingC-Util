//
//  compare.hpp
//  OOP
//
//  description: declares the following
//      - comparator object for holding comparison functions 
//      - comparison manager class (compManage) allow the assignment and reassignment of 
//        compare functions via static proxy "factory".
//
//  instance comparator is created upon construction at which point unassigned comparison functions
//  are assigned "natural order" comparison provided they are they are std::string, or numerical 
//  primitive times (e.g.: bool, char, int, double, float)
//
//  a static factory is created to prevent changes to comparison functions (in the class) from 
//  effecting existing instances
//
//  TO USE: 
//  1. structures requiring comparisons should inherit compManage
//  2. subclasses of compManage access comparator via protected member "C"
//
//  Created by Ming Kai Chen on 2014-07-15.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#include <functional>

#pragma once
#ifndef __COMPARE__H
#define __COMPARE__H
// HOW IT WORKS:
// return true if left and right are equal
template <typename T>
using equatable = std::function<bool (T left, T right)>;

// HOW IT WORKS:
// return 0 if left and right are equal
// return > 0 if right > left
// return < 0 if left < right
template <typename T>
using comparable = std::function<signed (T left, T right)>;

// HOW IT WORKS:
// return integer representation of input
template <typename T>
using hashable = std::function<long (T)>;

template <typename T>
class comparator
	{
    protected:
        // compile time connections
        template <bool Condition, typename U>
        friend class if_natural;

        // set default operations
        // param[out]    obj    reference to comparator object
        // returns void
        void naturalize (comparator<T>& obj);

        equatable<T> equals;

        comparable<T> compare;

        hashable<T> hashcode;

    public:
        // set static factory's equal function
        // param[in]    equals  function pointer with signature
        //                      bool (*) (T, T)
        // returns void
        void setEquals (equatable<T> equals)
            {
            this->equals = equals;
            }

        // set static factory's compare function
        // param[in]    compare     function pointer with signature
        //                          signed (*) (T, T)
        // returns void
        void setCompare (comparable<T> compare)
            {
            this->compare = compare;
            }

        // set static factory's hashcode function
        // param[in]    hashcode    function pointer with signature
        //                          size_t (*) (T)
        // returns void
        void setHashcode (hashable<T> hashcode)
            {
            this->hashcode = hashcode;
            }

        // constructs instance comparator and naturalizes when available
        // @remark default constructor
        comparator (void)
			{
            naturalize(*this);
			}

        // virtual destructor
        // @remark destructor
        virtual ~comparator() {}

        // copy assignment operator
        // @param[in]   src     reference to comparator object to copy from
        // @return      reference to this after copy assignment
        comparator<T>& operator = (const comparator<T>& src);
	};

#include "compare.cpp"

#endif /* __COMPARE__H */