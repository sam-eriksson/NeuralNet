//
//  Dropout.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-17.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef Dropout_hpp
#define Dropout_hpp

#include <stdio.h>
#include "Transform.hpp"

namespace DeepNeural {
    class Dropout : public Transform  {
    public:
        Dropout(Matrix in, double dropoutrate);
        virtual ~Dropout();
        void apply();
    private:
        double dropoutrate;
        void setZero(int x, int y);
    protected:
        
    };
}
#endif /* Dropout_hpp */
