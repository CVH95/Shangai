// SO2-CPG driving locomotion of a hexapod robot with tripod gait walking.
// SO2 Network.
// Activity: A_i(t+1) = Sum[j=1, n](weight_ij * Output_j) + Bias_i
// Activation function: Output_i = tanh(A_i)

//#ifndef SO2_H_
//#define SO2_H_

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

class so2{

    public:

        // Constructor
        so2();

        // Variables
        float FREQ = 0.02; // Slow wave
        //float FREQUENCY = 0.1 // Moderated speed
        //float FREQUENCY = 0.18 // High speed wave

        // Functions
        vector<float> timeSpace(float t0, float tf, int sample);
        tuple<float, float, float> intraLegCoordination(float ti, vector<float> weights, vector<float> biases, float hz, float o1, float o2);
        vector<float> get_output();
        float threshold_so2_signal(float oi, float oi_prev);
        void udpate_output(float x, float y);

    private:

        float network_output1;
        float network_output2;
        //float o1;
        //float o2;
        neuron n1;
        neuron n2;
};

//#endif /* SO2_H_ */