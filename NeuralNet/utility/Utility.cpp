//
//  Utility.cpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-11-08.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "Utility.hpp"
#include "../model/Kernel.hpp"
#include "tgmath.h"
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <fstream>

namespace DeepNeural {
    Utility::Utility() {
    }
    
    Utility::~Utility() {
    }
    
    double Utility::se(double typ, double ty) {
        return pow( (ty-typ),2 );
    }
    
    double Utility::dse(double typ, double ty) {
        return 2*ty-2*typ;
    }
    double Utility::dsoftmax(double soft, bool flag) {
        if (flag) {
            return soft * (1-soft);
        }
        return soft*(-soft);
    }
    
    double returnvalue[3];
    double *  Utility::softmax(double numbers[]) {
        double total = exp(numbers[0])+ exp(numbers[1]) + exp(numbers[2]);
        returnvalue[0] = exp(numbers[0])/total;
        returnvalue[1] = exp(numbers[1])/total;
        returnvalue[2] = exp(numbers[2])/total;
        return returnvalue;
    }
    
    std::vector<double> Utility::softmax(std::vector<double> numbers) {
        double total=0;
        for(int i=0; i<numbers.size(); i++) {
            total = total + exp(numbers.at(i));
        }
        std::vector<double> returnsoftmax;
        for(int j=0; j<numbers.size(); j++) {
            returnsoftmax.push_back(exp(numbers.at(j))/total);
        }
        return returnsoftmax;
    }
    
    void Utility::makeKernelOrLoad(Kernel * kernel, double low, double hi, int width, int height, std::string extraname, const std::string model_directory) {
        if (kernel->ifExistsLoad(model_directory+"/kernal"+std::to_string(width)+"_"+std::to_string(height)+"_"+extraname+".txt")==false) {
            kernel->seed(low, hi, width, height);
            kernel->saveMatrix(model_directory+"/kernal"+std::to_string(width)+"_"+std::to_string(height)+"_"+extraname+".txt");
        }
    }
    
    std::vector<std::string> Utility::listFiles(const std::string directory, const std::string search_parameter) {
        std::vector<std::string> listoffiles;
        read_directory(directory, listoffiles, search_parameter);
        return listoffiles;
    }
    
    void Utility::read_directory(const std::string& name, std::vector<std::string>& v, const std::string search_parameter)
    {
        DIR* dirp = opendir(name.c_str());
        struct dirent * dp;
        while ((dp = readdir(dirp)) != NULL) {
            std::string name = dp->d_name;
            if (name.find(search_parameter)!=std::string::npos) v.push_back(dp->d_name);
        }
        closedir(dirp);
    }
    
    void Utility::log(std::string logvalue, std::string logfilename) {
        std::ofstream logfile;
        logfile.open (logfilename, std::ios::app);
        logfile << logvalue;
        logfile << '\n';
        logfile.close();
    }
}
