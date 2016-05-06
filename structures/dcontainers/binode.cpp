//
//  binode.cpp
//  dataContainer
//  description: a doubly linked node
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#ifdef __BI_NODE__H

template <class T>
binode<T>::binode(T data) : prev(NULL), next(NULL)
    {
    this->dataInit(data);
    }

template <class T>
binode<T>::binode(binode<T>* prev, T data, binode<T>* next) :
prev(prev), next(next)
    {
    this->dataInit(data);
    }

template <class T>
void binode<T>::cascadeDelete()
    {
    binode<T>* buffer = NULL;
    while (NULL != prev)
        {
        buffer = prev;
        prev = prev->prev;
        delete buffer;
        }
    while (NULL != next)
        {
        buffer = next;
        next = next->next;
        delete buffer;
        }
    delete this;
    }

template <class T>
binode<T>* binode<T>::cascadeCopy()
    {
    binode<T>* copy = new binode<T>(this->data);
    binode<T>* buffer = copy;
    for (binode<T>* src = prev; NULL != src; src = src->prev)
        {
        buffer->prev = new binode<T>(buffer, src->getData(), NULL);
        buffer = buffer->prev;
        }
    buffer = copy;
    for (binode<T>* src = next; NULL != src; src = src->next)
        {
        buffer->next = new binode<T>(NULL, src->getData(), buffer);
        buffer = buffer->next;
        }
    return copy;
    }

#endif /* __BI_NODE__H */