//
//  listnode.hpp
//  dataContainer
//  description: singly linked node
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __LIST_NODE__H
#define __LIST_NODE__H

#include "gnode.hpp"

template <class T>
class listnode : public gnode<T>
    {
    protected:
        listnode<T>(){next = NULL;}
    public:
        listnode<T>* next;
        
        listnode(T data);
        listnode(T data, listnode<T>* next);
        virtual ~listnode() {}
        
        void cascadeDelete();
        virtual listnode<T>* cascadeCopy();
    };

#include "listnode.cpp"

#endif /* __LIST_NODE__H */