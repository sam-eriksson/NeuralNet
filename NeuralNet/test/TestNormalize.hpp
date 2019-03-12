//
//  TestNormalize.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-28.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef TestNormalize_hpp
#define TestNormalize_hpp

#include <stdio.h>
#include "../model/Matrix.h"

namespace DeepNeural {
    
    class TestNormalize {
    public:
        TestNormalize();
        virtual ~TestNormalize();
        void run();
    private:
        Matrix testMatrix;
    };
}
#endif /* TestNormalize_hpp */
