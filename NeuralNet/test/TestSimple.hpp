//
//  TestSimple.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-11-08.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef TestSimple_hpp
#define TestSimple_hpp

#include <stdio.h>
#include "../model/Kernel.hpp"
#include "../transform/SumProduct.hpp"

namespace DeepNeural {
    
    class TestSimple {
    public:
        TestSimple();
        virtual ~TestSimple();
        void run();
    private:
        void firstLoopSumProducts();
        void softMaxError();
        void calculateDerivative();
        void calculateNewKernels();
        void loopSumProducts();
        Matrix simple;
        Kernel top;
        Kernel side;
        Kernel top_a_dense;
        Kernel top_b_dense;
        Kernel side_a_dense;
        Kernel side_b_dense;
        
        SumProduct sumproduct_top;
        SumProduct sumproduct_side;
        SumProduct finalatop;
        SumProduct finalaside;
        SumProduct finalbtop;
        SumProduct finalbside;
        
        double a = double(0);
        double b = double(0);
        double ase = double(0);
        double bse = double(0);
        double softa = double(0);
        double softb = double(0);
    };
}
#endif /* TestSimple_hpp */
