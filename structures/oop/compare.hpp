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

#pragma once
#ifndef __COMPARE__H
#define __COMPARE__H
// HOW IT WORKS:
// return true if left and right are equal
template <typename T>
using equatable = bool (*) (T left, T right);

// HOW IT WORKS:
// return 0 if left and right are equal
// return > 0 if right > left
// return < 0 if left < right
template <typename T>
using comparable = signed (*) (T left, T right);

// HOW IT WORKS:
// return integer representation of input
template <typename T>
using hashable = size_t (*) (T);

template <typename T>
struct comparator
	{
	equatable<T> equals = NULL;

	comparable<T> compare = NULL;

	hashable<T> hashcode = NULL;
	};

enum COMPFUNC {
    EQUALS,
    COMPARE,
    HASHCODE,
    ALL,
};

// set unassigned comparator obj comparison function 
// pointers to natural order comp funcs if possible
// param[out]    obj    reference to comparator object
// returns void
template <typename T>
static void naturalize (comparator<T>& obj);

template <typename T>
class compManage
	{
    private:
        static comparator<T>* factory;

    protected:
        // constant member copy
        // naturalize for functions not set
        comparator<T> C;
    public:
        // set static factory's equal function
        // param[in]    equals  function pointer with signature
        //                      bool (*) (T, T)
        // returns true if successfully set, false if already set
        static bool setEquals (equatable<T> equals)
            {
            if (NULL == factory) factory = new comparator<T>;
            if (NULL == factory->equals)
                {
                factory->equals = equals;
                return true;
                }
            else
                {
                return false;
                }
            }

        // set static factory's compare function
        // param[in]    compare     function pointer with signature
        //                          signed (*) (T, T)
        // returns true if successfully set, false if already set
        static bool setCompare (comparable<T> compare)
            {
            if (NULL == factory) factory = new comparator<T>;
            if (NULL == factory->compare)
                {
                factory->compare = compare;
                return true;
                }
            else
                {
                return false;
                }
            }

        // set static factory's hashcode function
        // param[in]    hashcode    function pointer with signature
        //                          size_t (*) (T)
        // returns true if successfully set, false if already set
        static bool setHashcode (hashable<T> hashcode)
            {
            if (NULL == factory) factory = new comparator<T>;
            if (NULL == factory->hashcode)
                {
                factory->hashcode = hashcode;
                return true;
                }
            else
                {
                return false;
                }
            }

        // reverts factory function pointers to NULL
        // param[in]  unset enum COMPFUNC indicating which function to reset
        // returns void
        static void resetComparator (COMPFUNC f = ALL)
            {
            comparator<T>* bufferFactory = NULL;
            if (NULL != factory)
            	{
                if (ALL != f)
                    {
                    bufferFactory = new comparator<T>;
                    }
                switch (f) 
                    {
                    case EQUALS:
                        bufferFactory->compare = factory->compare;
                        bufferFactory->hashcode = factory->hashcode;
                        break;
                    case COMPARE:
                        bufferFactory->equals = factory->equals;
                        bufferFactory->hashcode = factory->hashcode;
                        break;
                    case HASHCODE:
                        bufferFactory->equals = factory->equals;
                        bufferFactory->compare = factory->compare;
                        break;
                    case ALL:
                        break;
                    }
                delete factory;
                factory = bufferFactory;
            	}
            }

        // constructs instance comparator and naturalizes when available
        // @remark default constructor
        compManage (void)
			{
            if (NULL != factory)
            	{
				C.equals = factory->equals;
				C.compare = factory->compare;
				C.hashcode = factory->hashcode;
            	}
			naturalize(C);
			}

        // virtual destructor
        // @remark destructor
        virtual ~compManage() {}
	};

// factory init
template <typename T>
comparator<T>* compManage<T>::factory = NULL;

#include "compare.cpp"

#endif /* __COMPARE__H */