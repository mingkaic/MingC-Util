//
//  hashmap.hpp
//  Map
//
//  description: hashed structure mapping keys to value 
//
//  Created by Ming Kai Chen on 2014-07-15.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#pragma once
#ifndef __HASH_MAP__H
#define __HASH_MAP__H

#include "../../utils/memory.hpp"
#include "../oop/compare.hpp"
#include "../lists/searchlist.hpp"
#include "../dcontainers/pair.hpp"
#include "../dcontainers/wrapper.hpp"
#include <vector>

namespace map
    {
    template <typename K, typename V>
    using pairptr = spointer<dcontain::pair<K, V> >;

    template <typename K, typename V>
    class hashmap : public comparator<K>
        {
        private:
            // initialize searchlist equality function
            void pairptr_initialize (void)
                {
                for (size_t i = 0; i < numBuckets; i++)
                    {
                    dictionary[i].setEquals([this](pairptr<K, V> p1, pairptr<K, V> p2)->bool 
                        {
                        return this->equals(p1->getKey(), p2->getKey());
                        });
                    }
                }

            list::searchlist<pairptr<K, V> >* dictionary = NULL;
            size_t curSize;
            size_t numBuckets;
        public:
            // constructs an array of searchlists
            // of size 101
            // @remark default constructor
            hashmap (void);

            // constructs an array of searchlists
            // of size primed number greater than
            // intendedSize * 2
            // @remark default constructor
            hashmap (size_t intendedSize);

            // destroys self content, then copy src content to self
            // minor issue: searchlist contains smart pointer which 
            //              discourages deep copying. unreference pair 
            //              when changing value
            // @remark copy constructor
            hashmap (const hashmap<K, V>& src);

            // destructor
            // @remark destructor
            virtual ~hashmap (void);

            // copy assignment operator
            // minor issue: searchlist contains smart pointer which 
            //              discourages deep copying. unreference pair 
            //              when changing value
            // @param[in]   src     reference to hashmap object to copy from
            // @return      reference to this after copy assignment
            hashmap<K, V>& operator = (const hashmap<K, V>& src);

            // get value in key-value pairs into this
            // @param[in]   key     key
            // @return wrapper object value associated with key, 
            // castable to false if there was no associated value
            // castable to true otherwise
            dcontain::wrapper<V> get (K key) const;

            // insert key-value pairs into this
            // @param[in]   key     key
            // @param[in]   value   value
            // @return wrapper object value associated with key, 
            // castable to false if there was no associated value
            // castable to true otherwise
            dcontain::wrapper<V> put (K key, V data);

            // UNTESTED
            // insert all key-value pairs in other into this
            // @param[in]   other   reference to another hashmap
            // @return void
            void putAll (const hashmap<K, V>& other);

            // remove key-value association
            // @param[in]   key     Key in the key-value pair
            // @return wrapper object value associated with key, 
            // castable to false if there was no associated value
            // castable to true otherwise
            dcontain::wrapper<V>  remove (K key);

            // UNTESTED
            // determines if key is stored
            // @param[in]   key     Key value
            // @return true if key is found, false otherwise
            bool containsKey (K key) const;

            // UNTESTED
            // determines if value is stored
            // @param[in]   value   Value
            // @param[in]   eq      optional equality function for finding 
            //                      value (defaults to == operator)
            // @return true if key is found, false otherwise
            bool containsValue (V value, equatable<V> eq = [](V left, V right) { return left == right; }) const;

            // TODO:
            // - KEYSET
            // - VALUESET
            // - ENTRYSET

            // determines if dictionary is empty
            // @param[]     void
            // @return true if empty, false otherwise
            bool isEmpty (void) const;

            // find the size of the list
            // @param[]     void
            // @return      integer size of list
            size_t size (void) const;

            // removes all pairs in dictionary
            // @param[]     void
            // @return      void
            void clear (void);
            
            // UNTESTED
            // returns vectors of keys
            std::vector<K> hashIntersect (const hashmap<K, V>& src) const;
            std::vector<K> hashUnion (const hashmap<K, V>& src) const;
            std::vector<K> hashDifference (const hashmap<K, V>& src) const;
        };

    #include "hashmap.cpp"
    }

#endif /* __HASH_MAP__H */
