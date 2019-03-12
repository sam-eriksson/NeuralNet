//
//  TestSimple.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-11-08.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "TestSimple.hpp"
#include "../model/Matrix.h"
#include <iostream>
#include "../transform/SumProduct.hpp"
#include "../utility/Utility.hpp"

namespace DeepNeural {
    const std::string path = "/Users/sameriksson/temp/testing/";
    
    TestSimple::TestSimple() {
        const std::string filename_simple = path + "simple_matrix.txt";
        simple.loadMatrix(filename_simple );
        
        const std::string filename_top = path + "simple_top_kernel.txt";
        top.loadMatrix(filename_top );
        const std::string filename_side = path + "simple_side_kernel.txt";
        side.loadMatrix(filename_side );
        
        const std::string filename_top_a_dense = path + "simple_topa_dense.txt";
        top_a_dense.loadMatrix(filename_top_a_dense );
        const std::string filename_top_b_dense = path + "simple_topb_dense.txt";
        top_b_dense.loadMatrix(filename_top_b_dense );
        
        const std::string filename_side_a_dense = path + "simple_sidea_dense.txt";
        side_a_dense.loadMatrix(filename_side_a_dense );
        const std::string filename_side_b_dense = path + "simple_sideb_dense.txt";
        side_b_dense.loadMatrix(filename_side_b_dense );
    }
    
    TestSimple::~TestSimple() {
    }
    
    void TestSimple::run() {
        
        //first sumproducts start
        firstLoopSumProducts();
        // first sumproducts end
        
        //calculate standard errors / softmax
        softMaxError();
        //end of standard errors calculation
        
        //Derivative calculation
        //Need a method to input the inputs and derivative to kernel to calculate
        //derivatives for each point
        calculateDerivative();
        
        //derivatives calculated...
        //apply calculate new values
        //apply new valuess
        //Learning rate (rate of change x slope)
        calculateNewKernels();
        loopSumProducts();
        softMaxError();
    }
    
    void TestSimple::firstLoopSumProducts() {
        sumproduct_top.setConstruct(simple, top, 2);
        sumproduct_top.apply();
        
        sumproduct_side.setConstruct(simple, side, 2);
        sumproduct_side.apply();
        
        Matrix top = sumproduct_top.getOutput();
        Matrix side = sumproduct_side.getOutput();
        
        finalatop.setConstruct(top, top_a_dense);
        finalatop.apply();
        Matrix finalatopresult = finalatop.getOutput();
        double atop = finalatopresult.getValue(0, 0);
        
        finalaside.setConstruct(side, side_a_dense);
        finalaside.apply();
        Matrix finalasideresult = finalaside.getOutput();
        double aside = finalasideresult.getValue(0, 0);
        
        finalbtop.setConstruct(top, top_b_dense);
        finalbtop.apply();
        Matrix finalbtopresult = finalbtop.getOutput();
        double btop = finalbtopresult.getValue(0, 0);
        
        finalbside.setConstruct(side, side_b_dense);
        finalbside.apply();
        Matrix finalbsideresult = finalbside.getOutput();
        double bside = finalbsideresult.getValue(0, 0);
        
        a = atop + aside;
        b = btop + bside;
    }
    
    void TestSimple::loopSumProducts() {
        sumproduct_top.apply();
        sumproduct_side.apply();
        
        Matrix top = sumproduct_top.getOutput();
        Matrix side = sumproduct_side.getOutput();
        
        finalatop.setInputMatrix(top);
        finalatop.apply();
        Matrix finalatopresult = finalatop.getOutput();
        double atop = finalatopresult.getValue(0, 0);
        
        finalaside.setInputMatrix(side);
        finalaside.apply();
        Matrix finalasideresult = finalaside.getOutput();
        double aside = finalasideresult.getValue(0, 0);
        
        finalbtop.setInputMatrix(top);
        finalbtop.apply();
        Matrix finalbtopresult = finalbtop.getOutput();
        double btop = finalbtopresult.getValue(0, 0);
        
        finalbside.setInputMatrix(side);
        finalbside.apply();
        Matrix finalbsideresult = finalbside.getOutput();
        double bside = finalbsideresult.getValue(0, 0);
        
        a = atop + aside;
        b = btop + bside;
    }
    
    void TestSimple::softMaxError() {
        Utility util;
        
        std::vector<double> presoft;
        presoft.push_back(a);
        presoft.push_back(b);
        std::vector<double> result = util.softmax(presoft);
        softa = result.at(0);
        softb = result.at(1);
        ase = util.se(softa, 1);
        bse = util.se(softb , 0);
        std::cout << "a: " << ase << " b: " << bse << std::endl;
    }
    
    void TestSimple::calculateDerivative() {
        
        Utility util;
        double derivative_a_se = util.dse(ase, 1);
        double derivative_b_se = util.dse(bse, 0);
        
        double derivative_soft_a = util.dsoftmax(softa, true);
        double derivative_soft_b = util.dsoftmax(softb, false);
        
        double total_derivative_a = derivative_a_se * derivative_soft_a;
        double total_derivative_b = derivative_b_se * derivative_soft_b;
        
        
        //Matrix totalAD;
        std::vector<double> row;
        row.push_back(total_derivative_a);
        finalatop.addOutputDerivativeRow(row);
        finalaside.addOutputDerivativeRow(row);
        
        //Matrix totalBD;
        std::vector<double> rowB;
        rowB.push_back(total_derivative_b);
        finalbtop.addOutputDerivativeRow(rowB);
        finalbside.addOutputDerivativeRow(rowB);
        
        finalatop.derivative();
        finalaside.derivative();
        finalbtop.derivative();
        finalbside.derivative();
        
        Matrix topA = finalatop.Transform::getInputDerivative();
        sumproduct_top.setOutputDerivative(topA);
        Matrix sideA = finalaside.Transform::getInputDerivative();
        sumproduct_side.setOutputDerivative(sideA);
        
        sumproduct_top.derivative();
        sumproduct_side.derivative();
    }
    
    void TestSimple::calculateNewKernels() {
        double lr = 0.1;
        finalatop.calculateNewKernel(lr);
        finalaside.calculateNewKernel(lr);
        finalbtop.calculateNewKernel(lr);
        finalbside.calculateNewKernel(lr);
        sumproduct_top.calculateNewKernel(lr);
        sumproduct_side.calculateNewKernel(lr);
    }
}
