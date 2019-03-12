/*
 * DeepNeural.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: sameriksson
 */

#include "DeepNeural.h"
#include <iostream>
#include "externalheader/jpeglib.h"
#include "string.h"
#include <iostream>
#include "image/Image.h"
#include "image/ImageDataLoader.hpp"
#include "model/Matrix.h"
#include "model/Kernel.hpp"
#include "transform/Normalize.hpp"
#include "transform/Sigmoid.hpp"
#include "transform/SumProduct.hpp"
#include "transform/TangentSigmoid.hpp"

#include <sys/types.h>
#include <dirent.h>
#include "transform/Maxpool.hpp"
#include "transform/Max.hpp"
#include "transform/SoftmaxClassification.hpp"
#include "tgmath.h"

namespace DeepNeural {

    DeepNeural::DeepNeural() {
    }

    DeepNeural::~DeepNeural() {

    }    
} /* namespace DeepNeural */


