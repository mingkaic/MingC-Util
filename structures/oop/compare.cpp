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
#include <stdexcept>
#include "../dcontainers/pcontainer.hpp"


// compile time connections
template <bool Condition, typename U>
class if_natural;

// is_integral and is_floating_point
template <typename T>
struct if_natural<true, T>
	{
	static void connect(comparator<T>& obj)
		{
		obj.equals = [] (T e1, T e2) 
			{ 
			return e1 == e2; 
			};
		obj.compare = [] (T e1, T e2) 
			{ 
			signed diff = 0;
			if (e2 > e1) diff = 1;
			if (e2 < e1) diff = -1;
			return diff; 
			};
		obj.hashcode = [] (T e) 
			{ 
			return (size_t) e;
			};
		}
	};

// is std::string
template <>
struct if_natural<true, std::string>
	{
	static void connect(comparator<std::string>& obj)
		{
		obj.equals = [] (std::string s1, std::string s2) 
			{
			return 0 == s1.compare(s2);
			};
		obj.compare = [] (std::string s1, std::string s2) 
			{
			return s2.compare(s1); 
			};
		obj.hashcode = [] (std::string s) 
			{ 
			size_t n = s.size();
			size_t hash = 0;
			for (size_t i = 0; i < n; i++)
				{
				hash += s[i]*pow(sizeof(size_t)*8, (n-i-1));
				}
			return hash;
			};
		}
	};

// is pcontainer
template <typename T>
struct if_natural<true, dcontain::pcontainer<T> >
	{
	static void connect(comparator<std::string>& obj)
		{
		obj.equals = [] (dcontain::pcontainer<T> p1, dcontain::pcontainer<T> p2) 
			{
			return p1.getPriority() == p2.getPriority();
			};
		obj.compare = [] (dcontain::pcontainer<T> p1, dcontain::pcontainer<T> p2) 
			{ 
			return (signed) p2.getPriority() - p1.getPriority();
			};
		obj.hashcode = [] (dcontain::pcontainer<T> p) 
			{
			return p.getPriority();
			};
		}
	};

// other types
template <typename T>
struct if_natural<false, T>
	{
	static void connect(comparator<T>& obj)
		{
		obj.equals = [obj] (T e1, T e2) 
			{ 
			if (obj.compare)
				return 0 == obj.compare(e1, e2);
			throw std::runtime_error("calling unimplemented equals function");
			return false;
			};
		obj.compare = [obj] (T e1, T e2) 
			{
			if (obj.hashcode)
				{
				long id1 = obj.hashcode(e1);
				long id2 = obj.hashcode(e2); 
				signed diff = 0;
				if (id2 > id1) diff = 1;
				if (id2 < id1) diff = -1;
				return diff;
				}
			throw std::runtime_error("calling unimplemented compare function");
			return 0;
			};
		obj.hashcode = [obj] (T e)
			{
			throw std::runtime_error("calling unimplemented hashcode function");
			return 0;
			};
		}
	};

// set unassigned comparator obj comparison function 
// pointers to natural order comp funcs if possible
// param[out]    obj    reference to comparator object
// returns void

template <typename T>
void comparator<T>::naturalize(comparator<T>& obj)
	{
	// change condition here to expand natural type options
	if_natural<std::is_integral<T>::value || 
		std::is_floating_point<T>::value || 
		std::is_same<T, std::string>::value, T>::connect(obj);
	}

// copy assignment operator
// @param[in]   src     reference to comparator object to copy from
// @return      reference to this after copy assignment

template <typename T>
comparator<T>& comparator<T>::operator = (const comparator<T>& src)
	{
    if (&src != this)
        {
		equals = src.equals;
		compare = src.compare;
		hashcode = src.hashcode;
        }
    return *this;
	}

#endif /* __COMPARE__H */