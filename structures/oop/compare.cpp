//
//  compare.cpp
//  OOP
//
//  description: implements naturalization for comparator objects in compare.hpp
//  based on local compare functions
//
//  Created by Ming Kai Chen on 2014-07-15.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __COMPARE__H

#include <string>
#include <cmath>
#include <type_traits>

// is std::string
static bool equals (std::string s1, std::string s2)
	{
	return 0 == s1.compare(s2);
	}

static signed compare (std::string s1, std::string s2)
	{
	return s2.compare(s1);
	}

static size_t hashcode (std::string s)
	{
	size_t n = s.size();
	size_t hash = 0;
	for (size_t i = 0; i < n; i++)
		{
		hash += s[i]*pow(sizeof(size_t)*8, (n-i-1));
		}
	return hash;
	}

// is_integral and is_floating_point
template <typename T>
static bool equals (T e1, T e2)
	{
	return e1 == e2;
	}

template <typename T>
static signed compare (T e1, T e2)
	{
	signed diff = 0;
	if (e2 > e1) diff = 1;
	if (e2 < e1) diff = -1;
	return diff;
	}

template <typename T>
static size_t hashcode (T e)
	{
	return (size_t) e;
	}

// set unassigned comparator obj comparison function 
// pointers to natural order comp funcs if possible
// param[out]    obj    reference to comparator object
// returns void

template <typename T>
static void naturalize(comparator<T>& obj)
	{
	if (true == std::is_integral<T>::value ||
		true == std::is_floating_point<T>::value ||
		true == std::is_same<T, std::string>::value)
		{
		obj.equals = equals;
		obj.compare = compare;
		obj.hashcode = hashcode;
		}
	}

#endif /* __COMPARE__H */