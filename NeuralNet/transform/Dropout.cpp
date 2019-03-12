//
//  Dropout.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-17.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "Dropout.hpp"
#include <string>

namespace DeepNeural {
    
    Dropout::Dropout(Matrix in, double idropoutrate) : Transform(in) {
        if (idropoutrate>1) dropoutrate =1;
        else if (idropoutrate<0) dropoutrate =0;
    }
    
    Dropout::~Dropout() {
    }
    
    void Dropout::apply() {
        srand (time(NULL));
        std::string points;
        long totalpoints = input.getWidth() * input.getHeight();
        long pointstoremove = totalpoints * dropoutrate;
        for(int i=0; i<pointstoremove; i++) {
            long xrange =input.getWidth();
            long xlow =0;
            long yrange =input.getHeight();
            long ylow =0;
            long x = rand() % xrange + xlow;
            long y = rand() % yrange + ylow;
            points = points + "("+std::to_string(x)+","+std::to_string(y)+")";
        }
        for (int yu=0; yu<input.getHeight();yu++) {
            std::vector<double> row_value;
            for (int xu=0; xu<input.getWidth(); xu++) {
                std::string point = "("+std::to_string(xu)+","+std::to_string(yu)+")";
                double value;
                if (points.find(point)) {
                    value=0;
                } else {
                    value = input.getValue(xu, yu);
                }
                row_value.push_back(value);
            }
            output.addRow(row_value);
        }
    }
}
