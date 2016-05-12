//
//  hashheap.cpp
//  hybrid priority map
//
//  description: hashmap that uses heaps as buckets
//               features min key value peek/removal
//
//  Created by Ming Kai Chen on 2016-01-30.
//  Copyright (c) 2016 Ming Kai Chen. All rights reserved.
//

#ifdef __HASH_HEAP__H

#include <stdexcept>
#include <string>

#define ASCII_SIZE 256

// constructs an array of heap
// of size 101
// @remark default constructor

template <typename K, typename V>
hashheap<K, V>::hashheap (void) : numBuckets(101), curSize(0)
    {
    dictionary = new spointer<tree::heap<pairptr<K, V> > >[numBuckets];
    pairptr_initialize();
    }

// constructs an array of heap
// of size primed number greater than
// intendedSize * 2
// @remark default constructor

template <typename K, typename V>
hashheap<K, V>::hashheap (size_t intendedSize) : curSize(0)
    {
    numBuckets = nearestPrime((int)2*intendedSize);
    dictionary = new spointer<tree::heap<pairptr<K, V> > >[numBuckets];
    pairptr_initialize();
    }

// destroys self content, then copy src content to self
// minor issue: heap contains smart pointer which 
//              discourages deep copying. unreference pair 
//              when changing value
// @remark copy constructor

template <typename K, typename V>
hashheap<K, V>::hashheap (const hashheap<K, V>& src) : 
    numBuckets(src.numBuckets), curSize(src.curSize), comparator<K>(src)
    {
    dictionary = new spointer<tree::heap<pairptr<K, V> > >[numBuckets];
    pairptr_initialize();
    for (size_t i = 0; i < src.numBuckets; i++)
        {
        dictionary[i].reset(new tree::heap<pairptr<K, V> >(*(src.dictionary[i].get())));
        }
    }

// destructor
// @remark destructor

template <typename K, typename V>
hashheap<K, V>::~hashheap (void)
    {
    delete[] dictionary;
    }

// copy assignment operator
// minor issue: heap contains smart pointer which 
//              discourages deep copying. unreference pair 
//              when changing value
// @param[in]   src     reference to hashheap object to copy from
// @return      reference to this after copy assignment

template <typename K, typename V>
hashheap<K, V>& hashheap<K, V>::operator = (const hashheap<K, V>& src)
    {
    comparator<K>::operator = (src);
    if (this != &src)
        {
        curSize = src.curSize;
        numBuckets = src.numBuckets;
        delete[] dictionary;
        dictionary = new spointer<tree::heap<pairptr<K, V> > >[numBuckets];
        for (size_t i = 0; i < src.numBuckets; i++)
            {
            dictionary[i].reset(new tree::heap<pairptr<K, V> >(*(src.dictionary[i].get())));
            }
        }
    
    return *this;
    }

// get pair with minimum key
// @param[]     void
// @return smart pointer of pairs removed
//          null smart pointer if empty

template <typename K, typename V>
pairptr<K, V> hashheap<K, V>::get (void) const
    {
    dcontain::wrapper<pairptr<K, V> > min; // not good
    for (size_t i = 0; i < numBuckets; i++)
        {
        dcontain::wrapper<pairptr<K, V> > data = dictionary[i]->get();
        if (data && 
            (false == min || 
            0 < this->compare(data.value->getKey(), min.value->getKey())))
            {
            min.good = true;
            min.value = data;
            }
        }
    pairptr<K, V> pass; // null smart pointer
    if (min)
        {
        pass = min.value;
        }
    return pass;
    }

// get value in key-value pairs into this
// @param[in]   key     key
// @return wrapper object value associated with key, 
// castable to false if there was no associated value
// castable to true otherwise

template <typename K, typename V>
dcontain::wrapper<V> hashheap<K, V>::get (K key) const
    {
    dcontain::wrapper<V> pass; // empty wrapper (bad)
    size_t hashIndex = this->hashcode(key) % numBuckets;

    pairptr<K, V> sample(new dcontain::pair<K, V>(key));
    dcontain::wrapper<pairptr<K, V> > data = dictionary[hashIndex]->get(sample);
    if (data)
        {
        pass.good = true;
        pass.value = (data.value)->getData();
        }
    return pass;
    }

// insert key-value pairs into this
// @param[in]   key     key
// @param[in]   value   value
// @return wrapper object value associated with key, 
// castable to false if there was no associated value
// castable to true otherwise

template <typename K, typename V>
dcontain::wrapper<V> hashheap<K, V>::put (K key, V value)
    {
    dcontain::wrapper<V> pass; // empty wrapper (bad)
    size_t hashIndex = this->hashcode(key) % numBuckets;

    pairptr<K, V> sample(new dcontain::pair<K, V>(key, value));
    dcontain::wrapper<pairptr<K, V> > data = dictionary[hashIndex]->remove(sample);
    if (data)
        {
        pass.good = true;
        pass.value = (data.value)->getData();
        }
    dictionary[hashIndex]->put(sample);
    return pass;
    }

// UNTESTED
// insert all key-value pairs in other into this
// @param[in]   other   reference to another hashheap
// @return void

template <typename K, typename V>
void hashheap<K, V>::putAll (const hashheap<K, V>& other)
    {
    tree::heap<pairptr<K, V> > h;
    size_t hashIndex;
    for (size_t i = 0; i < other.numBuckets; i++)
        {
        h = other.dictionary[i];
        while (false == h.isEmpty())
            {
            pairptr<K, V> sample = h.get();
            hashIndex = this->hashcode(sample->getKey()) % numBuckets;
            if (false == dictionary[hashIndex]->remove(sample))
                {
                curSize++;
                }
            dictionary[hashIndex]->put(sample);
            }
        }
    }

// remove pair with minimum key
// @param[]     void
// @return smart pointer of pairs removed
//          null smart pointer if empty

template <typename K, typename V>
pairptr<K, V> hashheap<K, V>::remove (void)
    {
    dcontain::wrapper<pairptr<K, V> > min; // not good
    signed min_index = -1;
    for (size_t i = 0; i < numBuckets; i++)
        {
        dcontain::wrapper<pairptr<K, V> > data = dictionary[i]->get();
        if (data && 
            (false == min || 
            0 < this->compare(data.value->getKey(), min.value->getKey())))
            {
            min_index = i;
            min.good = true;
            min.value = data;
            }
        }
    pairptr<K, V> pass; // null smart pointer
    if (min)
        {
        pass = dictionary[min_index]->remove();
        }
    return pass;
    }

// remove key-value association
// @param[in]   key     Key in the key-value pair
// @return wrapper object value associated with key, 
// castable to false if there was no associated value
// castable to true otherwise

template <typename K, typename V>
dcontain::wrapper<V> hashheap<K, V>::remove (K key)
    {
    dcontain::wrapper<V> pass; // empty wrapper (bad)
    size_t hashIndex = this->hashcode(key) % numBuckets;

    pairptr<K, V> sample(new dcontain::pair<K, V>(key));
    pairptr<K, V> data = dictionary[hashIndex]->remove(sample);
    if (data)
        {
        pass.good = true;
        pass.value = data->getData();
        }
    return pass;
    }

// UNTESTED
// determines if key is stored
// @param[in]   key     Key value
// @return true if key is found, false otherwise

template <typename K, typename V>
bool hashheap<K, V>::containsKey (K key) const
    {
    pairptr<K, V> sample(new dcontain::pair<K, V>(key));
    size_t hashIndex = this->hashcode(key);
    return dictionary[hashIndex]->get(sample);
    }

// UNTESTED
// determines if value is stored
// @param[in]   value   Value
// @param[in]   eq      optional equality function for finding 
//                      value (defaults to == operator)
// @return true if key is found, false otherwise
template <typename K, typename V>
bool hashheap<K, V>::containsValue (V value, equatable<V> eq) const
    {
    tree::heap<pairptr<K, V> > h;
    size_t hashIndex;
    bool found = false;
    for (size_t i = 0; i < numBuckets && false == found; i++)
        {
        while (false == h.isEmpty() && false == found)
            {
            pairptr<K, V> sample = h.get();
            found = found || eq(value, sample->getValue());
            }
        }
    return found;
    }

// determines if dictionary is empty
// @param[]     void
// @return true if empty, false otherwise
template <typename K, typename V>
bool hashheap<K, V>::isEmpty (void) const
    {
    return 0 == curSize;
    }

// find the size of the list
// @param[]     void
// @return      integer size of list
template <typename K, typename V>
size_t hashheap<K, V>::size (void) const
    {
    return curSize;
    }

// removes all pairs in dictionary
// @param[]     void
// @return      void
template <typename K, typename V>
void hashheap<K, V>::clear (void)
    {
    delete[] dictionary;
    dictionary = new spointer<tree::heap<pairptr<K, V> > >[numBuckets];
    pairptr_initialize();
    }

#endif /* __HASH_HEAP__H */