#include "so2_cpg.h"

using namespace std;

// Constructor
so2::so2()
{
    network_output1 = 0;
    network_output2 = 0;
}

// Time initiation function: Creates an equally spaced vector containing the sample points to build the CPG.
vector<float> so2::timeSpace(float t0, float tf, int sample)
{
    vector<float> T;
    float dt = (tf-t0)/(sample-1);
    for(int i=0; i<sample; i++)
    {
        T.push_back(t0 + dt*i);
    }

    return T;
}

// Locomotion pattern generator
// Requires defining weights[4], biases[2]
// weights = (w11, w22, w12, w21)
// biases = (b1, b2) 
// Weights and biases in absolute value!
// HZ is the frequency. Use hz=0.0 to leave it by default.
vector<tuple<float, float, float> > so2::intraLegCoordination(vector<float> tsp, vector<float> weights, vector<float> biases, float hz)
{
    vector<tuple<float, float, float> > cpg;

    // Set initial outputs
    float o1 = 0.0;
    float o2 = 0.0;

    // reflex
    float reflex;
    if(hz == 0.0)
    {
        reflex = FREQ;
    } 
    else
    {
        reflex = hz;
    }

    // SO2 network Construction
    for(size_t j; j<tsp.size(); j++)
    {
        float ti = tsp[j];

        // Adding reflex to weights
        float w12 = weights[2] + reflex;
        float w21 = - weights[3] - reflex;

        // Activities
        float a1 = (weights[0]*o1 + w12*o2) + biases[0];
        float a2 = (weights[1]*o2 + w21*o1) + biases[1];
        n1.set_activity(a1);
        n2.set_activity(a2);
        
        // Outputs
        n1.tanh_output();
        n2.tanh_output();
        o1 = n1.get_output();
        o2 = n2.get_output();
        cpg.push_back(make_tuple(ti, o1, o2));

    }

    return cpg;
}

// Get CPG output value
vector<float> so2::get_output()
{
    vector<float> output;
    output.push_back(network_output1);
    output.push_back(network_output2);
    return output;
}

// Update output value (positional)
void so2::udpate_output(vector<float> x)
{
    network_output1 = x[0];
    network_output2 = x[1];
}