#include "neuron.h"

// Constructor
neuron::neuron()
{
    activity = 0;
    output = 0;
}

// Calculate output
// Requires defining a transfer function type.
void neuron::tanh_output()
{
    output = G.tanh(activity);

    /*
    Needs further development.
    // Selection of the function:
    switch (f)
    {
        case 0:
            output = G.gaussian(activity);
        case 1:
            output = G.linear(activity);
        case 2:
            output = G.linear_biased(activity);
        case 3:
            output = G.sigmoid(activity);
        case 4:
            output = G.step_threshold()
    }*/
    
}

// Get activity
float neuron::get_activity()
{
    return activity;
}

// Get output
float neuron::get_output()
{
    return output;
}

// Calculate activity
void neuron::set_activity(float a)
{
    activity = a;
}