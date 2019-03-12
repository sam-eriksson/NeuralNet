//
//  TestPad.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-29.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "TestPad.hpp"
#include "../model/Matrix.h"
#include <iostream>

namespace DeepNeural {
    const std::string path = "/Users/sameriksson/temp/testing/";
    Matrix testMatrix;
    
    TestPad::TestPad() {
        const std::string filename = path + "matrix_test.txt";
        testMatrix.loadMatrix(filename );
    }
    
    TestPad::~TestPad() {
    }
    
    void TestPad::run() {
        testMatrix.padWith(20, 20, 9);
        testMatrix.saveMatrix(path+"pad_test.txt");
    }
}
