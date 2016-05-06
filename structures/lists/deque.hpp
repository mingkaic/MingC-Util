//
//  deque.hpp
//  List
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __DEQUE__H
#define __DEQUE__H

#include "queue.hpp"

// Double ended queue (throw error handle behavior with remove on empty)
template <class T>
class deque : public queue<T>
    {
    public:
        deque() {}
        deque(const deque& src);
        virtual ~deque() {}
        deque<T>& operator =(const deque<T>& src);

        void push_back(T data);
        T pop_front();
    };

#include "deque.cpp"

#endif /* __DEQUE__H */