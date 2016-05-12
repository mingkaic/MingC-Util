//
//  bstree.hpp
//  Tree
//
//  description: binary tree search
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __BSTREE__H
#define __BSTREE__H

#include <vector>
#include "../oop/compare.hpp"
#include "../dcontainers/treenode.hpp"

namespace tree
    {
    template <class T>
    class bstree : comparator<T>
        {
        private:
            dcontain::treenode<T>* root;

            // search for key in subtree i_root
            // @param[in]   key   T typed data to search for
            // return   NULL if root is NULL
            //          pointer to root (if root contains key)
            //          pointer to the parent to node containing key
            dcontain::treenode<T>* BinSearch (T key, dcontain::treenode<T>* i_root) const;

            // get the successor of subtree rooted by i_root
            // @param[in]   i_root  dcontain::treenode pointer root of subtree
            // return   NULL if root right is NULL
            //          pointer to successor's parent 
            //          (which is root if right node has no left child)
            dcontain::treenode<T>* successorParent (dcontain::treenode<T>* i_root);

            // recurse through this tree in order
            // @param[in]   root    pointer to root of subtree to recurse through
            // @param[in]   func    function to perform on each node
            // return  void
            void completeRecurse (dcontain::treenode<T>* root, 
                                std::function<void(dcontain::treenode<T>*)> func) const;
        public:
            // constructs NULL root
            // @remark default constructor
            bstree (void);

            // destroys self content, then copy src content to self
            // @remark copy constructor
            bstree (const bstree<T>& src);

            // destructor
            // @remark destructor
            virtual ~bstree (void);

            // copy assignment operator
            // @param[in]   src     reference to bstree object to copy from
            // @return      reference to this after copy assignment
            bstree<T>& operator = (const bstree<T>& src);

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

    #include "bstree.cpp"
    }

#endif /* __BSTREE__H */