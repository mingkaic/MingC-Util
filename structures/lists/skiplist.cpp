//
//  skiplist.cpp
//  List
//
//  Created by Mingkai Chen on 2016-02-02.
//
//

#ifdef __SKIP_LIST__H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <stdexcept>
#include <algorithm>

template <class T>
skipnode<T>::skipnode(T data, size_t height) : height(height)
	{
	this->dataInit(data);
	nexts = new skipnode<T>*[height];
	memset(nexts, (int) NULL, sizeof(skipnode<T>*)*height);
	}
	
template <class T>
void skipnode<T>::seriesConnection(skipnode<T>* next)
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
	
template <class T>
skipnode<T>::skipnode(T data)
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
	
template <class T>
skipnode<T>::skipnode(T data, skipnode<T>* next) : skipnode(data)
	{
	seriesConnection(next);
	}
	
template <class T>
skipnode<T>::~skipnode()
	{
	delete[] nexts;
	}
	
template <class T>
void skipnode<T>::cascadeDelete()
	{
	if (NULL != nexts[0])
		{
		nexts[0]->cascadeDelete();
		}
	delete this;
	}
	
template <class T>
skipnode<T>* skipnode<T>::cascadeCopy()
	{
	skipnode<T>* copy = new skipnode<T>(this->data, height);
	copy->seriesConnection(nexts[0]->cascadeCopy());
	return copy;
	}
	
template <class T>
skiplist<T>::skiplist() : head(NULL)
	{
	}
	
template <class T>
skiplist<T>::skiplist(const skiplist<T>& src)
	{
	if (NULL != src.head)
		{	
		head = src.head->cascadeCopy();
		}
	}
	
template <class T>
skiplist<T>::~skiplist()
	{
	if (NULL != head)
		{
		head->cascadeDelete();
		}
	}

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
	
template <class T>
bool skiplist<T>::insert(T data)
	{
	bool unique = true;
	if (NULL == head || data < head->getData())
		{
		head = new skipnode<T>(data, head);
		}
	else if (data == head->getData())
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
				(NULL == buffer->nexts[index] || data < buffer->nexts[index]->getData()))
				{
				index--;
				}
			next = buffer->nexts[index];
			}
		while (NULL != next && data >= next->getData());

		if (data == buffer->getData())
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

template <class T>
bool skiplist<T>::remove(T data)
	{
	bool found = true;
	
	if (NULL == head || data < head->getData())
		{
		found = false;
		}
	else if (data == head->getData())
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
		
		while (NULL != buffer->nexts[0] && data >= buffer->nexts[0]->getData())
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
				(NULL == buffer->nexts[index] || data <= buffer->nexts[index]->getData()))
				{
				index--;
				}
			buffer = buffer->nexts[index];
			}
		
		if (last.size() > 0 && data == buffer->getData())
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

template <class T>
bool skiplist<T>::search(T data)
	{
	bool found = true;
	
	if (NULL == head || data < head->getData())
		{
		found = false;
		}
	else if (data != head->getData())
		{
		skipnode<T>* buffer = head;
		size_t curheight = 0;
		size_t index;
		while (NULL != buffer->nexts[0] && data >= buffer->nexts[0]->getData())
			{
			curheight = buffer->height;
			index = curheight-1;
			while (index > 0 && 
				(NULL == buffer->nexts[index] || data < buffer->nexts[index]->getData()))
				{
				index--;
				}
			buffer = buffer->nexts[index];
			}
		if (data != buffer->getData())
			{
			found = false;
			}
		}
	return found;
	}

template <class T>
bool skiplist<T>::isEmpty() 
	{
	return NULL == head;
	}

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

template <class T>
size_t skiplist<T>::size() const
    {
    size_t incr = 0;
    for (skipnode<T>* buffer = head; NULL != buffer; buffer = buffer->nexts[0])
        {
        incr++;
        }
    return incr;
    }

#endif /* __SKIP_LIST__H */