//
//  Utility.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-11-08.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef Utility_hpp
#define Utility_hpp
#include <stdio.h>
#include "../model/Kernel.hpp"

namespace DeepNeural {
    
    class Utility {
    public:
        Utility();
        virtual ~Utility();
        double se(double typ, double ty);
        double dse(double typ, double ty);
        double dsoftmax(double soft, bool flag);
        double *  softmax(double numbers[]);
        void makeKernelOrLoad(Kernel * kernel, double low, double hi, int width, int height, std::string extraname, const std::string model_directory);
        std::vector<std::string> listFiles(const std::string directory, const std::string search_parameter);
        void read_directory(const std::string& name, std::vector<std::string>& v, const std::string search_parameter);
        std::vector<double> softmax(std::vector<double> numbers);
        void log(std::string logvalue, std::string logfilename);
    private:
    };
}
#endif /* Utility_hpp */
