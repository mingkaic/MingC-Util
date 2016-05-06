//
//  stack.cpp
//  List
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#ifdef __STACK__H

#include <stdexcept>

template <class T>
stack<T>::stack(): head(NULL)
    {
    }

template <class T>
stack<T>::stack(const stack& src) : head(NULL)
    {
    if (NULL != src.head)
        {
        head = src.head->cascadeCopy();
        }
    }

template <class T>
stack<T>::~stack()
    {
    if (NULL != head)
        {
        head->cascadeDelete();
        }
    }

template <class T>
stack<T>& stack<T>::operator = (const stack<T>& src)
    {
    // prevent self assignment
    if (&src != this)
        {
        if (NULL != head)
            {
            head->cascadeDelete();
            }
        
        if (NULL != src.head)
            {
            head = src.head->cascadeCopy();
            }
        }
    
    return *this;
    }

template <class T>
void stack<T>::push(T data)
    {
    head = new listnode<T>(data, head);
    }

template <class T>
T stack<T>::pop()
    {
    // checks for special case: empty list
    if (NULL == head)
        {
        throw std::runtime_error("removing from empty list");
        }
    
    T data = head->getData();
    
    listnode<T>* buffer = head;
    head = head->next;
    delete buffer;
    
    return data;
    }

template <class T>
T stack<T>::peek() const
    {
    if (NULL == head)
        {
        throw std::runtime_error("peeking in empty list");
        }
    
    return head->getData();
    }

template <class T>
bool stack<T>::isEmpty() const
    {
    return NULL == head;
    }

#endif /* __STACK__H */