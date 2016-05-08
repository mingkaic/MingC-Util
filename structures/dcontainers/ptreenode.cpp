//
//  ptreenode.cpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#ifdef __P_TREE_NODE__H

#include <cstdlib>

template <class T>
ptreenode<T>* ptreenode<T>::copyHelper (direction caller, ptreenode<T>* from)
    {
    ptreenode<T>* cpy = new ptreenode<T>(this->data);
    if (NULL != left)
        {
        if (LEFT == caller)
            {
            cpy->left = from;
            }
        else
            {
            cpy->left = left->copyHelper(TOP, cpy);
            }
        }
    if (NULL != right)
        {
        if (RIGHT == caller)
            {
            cpy->right = from;
            }
        else
            {
            cpy->right = right->copyHelper(TOP, cpy);
            }
        }
    if (NULL != parent)
        {
        if (TOP == caller)
            {
            cpy->parent = from;
            }
        else
            {
            direction d = parent->left == this ? LEFT : RIGHT;
            cpy->parent = parent->copyHelper(d, cpy);
            }
        }
    
    return cpy;
    }

template <class T>
void ptreenode<T>::trickleDelete (void)
    {
    if (NULL != left)
        {
        left->trickleDelete();
        }
    if (NULL != right)
        {
        right->trickleDelete();
        }
    delete this;
    }

template <class T>
ptreenode<T>::ptreenode (T data) :
left(NULL), right(NULL), parent(NULL)
    {
    this->dataInit(data);
    }

template <class T>
void ptreenode<T>::cascadeDelete (void)
    {
    ptreenode<T>* buffer = this;
    while (NULL != buffer->parent)
        {
        buffer = buffer->parent;
        }
    buffer->trickleDelete();
    }

template <class T>
ptreenode<T>* ptreenode<T>::cascadeCopy (void)
    {
    ptreenode<T>* cpy = new ptreenode<T>(this->data);
    
    if (NULL != left)
        {
        cpy->left = left->copyHelper(TOP, cpy);
        }
    if (NULL != right)
        {
        cpy->right = right->copyHelper(TOP, cpy);
        }
    if (NULL != parent)
        {
        direction d = parent->left == this ? LEFT : RIGHT;
        cpy->parent = parent->copyHelper(d, cpy);
        }
    
    return cpy;
    }

#endif /* __P_TREE_NODE__H */