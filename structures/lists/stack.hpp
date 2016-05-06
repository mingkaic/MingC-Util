//
//  stack.hpp
//  List
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __STACK__H
#define __STACK__H

#include "../dcontainers/listnode.hpp"

template <class T>
class stack
    {
    protected:
        listnode<T>* head;
    public:
        stack();
        stack(const stack& src);
        virtual ~stack();
        stack<T>& operator = (const stack<T>& src);
        
        void push(T data);
        T pop();
        T peek() const;
        bool isEmpty() const;
    };

#include "stack.cpp"

#endif /* __STACK__H */
