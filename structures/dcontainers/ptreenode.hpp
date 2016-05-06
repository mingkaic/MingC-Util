//
//  ptreenode.hpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __P_TREE_NODE__H
#define __P_TREE_NODE__H

#include "gnode.hpp"

template <class T>
class ptreenode : public gnode<T>
    {
    private:
        enum direction {LEFT, RIGHT, TOP};
        ptreenode<T>* copyHelper(direction caller, ptreenode<T>* from);
        void trickleDelete();
    protected:
        ptreenode(){left = right = parent = NULL;}
    public:
        ptreenode<T>* left;
        ptreenode<T>* right;
        ptreenode<T>* parent;
        
        ptreenode(T data);
        virtual ~ptreenode(){}
        
        void cascadeDelete();
        virtual ptreenode<T>* cascadeCopy();

        void injectData(T data){this->dataInit(data);}
        T& getDataRef(){return this->data;}
    };

#include "ptreenode.cpp"

#endif /* __P_TREE_NODE__H */