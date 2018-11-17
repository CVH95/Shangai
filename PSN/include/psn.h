// Phase Switching Network
// 12 neuron network

#ifndef PSN_H_
#define PSN_H_

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
#include "neuron.h"

#define PI 3.14159265

using namespace std;

// Forward Declarations.
class neuron;

class psn{

    public:

        // Constructor
        psn();

        // Functions
        vector<float> compute_psn_network(vector <float> inputs, vector<float> weights, vector<float> biases);
        vector<float> get_output();
        void update_network_output(float o13, float o14);

    private:

        float network_output1;
        float network_output2;
        // Neurons
        neuron n1;
        neuron n2;
        neuron n3;
        neuron n4;
        neuron n5;
        neuron n6;
        neuron n7;
        neuron n8;
        neuron n9; 
        neuron n10;
        neuron n11;
        neuron n12;
};

#endif /* PSN_H_ */