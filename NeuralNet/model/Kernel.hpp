//
//  Kernel.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-13.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef Kernel_hpp
#define Kernel_hpp

#include <stdio.h>
#include "Matrix.h"

namespace DeepNeural {
    class Kernel : public Matrix {
public:
    Kernel();
    virtual ~Kernel();
    void seed(double low, double high, int width, int height);
};
}
#endif /* Kernel_hpp */
