//
//  deque.cpp
//  List
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#ifdef __DEQUE__H

#include <stdexcept>

template <class T>
deque<T>::deque(const deque& src) : queue<T>(src)
    {
    }

template <class T>
deque<T>& deque<T>::operator =(const deque<T>& src)
    {
    queue<T>::operator = (src);
    return *this;
    }

template <class T>
void deque<T>::push_back(T data) {
    if (NULL == this->tail)
        {
        this->head = this->tail = new binode<T>(this->tail, data, NULL);
        }
    else
        {
        this->tail->next = new binode<T>(this->tail, data, NULL);
        this->tail = this->tail->next;
        }
}

template <class T>
T deque<T>::pop_front() {
    if (NULL == this->head)
        {
        throw std::runtime_error("removing from empty list");
        }
    
    T data = this->head->getData();
    binode<T>* buffer = this->head;
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