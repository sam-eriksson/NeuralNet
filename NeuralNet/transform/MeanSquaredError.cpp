//
//  MeanSquaredError.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-24.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "MeanSquaredError.hpp"
#include "tgmath.h"

namespace DeepNeural {
    
    MeanSquaredError::MeanSquaredError(Matrix in) : Transform(in) {
        input = in;
    }

    MeanSquaredError::~MeanSquaredError() {
    }
    
    void MeanSquaredError::apply() {
        // sum of (( mean - y )^2 )/2*observations
        
        //calculate mean
        double total=double(0);
        double observations = 0;
        for(int i=0; i < input.getWidth(); i++) {
            total =  total + input.getValue(i, 0);
            observations = observations + 1;
        }
        double mean = total/observations;
        
        //calculate mse
        double mse =0;
        for(int j=0; input.getWidth(); j++) {
            //2 removed since it is only used for simplification of the derivative
            mse = mse + pow((mean - input.getValue(j, 0)),2)/(observations);
        }
        
        std::vector<double> row;
        row.push_back(mse);
        output.addRow(row);
    }
    
    double MeanSquaredError::backPropagation() {
        //derivative function ...
        // 
        return double(0);
    }

}
