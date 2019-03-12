//
//  Maxpool.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-17.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "Maxpool.hpp"
namespace DeepNeural {
    
    Maxpool::Maxpool(Matrix in, int xbox, int ybox) : Transform(in) {
        x_delta = xbox;
        y_delta = ybox;
    }
    
    Maxpool::Maxpool(Matrix in, int xbox, int ybox, double in_cutoff) : Transform(in) {
        x_delta = xbox;
        y_delta = ybox;
        cutoff = in_cutoff;
    }
    
    Maxpool::~Maxpool() {
    }
    
    void Maxpool::apply() {
        output.clearValues();
        output.clearDerivativeValues();
        for(int y=0; y+y_delta<input.getHeight(); y=y+y_delta)
        {
            std::vector<double> row_value;
            for(int x=0; x+x_delta<input.getWidth(); x=x+x_delta) {
                 double singlepoint =cutoff;
                 for(int yb=0; yb<y_delta; yb++){
                    for (int xb=0; xb<x_delta; xb++) {
                        double val= input.getValue(x+xb, y+yb);
                        if (val<cutoff) singlepoint =0;
                        else if (singlepoint<val) singlepoint = val;
                    }
                }
                row_value.push_back(singlepoint);
            }
            output.addRow(row_value);
        }
    }
    
    void Maxpool::derivative() {
        long iw = input.getWidth();
        long ih = input.getHeight();
        input.initializeDerivative(iw, ih, 0);
        for (int y=0; y<ih; y++) {
            for (int x=0; x<iw; x++) {
                long oposx = x/x_delta;
                long oposy = y/y_delta;
                if (oposx<output.getWidth() && oposy<output.getHeight()) {
                    if (input.getValue(x,y) == output.getValue(oposx, oposy) ) {
                        input.setValueDerivative(x, y, output.getValueDerivative(oposx, oposy));
                        
                    }
                }
            }
        }
    }
}
