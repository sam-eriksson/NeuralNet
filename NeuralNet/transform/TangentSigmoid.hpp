//
//  TangentSigmoid.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-17.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef TangentSigmoid_hpp
#define TangentSigmoid_hpp

#include <stdio.h>
#include "Transform.hpp"

namespace DeepNeural {
    class TangentSigmoid : public Transform  {
    public:
        TangentSigmoid(Matrix in);
        virtual ~TangentSigmoid();
        void apply();
    private:
        
    protected:
        
    };
}
#endif /* TangentSigmoid_hpp */
