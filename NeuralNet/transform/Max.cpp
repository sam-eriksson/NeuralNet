//
//  Max.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-31.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "Max.hpp"
#include <string>

namespace DeepNeural {
    
    Max::Max(Matrix in, double _bottom) : Transform(in) {
        bottom = _bottom;
    }
    
    Max::~Max() {
    }
    
    void Max::apply() {
        output.clearValues();
        output.clearDerivativeValues();
        long height = input.getHeight();
        long width = input.getWidth();
        for(long y=0; y<height ; y++ ) {
            std::vector<double> row;
            for (long x=0; x<width; x++) {
                double value = input.getValue(x, y);
                if (value< bottom) value = 0;
                row.push_back(value);
            }
            output.addRow(row);
        }
    }
    
    void Max::derivative() {
        long iw = input.getWidth();
        long ih = input.getHeight();
        input.initializeDerivative(iw, ih, 0);
        for (int y=0; y<ih; y++) {
            for (int x=0; x<iw; x++) {
                if (input.getValue(x,y) > bottom ) {
                    input.setValueDerivative(x, y, output.getValueDerivative(x, y));
                }
            }
        }
    }
}
