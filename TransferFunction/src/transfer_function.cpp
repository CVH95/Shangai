#include <transfer_function.h>


// Gaussian transfer function
float transfer_function::gaussian(float x, float std)
{

    float y = exp((- x*x ) / (2*std*std));
    return y;

}

// Linear combination y = x
float transfer_function::linear(float x)
{
    return x;
}

// Linear function biased (slope and offset)
float transfer_function::linear_biased(float x, float m, float n)
{
    float y = m*x + n;
    return y;
}

// Sigmoid function
// Range [0, 1]
float transfer_function::sigmoid(float x)
{
    float y = 1 / (1 + exp(-x));
    return y;
}

// Step function
float transfer_function::step_threshold(float x, float threshold)
{
    float y;
    if( x <= threshold )
    {
        y = 0.0;
    }
    else
    {
        y = 1.0;
    }

    return y;
}

// Hyperbolic tangent activation function 
// Range [-1, 1]
float transfer_function::tanh(float x)
{
    float y = ((2.0/ (1.0 + exp(-2.0 * x))) - 1.0);
    return y;
}