//
//  Kernel.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-13.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "Kernel.hpp"
#include <chrono>

namespace DeepNeural {
    
    Kernel::Kernel() {
    }

    Kernel::~Kernel() {
    }

    void Kernel::seed(double low, double high, int width, int height) {
        auto start = std::chrono::system_clock::now();
        auto ts = start.time_since_epoch();
        long s = ts.count();
        srand (s);
        double range = high - low;
        for(int y=0; y<height; y++) {
            std::vector<double> row_vec;
            for(int x=0; x<width; x++) {
                double f = (double)rand() / RAND_MAX;
                double randomnumber = low + f * (high - low);
                row_vec.push_back(randomnumber);
            }
            addRow(row_vec);
        }
    }    
}
