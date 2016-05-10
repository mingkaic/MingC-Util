//
//  deque.hpp
//  List
//
//  description: data structure allowing read/write to front/back of list only
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __DEQUE__H
#define __DEQUE__H

#include "queue.hpp"

namespace list
    {
    // Double ended queue (throw error handle behavior with remove on empty)
    template <class T>
    class deque : public queue<T>
        {
        public:
        	// constructs NULL head and tail
        	// @remark default constructor
            deque (void) {}

        	// destroys self content, then copy src content to self
        	// @remark copy constructor
            deque (const deque& src);

        	// destructor
        	// @remark destructor
            virtual ~deque (void) {}

        	// copy assignment operator
        	// @param[in]	src		reference to deque object to copy from
        	// @return		reference to this after copy assignment
            deque<T>& operator = (const deque<T>& src);

        	// add data to back (tail) of list
        	// @param[in]	data	T type data to add
        	// @return		void
            void push_back (T data);

        	// remove data from front (head) of list
        	// @param[]		void
        	// @return		T type data removed
            T pop_front (void);

            // --- INHERITED FROM QUEUE --- //
            // add data to front (head) of list
        	// @param[in]	data	T type data to add
        	// @return		void
        	// void push_front (T data);

            // remove data from back (tail) of list
        	// @param[in]	void
            // @return      T type data removed
            // T pop_back (void);

            // accesses data from front (head) of list
        	// @param[]		void
        	// @return		T type data accessed
            // T peek_front (void) const;

            // accesses data from back (tail) of list
        	// @param[]		void
        	// @return		T type data accessed
            // T peek_back (void) const;

            // determines if the list is empty
        	// @param[]		void
        	// @return		true if empty, false otherwise
            // bool isEmpty (void) const;

            // wipes all data in queue
            // @param[]     void
            // @return      void
            // void clear (void);
        };

    #include "deque.cpp"
    }

#endif /* __DEQUE__H */