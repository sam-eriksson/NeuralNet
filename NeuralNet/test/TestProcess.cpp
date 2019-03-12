//
//  TestProcess.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-29.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "TestProcess.hpp"
#include <iostream>
#include "../model/Kernel.hpp"
#include "../transform/Normalize.hpp"
#include "../transform/TangentSigmoid.hpp"
#include "../image/Image.h"
#include "../image/ImageDataLoader.hpp"
#include "../transform/Sigmoid.hpp"
#include "../transform/SumProduct.hpp"
#include "../transform/Maxpool.hpp"


namespace DeepNeural {
    TestProcess::TestProcess() {
    }
    
    TestProcess::~TestProcess() {
    }
    
    void TestProcess::run(int argc, const char * argv[]) {
        //Get filename for jpg.
        std::string filename = "a.jpg";
        if (!(argc <2)) {
            filename = argv[1];
        }
        //Create an image in out framework
        Image image(filename);
        long height = image.getHeight();
        //Load jpg into our Matrices
        ImageDataLoader dataloader(image);
        Matrix red_matrix = dataloader.getRedMatrix();
        int value = red_matrix.getValue(2, 2);
        std::cout << "Height of Image : " << height << "\r\n";
        std::cout << "Red Pixel value at 2,2 : " << value << "\r\n";
        red_matrix.saveMatrix("test.txt");
        red_matrix.loadMatrix("test.txt");
        red_matrix.saveMatrix("test2.txt");
        //create a test kernel
        Kernel kernel;
        //kernel.seed(-1, 1, 3,3);
        kernel.loadMatrix("kernel.txt");
        /**
         * 1. Run the Red Matrix through a normalization
         * 2. Apply Sigmoid to normalized Matrix
         * 3. Apply Kernel (3x3) with stride =3 to One Matrix as SumProduct
         *
         */
        Normalize normalized(red_matrix);
        normalized.apply();
        normalized.getOutput().saveMatrix("normalized.txt");
        Sigmoid sigmoid(normalized.getOutput());
        sigmoid.apply();
        sigmoid.getOutput().saveMatrix("sigmoid.txt");
        TangentSigmoid tangentsigmoid(normalized.getOutput());
        tangentsigmoid.apply();
        tangentsigmoid.getOutput().saveMatrix("tangentsigmoid.txt");
        SumProduct sumproduct(sigmoid.getOutput(), kernel, 3);
        sumproduct.apply();
        sumproduct.getOutput().saveMatrix("sumproduct.txt");
        Maxpool maxpool(sumproduct.getOutput() ,2,2,0.001);
        maxpool.apply();
        Matrix max_matrix = maxpool.getOutput();
        max_matrix.saveMatrix("maxpool.txt");
        
        }
}
