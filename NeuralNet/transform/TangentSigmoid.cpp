//
//  TangentSigmoid.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-17.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "TangentSigmoid.hpp"
#include "tgmath.h"

namespace DeepNeural {
    
    TangentSigmoid::TangentSigmoid(Matrix in) : Transform(in) {
        input = in;
    }
    
    
    TangentSigmoid::~TangentSigmoid() {
    }
    
    void TangentSigmoid::apply() {
        long width = input.getWidth();
        long height = input.getHeight();
        for (long y=0; y<height; y++) {
            std::vector< double > row_value;
            for(long x=0; x<width;x++) {
                double value = input.getValue(x, y);
                double double_converted = 1/(exp(-value)+1);
                row_value.push_back(double_converted);
            }
            output.addRow(row_value);
        }
    }
}
