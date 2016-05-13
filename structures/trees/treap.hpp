//
//  treap.h
//  Tree
//
//  description: randomized binary search tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __TREAP__H
#define __TREAP__H

#include "../dcontainers/gnode.hpp"
#include "../oop/compare.hpp"

namespace tree
    {
    template <typename T>
    class prinode : public dcontain::gnode<T>
        {
        private:
            size_t priority;
        public:
            prinode<T>* left;
            prinode<T>* right;
            prinode<T>* parent;
            
            // constructs node with data
            // @remark constructor
            prinode (T data);
            
            // constructs node with data and determined priority
            // @remark constructor
            prinode (T data, size_t priority);

            // destructor
            // @remark destructor
            ~prinode (void) {}
            
            // deletes self and children
            void cascadeDelete (void);

            // copies self and children
            prinode<T>* cascadeCopy (void) const;

            // change data content
            void injectData (T data) { this->dataInit(data); }
            
            void copy (const prinode<T>* ptr) { 
                this->dataInit(ptr->data);
                priority = ptr->priority;
            }

            // get priority value
            size_t getPriority() const { return priority; }
        };

    template <typename T>
    class treap : public comparator<T>
        {
        private:
            prinode<T>* root;

            treap* split (void);
            void merge (treap* other);

            // rotate node section
            // @param[out]  parent      pointer to the pivot node
            // @param[in]   rotateLeft  true if right child should become new parent
            // @return void
            void rotate(prinode<T>* parent, bool rotateLeft);

            // search for key in subtree i_root
            // @param[in]   key   T typed data to search for
            // return   NULL if root is NULL
            //          pointer to node containing key
            prinode<T>* BinSearch (T key, prinode<T>* i_root) const;

            // get the successor of subtree rooted by i_root
            // @param[in]   i_root  rbnode pointer root of subtree
            // return   NULL if root right is NULL
            //          pointer to successor
            prinode<T>* successor (prinode<T>* i_root);

            // recurse through this tree in order
            // @param[in]   root    pointer to root of subtree to recurse through
            // @param[in]   func    function to perform on each node
            // return  void
            void completeRecurse (prinode<T>* root, 
                                std::function<void(prinode<T>*)> func) const;
        public:
            // constructs NULL root
            // @remark default constructor
            treap (void) : root(NULL) {}

            // destroys self content, then copy src content to self
            // @remark copy constructor
            treap (const treap<T>& src);

            // destructor
            // @remark destructor
            virtual ~treap (void);

            // copy assignment operator
            // @param[in]   src     reference to treap object to copy from
            // @return      reference to this after copy assignment
            treap<T>& operator = (const treap<T>& src);

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

            dcontain::wrapper<T> peekTop (void);

            // bulk ops
            void tr_union();
            void tr_intersection();
            void tr_difference();

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

    #include "treap.cpp"
    }

#endif /* __TREAP__H */