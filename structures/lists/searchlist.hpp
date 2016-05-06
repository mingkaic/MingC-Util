//
//  searchlist.hpp
//  List
//  Description: fairly inefficient list 
//  that uses linear search
//
//  Created by Ming Kai Chen on 2014-07-15.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#pragma once
#ifndef __SEARCH_LIST__H
#define __SEARCH_LIST__H

#include "deque.hpp"
#include <iostream>

template <class T>
class searchlist : public deque<T>
    {
    public:
        searchlist() {}
        searchlist(const searchlist& src);
        virtual ~searchlist() {}
        searchlist<T>& operator = (const searchlist<T>& src);
        
        signed search(T elem); // find and return the index of the node containing elem -1 if not found
        void nInsert(T elem, size_t N);
        T nRemove(size_t N);
        T nPeek(size_t N) const;
        // returns replaced data
        T nReplace(T elem, size_t N);

        friend std::ostream& operator << (std::ostream& out, const searchlist& list) 
            {
            for (binode<T>* buffer = list.head; NULL != buffer; buffer = buffer->next) 
                {
                out << buffer->getData() << " ";
                }
            out << std::endl;
            return out;
            }
        
        size_t size() const;
    };

#include "searchlist.cpp"

#endif /* __SEARCH_LIST__H */