//
//  Normalize.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-15.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef Normalize_hpp
#define Normalize_hpp

#include <stdio.h>
#include "Transform.hpp"

namespace DeepNeural {
    class Normalize : public Transform  {
    public:
        Normalize(Matrix in);
        virtual ~Normalize();
        void apply();
        double backPropagation();
        double mean=0;
        double standdeviation=0;
    protected:
        
    };
}
#endif /* Normalize_hpp */
