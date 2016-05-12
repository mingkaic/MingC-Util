//
//  heap.hpp
//  List
//
//  description: min heap
//
//  Created by Mingkai Chen on 2016-02-01.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#pragma once
#ifndef __HEAP__H
#define __HEAP__H

#include "../oop/compare.hpp"
#include "../dcontainers/treenode.hpp"
#include "../lists/dynamicarr.hpp"
#include "../dcontainers/wrapper.hpp"

namespace tree
	{
	// current implementation: min heap
	template <class T>
	class heap : comparator<T>
		{
		private:
			list::dynamicarr<T> treeArr;
			size_t curSize;
            T defaultval;
			
			// fix heap ordering
			// @param[in]	index	size_t index to fix the heap around
			// @return 	void
			void reheap(size_t index);
		public:
            // streaming operator
            // @param[out]   out    reference to out-stream
            // @param[in]    h    	reference to heap
            // @return       out-stream
            friend std::ostream& operator << (std::ostream& out, const heap& h) 
                {
                size_t nextline = 1;
                for (size_t i = 0; i < h.curSize; i++) 
                    {
                    if (i == nextline-1)
                    	{
                    	out << "\n";
                    	nextline *= 2;
                    	}
                    out << h.treeArr[i] << " ";
                    }
                out << std::endl;
                return out;
                }

		    // overload comparator equality setting to also set 
		    // this dynamic array's equality
		    // param[in]    equals  function pointer with signature
		    //                      bool (*) (T, T)
		    // returns void
		    void setEquals (equatable<T> equals)
		        {
		        this->equals = equals;
		        treeArr.setEquals(equals);
		        }

            // constructs empty heap
            // @remark default constructor
			heap (void);

            // constructs empty heap with default value
            // @remark constructor
            heap (T defaultval);

            // destroys self content, then copy src content to self
            // @remark copy constructor
			heap (const heap<T>& src);

            // destructor
            // @remark destructor
			virtual ~heap (void) {}

            // copy assignment operator
            // @param[in]   src     reference to heap object to copy from
            // @return      reference to this after copy assignment
			heap<T>& operator = (const heap<T>& src);
			
            // insert key into heap
            // @param[in]   data	T typed data
            // @return void
			void put (T data);

            // get top of heap (min value)
            // @param[] 	void
            // @return wrapper object top value (min value)
            // castable to false if the heap is empty
            // castable to true otherwise
			dcontain::wrapper<T> get (void) const;

            // get data if data is in heap
            // @param[in]   data	T typed data
            // @return wrapper object value associated with data,
            // castable to false if data is not in heap
            // castable to true otherwise
			dcontain::wrapper<T> get (T data) const;

            // remove top of heap (min value)
            // @param[] 	void
            // @return wrapper object of removed value, 
            // castable to false if the heap is empty
            // castable to true otherwise
			dcontain::wrapper<T> remove (void);

            // remove data if data is in heap
            // @param[in]   data	T typed data
            // @return wrapper object of removed value, 
            // castable to false if there was no associated value
            // castable to true otherwise
			dcontain::wrapper<T> remove (T data);

            // determine if this heap is empty
            // @param[]  void
            // @return true if this heap is empty
            bool isEmpty (void) const { return 0 == curSize; }

            // determine the number of nodes in this heap
            // @param[]  void
            // @return size_t number of nodes in this heap
            size_t size (void) const { return curSize; }

            // remove all nodes in this heap
            // @param[]  void
            // @return void
            void clear (void) { curSize = 0; }
		};
		
	#include "heap.cpp"
	}

#endif /* __HEAP__H */
