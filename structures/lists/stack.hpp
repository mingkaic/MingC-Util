//
//  stack.hpp
//  List
//
//  description: data structure allowing read/write to front of list only with first in last out ordering
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
        // constructs NULL head and tail
        // @remark default constructor
        stack (void);

        // destroys self content, then copy src content to self
        // @remark copy constructor
        stack (const stack& src);

        // destructor
        // @remark destructor
        virtual ~stack (void);

        // copy assignment operator
        // @param[in]   src     reference to stack object to copy from
        // @return      reference to this after copy assignment
        stack<T>& operator = (const stack<T>& src);
        
        // add data to top of stack
        // @param[in]   data    T type data to add
        // @return      void
        void push (T data);

        // remove data from top of stack
        // @param[]     void
        // @return      T type data removed
        T pop (void);

        // accesses data from top of stack
        // @param[]     void
        // @return      T type data accessed
        T peek (void) const;

        // determines if the stack is empty
        // @param[]     void
        // @return      true if empty, false otherwise
        bool isEmpty (void) const;
    };

#include "stack.cpp"

#endif /* __STACK__H */
