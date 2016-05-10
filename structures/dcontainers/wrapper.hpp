//
//  wrapper.hpp
//  dataContainer
//
//  description: data container with automatically unwrap via implicit casting
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __SWRAP__H
#define __SWRAP__H

#include <iostream>
namespace dcontain
    {
    template <class T>
    class wrapper
        {
        public:
            T value;
            bool good = true;
            wrapper (void) : good(false) {}
            wrapper (T data) : value(data) {}
            virtual ~wrapper (void) {}

            wrapper<T>& operator = (const wrapper<T>& other)
                {
                if (this != &other)
                    {
                    value = other.value;
                    good = other.good;
                    }
                return *this;
                }
            operator T() const
                {
                T ret = value;
                return ret;
                }
            operator bool() const
                {
                return good;
                }
        };
    }
    
#endif /* __SWRAP__H */