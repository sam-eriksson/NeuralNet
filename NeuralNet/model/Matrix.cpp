/*
 * Matrix.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: sameriksson
 */

#include "Matrix.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "tgmath.h"

namespace DeepNeural {

    Matrix::Matrix() {
    }
    
    Matrix::Matrix(long width, long height, double prepopulate) {
        for (int x=0; x<width; x++) {
            std::vector< double > row;
            for (int y=0; y<height; y++) {
                row.push_back(prepopulate);
            }
            values.push_back(row);
        }
    }
    
    Matrix::Matrix(std::vector<std::vector<double>> data) {
        values = data;
    }
    
    Matrix::~Matrix() {
    }
    
    void Matrix::saveMatrix(const std::string& filename ) {
        std::ofstream matrixfile;
        matrixfile.open (filename);
        for (const auto& row: values) {
            bool first = true;
            if (row.size()>1) {
                for (const auto& e: row) {
                if (first) {
                    first =false;
                } else {
                    matrixfile << ",";
                }
                matrixfile << e;
                }
            } else {
                for (const auto& e: row) {
                    matrixfile << e;
                }
            }
            matrixfile << '\n';
        }
        matrixfile.close();
    }
    
    long Matrix::getWidth() {
        if(values.size()>=1) {
        auto va = values.front();
        return va.size();
        }
        return 0;
    }
    
    long Matrix::getHeight() {
        return values.size();
    }
    
    double Matrix::getValue(long posx, long posy) {
        return values.at(posy).at(posx);
    }
    
    void Matrix::addRow(std::vector<double> row) {
        values.push_back(row);
    }

    void Matrix::loadMatrix(const std::string& filename) {
        values.clear();
        std::ifstream in(filename);
        if(!in.is_open())
        {
            std::cerr << "Cannot open the File : "<<filename<<std::endl;
            return;
        }

        std::string str;
        while (std::getline(in, str))
        {
            std::vector<double> row_vec;
            if(str.size() > 0) {
                std::size_t pos = str.find(",");
                std::size_t pos1=0;
                while (pos!=std::string::npos) {
                    std::string substr = str.substr(pos1, pos-pos1);
                    double doublestr = stod(substr);
                    row_vec.push_back(doublestr);
                    pos1=pos+1;
                    pos = str.find(",", pos1);
                }
                std::string substr = str.substr(pos1, str.length());
                double doublestr = stod(substr);
                row_vec.push_back(doublestr);
                addRow(row_vec);
            }
        }
        //Close The File
        in.close();
    }
    
    bool Matrix::ifExistsLoad(const std::string& filename) {
        std::ifstream in(filename);
        if(!in.is_open())
        {
            std::cerr << "Cannot open the File : "<<filename<<std::endl;
            return false;
        }
        loadMatrix(filename);
        return true;
    }
    
    void Matrix::padWith(const long width, long height, double value) {
        long original_height = getHeight();
        long original_width = getWidth();
        
        for(int y=0; y<height; y++) {
            if (y>=original_height) {
                std::vector < double > newvalue;
                for(int x=0; x<width; x++) newvalue.push_back(value);
                values.push_back(newvalue);
            } else {
                for(int x=0; x<width-original_width; x++)
                    values.at(y).push_back(value);
            }

            
        }
    }
    
    double Matrix::mean() {
        long width = getWidth();
        long height = getHeight();
        long total =0;
        long observations=0;
        for (long y=0; y<height; y++) {
            for(long x=0; x<width;x++) {
                double value = getValue(x, y);
                total = total +value;
                observations = observations +1;
            }
        }
        // mean = sum of y's / obsersvations n
        average = total/double(observations);
        numberOfpoints=observations;
        return total/double(observations);
    }

    double Matrix::stdev() {
        long width = getWidth();
        long height = getHeight();
        double totalsquareddifferencemean=0;
        for (long y=0; y<height; y++) {
            for(long x=0; x<width;x++) {
                // (y -m)^2
                double squareddifferencemean = (getValue(x, y) - average)*(getValue(x, y) - average);
                // sum of (y-m)^2
                totalsquareddifferencemean = totalsquareddifferencemean +squareddifferencemean;
            }
        }
        // stdev = sqrt( (y-m)^2 / n-1 )
        standarddev = sqrt(totalsquareddifferencemean/(numberOfpoints-1));
        if (standarddev==0) standarddev=0.0000001;
        return standarddev;
    }
    
    void Matrix::setValue(long x, long y, double value) {
        values.at(y).at(x) = value;
    }
    
    void Matrix::addDerivativeRow(std::vector< double >  row) {
        derivative.push_back(row);
    }
    
    void Matrix::initializeDerivative(long width, long height, double value) {
        clearDerivativeValues();
        for (int x=0; x<width; x++) {
            std::vector< double > row;
            for (int y=0; y<height; y++) {
                row.push_back(value);
            }
            derivative.push_back(row);
        }
    }
    
    void Matrix::setValueDerivative(long x, long y, double value) {
        derivative.at(y).at(x) = value;
    }
    
    double Matrix::getValueDerivative(long x, long y) {
        return derivative.at(y).at(x);
    }
    
    Matrix Matrix::getDerivative() {
        return Matrix(derivative);
    }
    
    void Matrix::clearValues() {
        for (int rows=0; rows<values.size(); rows++) {
            values.at(rows).clear();
        }
        values.clear();
    }
    
    void Matrix::clearDerivativeValues() {
        for (int rows=0; rows<derivative.size(); rows++) {
            derivative.at(rows).clear();
        }
        derivative.clear();
    }
    
    void Matrix::invert(int max) {
        for (int y=0; y< getHeight(); y++) {
            for(int x=0; x <getWidth(); x++) {
                double value = values.at(y).at(x);
                values.at(y).at(x) = max - value;
            }
        }
    }
    
    double Matrix::getMax() {
        double max= double(0);
        for (int y=0; y< getHeight(); y++) {
            for(int x=0; x <getWidth(); x++) {
                double value = values.at(y).at(x);
                if (max<value) max=value;
            }
        }
        return max;
    }

    double Matrix::getMinimum() {
        double min= double(0);
        for (int y=0; y< getHeight(); y++) {
            for(int x=0; x <getWidth(); x++) {
                double value = values.at(y).at(x);
                if (min>value) min=value;
            }
        }
        return min;
    }
} /* namespace DeepNeural */
