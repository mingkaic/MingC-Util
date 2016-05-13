//
//  heap.cpp
//  List
//
//  description: min heap
//
//  Created by Mingkai Chen on 2016-02-01.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __HEAP__H

// swap between indices in arr
// @param[out]	arr 	pointer to dynamic array
// @param[in]	index1 	size_t index to swap with
// @param[in]	index2 	size_t index to swap with
// @return	void

template <typename T>
void swap (list::dynamicarr<T>& arr, size_t index1, size_t index2)
	{
	T buffer = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = buffer;
	}
			
// fix heap ordering
// @param[in]	index	size_t index to fix the heap around
// @return 	void

template <typename T>
void heap<T>::reheap (size_t index)
	{
	// bubble up
	for (size_t p = (index-1)/2; index > 0 && treeArr[index] < treeArr[p]; p = (index-1)/2)
		{
		swap(treeArr, p, index);
		index = p;
		}
	// bubble down
	size_t left = index*2+1;
	size_t right = index*2+2;
	while ((curSize > left && treeArr[index] > treeArr[left]) || 
		(curSize > right && treeArr[index] > treeArr[right]))
		{
		if (treeArr[left] < treeArr[right] || curSize <= right)
			{
			swap(treeArr, left, index);
			index = left;
			}
		else
			{
			swap(treeArr, right, index);
			index = right;
			}
		left = index*2+1;
		right = index*2+2;
		}
	}
	
// constructs empty heap
// @remark default constructor

template <typename T>
heap<T>::heap (void) : curSize(0)
	{
	}

// constructs empty heap with default value
// @remark constructor

template <typename T>
heap<T>::heap (T defaultval) : curSize(0), defaultval(defaultval)
	{
	}

// destroys self content, then copy src content to self
// @remark copy constructor
	
template <typename T>
heap<T>::heap (const heap<T>& src) : 
	curSize(src.curSize), defaultval(src.defaultval), comparator<T>(src)
	{
	treeArr = src.treeArr;
	}

// copy assignment operator
// @param[in]   src     reference to heap object to copy from
// @return      reference to this after copy assignment
	
template <typename T>
heap<T>& heap<T>::operator = (const heap<T>& src)
	{
    comparator<T>::operator = (src);
	if (this != &src)
		{
		curSize = src.curSize;
		treeArr = src.treeArr;
		defaultval = src.defaultval;
		}
	return *this;
	}
			
// insert key into heap
// @param[in]   data	T typed data
// @return void
	
template <typename T>
void heap<T>::put (T data)
	{
	T buffer;
	treeArr[curSize++] = data;
	reheap(curSize-1);
	}

// get top of heap (min value)
// @param[] 	void
// @return wrapper object top value (min value)
// castable to false if the heap is empty
// castable to true otherwise
	
template <typename T>
dcontain::wrapper<T> heap<T>::get (void) const
	{
	dcontain::wrapper<T> pass;
	if (0 < curSize)
		{
		pass.good = true;
		pass.value = treeArr[0];
		}
	return pass;
	}

// get data if data is in heap
// @param[in]   data	T typed data
// @return wrapper object value associated with data,
// castable to false if data is not in heap
// castable to true otherwise

template <typename T>
dcontain::wrapper<T> heap<T>::get (T data) const
	{
	dcontain::wrapper<T> pass;
	
	signed i = treeArr.indexOf(data);

	if (i >= 0 && i < curSize)
		{
		pass.good = true;
		pass.value = treeArr[i];
		}
	
	return pass;
	}

// remove top of heap (min value)
// @param[] 	void
// @return wrapper object of removed value, 
// castable to false if the heap is empty
// castable to true otherwise

template <typename T>
dcontain::wrapper<T> heap<T>::remove (void)
	{
	dcontain::wrapper<T> pass;
	if (0 < curSize)
		{
		pass.good = true;
		pass.value = treeArr[0];
		swap(treeArr, 0, --curSize);
		reheap(0);
		}
	return pass;
	}

// remove data if data is in heap
// @param[in]   data	T typed data
// @return wrapper object of removed value, 
// castable to false if there was no associated value
// castable to true otherwise

template <typename T>
dcontain::wrapper<T> heap<T>::remove (T data)
	{
	dcontain::wrapper<T> pass;
	signed i = treeArr.indexOf(data);

	if (i > -1 && i < curSize)
		{
		pass.good = true;
		pass.value = treeArr[i];
		swap(treeArr, i, --curSize);
		reheap(i);
		}
	
	return pass;
	}

#endif /* __HEAP__H */