//
//  rbtree.h
//  Tree
//
//  description: red black marked binary tree search to ensure log n search/insertion/removal
//
//  Created by Ming Kai Chen on 2014-06-26.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#pragma once
#ifndef __RB_TREE__H
#define __RB_TREE__H

#include <vector>
#include "../dcontainers/gnode.hpp"
#include "../oop/compare.hpp"

namespace tree
    {
    template <typename T>
    class rbnode : public dcontain::gnode<T>
        {
        public:
            rbnode<T>* left;
            rbnode<T>* right;
            rbnode<T>* parent;
            bool isBlack;
            
            // constructs node with data
            // @remark constructor
            rbnode (T data);
            
            // constructs node with data and color
            // @remark constructor
            rbnode (T data, bool black);

            // destructor
            // @remark destructor
            ~rbnode (void) {}
            
            // deletes self and children
            void cascadeDelete (void);

            // copies self and children
            rbnode<T>* cascadeCopy (void);

            // change data content
            void injectData (T data) {this->dataInit(data);}
        };

    template <typename T>
    class rbtree : comparator<T>
        {
        private:
            rbnode<T>* root;

            // fixes redblack order after removal
            // @param[out]  parent          pointer to the parent node to fix around
            // @param[in]   childIsLeft     true if troubled child is left of parent
            // @return void
            void deleteFixUp (rbnode<T>* parent, bool childIsLeft);

            // rotate node section
            // @param[out]  parent      pointer to the pivot node
            // @param[in]   rotateLeft  true if right child should become new parent
            // @return void
            void rotate (rbnode<T>* parent, bool rotateLeft);

            // search for key in subtree i_root
            // @param[in]   key   T typed data to search for
            // return   NULL if root is NULL
            //          pointer to node containing key
            rbnode<T>* BinSearch (T key, rbnode<T>* i_root) const;

            // get the successor of subtree rooted by i_root
            // @param[in]   i_root  rbnode pointer root of subtree
            // return   NULL if root right is NULL
            //          pointer to successor
            rbnode<T>* successor (rbnode<T>* i_root);

            // recurse through this tree in order
            // @param[in]   root    pointer to root of subtree to recurse through
            // @param[in]   func    function to perform on each node
            // return  void
            void completeRecurse (rbnode<T>* root, 
                                std::function<void(dcontain::treenode<T>*)> func) const;
        public:
            // constructs NULL root
            // @remark default constructor
            rbtree (void);

            // destroys self content, then copy src content to self
            // @remark copy constructor
            rbtree(const rbtree<T>& src);

            // destructor
            // @remark destructor
            virtual ~rbtree (void);

            // copy assignment operator
            // @param[in]   src     reference to rbtree object to copy from
            // @return      reference to this after copy assignment
            rbtree<T>& operator = (const rbtree<T>& src);

            // determine if key is in tree
            // @param[in]   key     key
            // @return wrapper object value associated with key,
            // castable to false if there was no associated value
            // castable to true otherwise
            dcontain::wrapper<T> get (T key) const;

            // insert key into tree
            // @param[in]   key     key
            // @return wrapper object value associated with previous key, 
            // castable to false if there was no associated value
            // castable to true otherwise
            dcontain::wrapper<T> put (T key);

            // remove value in tree
            // @param[in]   key     key
            // @return wrapper object value associated with previous key, 
            // castable to false if there was no associated value
            // castable to true otherwise
            dcontain::wrapper<T> remove (T key);

            // creates a searchlist copy of this tree in order
            // @param[]  void
            // @return a searchlist of this tree
            std::vector<T> getList (void) const;

            // determine if this tree is empty
            // @param[]  void
            // @return true if this tree is empty
            bool isEmpty (void) const { return NULL == root; }

            // determine the number of nodes in this tree
            // @param[]  void
            // @return size_t number of nodes in this tree
            size_t size (void) const;

            // remove all nodes in this tree
            // @param[]  void
            // @return void
            void clear (void);
        };

    #include "rbtree.cpp"
    }

#endif /* __RB_TREE__H */