//
//  TestNormalize.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-28.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "TestNormalize.hpp"
#include "../model/Matrix.h"
#include <iostream>
#include "../transform/Normalize.hpp"
#include "../transform/Sigmoid.hpp"

namespace DeepNeural {
    TestNormalize::TestNormalize() {
        const std::string filename = "normalize_test.txt";
        testMatrix.loadMatrix(filename );
    }
    
    TestNormalize::~TestNormalize() {
    }
    
    void TestNormalize::run() {
        std::cout<<testMatrix.getWidth()<<std::endl;
        Normalize normalize(testMatrix);
        normalize.apply();
        Matrix output = normalize.getOutput();
        std::cout<<normalize.mean << std::endl;
        std::cout<<normalize.standdeviation<< std::endl;
        output.saveMatrix("normalize_result.txt");
        Sigmoid sigmoid(output);
        sigmoid.apply();
        Matrix outputsigmoid = sigmoid.getOutput();
        outputsigmoid.saveMatrix("sigmoid_result.txt");
    }
}
