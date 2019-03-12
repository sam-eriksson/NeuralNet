//
//  TestSumproduct.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-29.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef TestSumproduct_hpp
#define TestSumproduct_hpp

#include <stdio.h>
#include "../model/Matrix.h"
#include "../model/Kernel.hpp"

namespace DeepNeural {
    
    class TestSumproduct {
    public:
        TestSumproduct();
        virtual ~TestSumproduct();
        void run();
    private:
        Matrix testMatrix;
        Kernel kernelA;
        Kernel kernelB;
    };
}
#endif /* TestSumproduct_hpp */
