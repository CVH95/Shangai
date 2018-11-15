#include <so2_cpg.h>

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
vector<tuple<float, float, float> > so2::intraLegCoordination(vector<float> tsp)
{
    vector<tuple<float, float, float> > cpg;
    // Network Parameters
    float weightH1_H1 = 1.4;
    float weightH2_H2 = 1.4;
    float BiasH1 = 0.01;
    float BiasH2 = 0.01;
    float Output1 = 0.0;
    float Output2 = 0.0;

    float reflex = FREQ;
    // SO2 network Construction
    for(size_t j; j<tsp.size(); j++)
    {
        float ti = tsp[j];

        // CPG parameters
        float weightH1_H2 = 0.18 + reflex;
        float weightH2_H1 = -0.18 - reflex;

        // SO2 Network
        // Activity: A_i(t+1) = Sum[j=1, n](weight_ij * Output_j) + Bias_i
        // Activation function: Output_i = tanh(A_i)
        float activityH1 = (weightH1_H1*Output1 + weightH1_H2*Output2) + BiasH1;
        float activityH2 = (weightH2_H2*Output2 + weightH2_H1*Output1) + BiasH2;
        
        transfer_function G; // = new transferfunction::transfer_function();

        Output1 = G.tanh(activityH1);
        Output2 = G.tanh(activityH2);

        cpg.push_back(make_tuple(ti, Output1, Output2));
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