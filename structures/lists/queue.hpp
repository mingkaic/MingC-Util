//
//  queue.hpp
//  List
//
//  description: data structure allowing read/write to front/back of list only with first in first out ordering
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __QUEUE__H
#define __QUEUE__H

#include "../dcontainers/binode.hpp"

namespace list
    {
    template <class T>
    class queue
        {
        protected:
            dcontain::binode<T>* head;
            dcontain::binode<T>* tail;
        public:
            // constructs NULL head and tail
            // @remark default constructor
            queue (void);

            // destroys self content, then copy src content to self
            // @remark copy constructor
            queue (const queue& src);

            // destructor
            // @remark destructor
            virtual ~queue (void);

            // copy assignment operator
            // @param[in]   src     reference to deque object to copy from
            // @return      reference to this after copy assignment
            queue<T>& operator = (const queue<T>& src);
            
            // add data to front (head) of list
            // @param[in]   data    T type data to add
            // @return      void
            void push_front (T data);

            // remove data from back (tail) of list
            // @param[in]   void
            // @return      T type data removed
            T pop_back (void);

            // accesses data from front (head) of list
            // @param[]     void
            // @return      T type data accessed
            T peek_front (void) const;

            // accesses data from back (tail) of list
            // @param[]     void
            // @return      T type data accessed
            T peek_back (void) const;

            // determines if the list is empty
            // @param[]     void
            // @return      true if empty, false otherwise
            bool isEmpty (void) const;

            // wipes all data in queue
            // @param[]     void
            // @return      void
            void clear (void);
        };

    #include "queue.cpp"
    }

#endif /* __QUEUE__H */
