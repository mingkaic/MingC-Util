//
//  treenode.cpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#ifdef __TREE_NODE__H

#include <cstdlib>

template <class T>
treenode<T>::treenode (T data)
    {
    this->dataInit(data);
    this->left = this->right = NULL;
    }

template <class T>
void treenode<T>::cascadeDelete (void)
    {
    if (NULL != this->left)
        {
        this->left->cascadeDelete();
        }
    if (NULL != this->right)
        {
        this->right->cascadeDelete();
        }
    }

template <class T>
treenode<T>* treenode<T>::cascadeCopy (void)
    {
    treenode<T>* cpy = new treenode<T>(this->data);
    if (NULL != left)
        {
        cpy->left = left->cascadeCopy();
        }
    if (NULL != right)
        {
        cpy->right = right->cascadeCopy();
        }
    return cpy;
    }

#endif /* __TREE_NODE__H */