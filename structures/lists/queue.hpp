//
//  queue.hpp
//  List
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __QUEUE__H
#define __QUEUE__H

#include "../dcontainers/binode.hpp"

template <class T>
class queue
    {
    protected:
        binode<T>* head;
        binode<T>* tail;

        void findTail(binode<T>* n);
    public:
        queue();
        queue(const queue& src);
        virtual ~queue();
        queue<T>& operator = (const queue<T>& src);
        
        void push_front(T data);
        T pop_back();
        T peek_front() const;
        T peek_back() const;
        bool isEmpty() const;
    };

#include "queue.cpp"

#endif /* __QUEUE__H */
