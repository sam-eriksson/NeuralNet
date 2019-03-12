//
//  SoftmaxClassification.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-17.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef SoftmaxClassification_hpp
#define SoftmaxClassification_hpp

#include <stdio.h>
#include "Transform.hpp"

namespace DeepNeural {
    class SoftmaxClassification : public Transform  {
    public:
        SoftmaxClassification(Matrix in);
        virtual ~SoftmaxClassification();
        void apply();
        double backPropagation();
    private:
    protected:
    };
}
#endif /* SoftmaxClassification_hpp */
