//
//  Transform.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-15.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <stdio.h>
#include "../model/Matrix.h"
#include "../model/Kernel.hpp"

namespace DeepNeural {
    class Transform {
    public:
        Transform(Matrix in, Kernel ker);
        Transform(Matrix in, std::vector< Kernel > kers);
        Transform(Matrix in);
        Transform();
        virtual ~Transform();
        Matrix getOutput();
        
        void addOutputDerivativeRow(std::vector< double >  row);
        void setOutputDerivative(Matrix derivative);
        void setInputMatrix(Matrix in);
        Matrix getInputDerivative();
        
    private:

    protected:
        Matrix input;
        //Kernel kernel;
        Matrix output;
        std::vector< Kernel > kernels;
    };
}
#endif /* Transform_hpp */
