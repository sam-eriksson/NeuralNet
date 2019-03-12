//
//  Sigmoid.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-15.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef Sigmoid_hpp
#define Sigmoid_hpp

#include <stdio.h>
#include "Transform.hpp"

namespace DeepNeural {
    class Sigmoid : public Transform  {
    public:
        Sigmoid(Matrix in);
        virtual ~Sigmoid();
        void apply();
    private:
        
    protected:

    };
}
#endif /* Sigmoid_hpp */
