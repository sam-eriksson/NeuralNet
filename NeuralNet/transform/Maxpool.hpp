//
//  Maxpool.hpp
//  NeuralNet
//
//  Created by Sam Eriksson on 2018-10-17.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef Maxpool_hpp
#define Maxpool_hpp

#include <stdio.h>
#include "Transform.hpp"

namespace DeepNeural {
    class Maxpool : public Transform  {
    public:
        Maxpool(Matrix in, int xbox, int ybox);
        Maxpool(Matrix in, int xbox, int ybox, double cutoff );
        virtual ~Maxpool();
        void apply();
        void derivative();
    private:
        int x_delta;
        int y_delta;
        double cutoff = 0;
    protected:
        
    };
}
#endif /* Maxpool_hpp */
