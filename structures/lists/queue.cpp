//
//  queue.hpp
//  List
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#ifdef __QUEUE__H

#include <stdexcept>

template <class T>
void queue<T>::findTail(binode<T>* n)
    {
    tail = n;
    while (NULL != tail->next)
        {
        tail = tail->next;
        }
    }

template <class T>
queue<T>::queue(): head(NULL), tail(NULL)
    {
    }

template <class T>
queue<T>::queue(const queue& src) : head(NULL), tail(NULL)
    {
    if (NULL != src.head)
        {
        head = src.head->cascadeCopy();
        findTail(head);
        }
    }

template <class T>
queue<T>::~queue()
    {
    if (NULL != head)
        {
        head->cascadeDelete();
        }
    }

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
            head = src.head->cascadeCopy();
            findTail(head);
            }
        }
    
    return *this;
    }

template <class T>
void queue<T>::push_front(T data)
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

template <class T>
T queue<T>::pop_back()
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

template <class T>
T queue<T>::peek_front() const
    {
    if (NULL == head)
        {
        throw std::runtime_error("peeking in empty list");
        }
    
    return head->getData();
    }

template <class T>
T queue<T>::peek_back() const
    {
    if (NULL == head)
        {
        throw std::runtime_error("peeking in empty list");
        }
    
    return tail->getData();
    }

template <class T>
bool queue<T>::isEmpty() const
    {
    return NULL == head;
    }

#endif /* __QUEUE__H */