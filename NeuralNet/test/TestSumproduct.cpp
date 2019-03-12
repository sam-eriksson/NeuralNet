//
//  TestSumproduct.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-29.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "TestSumproduct.hpp"
#include <iostream>
#include "../model/Kernel.hpp"
#include "../transform/SumProduct.hpp"

namespace DeepNeural {
    const std::string path = "/Users/sameriksson/temp/testing/";
    TestSumproduct::TestSumproduct() {
        const std::string filename = path + "matrix_test.txt";
        testMatrix.loadMatrix(filename );
        kernelA.loadMatrix(path +"matrix_test3.txt");
        kernelB.loadMatrix(path +"matrix_test3.txt");
    }
    
    TestSumproduct::~TestSumproduct() {
    }
    
    void TestSumproduct::run() {
        SumProduct sumproduct(testMatrix, kernelA);
        sumproduct.addKernel(kernelB);
        sumproduct.apply();
        Matrix matrix = sumproduct.getOutput();
        matrix.saveMatrix(path +"sumproduct_test.txt");
    }
}
