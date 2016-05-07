//
//  queue.hpp
//  List
//
//  description: data structure allowing read/write to front/back of list only with first in first out ordering
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#ifdef __QUEUE__H

#include <stdexcept>

// constructs NULL head and tail
// @remark default constructor
template <class T>
queue<T>::queue (void): head(NULL), tail(NULL)
    {
    }

// destroys self content, then copy src content to self
// @remark copy constructor
template <class T>
queue<T>::queue (const queue& src) : head(NULL), tail(NULL)
    {
    if (NULL != src.head)
        {
        head = src.head->cascadeCopy(tail);
        }
    }

// destructor
// @remark destructor
template <class T>
queue<T>::~queue (void)
    {
    if (NULL != head)
        {
        head->cascadeDelete();
        }
    }

// copy assignment operator
// @param[in]   src     reference to deque object to copy from
// @return      reference to this after copy assignment
template <class T>
queue<T>& queue<T>::operator = (const queue<T>& src)
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
            head = src.head->cascadeCopy(tail);
            }
        }
    
    return *this;
    }
        
// add data to front (head) of list
// @param[in]   data    T type data to add
// @return      void

template <class T>
void queue<T>::push_front (T data)
    {
    head = new binode<T>(NULL, data, head);
    if (NULL == head->next)
        {
        tail = head;
        }
    else
        {
        head->next->prev = head;
        }
    }

// remove data from back (tail) of list
// @param[in]   void
// @return      T type data removed

template <class T>
T queue<T>::pop_back (void)
    {
    // checks for special case: empty list
    if (NULL == head)
        {
        throw std::runtime_error("removing from empty list");
        }
    
    T data = tail->getData();
    binode<T>* buffer = tail;
    if (tail == head)
        {
        tail = head = NULL;
        }
    else
        {
        tail = tail->prev;
        tail->next = NULL;
        }
    delete buffer;

    return data;
    }

// accesses data from front (head) of list
// @param[]     void
// @return      T type data accessed

template <class T>
T queue<T>::peek_front (void) const
    {
    if (NULL == head)
        {
        throw std::runtime_error("peeking in empty list");
        }
    
    return head->getData();
    }

// accesses data from back (tail) of list
// @param[]     void
// @return      T type data accessed

template <class T>
T queue<T>::peek_back (void) const
    {
    if (NULL == head)
        {
        throw std::runtime_error("peeking in empty list");
        }
    
    return tail->getData();
    }

// determines if the list is empty
// @param[]     void
// @return      true if empty, false otherwise

template <class T>
bool queue<T>::isEmpty (void) const
    {
    return NULL == head;
    }

#endif /* __QUEUE__H */