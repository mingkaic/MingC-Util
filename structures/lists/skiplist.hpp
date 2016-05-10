//
//  skiplist.hpp
//  List
//
//  description: singly linked list featuring O(log(n)) search, and guaranteed sorted order
//
//  Created by Mingkai Chen on 2016-02-02.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __SKIP_LIST__H
#define __SKIP_LIST__H

#include "../dcontainers/gnode.hpp"

namespace list
    {
    // unique skip-list only node
    // each node has a random numberly generated height, which determines the next pointers
    // the lowest height points always points to the very next node
    // N-level nexts point to the next node with height >= N
    template <class T>
    class skipnode : public dcontain::gnode<T>
    	{
    	private:
            // constructs a node containing data and has determined height
            // @remark private constructor called in copy operations
            skipnode (T data, size_t height);

            // not so optimized connect current node to every node including and after next
            // @param[in]   next     pointer to next skipnode to connect
            // @return      void
    		void seriesConnection (skipnode<T>* next);

            // recursively create a linked deep copy this and nexts and records 
            // the front most nodes of each level into frontrunner vector reference 
            // @param[out]  frontrunners     reference to storage vector for front nodes 
            // @return      deep copy of this
            skipnode<T>* cascadeCopy (std::vector<skipnode<T>*>& frontrunners);
    	public:
    		skipnode<T>** nexts;
    		size_t height;

            // constructs a node containing data and has random height
            // @remark constructor
    		skipnode (T data);

            // constructs a node containing data and has random height
            // and connects to nodes at or after next
            // @remark constructor
    		skipnode (T data, skipnode<T>* next);

            // destructor
            // @remark destructor
    		~skipnode (void);
    		
            // recursively delete this and nodes after this
            // @param[out]  void
            // @return      void
    		void cascadeDelete (void);

            // recursively create a linked deep copy this (calls private cascadeCopy)
            // @param[out]  void
            // @return      deep copy of this
    		skipnode<T>* cascadeCopy (void);
    	};

    template <class T>
    class skiplist : public comparator<T>
    	{
    	private:
    		skipnode<T>* head;
    	public:
            // constructs NULL head
            // @remark default constructor
    		skiplist (void);

            // destroys self content, then copy src content to self
            // @remark copy constructor
    		skiplist (const skiplist<T>& src);

            // destructor
            // @remark destructor
    		virtual ~skiplist (void);

            // copy assignment operator
            // @param[in]   src     reference to skiplist object to copy from
            // @return      reference to this after copy assignment
    		skiplist<T>& operator = (const skiplist<T>& src);
    		
            // add data to a sorted position
            // @param[in]   data    T type data to add
            // @return      true if data wasn't in the list prior to insertion, false otherwise
    		bool insert (T data);

            // remove data while maintaining sorted order
            // @param[in]   data    T type data to remove
            // @return      true if data was found and removed, false otherwise
    		bool remove (T data);

            // search if data exists in list
            // @param[in]   data    T type data to remove
            // @return      true if data was found, false otherwise
    		bool search (T data) const;

            // determine if list is empty
            // @param[]   void
            // @return      true if list is empty
    		bool isEmpty (void) const;

            // overloaded bracket access operator
            // @param[in]   index   integer index to access
            // @remark  throws error if index > size
            // @return  T type data of data at index
    		T operator [] (size_t index);

            // determine the size of list
            // @param[]   void
            // @return  integer size of list
            size_t size(void) const;

            // wipes all data in list
            // @param[]     void
            // @return      void
            void clear (void);

            // streaming operator
            // @param[out]   out     reference to out-stream
            // @param[in]    list    instance of this class
            // @return       out-stream
            friend std::ostream& operator << (std::ostream& out, const skiplist& list) 
                {
                out << "---------------------------------\n";
                size_t maxheight = 0;
                out << "height 0: ";
                for (skipnode<T>* buffer = list.head; NULL != buffer; buffer = buffer->nexts[0]) 
                    {
                    out << buffer->getData() << " ";
                    if (maxheight < buffer->height)
                    	{
                    	maxheight = buffer->height;
                    	}
                    }
                out << std::endl;

                for (size_t i = 1; i < maxheight; i++)
                	{
                	out << "height " << i << ": ";
                	skipnode<T>* buffer = list.head;
                	size_t curheight = buffer->height;
                	// find first node with height greater than or equal to i
                	while (curheight < i+1 && NULL != buffer->nexts[curheight-1])
                		{
                		buffer = buffer->nexts[curheight-1];
                		curheight = buffer->height;
                		}

                	while (NULL != buffer)
                		{
                    	out << buffer->getData() << " ";
                    	buffer = buffer->nexts[i];
                		}
                	out << std::endl;
                	}
                out << "maxheight = " << maxheight << std::endl;
                out << "---------------------------------\n";
                return out;
                }
    	};

    #include "skiplist.cpp"
    }

#endif /* __SKIP_LIST__H */
