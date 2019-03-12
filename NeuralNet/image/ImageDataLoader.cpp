//
//  ImageDataLoader.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-12.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "ImageDataLoader.hpp"
#include "Image.h"
#include <iostream>
#include "Matrix.h"
#include <vector>

namespace DeepNeural {
    
    ImageDataLoader::ImageDataLoader(Image image) {
        long height = image.getHeight();
        long width = image.getWidth();
        for(int y=0; y<height; y++) {
            std::vector<double> vec_row_red;
            std::vector<double> vec_row_blue;
            std::vector<double> vec_row_green;
            for(int x=0; x<width; x++) {
                auto vec = image.getPixel(x, y);
                if ( vec.size() == 1 )
                {   // monochrome image
                    vec[0];
                }
                if ( vec.size() == 3 )
                {
                    vec_row_red.push_back( vec[0] );
                    vec_row_green.push_back( vec[1] );
                    vec_row_blue.push_back( vec[2] );
                }
                //
            }
            red_matrix.addRow(vec_row_red);
            blue_matrix.addRow(vec_row_blue);
            green_matrix.addRow(vec_row_green);
        }
    }
    
    ImageDataLoader::~ImageDataLoader() {
    }
    
    Matrix ImageDataLoader::getRedMatrix() {
        return red_matrix;
    }
    
    Matrix ImageDataLoader::getBlueMatrix() {
        return blue_matrix;
    }
    
    Matrix ImageDataLoader::getGreenMatrix() {
        return green_matrix;
    }
} /* namespace DeepNeural */
