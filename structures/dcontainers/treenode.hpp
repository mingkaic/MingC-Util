//
//  treenode.hpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __TREE_NODE__H
#define __TREE_NODE__H

#include "gnode.hpp"

template <class T>
class treenode : public gnode<T>
    {
    protected:
        treenode (void) {left = right = NULL;}
    public:
        treenode<T>* left;
        treenode<T>* right;
        
        treenode (T data);
        virtual ~treenode (void) {}
        
        void cascadeDelete (void);
        virtual treenode<T>* cascadeCopy (void);

        void injectData (T data) {this->dataInit(data);}
    };

#include "treenode.cpp"

#endif /* __TREE_NODE__H */