//
//  deque.cpp
//  List
//
//  description: data structure allowing read/write to front/back of list only
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#ifdef __DEQUE__H

#include <stdexcept>

// destroys self content, then copy src content to self
// @remark copy constructor

template <class T>
deque<T>::deque (const deque& src) : queue<T>(src)
    {
    }

// copy assignment operator
// @param[in]   src     reference to deque object to copy from
// @return      reference to this after copy assignment

template <class T>
deque<T>& deque<T>::operator = (const deque<T>& src)
    {
    queue<T>::operator = (src);
    return *this;
    }

// add data to back (tail) of list
// @param[in]   data    T type data to add
// @return      void

template <class T>
void deque<T>::push_back (T data) {
    if (NULL == this->tail)
        {
        this->head = this->tail = new dcontain::binode<T>(this->tail, data, NULL);
        }
    else
        {
        this->tail->next = new dcontain::binode<T>(this->tail, data, NULL);
        this->tail = this->tail->next;
        }
}

// remove data from front (head) of list
// @param[]     void
// @return      T type data removed

template <class T>
T deque<T>::pop_front (void) {
    if (NULL == this->head)
        {
        throw std::runtime_error("removing from empty list");
        }
    
    T data = this->head->getData();
    dcontain::binode<T>* buffer = this->head;
    if (this->tail == this->head)
        {
        this->tail = this->head = NULL;
        }
    else
        {
        this->head = this->head->next;
        }
    delete buffer;

    return data;
}

#endif /* __DEQUE__H */