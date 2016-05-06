//
//  pair.cpp
//  dataContainer
//  description: pairs two data (often key and t data)
//
//  Created by Ming Kai Chen on 2014-08-30.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __PAIR__H

template <class K, class T>
pair<K, T>::pair(K key) : key(key)
    {
    }

template <class K, class T>
pair<K, T>::pair(K key, T data) : key(key), data(data)
    {
    }

template <class K, class T>
pair<K, T>::pair(const pair<K, T>& src) : key(src.key), data(src.data)
    {
    }

template <class K, class T>
pair<K, T>::~pair()
    {
    }

template <class K, class T>
pair<K, T>& pair<K, T>::operator = (const pair<K, T>& src)
    {
	if (this != &src)
		{
        key = src.key;
        data = src.data;
		}
	return *this;
    }

template <class K, class T>
K pair<K, T>::getKey()
    {
    return key;
    }

template <class K, class T>
K& pair<K, T>::getKeyRef()
    {
    return key;
    }

template <class K, class T>
T pair<K, T>::getData()
    {
    return data;
    }
    
template <class K, class T>
T& pair<K, T>::getDataRef()
    {
    return data;
    }
    
template <class K, class T>
bool operator == (const pair<K, T>& left, const pair<K, T>& right)
    {
    return left.key == right.key;
    }

template <class K, class T>
bool operator == (const K& left, const pair<K, T>& right)
    {
    return left == right.key;
    }

template <class K, class T>
bool operator == (const pair<K, T>& left, const K& right)
    {
    return left.key == right;
    }
    
template <class K, class T>
bool operator != (const pair<K, T>& left, const pair<K, T>& right)
    {
    return left.key != right.key;
    }

template <class K, class T>
bool operator != (const K& left, const pair<K, T>& right)
    {
    return left != right.key;
    }

template <class K, class T>
bool operator != (const pair<K, T>& left, const K& right)
    {
    return left.key != right;
    }

template <class K, class T>
bool operator > (const pair<K, T>& left, const pair<K, T>& right)
    {
    return left.key > right.key;
    }

template <class K, class T>
bool operator < (const pair<K, T>& left, const pair<K, T>& right)
    {
    return left.key < right.key;
    }

#endif /* __PAIR__H */