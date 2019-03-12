//
//  TestLetters.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-11-08.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "TestLetters.hpp"
#include <iostream>
#include "../externalheader/jpeglib.h"
#include <string>
#include <iostream>
#include "../image/Image.h"
#include "../image/ImageDataLoader.hpp"
#include "../model/Matrix.h"
#include "../model/Kernel.hpp"
#include "../transform/Normalize.hpp"
#include "../transform/Sigmoid.hpp"
#include "../transform/SumProduct.hpp"
#include "../transform/TangentSigmoid.hpp"

#include <sys/types.h>
#include <dirent.h>
#include "../transform/Maxpool.hpp"
#include "../transform/Max.hpp"
#include "../transform/SoftmaxClassification.hpp"
#include "tgmath.h"
#include "../utility/Utility.hpp"
#include "../transform/Transform.hpp"

namespace DeepNeural {
    
    TestLetters::TestLetters() {
    }
    
    TestLetters::~TestLetters() {
        
    }
    
    void TestLetters::test(int argc, const char * argv[]) {
        //create seed kernels if no kernels exists (check first and load if they exist)
        loadOrMakeKernels(model_directory);
        makeDense(5,
                  5,
                  5,
                  5,
                  5,
                  5,
                  model_directory);
        //load training files and loop through
        std::vector<std::vector<std::string>> trainfilesclasses;
        //long maxfiles = 0;
        Utility utility;
        /*for(int classnumber=0; classnumber < 3; classnumber++) {
            std::vector<std::string> trainfiles = utility.listFiles(train_directory+"/"+classes[classnumber], ".jpg");
            trainfilesclasses.push_back(trainfiles);
            if (maxfiles<trainfiles.size()) maxfiles = trainfiles.size();
        }*/
        for(int classnumber=0; classnumber < 3; classnumber++) {
            std::vector<std::string> trainfiles = utility.listFiles(train_directory+"/"+classes[classnumber], ".jpg");
            for(long filenumber=0; filenumber<trainfiles.size(); filenumber++) {
                //load individual train file
                //break into R,G,B matrix
                //Load jpg into our Matrices
                
                Image image(train_directory+"/"+classes[classnumber]+"/"+trainfiles.at(filenumber));
                ImageDataLoader dataloader(image);
                Matrix red_matrix = dataloader.getRedMatrix();
                Matrix blue_matrix = dataloader.getBlueMatrix();
                Matrix green_matrix = dataloader.getGreenMatrix();
                
                //pad with 0 to max width and height.
                //need to fix not working
                red_matrix.padWith(image_max_width, image_max_height, 255);
                green_matrix.padWith(image_max_width, image_max_height, 255);
                blue_matrix.padWith(image_max_width, image_max_height, 255);
                red_matrix.invert(255);
                green_matrix.invert(255);
                blue_matrix.invert(255);
                
                //normalize R,G,B matrix
                Normalize red_normalized(red_matrix);
                red_normalized.apply();
                Normalize green_normalized(red_matrix);
                green_normalized.apply();
                Normalize blue_normalized(red_matrix);
                blue_normalized.apply();
                
                Max red_max(red_normalized.getOutput(),0);
                red_max.apply();
                Max green_max(green_normalized.getOutput(),0);
                green_max.apply();
                Max blue_max(blue_normalized.getOutput(),0);
                blue_max.apply();
                
                Matrix redsmatrix=red_max.getOutput();
                Matrix greensmatrix=green_max.getOutput();
                Matrix bluesmatrix=blue_max.getOutput();
                
                //sigmoid R,G,B Matrix
                /*Sigmoid red_sigmoid(red_max.getOutput());
                red_sigmoid.apply();
                Sigmoid green_sigmoid(green_max.getOutput());
                green_sigmoid.apply();
                Sigmoid blue_sigmoid(red_max.getOutput());
                blue_sigmoid.apply();
                
                Matrix redsmatrix=red_sigmoid.getOutput();
                Matrix greensmatrix=green_sigmoid.getOutput();
                Matrix bluesmatrix=blue_sigmoid.getOutput();*/
                
                // Red channel
                //sumproduct level 1 R
                //SumProduct red_sumR1A(redsmatrix, kernel3_3_R1A1, 3);
                red_sumR1A.setConstruct(redsmatrix, kernel3_3_R1A1, 3);
                //red_sumR1A.addKernel(kernel3_3_R1A2);
                red_sumR1A.apply();
                
                Max max1r(red_sumR1A.getOutput(), double(-0.5));
                max1r.apply();
                
                //sumproduct level 2 R
                //SumProduct red_sumR2A(max1r.getOutput(), kernel2_2_R2A1, 2);
                red_sumR2A.setConstruct(max1r.getOutput(), kernel2_2_R2A1, 2);
                //red_sumR2A.addKernel(kernel2_2_R2A2);
                //red_sumR2A.addKernel(kernel2_2_R2A3);
                red_sumR2A.apply();
                
                Max max2r(red_sumR2A.getOutput(), double(-0.5));
                max2r.apply();
                
                //sumproduct level 3 R
                //SumProduct red_sumR3A(max2r.getOutput(), kernel2_2_R3A1, 2);
                red_sumR3A.setConstruct(max2r.getOutput(), kernel2_2_R3A1, 2);
                //red_sumR3A.addKernel(kernel2_2_R3A2);
                red_sumR3A.apply();
                
                // Green channel
                //sumproduct level 1 G
                //SumProduct green_sumG1A(greensmatrix, kernel3_3_G1A1, 3);
                green_sumG1A.setConstruct(greensmatrix, kernel3_3_G1A1, 3);
                //green_sumG1A.addKernel(kernel3_3_G1A2);
                green_sumG1A.apply();
                
                Max max1g(green_sumG1A.getOutput(), double(-0.5));
                max1g.apply();
                
                //sumproduct level 2 G
                //SumProduct green_sumG2A(max1g.getOutput(), kernel2_2_G2A1, 2);
                green_sumG2A.setConstruct(max1g.getOutput(), kernel2_2_G2A1, 2);
                //green_sumG2A.addKernel(kernel2_2_G2A2);
                //green_sumG2A.addKernel(kernel2_2_G2A3);
                green_sumG2A.apply();
                
                Max max2g(green_sumG2A.getOutput(), double(-0.5));
                max2g.apply();
                
                //sumproduct level 3 G
                //SumProduct green_sumG3A(max2g.getOutput(), kernel2_2_G3A1, 2);
                green_sumG3A.setConstruct(max2g.getOutput(), kernel2_2_G3A1, 2);
                //green_sumG3A.addKernel(kernel2_2_G3A2);
                green_sumG3A.apply();
                
                // Blue channel
                //sumproduct level 1 B
                //SumProduct blue_sumB1A(bluesmatrix, kernel3_3_B1A1, 3);
                blue_sumB1A.setConstruct(bluesmatrix, kernel3_3_B1A1, 3);
                //blue_sumB1A.addKernel(kernel3_3_B1A2);
                blue_sumB1A.apply();
                
                Max max1b(blue_sumB1A.getOutput(), double(-0.5));
                max1b.apply();
                
                //sumproduct level 2 B
                //SumProduct blue_sumB2A(max1b.getOutput(), kernel2_2_B2A1, 2);
                blue_sumB2A.setConstruct(max1b.getOutput(), kernel2_2_B2A1, 2);
                //blue_sumB2A.addKernel(kernel2_2_R2A2);
                //blue_sumB2A.addKernel(kernel2_2_R2A3);
                blue_sumB2A.apply();
                
                Max max2b(blue_sumB2A.getOutput(), double(-0.5));
                max2b.apply();
                
                //sumproduct level 3 B
                //SumProduct blue_sumB3A(max2b.getOutput(), kernel2_2_B3A1, 2);
                blue_sumB3A.setConstruct(max2b.getOutput(), kernel2_2_B3A1, 2);
                //blue_sumB3A.addKernel(kernel2_2_B3A2);
                blue_sumB3A.apply();
                
                //sumproduct class
                Maxpool blueA(blue_sumB3A.getOutput(), 2, 2);
                blueA.apply();
                Maxpool greenA(green_sumG3A.getOutput(), 2, 2);
                greenA.apply();
                Maxpool redA(red_sumR3A.getOutput(), 2, 2);
                redA.apply();
                
                //SumProduct redS0(redA.getOutput(), kernel_dense_w_red[0] );
                redS0.setConstruct(redA.getOutput(), kernel_dense_w_red[0] );
                redS0.apply();
                //SumProduct greenS0(greenA.getOutput(), kernel_dense_w_green[0]  );
                greenS0.setConstruct(greenA.getOutput(), kernel_dense_w_green[0]  );
                greenS0.apply();
                //SumProduct blueS0(blueA.getOutput(), kernel_dense_w_blue[0]  );
                blueS0.setConstruct(blueA.getOutput(), kernel_dense_w_blue[0]  );
                blueS0.apply();
                
                //SumProduct redS1(redA.getOutput(), kernel_dense_w_red[1] );
                redS1.setConstruct(redA.getOutput(), kernel_dense_w_red[1] );
                redS1.apply();
                //SumProduct greenS1(greenA.getOutput(), kernel_dense_w_green[1]  );
                greenS1.setConstruct(greenA.getOutput(), kernel_dense_w_green[1]  );
                greenS1.apply();
                //SumProduct blueS1(blueA.getOutput(), kernel_dense_w_blue[1]  );
                blueS1.setConstruct(blueA.getOutput(), kernel_dense_w_blue[1]  );
                blueS1.apply();
                
                //SumProduct redS2(redA.getOutput(), kernel_dense_w_red[2] );
                redS2.setConstruct(redA.getOutput(), kernel_dense_w_red[2] );
                redS2.apply();
                //SumProduct greenS2(greenA.getOutput(), kernel_dense_w_green[2]  );
                greenS2.setConstruct(greenA.getOutput(), kernel_dense_w_green[2]  );
                greenS2.apply();
                //SumProduct blueS2(blueA.getOutput(), kernel_dense_w_blue[2]  );
                blueS2.setConstruct(blueA.getOutput(), kernel_dense_w_blue[2]  );
                blueS2.apply();
                
                
                Matrix redmatrix0 = redS0.getOutput();
                Matrix bluematrix0 = blueS0.getOutput();
                Matrix greenmatrix0 = greenS0.getOutput();
                
                Matrix redmatrix1 = redS1.getOutput();
                Matrix bluematrix1 = blueS1.getOutput();
                Matrix greenmatrix1 = greenS1.getOutput();
                
                Matrix redmatrix2 = redS2.getOutput();
                Matrix bluematrix2 = blueS2.getOutput();
                Matrix greenmatrix2 = greenS2.getOutput();
                
                double value0 = redmatrix0.getValue(0, 0) + bluematrix0.getValue(0, 0) + greenmatrix0.getValue(0,0);
                double value1 = redmatrix1.getValue(0, 0) + bluematrix1.getValue(0, 0) + greenmatrix1.getValue(0,0);
                double value2 = redmatrix2.getValue(0, 0) + bluematrix2.getValue(0, 0) + greenmatrix2.getValue(0,0);
                
                double values[3] = {value0, value1, value2};
                double * softmaxval = utility.softmax(values);
                
                double sevalues[3] = { utility.se(onepartencoded[classnumber][0], *(softmaxval+0) ),
                    utility.se(onepartencoded[classnumber][1], *(softmaxval+1) ),
                    utility.se(onepartencoded[classnumber][2], *(softmaxval+2) )
                };
                
                std::string output = classes[0] + ":" + std::to_string(*(softmaxval+0)) + " should be " + std::to_string(onepartencoded[classnumber][0]) + " se " + std::to_string(sevalues[0]);
                std::string output1 = classes[1] + ":" + std::to_string(*(softmaxval+1)) + " should be " + std::to_string(onepartencoded[classnumber][1]) + " se " + std::to_string(sevalues[1]);
                std::string output2 = classes[2] + ":" + std::to_string(*(softmaxval+2)) + " should be " + std::to_string(onepartencoded[classnumber][2]) + " se " + std::to_string(sevalues[2]);
                
                std::cout << std::endl;
                std::cout << output <<std::endl;
                std::cout << output1 <<std::endl;
                std::cout << output2 <<std::endl;
                std::cout << std::endl;
                
                //utility.log(output + "\n" + output1 + "\n" +output2 , logs_directory+"/log.txt");
                
                //Now calculate derivatives
                Utility util;
                double dse[] = {util.dse(sevalues[0], onepartencoded[classnumber][0]),
                    util.dse(sevalues[1], onepartencoded[classnumber][1]),
                    util.dse(sevalues[2], onepartencoded[classnumber][2])
                };

                double dsoft[] = { util.dsoftmax(*(softmaxval+0) ,  onepartencoded[classnumber][0] ==1),
                    util.dsoftmax(*(softmaxval+1) , onepartencoded[classnumber][1] ==1),
                    util.dsoftmax(*(softmaxval+2) , onepartencoded[classnumber][2] ==1)
                };
                
                double total_derivative[] = { dse[0] * dsoft[0],
                    dse[1] * dsoft[1],
                    dse[2] * dsoft[2]
                };
                
                std::cout << " " << dse[0] <<" : " << dse[1] << " : " << dse[2] << std::endl;
                
                std::vector<double> row;
                row.push_back(total_derivative[0]);
                std::vector<double> row1;
                row1.push_back(total_derivative[1]);
                std::vector<double> row2;
                row2.push_back(total_derivative[2]);
                
                redS0.addOutputDerivativeRow(row);
                greenS0.addOutputDerivativeRow(row);
                blueS0.addOutputDerivativeRow(row);
                redS1.addOutputDerivativeRow(row1);
                greenS1.addOutputDerivativeRow(row1);
                blueS1.addOutputDerivativeRow(row1);
                redS2.addOutputDerivativeRow(row2);
                greenS2.addOutputDerivativeRow(row2);
                blueS2.addOutputDerivativeRow(row2);
                
                redS0.derivative();
                greenS0.derivative();
                blueS0.derivative();
                redS1.derivative();
                greenS1.derivative();
                blueS1.derivative();
                redS2.derivative();
                greenS2.derivative();
                blueS2.derivative();
                
                //Max Pool Derivative .. update using first dense weight matrix.
                //Need Logic here for using other paths.
                
                if (classnumber==0) {
                    redA.setOutputDerivative(redS0.Transform::getInputDerivative());
                    blueA.setOutputDerivative(blueS0.Transform::getInputDerivative());
                    greenA.setOutputDerivative(greenS0.Transform::getInputDerivative());
                } else if (classnumber ==1 ) {
                    redA.setOutputDerivative(redS1.Transform::getInputDerivative());
                    blueA.setOutputDerivative(blueS1.Transform::getInputDerivative());
                    greenA.setOutputDerivative(greenS1.Transform::getInputDerivative());
                } else {
                    redA.setOutputDerivative(redS2.Transform::getInputDerivative());
                    blueA.setOutputDerivative(blueS2.Transform::getInputDerivative());
                    greenA.setOutputDerivative(greenS2.Transform::getInputDerivative());
                }
                redA.derivative();
                blueA.derivative();
                greenA.derivative();
                
                blue_sumB3A.setOutputDerivative(blueA.getInputDerivative());
                green_sumG3A.setOutputDerivative(greenA.getInputDerivative());
                red_sumR3A.setOutputDerivative(redA.getInputDerivative());
                
                blue_sumB3A.derivative();
                green_sumG3A.derivative();
                red_sumR3A.derivative();
                
                max2b.setOutputDerivative(blue_sumB3A.Transform::getInputDerivative());
                max2r.setOutputDerivative(red_sumR3A.Transform::getInputDerivative());
                max2g.setOutputDerivative(green_sumG3A.Transform::getInputDerivative());
                
                max2b.derivative();
                max2r.derivative();
                max2g.derivative();
                
                blue_sumB2A.setOutputDerivative(max2b.getInputDerivative());
                red_sumR2A.setOutputDerivative(max2r.getInputDerivative());
                green_sumG2A.setOutputDerivative(max2g.getInputDerivative());
                
                blue_sumB2A.derivative();
                green_sumG2A.derivative();
                red_sumR2A.derivative();
                
                max1b.setOutputDerivative(blue_sumB2A.Transform::getInputDerivative());
                max1r.setOutputDerivative(red_sumR2A.Transform::getInputDerivative());
                max1g.setOutputDerivative(green_sumG2A.Transform::getInputDerivative());
                
                max1b.derivative();
                max1r.derivative();
                max1g.derivative();
                
                blue_sumB1A.setOutputDerivative(max1b.getInputDerivative());
                red_sumR1A.setOutputDerivative(max1r.getInputDerivative());
                green_sumG1A.setOutputDerivative(max1g.getInputDerivative());
                
                blue_sumB1A.derivative();
                red_sumR1A.derivative();
                green_sumG1A.derivative();
                
                //derivatives all calculated...
                //apply slopes
                applySlopes();
                
                //Rerun calculation..
                //calculateOutputs(classnumber);
                //saveKernels();
            }
        }
    }
    
    void TestLetters::saveKernels() {
        
        redS0.getKernel(0).saveMatrix(model_directory+"/kernal5_5_RDENSE0.txt");
        greenS0.getKernel(0).saveMatrix(model_directory+"/kernal5_5_GDENSE0.txt");
        blueS0.getKernel(0).saveMatrix(model_directory+"/kernal5_5_BDENSE0.txt");
        redS1.getKernel(0).saveMatrix(model_directory+"/kernal5_5_RDENSE1.txt");
        greenS1.getKernel(0).saveMatrix(model_directory+"/kernal5_5_GDENSE1.txt");
        blueS1.getKernel(0).saveMatrix(model_directory+"/kernal5_5_BDENSE1.txt");
        redS2.getKernel(0).saveMatrix(model_directory+"/kernal5_5_RDENSE2.txt");
        greenS2.getKernel(0).saveMatrix(model_directory+"/kernal5_5_GDENSE2.txt");
        blueS2.getKernel(0).saveMatrix(model_directory+"/kernal5_5_BDENSE2.txt");
        
        blue_sumB3A.getKernel(0).saveMatrix(model_directory+"/kernal2_2_B3A1.txt");
        green_sumG3A.getKernel(0).saveMatrix(model_directory+"/kernal2_2_G3A1.txt");
        red_sumR3A.getKernel(0).saveMatrix(model_directory+"/kernal2_2_R3A1.txt");
        
        blue_sumB2A.getKernel(0).saveMatrix(model_directory+"/kernal2_2_B2A1.txt");
        green_sumG2A.getKernel(0).saveMatrix(model_directory+"/kernal2_2_G2A1.txt");
        red_sumR2A.getKernel(0).saveMatrix(model_directory+"/kernal2_2_R2A1.txt");
        
        blue_sumB1A.getKernel(0).saveMatrix(model_directory+"/kernal3_3_B1A1.txt");
        red_sumR1A.getKernel(0).saveMatrix(model_directory+"/kernal3_3_R1A1.txt");
        green_sumG1A.getKernel(0).saveMatrix(model_directory+"/kernal3_3_G1A1.txt");
    }
    
    void TestLetters::applySlopes() {
        double lr = 1;
        redS0.calculateNewKernel(lr);
        greenS0.calculateNewKernel(lr);
        blueS0.calculateNewKernel(lr);
        redS1.calculateNewKernel(lr);
        greenS1.calculateNewKernel(lr);
        blueS1.calculateNewKernel(lr);
        redS2.calculateNewKernel(lr);
        greenS2.calculateNewKernel(lr);
        blueS2.calculateNewKernel(lr);
        
        blue_sumB3A.calculateNewKernel(lr);
        green_sumG3A.calculateNewKernel(lr);
        red_sumR3A.calculateNewKernel(lr);
        
        blue_sumB2A.calculateNewKernel(lr);
        green_sumG2A.calculateNewKernel(lr);
        red_sumR2A.calculateNewKernel(lr);
        
        blue_sumB1A.calculateNewKernel(lr);
        red_sumR1A.calculateNewKernel(lr);
        green_sumG1A.calculateNewKernel(lr);
    }
    
    void TestLetters::calculateOutputs(int classnumber) {
        // Red channel
        //sumproduct level 1 R
        //SumProduct red_sumR1A(redsmatrix, kernel3_3_R1A1, 3);
        //red_sumR1A.addKernel(kernel3_3_R1A2);
        red_sumR1A.apply();
        
        Max max1r(red_sumR1A.getOutput(), double(0));
        max1r.apply();
        
        //sumproduct level 2 R
        //SumProduct red_sumR2A(max1r.getOutput(), kernel2_2_R2A1, 2);
        red_sumR2A.setInputMatrix(max1r.getOutput());
        //red_sumR2A.addKernel(kernel2_2_R2A2);
        //red_sumR2A.addKernel(kernel2_2_R2A3);
        red_sumR2A.apply();
        
        Max max2r(red_sumR2A.getOutput(), double(0));
        max2r.apply();
        
        //sumproduct level 3 R
        //SumProduct red_sumR3A(max2r.getOutput(), kernel2_2_R3A1, 2);
        red_sumR3A.setInputMatrix(max2r.getOutput());
        //red_sumR3A.addKernel(kernel2_2_R3A2);
        red_sumR3A.apply();
        
        // Green channel
        //sumproduct level 1 G
        //SumProduct green_sumG1A(greensmatrix, kernel3_3_G1A1, 3);
        //green_sumG1A.addKernel(kernel3_3_G1A2);
        green_sumG1A.apply();
        
        Max max1g(green_sumG1A.getOutput(), double(0));
        max1g.apply();
        
        //sumproduct level 2 G
        //SumProduct green_sumG2A(max1g.getOutput(), kernel2_2_G2A1, 2);
        green_sumG2A.setInputMatrix(max1g.getOutput());
        //green_sumG2A.addKernel(kernel2_2_G2A2);
        //green_sumG2A.addKernel(kernel2_2_G2A3);
        green_sumG2A.apply();
        
        Max max2g(green_sumG2A.getOutput(), double(0));
        max2g.apply();
        
        //sumproduct level 3 G
        //SumProduct green_sumG3A(max2g.getOutput(), kernel2_2_G3A1, 2);
        green_sumG3A.setInputMatrix(max2g.getOutput());
        //green_sumG3A.addKernel(kernel2_2_G3A2);
        green_sumG3A.apply();
        
        // Blue channel
        //sumproduct level 1 B
        //SumProduct blue_sumB1A(bluesmatrix, kernel3_3_B1A1, 3);
        //blue_sumB1A.addKernel(kernel3_3_B1A2);
        blue_sumB1A.apply();
        
        Max max1b(blue_sumB1A.getOutput(), double(0));
        max1b.apply();
        
        //sumproduct level 2 B
        //SumProduct blue_sumB2A(max1b.getOutput(), kernel2_2_B2A1, 2);
        blue_sumB2A.setInputMatrix(max1b.getOutput());
        //blue_sumB2A.addKernel(kernel2_2_R2A2);
        //blue_sumB2A.addKernel(kernel2_2_R2A3);
        blue_sumB2A.apply();
        
        Max max2b(blue_sumB2A.getOutput(), double(0));
        max2b.apply();
        
        //sumproduct level 3 B
        //SumProduct blue_sumB3A(max2b.getOutput(), kernel2_2_B3A1, 2);
        blue_sumB3A.setInputMatrix(max2b.getOutput());
        //blue_sumB3A.addKernel(kernel2_2_B3A2);
        blue_sumB3A.apply();
        
        //sumproduct class
        Maxpool blueA(blue_sumB3A.getOutput(), 2, 2);
        blueA.apply();
        Maxpool greenA(green_sumG3A.getOutput(), 2, 2);
        greenA.apply();
        Maxpool redA(red_sumR3A.getOutput(), 2, 2);
        redA.apply();
        
        //SumProduct redS0(redA.getOutput(), kernel_dense_w_red[0] );
        redS0.setInputMatrix(redA.getOutput());
        redS0.apply();
        //SumProduct greenS0(greenA.getOutput(), kernel_dense_w_green[0]  );
        greenS0.setInputMatrix(greenA.getOutput());
        greenS0.apply();
        //SumProduct blueS0(blueA.getOutput(), kernel_dense_w_blue[0]  );
        blueS0.setInputMatrix(blueA.getOutput());
        blueS0.apply();
        
        //SumProduct redS1(redA.getOutput(), kernel_dense_w_red[1] );
        redS1.setInputMatrix(redA.getOutput());
        redS1.apply();
        //SumProduct greenS1(greenA.getOutput(), kernel_dense_w_green[1]  );
        greenS1.setInputMatrix(greenA.getOutput());
        greenS1.apply();
        //SumProduct blueS1(blueA.getOutput(), kernel_dense_w_blue[1]  );
        blueS1.setInputMatrix(blueA.getOutput());
        blueS1.apply();
        
        //SumProduct redS2(redA.getOutput(), kernel_dense_w_red[2] );
        redS2.setInputMatrix(redA.getOutput());
        redS2.apply();
        //SumProduct greenS2(greenA.getOutput(), kernel_dense_w_green[2]  );
        greenS2.setInputMatrix(greenA.getOutput());
        greenS2.apply();
        //SumProduct blueS2(blueA.getOutput(), kernel_dense_w_blue[2]  );
        blueS2.setInputMatrix(blueA.getOutput());
        blueS2.apply();
        
        
        Matrix redmatrix0 = redS0.getOutput();
        Matrix bluematrix0 = blueS0.getOutput();
        Matrix greenmatrix0 = greenS0.getOutput();
        
        Matrix redmatrix1 = redS1.getOutput();
        Matrix bluematrix1 = blueS1.getOutput();
        Matrix greenmatrix1 = greenS1.getOutput();
        
        Matrix redmatrix2 = redS2.getOutput();
        Matrix bluematrix2 = blueS2.getOutput();
        Matrix greenmatrix2 = greenS2.getOutput();
        
        double value0 = redmatrix0.getValue(0, 0) + bluematrix0.getValue(0, 0) + greenmatrix0.getValue(0,0);
        double value1 = redmatrix1.getValue(0, 0) + bluematrix1.getValue(0, 0) + greenmatrix1.getValue(0,0);
        double value2 = redmatrix2.getValue(0, 0) + bluematrix2.getValue(0, 0) + greenmatrix2.getValue(0,0);
        
        Utility utility;
        
        double values[3] = {value0, value1, value2};
        double * softmaxval = utility.softmax(values);

        double sevalues[3] = { utility.se(onepartencoded[classnumber][0], *(softmaxval+0) ),
            utility.se(onepartencoded[classnumber][1], *(softmaxval+1) ),
            utility.se(onepartencoded[classnumber][2], *(softmaxval+2) )
        };
        
        std::string output = classes[0] + ":" + std::to_string(*(softmaxval+0)) + " should be " + std::to_string(onepartencoded[classnumber][0]) + " se " + std::to_string(sevalues[0]);
        std::string output1 = classes[1] + ":" + std::to_string(*(softmaxval+1)) + " should be " + std::to_string(onepartencoded[classnumber][1]) + " se " + std::to_string(sevalues[1]);
        std::string output2 = classes[2] + ":" + std::to_string(*(softmaxval+2)) + " should be " + std::to_string(onepartencoded[classnumber][2]) + " se " + std::to_string(sevalues[2]);
        
        std::cout << std::endl;
        std::cout << output <<std::endl;
        std::cout << output1 <<std::endl;
        std::cout << output2 <<std::endl;
        std::cout << std::endl;
        
        //utility.log(output +"\n" + output1 + "\n" +output2 , logs_directory+"/log.txt");
    }
    
    void TestLetters::loadOrMakeKernels(const std::string model_directory) {
        Utility utility;
        //RED CHANNEL
        //level 1
        // create 7x7 kernel for R for letter a first level (extra is  R = Red, 1=first level, A class A, 1= 1st)
        utility.makeKernelOrLoad(&kernel3_3_R1A1, -1, 1, 3, 3, "R1A1", model_directory);
        // create second 7x7 kernel for R for letter a first level
        utility.makeKernelOrLoad(&kernel3_3_R1A2, -1, 1, 3, 3, "R1A2", model_directory);
        
        //level 2
        // create 3x3 kernel for R for letter a second level
        utility.makeKernelOrLoad(&kernel2_2_R2A1, -1, 1, 2, 2, "R2A1", model_directory);
        // create second 3x3 kernel for R for letter a second level
        utility.makeKernelOrLoad(&kernel2_2_R2A2, -1, 1, 2, 2, "R2A2", model_directory);
        // create third 3x3 kernel for R for letter a second level
        utility.makeKernelOrLoad(&kernel2_2_R2A3, -1, 1, 2, 2, "R2A3", model_directory);
        
        //level 3
        // create 3x3 kernel for R for letter a third level
        utility.makeKernelOrLoad(&kernel2_2_R3A1, -1, 1, 2, 2, "R3A1", model_directory);
        // create second 3x3 kernel for R for letter a third level
        utility.makeKernelOrLoad(&kernel2_2_R3A2, -1, 1, 2, 2, "R3A2", model_directory);
        
        //GREEN CHANNEL
        //level 1
        // create 7x7 kernel for G for letter a first level (extra is  G = Green, 1=first level, A class A, 1= 1st)
        utility.makeKernelOrLoad(&kernel3_3_G1A1, -1, 1, 3, 3, "G1A1", model_directory);
        // create second 7x7 kernel for G for letter a first level
        utility.makeKernelOrLoad(&kernel3_3_G1A2, -1, 1, 3, 3, "G1A2", model_directory);
        
        //level 2
        // create 3x3 kernel for G for letter a second level
        utility.makeKernelOrLoad(&kernel2_2_G2A1, -1, 1, 2, 2, "G2A1", model_directory);
        // create second 3x3 kernel for G for letter a second level
        utility.makeKernelOrLoad(&kernel2_2_G2A2, -1, 1, 2, 2, "G2A2", model_directory);
        // create third 3x3 kernel for G for letter a second level
        utility.makeKernelOrLoad(&kernel2_2_G2A3, -1, 1, 2, 2, "G2A3", model_directory);
        
        //level 3
        // create 3x3 kernel for G for letter a third level
        utility.makeKernelOrLoad(&kernel2_2_G3A1, -1, 1, 2, 2, "G3A1", model_directory);
        // create second 3x3 kernel for G for letter a third level
        utility.makeKernelOrLoad(&kernel2_2_G3A2, -1, 1, 2, 2, "G3A2", model_directory);
        
        //BLUE CHANNEL
        //level 1
        // create 7x7 kernel for B for letter a first level (extra is  B = Blue, 1=first level, A class A, 1= 1st)
        utility.makeKernelOrLoad(&kernel3_3_B1A1, -1, 1, 3, 3, "B1A1", model_directory);
        // create second 7x7 kernel for B for letter a first level
        utility.makeKernelOrLoad(&kernel3_3_B1A2, -1, 1, 3, 3, "B1A2", model_directory);
        
        //level 2
        // create 3x3 kernel for B for letter a second level
        utility.makeKernelOrLoad(&kernel2_2_B2A1, -1, 1, 2, 2, "B2A1", model_directory);
        // create second 3x3 kernel for R for letter a second level
        utility.makeKernelOrLoad(&kernel2_2_B2A2, -1, 1, 2, 2, "B2A2", model_directory);
        // create third 3x3 kernel for R for letter a second level
        utility.makeKernelOrLoad(&kernel2_2_B2A3, -1, 1, 2, 2, "B2A3", model_directory);
        
        //level 3
        // create 3x3 kernel for B for letter a third level
        utility.makeKernelOrLoad(&kernel2_2_B3A1, -1, 1, 2, 2, "B3A1", model_directory);
        // create second 3x3 kernel for R for letter a third level
        utility.makeKernelOrLoad(&kernel2_2_B3A2, -1, 1, 2, 2, "B3A2", model_directory);
    }
    
    void TestLetters::makeDense(long red_width,
                               long red_height,
                               long blue_width,
                               long blue_height,
                               long green_width,
                               long green_height,
                               std::string model_directory) {
        Utility utility;
        utility.makeKernelOrLoad(&kernel_dense_w_red[0], -1, 1, red_width, red_height, "RDENSE0", model_directory);
        utility.makeKernelOrLoad(&kernel_dense_w_blue[0], -1, 1, blue_width, blue_height, "BDENSE0", model_directory);
        utility.makeKernelOrLoad(&kernel_dense_w_green[0], -1, 1, green_width, green_height, "GDENSE0", model_directory);
        utility.makeKernelOrLoad(&kernel_dense_w_red[1], -1, 1, red_width, red_height, "RDENSE1", model_directory);
        utility.makeKernelOrLoad(&kernel_dense_w_blue[1], -1, 1, blue_width, blue_height, "BDENSE1", model_directory);
        utility.makeKernelOrLoad(&kernel_dense_w_green[1], -1, 1, green_width, green_height, "GDENSE1", model_directory);
        utility.makeKernelOrLoad(&kernel_dense_w_red[2], -1, 1, red_width, red_height, "RDENSE2", model_directory);
        utility.makeKernelOrLoad(&kernel_dense_w_blue[2], -1, 1, blue_width, blue_height, "BDENSE2", model_directory);
        utility.makeKernelOrLoad(&kernel_dense_w_green[2], -1, 1, green_width, green_height, "GDENSE2", model_directory);
    }
} /* namespace DeepNeural */
