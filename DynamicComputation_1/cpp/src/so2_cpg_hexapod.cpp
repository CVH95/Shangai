// SO2-CPG driving locomotion of a hexapod robot with tripod gait walking.

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

#define PI 3.14159265

using namespace std;

// Frequency of the pattern
float FREQUENCY = 0.02; // Slow wave
//float FREQUENCY = 0.1 // Moderated speed
//float FREQUENCY = 0.18 // High speed wave

// Hyperbolic tangent ctivation function
float tanh(float x)
{
    float y;
    y = ((2.0/ (1.0 + exp(-2.0 * x))) - 1.0);
    return y;
}

// Time initiation function: Creates an equally spaced vector containing the sample points to build the CPG.
vector<float> timeSpace(float t0, float tf, int sample)
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
vector<tuple<float, float, float> > intraLegCoordination(vector<float> tsp)
{
    vector<tuple<float, float, float> > cpg;
    // Network Parameters
    float weightH1_H1 = 1.4;
    float weightH2_H2 = 1.4;
    float BiasH1 = 0.01;
    float BiasH2 = 0.01;
    float Output1 = 0.0;
    float Output2 = 0.0;

    float reflex = FREQUENCY;
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
        Output1 = tanh(activityH1);
        Output2 = tanh(activityH2);

        cpg.push_back(make_tuple(ti, Output1, Output2));
    }

    return cpg;
}

int main()
{
    cout << "STANDARD CO2 NEURAL NETWORK FOR HEXAPOD CPG COMPUTATION" << endl;
    cout << "The locomotion pattern describes tripod the walking gait of a hexapod robot." << endl << endl;

    //cout << "Tanh test:" << endl;
    //float x1 = 0.01;
    //float x2 = 3.5;
    //float y1 = tanh(x1);
    //float y2 = tanh(x2);
    //cout << "x1 = " << x1 << " | tanh(x1) = " << y1 << endl;
    //cout << "x2 = " << x2 << " | tanh(x2) = " << y2 << endl;

    cout << "SO2 neural network CPG generation:" << endl;
    cout << "Neuron Activity: A_i(t+1) = Sum[j=1, n](weight_ij * Output_j) + Bias_i" << endl;
    cout << "Neuron Output: Output_i = tanh(A_i)" << endl << endl;

    // Initialization:
    float t0 = 0.0;
    float tf = 10.0;
    float f = 10*10;
    int sample = (tf-t0)*f +1;
    vector<float> tsp = timeSpace(t0, tf, sample); 

    // Calculation
    vector<tuple<float, float, float> > neuronOutput = intraLegCoordination(tsp);
    /*for(int i; i<neuronOutput.size(); i++)
    {
        cout << get<0>(neuronOutput[i]) << ",  " << get<1>(neuronOutput[i]) << ",  " << get<2>(neuronOutput[i]) << endl;
    }*/

    cout << "Plotting the CPG signals. Check CPG_groups.csv and CPG_leg.csv in genfiles/ dir." << endl;

    //Data storing
    int st = neuronOutput.size();
    float H1[st], H2[st], R1[st], R2[st], R3[st], L1[st], L2[st], L3[st], times[st];
    for(int i; i<st; i++)
    {
        times[i] = get<0>(neuronOutput[i]);
        H1[i] = R1[i] = R3[i] = L2[i] = get<1>(neuronOutput[i]);
        H2[i] = L1[i] = L3[i] = R2[i] = get<2>(neuronOutput[i]);
    }
    
    // Storing data
    ofstream fs1, fs2;
    
    // Grouped legs pattern
    fs1.open("../genfiles/CPG_groups.csv");
    for (int i; i<st; i++)
    {
        fs1 << get<0>(neuronOutput[i]) << "," << get<1>(neuronOutput[i]) << "," << get<2>(neuronOutput[i]) << endl;
    }
    fs1.close();

    // Leg coordination gait
    fs2.open("../genfiles/CPG_leg.csv");
    for (int i; i<st; i++)
    {
        fs2 << times[i] << "," << R1[i] << "," << R2[i] << "," << R3[i] << "," << L1[i] << "," << L2[i] << "," << L3[i] << endl;
    }
    fs2.close();

    cout << "Program Finished." << endl;

    return 0;
}