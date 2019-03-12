//
//  TestLetters.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-11-08.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef TestLetters_hpp
#define TestLetters_hpp

#include <stdio.h>
#include <string>
#include "../model/Kernel.hpp"
#include "../transform/SumProduct.hpp"

namespace DeepNeural {
    
    class TestLetters {
    public:
        TestLetters();
        virtual ~TestLetters();
        void test(int argc, const char * argv[]);
        void loadOrMakeKernels(const std::string model_directory);
    private:
        void saveKernels();
        void applySlopes();
        void calculateOutputs(int classnumber);
        /*double mse(double typ, double ty);
        double *  softmax(double numbers[]);*/
        /*std::vector<std::string> listFiles(const std::string directory, const std::string search_parameter);*/
        /*void read_directory(const std::string& name, std::vector<std::string>& v, const std::string search_parameter);*/
        /*void makeKernelOrLoad( Kernel * kernel, double low, double hi, int width, int height, std::string extraname, const std::string model_directory);*/
        void makeDense(long red_width,
                       long red_height,
                       long blue_width,
                       long blue_height,
                       long green_width,
                       long green_height,
                       std::string model_directory);
        
        Kernel kernel3_3_R1A1;
        Kernel kernel3_3_R1A2;
        Kernel kernel2_2_R2A1;
        Kernel kernel2_2_R2A2;
        Kernel kernel2_2_R2A3;
        Kernel kernel2_2_R3A1;
        Kernel kernel2_2_R3A2;
        Kernel kernel3_3_G1A1;
        Kernel kernel3_3_G1A2;
        Kernel kernel2_2_G2A1;
        Kernel kernel2_2_G2A2;
        Kernel kernel2_2_G2A3;
        Kernel kernel2_2_G3A1;
        Kernel kernel2_2_G3A2;
        Kernel kernel3_3_B1A1;
        Kernel kernel3_3_B1A2;
        Kernel kernel2_2_B2A1;
        Kernel kernel2_2_B2A2;
        Kernel kernel2_2_B2A3;
        Kernel kernel2_2_B3A1;
        Kernel kernel2_2_B3A2;
        
        Kernel kernel_dense_w_red[3];
        Kernel kernel_dense_w_green[3];
        Kernel kernel_dense_w_blue[3];
        
        SumProduct redS0;
        SumProduct greenS0;
        SumProduct blueS0;
        SumProduct redS1;
        SumProduct greenS1;
        SumProduct blueS1;
        SumProduct redS2;
        SumProduct greenS2;
        SumProduct blueS2;
        
        SumProduct blue_sumB3A;
        SumProduct green_sumG3A;
        SumProduct red_sumR3A;
        
        SumProduct blue_sumB2A;
        SumProduct green_sumG2A;
        SumProduct red_sumR2A;
        
        SumProduct blue_sumB1A;
        SumProduct red_sumR1A;
        SumProduct green_sumG1A;
        
        //Define classes a,b,c for the letters used
        const std::string classes[3] = {"a", "b", "c"};
        double classvalues[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
        double onepartencoded[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
        //image max width and height
        const long image_max_width = 153;
        const long image_max_height = 153;
        //define directory with loadable models
        const std::string train_directory = "/Users/sameriksson/Documents/handwriting/train";
        const std::string test_directory = "/Users⁩/sameriksson⁩/Documents⁩/handwriting⁩/test";
        //const std::string model_directory = ".";
        const std::string model_directory = "/Users/sameriksson/Documents/handwriting/models2";
        const std::string logs_directory = "/Users/sameriksson/Documents/handwriting/logs";
    };
} /* namespace DeepNeural */
#endif /* TestLetters_hpp */
