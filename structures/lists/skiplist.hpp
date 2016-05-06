//
//  skiplist.hpp
//  List
//
//  Created by Mingkai Chen on 2016-02-02.
//
//

#pragma once
#ifndef __SKIP_LIST__H
#define __SKIP_LIST__H

#include "../dcontainers/gnode.hpp"

template <class T>
class skipnode : public gnode<T>
	{
	private:
		skipnode(T data, size_t height);
		void seriesConnection(skipnode<T>* series);
	public:
		skipnode<T>** nexts;
		size_t height;
	
		skipnode(T data);
		skipnode(T data, skipnode<T>* next);
		~skipnode();
		
		void cascadeDelete();
		skipnode<T>* cascadeCopy();
	};

template <class T>
class skiplist
	{
	private:
		skipnode<T>* head;
	public:
		skiplist();
		skiplist(const skiplist<T>& src);
		~skiplist();
		skiplist<T>& operator = (const skiplist<T>& src);
		
		bool insert(T data);
		bool remove(T data);
		bool search(T data);
		bool isEmpty();
		T operator [] (size_t index);
        size_t size() const;

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

#endif /* __SKIP_LIST__H */
