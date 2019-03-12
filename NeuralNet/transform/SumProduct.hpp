//
//  SumProduct.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-15.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef SumProduct_hpp
#define SumProduct_hpp

#include <stdio.h>
#include "Transform.hpp"

namespace DeepNeural {
    class SumProduct : public Transform {
    public:
        SumProduct(Matrix in, Kernel ker);
        SumProduct(Matrix in, Kernel ker, int stri);
        SumProduct(Matrix in, std::vector< Kernel > kers);
        SumProduct(Matrix in, std::vector< Kernel > kers, int stri);
        SumProduct();
        virtual ~SumProduct();
        void apply();
        void addKernel(Kernel ker);
        void derivative();
        //void addOutputDerivativeRow(std::vector< double >  row);
        //void setOutputDerivative(Matrix derivative);
        //void setInputMatrix(Matrix in);
        //Matrix getInputDerivative();
        void calculateNewKernel(double lr);
        void setConstruct(Matrix in, Kernel ker, int stri);
        void setConstruct(Matrix in, Kernel ker);
        Matrix getKernel(int kernum);
    private:
        void loopDerivative();
        int stride = 1;
        double getInputDerivative(long x, long y);
        double getKernelDerivative(long x, long y);
        double getOutputDerivative(long x, long y);
        long kw = 0;
        long kh = 0;
        long iw = 0;
        long ih = 0;
        long ow = 0;
        long oh = 0;
    };
}
#endif /* SumProduct_hpp */
