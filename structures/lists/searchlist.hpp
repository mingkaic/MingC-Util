//
//  searchlist.hpp
//  List
//
//  description: doubly linked list featuring linear search, replacement, n-insertion, n-access, along with deque functions
//
//  Created by Ming Kai Chen on 2014-07-15.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#pragma once
#ifndef __SEARCH_LIST__H
#define __SEARCH_LIST__H

#include <iostream>
#include "deque.hpp"
#include "../oop/compare.hpp"

template <class T>
class searchlist : public deque<T>, public compManage<T>
    {
    public:
        // constructs NULL head and tail
        // @remark default constructor
        searchlist (void) {}

        // destroys self content, then copy src content to self
        // @remark copy constructor
        searchlist (const searchlist& src);

        // destructor
        // @remark destructor
        virtual ~searchlist (void) {}

        // copy assignment operator
        // @param[in]   src     reference to searchlist object to copy from
        // @return      reference to this after copy assignment
        searchlist<T>& operator = (const searchlist<T>& src);

        // search for the index of elem
        // @param[in]   elem     T typed data to search for
        // @return      index of element in list if found, -1 otherwise
        signed search (T elem);

        // insert elem at index N
        // @param[in]   elem     T typed data to insert
        // @param[in]   N        integer index to insert elem
        // @return      void
        void nInsert (T elem, size_t N);

        // remove elem at index N
        // @param[in]   N        integer index to remove elem
        // @return      void
        T nRemove (size_t N);

        // get elem at index N
        // @param[in]   N        integer index to get elem
        // @return      T typed data at index N
        T nPeek (size_t N) const;

        // replace data at index N with elem
        // @param[in]   elem     T typed data to replace data at index N
        // @param[in]   N        integer index
        // @return      T typed old (replaced) data 
        T nReplace (T elem, size_t N);
        
        // find the size of the list
        // @param[]     void
        // @return      integer size of list
        size_t size (void) const;

        // streaming operator
        // @param[out]   out     reference to out-stream
        // @param[in]    list    instance of this class
        // @return       out-stream
        friend std::ostream& operator << (std::ostream& out, const searchlist& list) 
            {
            for (binode<T>* buffer = list.head; NULL != buffer; buffer = buffer->next) 
                {
                out << buffer->getData() << " ";
                }
            out << std::endl;
            return out;
            }

        // --- INHERITED FROM DEQUE --- //
        // add data to back (tail) of list
        // @param[in]   data    T type data to add
        // @return      void
        // void push_back (T data);

        // remove data from front (head) of list
        // @param[]     void
        // @return      T type data removed
        // T pop_front (void);

        // --- INHERITED FROM QUEUE --- //
        // add data to front (head) of list
        // @param[in]   data    T type data to add
        // @return      void
        // void push_front (T data);

        // remove data from back (tail) of list
        // @param[in]   void
        // @return      T type data removed
        // T pop_back (void);

        // accesses data from front (head) of list
        // @param[]     void
        // @return      T type data accessed
        // T peek_front (void) const;

        // accesses data from back (tail) of list
        // @param[]     void
        // @return      T type data accessed
        // T peek_back (void) const;

        // determines if the list is empty
        // @param[]     void
        // @return      true if empty, false otherwise
        // bool isEmpty (void) const;
    };

#include "searchlist.cpp"

#endif /* __SEARCH_LIST__H */