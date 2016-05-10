//
//  searchlist.cpp
//  List
//
//  description: doubly linked list featuring linear search, replacement, n-insertion, n-access, along with deque functions
//
//  Created by Ming Kai Chen on 2014-07-15.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __SEARCH_LIST__H

#include "../dcontainers/binode.hpp"
#include "deque.hpp"

// destroys self content, then copy src content to self
// @remark copy constructor

template <class T>
searchlist<T>::searchlist (const searchlist& src) : deque<T>(src)
    {
    }

// copy assignment operator
// @param[in]   src     reference to searchlist object to copy from
// @return      reference to this after copy assignment

template <class T>
searchlist<T>& searchlist<T>::operator = (const searchlist<T>& src)
    {
    comparator<T>::operator = (src);
    deque<T>::operator = (src);
    return *this;
    }

// search for the index of elem
// @param[in]   elem     T typed data to search for
// @return      index of element in list if found, -1 otherwise

template <class T>
signed searchlist<T>::search (T elem)
    {
    size_t index = 0;
    dcontain::binode<T>* buffer = this->head;
    while (NULL != buffer && false == this->equals(elem, buffer->getData()))
        {
        buffer = buffer->next;
        index++;
        }
    return NULL == buffer ? -1 : index;
    }

// insert elem at index N
// @param[in]   elem     T typed data to insert
// @param[in]   N        integer index to insert elem

template <class T>
void searchlist<T>::nInsert (T elem, size_t N)
    {
    dcontain::binode<T>* buffer = this->head;
    for (size_t i = 0; i < N && NULL != buffer; i++)
        {
        buffer = buffer->next;
        }
    if (NULL == buffer) 
        {
        this->tail = new dcontain::binode<T>(this->tail, elem, NULL);
        if (NULL != this->tail->prev)
            {
            this->tail->prev->next = this->tail;
            }
        }
    else
        {
        dcontain::binode<T>* holder = new dcontain::binode<T>(buffer->prev, elem, buffer);
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

// remove elem at index N
// @param[in]   N        integer index to remove elem
// @return      void

template <class T>
T searchlist<T>::nRemove (size_t N)
    {
    if (NULL == this->head)
        {
        throw std::runtime_error("removing from empty list");
        }

    dcontain::binode<T>* buffer = this->head;
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

// get elem at index N
// @param[in]   N        integer index to get elem
// @return      T typed data at index N

template <class T>
T searchlist<T>::nPeek (size_t N) const
    {
    if (NULL == this->head)
        {
        throw std::runtime_error("peeking in empty list");
        }
    dcontain::binode<T>* buffer = this->head;
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

// replace data at index N with elem
// @param[in]   elem     T typed data to replace data at index N
// @param[in]   N        integer index
// @return      T typed old (replaced) data 
    
template <class T>
T searchlist<T>::nReplace (T elem, size_t N)
    {
    if (NULL == this->head)
        {
        throw std::runtime_error("removing from empty list");
        }

    dcontain::binode<T>* buffer = this->head;
    for (size_t i = 0; i < N && NULL != buffer->next; i++)
        {
        buffer = buffer->next;
        }
    if (NULL == buffer)
        {
        throw std::out_of_range("index greater than size of list");
        }

    dcontain::binode<T>* holder = new dcontain::binode<T>(buffer->prev, elem, buffer->next);
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
        
// find the size of the list
// @param[]     void
// @return      integer size of list

template <class T>
size_t searchlist<T>::size (void) const
    {
    size_t incr = 0;
    for (dcontain::binode<T>* buffer = this->head; NULL != buffer; buffer = buffer->next)
        {
        incr++;
        }
    return incr;
    }

#endif /* __SEARCH_LIST__H */