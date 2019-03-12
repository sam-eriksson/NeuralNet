//
//  ImageDataLoader.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-12.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef ImageDataLoader_hpp
#define ImageDataLoader_hpp

#include <stdio.h>
#include "Image.h"
#include "../model/Matrix.h"

namespace DeepNeural {
    
    class ImageDataLoader {
    public:
        ImageDataLoader(Image image);
        virtual ~ImageDataLoader();
        Matrix getRedMatrix();
        Matrix getBlueMatrix();
        Matrix getGreenMatrix();
    private:
        Matrix red_matrix;
        Matrix green_matrix;
        Matrix blue_matrix;
        
    };
    
} /* namespace DeepNeural */
#endif /* ImageDataLoader_hpp */
