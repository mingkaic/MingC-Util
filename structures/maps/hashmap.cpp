//
//  hashmap.cpp
//  Map
//
//  description: hashmap that uses heaps as buckets
//               features priority removal
//
//  description: hashed structure mapping keys to value 
//
//  Created by Ming Kai Chen on 2014-07-15.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __HASH_MAP__H

#include <string>

#define DEFAULT_NBUCKET 101

// constructs an array of searchlists
// of size 101
// @remark default constructor

template <typename K, typename V>
hashmap<K, V>::hashmap (void) : numBuckets(DEFAULT_NBUCKET), curSize(0)
    {
    dictionary = new list::searchlist<pairptr<K, V> >[numBuckets];
    pairptr_initialize();
    }

// constructs an array of searchlists
// of size primed number greater than
// intendedSize * 2
// @remark default constructor

template <typename K, typename V>
hashmap<K, V>::hashmap (size_t intendedSize) : curSize(0)
    {
    numBuckets = nearestPrime(intendedSize*2);
    dictionary = new list::searchlist<pairptr<K, V> >[numBuckets];
    pairptr_initialize();
    }

// destroys self content, then copy src content to self
// minor issue: searchlist contains smart pointer which 
//              discourages deep copying. unreference pair 
//              when changing value
// @remark copy constructor

template <typename K, typename V>
hashmap<K, V>::hashmap (const hashmap& src) : 
    numBuckets(src.numBuckets), curSize(src.curSize), comparator<K>(src)
    {
    dictionary = new list::searchlist<pairptr<K, V> >[numBuckets];
    pairptr_initialize();
    for (size_t i = 0; i < src.numBuckets; i++)
        {
        dictionary[i] = src.dictionary[i];
        }
    }

// destructor
// @remark destructor

template <typename K, typename V>
hashmap<K, V>::~hashmap (void)
    {
    delete[] dictionary;
    }

// copy assignment operator
// minor issue: searchlist contains smart pointer which 
//              discourages deep copying. unreference pair 
//              when changing value
// @param[in]   src     reference to hashmap object to copy from
// @return      reference to this after copy assignment

template <typename K, typename V>
hashmap<K, V>& hashmap<K, V>::operator = (const hashmap<K, V>& src)
    {
    comparator<K>::operator = (src);
    if (this != &src)
        {
        curSize = src.curSize;
        numBuckets = src.numBuckets;
        clear();
        for (size_t i = 0; i < src.numBuckets; i++)
            {
            dictionary[i] = src.dictionary[i];
            }
        }
    
    return *this;
    }

// get value in key-value pairs into this
// @param[in]   key     key
// @return wrapper object value associated with key, 
// castable to false if there was no associated value
// castable to true otherwise

template <typename K, typename V>
dcontain::wrapper<V> hashmap<K, V>::get (K key) const
    {
    dcontain::wrapper<V> pass; // empty wrapper (bad)
    size_t hashIndex = this->hashcode(key) % numBuckets;

    pairptr<K, V> sample(new dcontain::pair<K, V>(key));
    signed searchIndex = dictionary[hashIndex].search(sample);
    if (searchIndex > -1)
        {
        pairptr<K, V> ptr = dictionary[hashIndex].nPeek(searchIndex);
        pass.value = ptr->getData();
        pass.good = true;
        }
    return pass;
    }

// insert key-value pairs into this
// @param[in]   key     key
// @param[in]   value   value
// @return wrapper object of previous value associated with key, 
// castable to false if no previous value associated with key
// castable to true otherwise

template <typename K, typename V>
dcontain::wrapper<V> hashmap<K, V>::put (K key, V data)
    {
    dcontain::wrapper<V> pass; // empty wrapper (bad)
    size_t hashIndex = this->hashcode(key) % numBuckets;
    
    pairptr<K, V> sample(new dcontain::pair<K, V>(key, data));
    signed searchIndex = dictionary[hashIndex].search(sample);
    if (searchIndex > -1)
        {
        pairptr<K, V> ptr = dictionary[hashIndex].nReplace(sample, searchIndex);
        pass.value = ptr->getData();
        pass.good = true;
        }
    else
        {
        dictionary[hashIndex].push_back(sample);
        curSize++;
        }
    return pass;
    }

// insert all key-value pairs in other into this
// @param[in]   other   reference to another hashmap
// @return void

template <typename K, typename V>
void hashmap<K, V>::putAll (const hashmap<K, V>& other)
    {
    size_t listsize;
    size_t hashIndex;
    signed searchIndex;
    for (size_t i = 0; i < other.numBuckets; i++)
        {
        listsize = other.dictionary[i].size();
        for (size_t j = 0; j < listsize; j++)
            {
            pairptr<K, V> sample = other.dictionary[i].nPeek(j);
            hashIndex = this->hashcode(sample->getKey()) % numBuckets;
            searchIndex = dictionary[hashIndex].search(sample);
            if (searchIndex > -1)
                {
                dictionary[hashIndex].nReplace(sample, searchIndex);
                }
            else
                {
                dictionary[hashIndex].push_back(sample);
                curSize++;
                }
            }
        }
    }

// remove key-value association
// @param[in]   key     Key in the key-value pair
// @return wrapper object value associated with key, 
// castable to false if there was no associated value
// castable to true otherwise

template <typename K, typename V>
dcontain::wrapper<V> hashmap<K, V>::remove (K key)
    {
    dcontain::wrapper<V> pass; // empty wrapper (bad)
    size_t hashIndex = this->hashcode(key) % numBuckets;

    pairptr<K, V> sample(new dcontain::pair<K, V>(key));
    signed searchIndex = dictionary[hashIndex].search(sample);
    if (searchIndex > -1)
        {
        pairptr<K, V> ptr = dictionary[hashIndex].nRemove(searchIndex);
        pass.value = ptr->getData();
        pass.good = true;
        curSize--;
        }
    return pass;
    }

// determines if key is stored
// @param[in]   key     Key value
// @return true if key is found, false otherwise

template <typename K, typename V>
bool hashmap<K, V>::containsKey (K key) const
    {
    pairptr<K, V> sample(new dcontain::pair<K, V>(key));
    size_t hashIndex = this->hashcode(key);
    signed searchIndex = dictionary[hashIndex].search(sample);
    return searchIndex > -1;
    }

// determines if value is stored
// @param[in]   value     Value
// @return true if key is found, false otherwise

template <typename K, typename V>
bool hashmap<K, V>::containsValue (V value, equatable<V> eq) const
    {
    size_t listsize;
    size_t hashIndex;
    signed searchIndex;
    bool found = false;
    for (size_t i = 0; i < numBuckets && false == found; i++)
        {
        listsize = dictionary[i].size();
        for (size_t j = 0; j < listsize && false == found; j++)
            {
            pairptr<K, V> sample = dictionary[i].nPeek(j);
            found = found || eq(value, sample->getValue());
            }
        }
    return found;
    }

// determines if dictionary is empty
// @param[]     void
// @return true if empty, false otherwise

template <typename K, typename V>
bool hashmap<K, V>::isEmpty (void) const
    {
    return 0 == curSize;
    }

// find the size of the list
// @param[]     void
// @return      integer size of list

template <typename K, typename V>
size_t hashmap<K, V>::size (void) const
    {
    return curSize;
    }

// removes all pairs in dictionary
// @param[]     void
// @return      void

template <typename K, typename V>
void hashmap<K, V>::clear (void)
    {
    delete[] dictionary;
    dictionary = new list::searchlist<pairptr<K, V> >[numBuckets];
    }

template <typename K, typename V>
std::vector<K> hashmap<K, V>::hashIntersect (const hashmap<K, V>& src) const
    {
    std::vector<K> joined;
    size_t listsize;
    size_t hashIndex;
    signed searchIndex;
    for (size_t i = 0; i < src.numBuckets; i++)
        {
        listsize = src.dictionary[i].size();
        for (size_t j = 0; j < listsize; j++)
            {
            pairptr<K, V> sample = src.dictionary[i].nPeek(j);
            hashIndex = this->hashcode(sample->getKey()) % numBuckets;
            searchIndex = dictionary[hashIndex].search(sample);
            
            if (searchIndex > -1)
                {
                joined.push_back(sample.getKey());
                }
            }
        }
    
    return joined;
    }

template <typename K, typename V>
std::vector<K> hashmap<K, V>::hashUnion (const hashmap& src) const
    {
    std::vector<K> joined;
    size_t listsize;
    size_t hashIndex;
    signed searchIndex;
    for (size_t i = 0; i < src.numBuckets; i++)
        {
        listsize = src.dictionary[i].size();
        for (size_t j = 0; j < listsize; j++)
            {
            pairptr<K, V> sample = src.dictionary[i].nPeek(j);
            hashIndex = this->hashcode(sample->getKey()) % numBuckets;
            searchIndex = dictionary[hashIndex].search(sample);
            
            if (searchIndex < 0)
                {
                joined.push_back(sample.getKey());
                }
            }
        }

    for (size_t i = 0; i < numBuckets; i++)
        {
        listsize = dictionary[i].size();
        for (size_t j = 0; j < listsize; j++)
            {
            pairptr<K, V> sample = dictionary[i].nPeek(j);
            joined.push_back(sample.getKey());
            }
        }
    
    return joined;
    }

template <typename K, typename V>
std::vector<K> hashmap<K, V>::hashDifference (const hashmap& src) const
    {
    std::vector<K> diff;
    size_t listsize;
    size_t hashIndex;
    signed searchIndex;
    for (size_t i = 0; i < numBuckets; i++)
        {
        listsize = dictionary[i].size();
        for (size_t j = 0; j < listsize; j++)
            {
            pairptr<K, V> sample = dictionary[i].nPeek(j);
            if (false == src.get(sample->getKey()))
                {
                diff.push_back(sample.getKey());
                }
            }
        }
    
    return diff;
    }

#endif /* __HASH_MAP__H */