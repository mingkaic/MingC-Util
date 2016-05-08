//
//  skiplist.cpp
//  List
//
//  description: singly linked list featuring O(log(n)) search, and guaranteed sorted order
//
//  Created by Mingkai Chen on 2016-02-02.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//
//

#ifdef __SKIP_LIST__H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <stdexcept>
#include <algorithm>

// constructs a node containing data and has determined height
// @remark private constructor called in copy operations

template <class T>
skipnode<T>::skipnode (T data, size_t height) : height(height)
	{
	this->dataInit(data);
	nexts = new skipnode<T>*[height];
	memset(nexts, (int) NULL, sizeof(skipnode<T>*)*height);
	}

// not so optimized connect current node to every node including and after next
// @param[in]   next     pointer to next skipnode to connect
// @return      void
	
template <class T>
void skipnode<T>::seriesConnection (skipnode<T>* next)
	{
	skipnode<T>* buffer = next;
	for (size_t i = 0; i < height && NULL != buffer; i++)
		{
		// grabs the closest node with height greater than i
		while (NULL != buffer && buffer->height <= i)
			{
			buffer = buffer->nexts[buffer->height-1];
			}
		nexts[i] = buffer;
		}
	}

// recursively create a linked deep copy this and nexts and records 
// the front most nodes of each level into frontrunner vector reference 
// @param[out]  frontrunners     reference to storage vector for front nodes 
// @return      deep copy of this
	
template <class T>
skipnode<T>* skipnode<T>::cascadeCopy (std::vector<skipnode<T>*>& frontrunners)
	{
	skipnode<T>* copy = new skipnode<T>(this->data, height);
	if (NULL != nexts[0])
		{
		copy->seriesConnection(nexts[0]->cascadeCopy(frontrunners));
		signed diff = height-frontrunners.size();
		size_t min = diff > 0 ? frontrunners.size() : height;
		for (size_t i = 0; i < min; i++)
			{
			copy->nexts[i] = frontrunners[i];
			}
		if (diff > 0)
			{
			std::fill(frontrunners.begin(), frontrunners.end(), copy);
			frontrunners.insert(frontrunners.end(), diff, copy);
			}
		else
			{
			std::fill(frontrunners.begin(), frontrunners.begin()+height, copy);
			}
		}
	return copy;
	}

// constructs a node containing data and has random height
// @remark constructor
	
template <class T>
skipnode<T>::skipnode (T data)
	{
	this->dataInit(data);
	height = 1;
	while (0 == rand()%2)
		{
		height++;
		}
	nexts = new skipnode<T>*[height];
	memset(nexts, (int) NULL, sizeof(skipnode<T>*)*height);
	}

// constructs a node containing data and has random height
// and connects to nodes at or after next
// @remark constructor
	
template <class T>
skipnode<T>::skipnode (T data, skipnode<T>* next) : skipnode(data)
	{
	seriesConnection(next);
	}

// destructor
// @remark destructor
	
template <class T>
skipnode<T>::~skipnode (void)
	{
	delete[] nexts;
	}
		
// recursively delete this and nodes after this
// @param[out]  void
// @return      void
	
template <class T>
void skipnode<T>::cascadeDelete (void)
	{
	if (NULL != nexts[0])
		{
		nexts[0]->cascadeDelete();
		}
	delete this;
	}

// recursively create a linked deep copy this (calls private cascadeCopy)
// @param[out]  void
// @return      deep copy of this
	
template <class T>
skipnode<T>* skipnode<T>::cascadeCopy (void)
	{
	std::vector<skipnode<T>*> frontrunners;
	skipnode<T>* front = new skipnode<T>(this->data, height);

	if (NULL != nexts[0])
		{
		front->seriesConnection(nexts[0]->cascadeCopy(frontrunners));
		size_t min = height > frontrunners.size() ? frontrunners.size() : height;
		for (size_t i = 0; i < min; i++)
			{
			front->nexts[i] = frontrunners[i];
			}
		}
	return front;
	}
	
// ========== SKIP LIST IMPLEMENTATIONS ============= //

// constructs NULL head
// @remark default constructor

template <class T>
skiplist<T>::skiplist (void) : head(NULL)
	{
	}

// destroys self content, then copy src content to self
// @remark copy constructor
	
template <class T>
skiplist<T>::skiplist (const skiplist<T>& src) : head(NULL)
	{
	if (NULL != src.head)
		{
		head = src.head->cascadeCopy();
		}
	}

// destructor
// @remark destructor
	
template <class T>
skiplist<T>::~skiplist (void)
	{
	if (NULL != head)
		{
		head->cascadeDelete();
		}
	}

// copy assignment operator
// @param[in]   src     reference to skiplist object to copy from
// @return      reference to this after copy assignment

template <class T>
skiplist<T>& skiplist<T>::operator = (const skiplist<T>& src)
	{
	if (this != &src)
		{
		if (NULL != head)
			{
			head->cascadeDelete();
			}
		if (NULL != src.head)
			{	
			head = src.head->cascadeCopy();
			}
		}
	return *this;
	}
		
// add data to a sorted position
// @param[in]   data    T type data to add
// @return      true if data wasn't in the list prior to insertion, false otherwise
	
template <class T>
bool skiplist<T>::insert (T data)
	{
	bool unique = true;
	if (NULL == head || 0 < this->C.compare(data, head->getData()))
		{
		head = new skipnode<T>(data, head);
		}
	else if (this->C.equals(data, head->getData()))
		{
		unique = false;
		}
	else
		{
		skipnode<T>* buffer = NULL;
		skipnode<T>* next = head;
		size_t curheight = 0;
		size_t index = 0;
		// a vector of skipnodes whose next should point to new data
		std::vector<skipnode<T>*> last;
		do
			{
			buffer = next;
			// use skip-list enhanced optimized search
			curheight = buffer->height;
			// update lasts to ensure last covers the highest skipnode before new data's position
			signed diff = curheight-last.size();
			if (diff > 0)
				{
				// buffer is the highest last element, fill all
				std::fill(last.begin(), last.end(), buffer);
				// append additional NULLs to the end
				last.insert(last.end(), diff, buffer);
				}
			else
				{
				// buffer's not the highest, but fill up until curheight
				std::fill(last.begin(), last.begin()+curheight, buffer);
				}
			// get next.
			// if height is not 0 and next is valid, back track, lower, then try again
			index = curheight - 1;
			while (index > 0 && 
				(NULL == buffer->nexts[index] || 0 < this->C.compare(data, buffer->nexts[index]->getData())))
				{
				index--;
				}
			next = buffer->nexts[index];
			}
		while (NULL != next && 0 >= this->C.compare(data, next->getData()));

		if (this->C.equals(data, buffer->getData()))
			{
			unique = false;
			}
		else
			{
			buffer->nexts[0] = new skipnode<T>(data, buffer->nexts[0]);
			buffer = buffer->nexts[0];
			curheight = last.size() > buffer->height ? buffer->height : last.size();
			for (index = curheight-1; index > 0; index--)
				{
				last[index]->nexts[index] = buffer;
				}
			}
		}
	return unique;
	}

// remove data while maintaining sorted order
// @param[in]   data    T type data to remove
// @return      true if data was found and removed, false otherwise

template <class T>
bool skiplist<T>::remove (T data)
	{
	bool found = true;
		this->C.compare(data, head->getData());
	if (NULL == head || 0 < this->C.compare(data, head->getData()))
		{
		found = false;
		}
	else if (this->C.equals(data, head->getData()))
		{
		skipnode<T>* buffer = head;
		head = head->nexts[0];
		delete buffer;
		}
	else
		{
		skipnode<T>* buffer = head;
		std::vector<skipnode<T>*> last;
		size_t curheight = 0;
		size_t index = 0;
		
		while (NULL != buffer->nexts[0] && 0 >= this->C.compare(data, buffer->nexts[0]->getData()))
			{
			curheight = buffer->height;
			// update lasts to ensure last covers the highest skipnode before new data's position
			signed diff = curheight-last.size();
			if (diff > 0)
				{
				// buffer is the highest last element, fill all
				std::fill(last.begin(), last.end(), buffer);
				// append additional NULLs to the end
				last.insert(last.end(), diff, buffer);
				}
			else
				{
				// buffer's not the highest, but fill up until curheight
				std::fill(last.begin(), last.begin()+curheight, buffer);
				}

			index = curheight - 1;
			while (index > 0 && 
				(NULL == buffer->nexts[index] || 0 <= this->C.compare(data, buffer->nexts[index]->getData())))
				{
				index--;
				}
			buffer = buffer->nexts[index];
			}
		
		if (last.size() > 0 && this->C.equals(data, buffer->getData()))
			{
			curheight = last.size() > buffer->height ? buffer->height : last.size();
			for (index = 0; index < curheight; index++)
				{
				last[index]->nexts[index] = buffer->nexts[index];
				}
			delete buffer;
			}
		else
			{
			found = false;
			}
		}
	return found;
	}

// search if data exists in list
// @param[in]   data    T type data to remove
// @return      true if data was found, false otherwise

template <class T>
bool skiplist<T>::search (T data) const
	{
	bool found = true;
	
	if (NULL == head || 0 < this->C.compare(data, head->getData()))
		{
		found = false;
		}
	else if (false == this->C.equals(data, head->getData()))
		{
		skipnode<T>* buffer = head;
		size_t curheight = 0;
		size_t index;
		while (NULL != buffer->nexts[0] && 0 >= this->C.compare(data, buffer->nexts[0]->getData()))
			{
			curheight = buffer->height;
			index = curheight-1;
			while (index > 0 && 
				(NULL == buffer->nexts[index] || 0 < this->C.compare(data, buffer->nexts[index]->getData())))
				{
				index--;
				}
			buffer = buffer->nexts[index];
			}
		if (false == this->C.equals(data, buffer->getData()))
			{
			found = false;
			}
		}
	return found;
	}

// determine if list is empty
// @param[]   void
// @return      true if list is empty

template <class T>
bool skiplist<T>::isEmpty (void) const
	{
	return NULL == head;
	}

// overloaded bracket access operator
// @param[in]   index   integer index to access
// @remark  throws error if index > size
// @return  T type data of data at index

template <class T>
T skiplist<T>::operator [] (size_t index)
	{
	skipnode<T>* buffer = head;
    size_t i = 0;
	for (i = 0; NULL != buffer && i < index; i++)
		{
		buffer = buffer->nexts[0];
		}
	if (i < index)
		{
		throw std::out_of_range("index out of bounds");
		}
	return buffer->getData();
	}

// determine the size of list
// @param[]   void
// @return  integer size of list

template <class T>
size_t skiplist<T>::size (void) const
    {
    size_t incr = 0;
    for (skipnode<T>* buffer = head; NULL != buffer; buffer = buffer->nexts[0])
        {
        incr++;
        }
    return incr;
    }

#endif /* __SKIP_LIST__H */