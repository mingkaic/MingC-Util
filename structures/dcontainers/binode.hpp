//
//  binode.hpp
//  dataContainer
//  description: a doubly linked node
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __BI_NODE__H
#define __BI_NODE__H

#include <cstdlib>
#include "gnode.hpp"

template <class T>
class binode : public gnode<T>
    {
    protected:
        binode(){prev = next = NULL;}
    public:
        binode<T>* prev;
        binode<T>* next;
        
        binode(T data);
        binode(binode<T>* prev, T data, binode<T>* next);
        virtual ~binode() {}

        void cascadeDelete();
        virtual binode<T>* cascadeCopy();
    };

#include "binode.cpp"

#endif /* __BI_NODE__H */