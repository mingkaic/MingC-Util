//
//  gnode.hpp
//  dataContainer
//
//  description: generic node for all data container classes
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __GNODE__H
#define __GNODE__H

#include <cstdlib>

namespace dcontain
    {
    // abstract class
    template <class T>
    class gnode
        {
        protected:
            T data;
            virtual void dataInit(T data){this->data = data;}
        public:
            virtual ~gnode (void) {}
            virtual void cascadeDelete   (void) = 0;
            virtual gnode<T>* cascadeCopy (void) = 0;

            T getData()const{return data;}
        };
    }
    
#endif /* __GNODE__H */