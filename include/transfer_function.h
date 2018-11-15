//  Transfer function class

#ifndef TRANSFER_FUNCTION_H_
#define TRANSFER_FUNCTION_H_

#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <sstream>
#include <tuple>
#include <map>
#include <vector>

#define PI 3.14159265

using namespace std;

class transfer_function{

    public:

        // Functions
        float gaussian(float x, float std);
        float linear(float x);
        float linear_biased(float x, float m, float n);
        float sigmoid(float x);
        float step_threshold(float x, float threshold);
        float tanh(float x);
        
};

#endif /* TRANSFER_FUNCTION_H_ */