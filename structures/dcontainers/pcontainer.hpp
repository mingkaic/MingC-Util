//
//  pcontainer.hpp
//  dataContainer
//
//  Created by Ming Kai Chen on 2015-09-30.
//  Copyright (c) 2015 Ming Kai Chen. All rights reserved.
//

#pragma once
#ifndef __PRIORITY__H
#define __PRIORITY__H

template <class T>
class pcontainer
    {
    private:
        size_t priority;
        T content;
    public:
        pcontainer (T content);
        pcontainer (T content, size_t priority);
        pcontainer (const pcontainer<T>& src);
        ~pcontainer (void);
        pcontainer<T>& operator = (const pcontainer<T>& src);
        
        T& getContent (void);
        size_t getPriority (void);
    };
    
template <class T>
bool operator == (const pcontainer<T>& left, const pcontainer<T>& right);

template <class T>
bool operator == (const T& left, const pcontainer<T>& right);

template <class T>
bool operator == (const pcontainer<T>& left, const T& right);

template <class T>
bool operator != (const pcontainer<T>& left, const pcontainer<T>& right);

template <class T>
bool operator != (const T& left, const pcontainer<T>& right);

template <class T>
bool operator != (const pcontainer<T>& left, const T& right);

template <class T>
bool operator > (const pcontainer<T>& left, const pcontainer<T>& right);

template <class T>
bool operator < (const pcontainer<T>& left, const pcontainer<T>& right);

#include "pcontainer.cpp"

#endif /* __PRIORITY__H */