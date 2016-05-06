//
//  listnode.cpp
//  dataContainer
//  description: singly linked node
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#ifdef __LIST_NODE__H

template <class T>
listnode<T>::listnode(T data) : next(NULL)
    {
    this->dataInit(data);
    }

template <class T>
listnode<T>::listnode(T data, listnode<T>* next) : next(next)
    {
    this->dataInit(data);
    }

template <class T>
void listnode<T>::cascadeDelete()
    {
    if (NULL != next)
        {
        next->cascadeDelete();
        }
    delete this;
    }

template <class T>
listnode<T>* listnode<T>::cascadeCopy()
    {
    listnode<T>* copy = new listnode<T>(this->data);
    listnode<T>* buffer = copy;
    for (listnode<T>* src = next; NULL != src; src = src->next)
        {
        buffer->next = new listnode<T>(src->getData());
        buffer = buffer->next;
        }
    return copy;
    }

#endif /* __LIST_NODE__H */