//
//  SumProduct.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-15.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "SumProduct.hpp"
#include <cmath>
#include <iostream>

namespace DeepNeural {
    
    SumProduct::SumProduct(Matrix in, Kernel ker) : Transform(in,ker) {
    }
    
    SumProduct::SumProduct(Matrix in, Kernel ker, int stri) : Transform(in,ker) {
        stride = stri;
    }
    
    SumProduct::SumProduct(Matrix in, std::vector< Kernel > kers, int stri) : Transform(in,kers) {
        stride = stri;
    }
    
    SumProduct::SumProduct(Matrix in, std::vector< Kernel > kers) : Transform(in,kers) {
    }
    
    SumProduct::SumProduct(): Transform() {
        
    }
    
    void SumProduct::setConstruct(Matrix in, Kernel ker, int stri) {
        input = in;
        kernels.clear();
        kernels.push_back(ker);
        stride = stri;
    }
    
    void SumProduct::setConstruct(Matrix in, Kernel ker) {
        input = in;
        kernels.clear();
        kernels.push_back(ker);
    }
    
    SumProduct::~SumProduct() {
    }
    
    void SumProduct::addKernel(Kernel ker) {
        kernels.push_back(ker);
    }
    
    /*void SumProduct::setInputMatrix(Matrix in) {
        input = in;
    }*/
    
    void SumProduct::apply() {
        output.clearValues();
        output.clearDerivativeValues();
        long height_kernel = kernels.at(0).getHeight();
        long width_kernel = kernels.at(0).getWidth();
        double total_convolution_point= double(0);
        long edge_h=input.getHeight();
        long edge_w=input.getWidth();
        
        for(long hh = 0; (hh+height_kernel)<(edge_h+1); hh=hh+stride) {
            std::vector< double > row;
            for(long ww=0; (ww+width_kernel)<(edge_w+1); ww=ww+stride) {
                total_convolution_point = double(0);
                for(long h=0; h<height_kernel; h++) {
                    for(long w=0; w<width_kernel; w++) {
                        //fix kernels kernel issue
                        for(int convn =0 ; convn < kernels.size(); convn++) {
                            Kernel kernel = kernels.at(convn);
                            double kvalue = kernel.getValue(w, h);
                            double ivalue = input.getValue(w+ww,h+hh);
                            total_convolution_point = total_convolution_point + (ivalue*kvalue);
                        }
                    }
                }
                row.push_back(total_convolution_point);
            }
            output.addRow(row);
        }
    }
    
    void SumProduct::derivative() {
        kw = kernels.at(0).getWidth();
        kh = kernels.at(0).getHeight();
        iw = input.getWidth();
        ih = input.getHeight();
        oh = output.getHeight();
        ow = output.getWidth();
        loopDerivative();
    }
    
    void SumProduct::calculateNewKernel(double lr) {
        long width = kernels.at(0).getWidth();
        long height = kernels.at(0).getHeight();
        
        for (int y=0; y< height; y++) {
            for (int x=0; x< width; x++) {
                double newvalue = kernels.at(0).getValue(x, y) + lr * kernels.at(0).getValueDerivative(x, y);
                //std::cout << "newvalue:" << newvalue << " kernel:" << kernels.at(0).getValue(x, y)<< " derivative:" << kernels.at(0).getValueDerivative(x, y) <<std::endl;
                kernels.at(0).setValue(x, y, newvalue);
            }
        }
    }
    
    void SumProduct::loopDerivative() {
        for (int kn=0; kn<kernels.size(); kn++)
        {
            kernels.at(kn).initializeDerivative(kw, kh, double(0));
            for (long x=0; x<kw; x++) {
                for (long y=0; y< kh; y++) {
                    kernels.at(kn).setValueDerivative(x, y, getKernelDerivative(x, y));
                }
            }
        }
        input.initializeDerivative(iw, ih, double(0));
        for (long xx=0; xx<iw; xx++) {
            for (long yy=0; yy< ih; yy++) {
                input.setValueDerivative(xx, yy, getInputDerivative(xx, yy));
            }
        }
    }

    //Need to deal with two Kernels
    double SumProduct::getInputDerivative(long ix, long iy) {
        long kx= ix - kw * (ix/kw);
        long ky= iy - kh * (iy/kh);
        
        long ox=ix/kw;
        long oy=iy/kh;
        if (kx<kw && ky<kh && ox<ow && oy <oh)
        return kernels.at(0).getValue(kx, ky) * output.getValueDerivative(ox, oy);
        return double(0);
    }
    
    double SumProduct::getKernelDerivative(long kx, long ky) {
        double kdv = double(0);
        long anchor_x = 1+(iw-kw)/stride;
        long anchor_y = 1+(ih-kh)/stride;
        long rx = kx % kw;
        long ry = ky % kh;
        for (long yy=0; yy<anchor_x; yy++) {
            for (long xx=0; xx<anchor_y; xx++) {
                for (long y=0; y<oh; y=y+anchor_y) {
                    for (long x=0; x<ow; x=x+anchor_x) {
                        kdv = kdv + input.getValue(rx +xx*stride,y + ry +yy*stride) * output.getValueDerivative(xx,yy);
                    }
                }
            }
        }
        return kdv;
    }
    
    double SumProduct::getOutputDerivative(long x, long y) {
        return output.getValueDerivative(x, y);
    }
    
    Matrix SumProduct::getKernel(int kernum) {
        return kernels.at(kernum);
    }
}
