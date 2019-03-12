//
//  SoftmaxClassification.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-17.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "SoftmaxClassification.hpp"
#include "tgmath.h"
namespace DeepNeural {

    SoftmaxClassification::SoftmaxClassification(Matrix in) : Transform(in) {
    }

    SoftmaxClassification::~SoftmaxClassification() {
    }

    void SoftmaxClassification::apply() {
        // Should only be a 1 x N matrix
        // we will just use a row.
        std::vector<double> row;
        double total = 0;
        for ( int i=0; i<input.getWidth(); i++) {
            double value = input.getValue(i, 0);
            total = total + exp(value);
            row.push_back(exp(value));
        }
        std::vector<double> rowt;
        for ( int j=0; j<row.size(); j++) {
            double val = row.at(j);
            double softmax = val/total;
            rowt.push_back(softmax);
        }
        output.addRow(rowt);
    }
    
    double SoftmaxClassification::backPropagation() {
        return double(0);
    }
}
