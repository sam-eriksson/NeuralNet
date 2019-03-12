//
//  Transform.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-15.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "Transform.hpp"
#include "../model/Matrix.h"
#include "../model/Kernel.hpp"

namespace DeepNeural {
    
    Transform::Transform(Matrix in, Kernel ker) {
        kernels.push_back(ker);
        input = in;
    }
    
    Transform::Transform(Matrix in, std::vector< Kernel > kers) {
        kernels = kers;
        input = in;
    }
    
    Transform::Transform(Matrix in) {
        input = in;
    }
    
    Transform::Transform() {
    }
    
    Transform::~Transform() {
    }
    
    Matrix Transform::getOutput() {
        return output;
    }
    
    void Transform::addOutputDerivativeRow(std::vector< double >  row) {
        output.addDerivativeRow(row);
    }
    
    void Transform::setOutputDerivative(Matrix derivative) {
        output.initializeDerivative(derivative.getWidth(), derivative.getHeight(), 0);
        for (int y=0; y<derivative.getHeight(); y++) {
            for(int x=0; x< derivative.getWidth(); x++) {
                output.setValueDerivative(x, y, derivative.getValue(x, y));
            }
        }
    }
    
    Matrix Transform::getInputDerivative() {
        return input.getDerivative();
    }
    
    void Transform::setInputMatrix(Matrix in) {
        input = in;
    }
}
