//
//  Max.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-31.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef Max_hpp
#define Max_hpp

#include <stdio.h>
#include "Transform.hpp"

namespace DeepNeural {
    class Max : public Transform  {
    public:
        Max(Matrix in, double bottom);
        virtual ~Max();
        void apply();
        void derivative();
    private:
        double bottom =0;
    protected:
        
    };
}
#endif /* Max_hpp */
