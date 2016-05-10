//
//  stack.cpp
//  List
//
//  description: data structure allowing read/write to front of list only with first in last out ordering
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#ifdef __STACK__H

#include <stdexcept>

// constructs NULL head and tail
// @remark default constructor

template <class T>
stack<T>::stack (void): head(NULL)
    {
    }

// destroys self content, then copy src content to self
// @remark copy constructor

template <class T>
stack<T>::stack (const stack& src) : head(NULL)
    {
    if (NULL != src.head)
        {
        head = src.head->cascadeCopy();
        }
    }

// destructor
// @remark destructor

template <class T>
stack<T>::~stack (void)
    {
    clear();
    }

// copy assignment operator
// @param[in]   src     reference to stack object to copy from
// @return      reference to this after copy assignment

template <class T>
stack<T>& stack<T>::operator = (const stack<T>& src)
    {
    // prevent self assignment
    if (&src != this)
        {
        clear();
        
        if (NULL != src.head)
            {
            head = src.head->cascadeCopy();
            }
        }
    
    return *this;
    }
        
// add data to top of stack
// @param[in]   data    T type data to add
// @return      void

template <class T>
void stack<T>::push (T data)
    {
    head = new dcontain::listnode<T>(data, head);
    }

// remove data from top of stack
// @param[]     void
// @return      T type data removed

template <class T>
T stack<T>::pop (void)
    {
    // checks for special case: empty list
    if (NULL == head)
        {
        throw std::runtime_error("removing from empty list");
        }
    
    T data = head->getData();
    
    dcontain::listnode<T>* buffer = head;
    head = head->next;
    delete buffer;
    
    return data;
    }

// accesses data from top of stack
// @param[]     void
// @return      T type data accessed

template <class T>
T stack<T>::peek (void) const
    {
    if (NULL == head)
        {
        throw std::runtime_error("peeking in empty list");
        }
    
    return head->getData();
    }

// determines if the stack is empty
// @param[]     void
// @return      true if empty, false otherwise

template <class T>
bool stack<T>::isEmpty (void) const
    {
    return NULL == head;
    }

// wipes all data in stack
// @param[]     void
// @return      void

template <class T>
void stack<T>::clear (void)
    {
    if (NULL != head)
        {
        head->cascadeDelete();
        }
    head = NULL;
    }

#endif /* __STACK__H */