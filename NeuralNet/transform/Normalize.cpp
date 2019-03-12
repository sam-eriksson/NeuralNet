//
//  Normalize.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-15.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "Normalize.hpp"
#include "tgmath.h"

namespace DeepNeural {
    
    Normalize::Normalize(Matrix in) : Transform(in) {
        input = in;
    }
    
    
    Normalize::~Normalize() {
    }
    
    void Normalize::apply() {
        output.clearValues();
        output.clearDerivativeValues();
        long width = input.getWidth();
        long height = input.getHeight();
        double max = input.getMax();
        double min = input.getMinimum();
        for (long y=0; y<height; y++) {
            std::vector<double> row_double;
            for(long x=0; x<width;x++) {
                double normalized = (input.getValue(x,y)-min)/(max-min);
                row_double.push_back(normalized);
            }
            output.addRow(row_double);
        }
        
        
    }

    double Normalize::backPropagation() {
        return double(0);
    }
}
