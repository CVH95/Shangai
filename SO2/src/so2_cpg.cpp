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
tuple<float, float, float> so2::intraLegCoordination(float ti, vector<float> weights, vector<float> biases, float hz, float o1, float o2)
{
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
    
    return make_tuple(ti, o1, o2);
}

// Get CPG output value
vector<float> so2::get_output()
{
    vector<float> output;
    output.push_back(network_output1);
    output.push_back(network_output2);
    return output;
}

// Threshold SO2 signal (dung beetle)
float so2::threshold_so2_signal(float oi, float oi_prev)
{
    float _oi;
    // First threshold, on y(x)
    if(oi >= 0.0)
    {
        // Approximating derivative
        float diff = oi - oi_prev;
        // Second threshold, on y'(x)
        if(diff >= 0.0)
        {
            _oi = oi;
        }
        else
        {       
            _oi = 0;
        }
    }
    else
    {
        _oi = 0;
    }

    return _oi;
}

// Update output value (positional)
void so2::udpate_output(float x, float y)
{
    network_output1 = x;
    network_output2 = y;
}