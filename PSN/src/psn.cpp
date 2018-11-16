#include <psn.h>

// Constructor
psn::psn()
{
    network_output1 = 0;
    network_output2 = 0;
}


// Requires defining vector variables as inputs[4], weights[16], biases[7]:
// inputs = (i1, i2, i3, i4)
// i1, i2 come from CG; i3 = - i4
// weights = (w15, w18, w26, w27, w35, w37, w46, w48, w59, w610, w711, w812, w913, w1013, w1114, w1214) 
// Weights must be defined in absolute value!!!!
// biases = (b5, b9, b10, b11, b12, b13, b14) 
// Biases must be defined in absolute value!!!
// The 2 first "neurons" H1 and H2 do not modify CPG signal
vector<float> psn::compute_psn_network(vector <float> inputs, vector<float> weights, vector<float> biases)
{
    vector<float> neuron_outputs;
    
    // Neurons
    neuron n1;// = new neuron::neuron();
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

    // Activities in layer 1:
    float a1 = inputs[2] + biases[0];
    n1.set_activity(a1); // i3 
    n2.set_activity(inputs[3]); // i4 

    // Outputs in layer 1:
    n1.tanh_output();
    n2.tanh_output();
    float o1 = n1.get_output();
    neuron_outputs.push_back(o1);
    float o2 = n2.get_output();
    neuron_outputs.push_back(o2);

    // Activities in layer 2:
    float a3 = inputs[0]*weights[0] - o1*weights[4];
    float a4 = inputs[1]*weights[2] - o2*weights[6];
    float a5 = inputs[1]*weights[3] + o1*weights[5];
    float a6 = inputs[0]*weights[1] + o1*weights[7];
    n3.set_activity(a3);
    n4.set_activity(a4);
    n5.set_activity(a5);
    n6.set_activity(a6);

    // Outputs in layer 2:
    n3.tanh_output();
    n4.tanh_output();
    n5.tanh_output();
    n6.tanh_output();
    float o3 = n3.get_output();
    float o4 = n4.get_output();
    float o5 = n5.get_output();
    float o6 = n6.get_output();
    neuron_outputs.push_back(o3);
    neuron_outputs.push_back(o4);
    neuron_outputs.push_back(o5);
    neuron_outputs.push_back(o6);

    // Activities in layer 3:
    float a7 = o3*weights[8] + biases[1];
    float a8 = o4*weights[9] + biases[2];
    float a9 = o5*weights[10] + biases[3];
    float a10 = o6*weights[11] + biases[4];
    n7.set_activity(a7);
    n8.set_activity(a8);
    n9.set_activity(a9);
    n10.set_activity(a10);

    // Outputs in layer 3:
    n7.tanh_output();
    n8.tanh_output();
    n9.tanh_output();
    n10.tanh_output();
    float o7 = n7.get_output();
    float o8 = n8.get_output();
    float o9 = n9.get_output();
    float o10 = n10.get_output();
    neuron_outputs.push_back(o7);
    neuron_outputs.push_back(o8);
    neuron_outputs.push_back(o9);
    neuron_outputs.push_back(o10);

    // Activities in layer 4:
    float a11 = o7*weights[12] + o8*weights[13] - biases[5];
    float a12 = o9*weights[14] + o10*weights[15] - biases[6];
    n11.set_activity(a11);
    n12.set_activity(a12);

    // Outputs in layer 4:
    n11.tanh_output();
    n12.tanh_output();
    float o11 = n11.get_output();
    neuron_outputs.push_back(o11);
    float o12 = n12.get_output();
    neuron_outputs.push_back(o12);

    return neuron_outputs;
}

// Get network output
vector<float> psn::get_output()
{
    vector<float> outputs;
    
    outputs.push_back(network_output1);
    outputs.push_back(network_output2);

    return outputs;
}

// Update outputs
void psn::update_network_output(float o13, float o14)
{
    network_output1 = o13;
    network_output2 = o14;
}
