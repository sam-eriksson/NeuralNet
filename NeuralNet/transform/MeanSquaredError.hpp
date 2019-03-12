//
//  MeanSquaredError.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-24.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef MeanSquaredError_hpp
#define MeanSquaredError_hpp

#include <stdio.h>
#include "Transform.hpp"

namespace DeepNeural {
    class MeanSquaredError : public Transform  {
    public:
        MeanSquaredError(Matrix in);
        virtual ~MeanSquaredError();
        void apply();
        double backPropagation();
    private:
        
    protected:
        
    };
}
#endif /* MeanSquaredError_hpp */
