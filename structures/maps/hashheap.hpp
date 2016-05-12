//
//  hashheap.hpp
//  hybrid priority map
//
//  description: hashmap that uses heaps as buckets
//               features min key value peek/removal
//
//  Created by Ming Kai Chen on 2016-01-30.
//  Copyright (c) 2016 Ming Kai Chen. All rights reserved.
//

#pragma once
#ifndef __HASH_HEAP__H
#define __HASH_HEAP__H

#include "../../math/number.hpp"
#include "../../utils/memory.hpp"
#include "../oop/compare.hpp"
#include "../trees/heap.hpp"
#include "../dcontainers/pair.hpp"
#include "../dcontainers/wrapper.hpp"

namespace map
    {
    template <typename K, typename V>
    using pairptr = spointer<dcontain::pair<K, V> >;
    
    template <typename K, typename V>
    class hashheap : public comparator<K>
        {
        private:
            // initialize searchlist equality function
            void pairptr_initialize (void)
                {
                pairptr<K, V> nil;
                for (size_t i = 0; i < numBuckets; i++)
                    {
                    dictionary[i].reset(new tree::heap<pairptr<K, V> >(nil));
                    dictionary[i]->setEquals([this](pairptr<K, V> p1, pairptr<K, V> p2)->bool 
                        {
                        return p1 && p2 && this->equals(p1->getKey(), p2->getKey());
                        });
                    }
                }

            spointer<tree::heap<pairptr<K, V> > >* dictionary = NULL;
            size_t curSize;
            size_t numBuckets;
        public:
            // constructs an array of heap
            // of size 101
            // @remark default constructor
            hashheap (void);

            // constructs an array of heap
            // of size primed number greater than
            // intendedSize * 2
            // @remark default constructor
            hashheap (size_t intendedSize);

            // destroys self content, then copy src content to self
            // minor issue: heap contains smart pointer which 
            //              discourages deep copying. unreference pair 
            //              when changing value
            // @remark copy constructor
            hashheap (const hashheap<K, V>& src);

            // destructor
            // @remark destructor
            ~hashheap (void);

            // copy assignment operator
            // minor issue: heap contains smart pointer which 
            //              discourages deep copying. unreference pair 
            //              when changing value
            // @param[in]   src     reference to hashheap object to copy from
            // @return      reference to this after copy assignment
            hashheap<K, V>& operator = (const hashheap<K, V>& src);

            // get pair with minimum key
            // @param[]     void
            // @return smart pointer of pairs removed
            //          null smart pointer if empty
            pairptr<K, V> get (void) const;

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
            dcontain::wrapper<V> put (K key, V value);

            // UNTESTED
            // insert all key-value pairs in other into this
            // @param[in]   other   reference to another hashheap
            // @return void
            void putAll (const hashheap<K, V>& other);

            // remove pair with minimum key
            // @param[]     void
            // @return smart pointer of pairs removed
            //          null smart pointer if empty
            pairptr<K, V> remove (void);

            // remove key-value association
            // @param[in]   key     Key in the key-value pair
            // @return wrapper object value associated with key, 
            // castable to false if there was no associated value
            // castable to true otherwise
            dcontain::wrapper<V> remove (K key);

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
            bool containsValue (V value, 
                equatable<V> eq = [](V left, V right) { return left == right; }) const;

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
        };

    #include "hashheap.cpp"
    }

#endif /* __HASH_HEAP__H */