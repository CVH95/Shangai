// Velocity Reduction Network
// 7 neuron network

#ifndef VRN_H_
#define VRN_H_

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
#include <neuron.h>

#define PI 3.14159265

using namespace std;

// Forward Declarations.
class neuron;

class vrn{

    public:
        
        // Constructor 
        vrn();

        // Functions
        vector<float> compute_vrn_network(vector <float> inputs, vector<float> weights, vector<float> biases);
        float get_output();
        void update_network_output(float o7);

    private:

        float network_output;
};

#endif /* VRN_H_ */