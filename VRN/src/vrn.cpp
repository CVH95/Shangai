#include <vrn.h>

// Constructor
vrn::vrn()
{
    network_output = 0;
}

// Requires defining vector variables as inputs[2], weights[12], biases[12]:
// inputs = (i1, i2)
// weights = (w13, w14, w15, w16, w23, w24, w25, w26, w37, w47, w57, w67) 
// Weights must be defined in absolute value!!!!
// biases = (b3, b4, b5, b6) 
// Biases must be defined in absolute value!!!
vector<float> vrn::compute_vrn_network(vector<float> inputs, vector<float> weights, vector<float> biases)
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

    // Activities in layer 1:
    n1.set_activity(inputs[0]);
    n2.set_activity(inputs[1]);

    // Outputs in layer 1:
    n1.tanh_output();
    n2.tanh_output();
    float o1 = n1.get_output();
    neuron_outputs.push_back(o1);
    float o2 = n2.get_output();
    neuron_outputs.push_back(o2);

    // Activities in layer 2:
    float a3 = o1*weights[0] + o2*weights[4] - biases[0];
    float a4 = - o1*weights[1] - o2*weights[5] - biases[1];
    float a5 = o1*weights[2] - o2*weights[6] - biases[2];
    float a6 = - o1*weights[3] + o2*weights[7] - biases[3];
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
    
    // Activity in layer 3:
    float a7 = o3*weights[8] + o4*weights[9] - o5*weights[10] - o6*weights[11];
    n7.set_activity(a7);

    // Output in layer 3:
    n7.tanh_output();
    float o7 = n7.get_output();
    neuron_outputs.push_back(o7);

    return neuron_outputs;
}

// Get network output
float vrn::get_output()
{
    return network_output;
}


// Update outputs
void vrn::update_network_output(float o7)
{
    network_output = o7;
}
