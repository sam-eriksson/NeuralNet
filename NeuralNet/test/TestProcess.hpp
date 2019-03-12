//
//  TestProcess.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-29.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef TestProcess_hpp
#define TestProcess_hpp

#include <stdio.h>

namespace DeepNeural {
    
    class TestProcess {
    public:
        TestProcess();
        virtual ~TestProcess();
        void run(int argc, const char * argv[]);
    private:
    };
}
#endif /* TestProcess_hpp */
