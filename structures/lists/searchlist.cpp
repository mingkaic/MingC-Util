//
//  searchlist.cpp
//  List
//
//  Created by Ming Kai Chen on 2014-07-15.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __SEARCH_LIST__H

#include "../dcontainers/binode.hpp"
#include "deque.hpp"

template <class T>
searchlist<T>::searchlist(const searchlist& src) : deque<T>(src)
    {
    }

template <class T>
searchlist<T>& searchlist<T>::operator = (const searchlist<T>& src)
    {
    deque<T>::operator = (src);
    return *this;
    }

template <class T>
signed searchlist<T>::search(T elem)
    {
    size_t index = 0;
    binode<T>* buffer = this->head;
    while (NULL != buffer && elem != buffer->getData())
        { 
        buffer = buffer->next;
        index++;
        }
    return NULL == buffer ? -1 : index;
    }

template <class T>
void searchlist<T>::nInsert(T elem, size_t N)
    {
    binode<T>* buffer = this->head;
    for (size_t i = 0; i < N && NULL != buffer; i++)
        {
        buffer = buffer->next;
        }
    if (NULL == buffer) 
        {
        this->tail = new binode<T>(this->tail, elem, NULL);
        if (NULL != this->tail->prev)
            {
            this->tail->prev->next = this->tail;
            }
        }
    else
        {
        binode<T>* holder = new binode<T>(buffer->prev, elem, buffer);
        buffer->prev->next = holder;
        buffer->prev = holder;
        }
    if (NULL == this->head)
        {
        this->head = this->tail;
        }
    else if (NULL != this->head->prev)
        {
        this->head = this->head->prev;
        }
    }

template <class T>
T searchlist<T>::nRemove(size_t N)
    {
    if (NULL == this->head)
        {
        throw std::runtime_error("removing from empty list");
        }

    binode<T>* buffer = this->head;
    for (size_t i = 0; i < N && NULL != buffer->next; i++)
        {
        buffer = buffer->next;
        }
    if (NULL == buffer)
        {
        throw std::out_of_range("index greater than size of list");
        }
    if (this->head == buffer) 
        {
        this->head = buffer->next;
        }
    if (this->tail == buffer)
        {
        this->tail = buffer->prev;
        }
    if (NULL != buffer->prev)
        {
        buffer->prev->next = buffer->next;
        }
    if (NULL != buffer->next)
        {
        buffer->next->prev = buffer->prev;
        }

    T removeData = buffer->getData();
    delete buffer;

    return removeData;
    }

template <class T>
T searchlist<T>::nPeek(size_t N) const
    {
    if (NULL == this->head)
        {
        throw std::runtime_error("peeking in empty list");
        }
    binode<T>* buffer = this->head;
    for (size_t incr = 0; incr < N && NULL != buffer; incr++)
        {
        buffer = buffer->next;
        }
    
    if (NULL == buffer)
        {
        throw std::out_of_range("index greater than size of list");
        }
        
    return buffer->getData();
    }
    
template <class T>
T searchlist<T>::nReplace(T elem, size_t N)
    {
    if (NULL == this->head)
        {
        throw std::runtime_error("removing from empty list");
        }

    binode<T>* buffer = this->head;
    for (size_t i = 0; i < N && NULL != buffer->next; i++)
        {
        buffer = buffer->next;
        }
    if (NULL == buffer)
        {
        throw std::out_of_range("index greater than size of list");
        }

    binode<T>* holder = new binode<T>(buffer->prev, elem, buffer->next);
    if (this->head == buffer) 
        {
        this->head = holder;
        }
    if (this->tail == buffer)
        {
        this->tail = holder;
        }
    if (NULL != buffer->prev)
        {
        buffer->prev->next = holder;
        }
    if (NULL != buffer->next)
        {
        buffer->next->prev = holder;
        }
    T removeData = buffer->getData();
    delete buffer;
        
    return removeData;
    }

template <class T>
size_t searchlist<T>::size() const
    {
    size_t incr = 0;
    for (binode<T>* buffer = this->head; NULL != buffer; buffer = buffer->next)
        {
        incr++;
        }
    return incr;
    }

#endif /* __SEARCH_LIST__H */