//
//  main.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-11.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//
#include <ctime>
#include <chrono>
#include <iostream>

#include "model/Matrix.h"
#include "DeepNeural.h"
#include "test/TestNormalize.hpp"
#include "test/TestSumproduct.hpp"
#include "test/TestPad.hpp"
#include "test/TestLetters.hpp"
#include "test/TestSimple.hpp"

int main(int argc, const char * argv[]) {

    auto start = std::chrono::system_clock::now();
    DeepNeural::TestSimple test;
    test.run();
    //DeepNeural::TestLetters testletters;
    //testletters.test(argc, argv);
    //DeepNeural::TestNormalize tn;
    //tn.run();
    //DeepNeural::TestSumproduct sump;
    //sump.run();
    //DeepNeural::TestPad testpad;
    //testpad.run();
    
    auto end = std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    
    std::cout << "finished computation at " << std::ctime(&end_time)
    << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}


