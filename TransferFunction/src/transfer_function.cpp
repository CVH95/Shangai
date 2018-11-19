#include <transfer_function.h>

// Cosine function (x must be in radians)
float transfer_function::cosine(float amp, float f, float rad)
{
    float w = 2*PI*f;
    float y = amp*cos(w*rad);
    return y;
}

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

// Sine function (x must be in radians)
float transfer_function::sine(float amp, float f, float rad)
{
    float w = 2*PI*f;
    float y = amp*sin(w*rad);
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

// Thresholded sine
tuple<float, float> transfer_function::thresholded_sine(float amp, float f, float rad, float z_prev)
{
    float w = 2*PI*f;
    float y;
    float z = amp*sin(w*rad);
    // First threshold, on F(x)
    if(z >= 0.0)
    {
        // Second threshold, on F'(x)
        float diff = z - z_prev;
        if(diff >= 0.0)
        {
            y = z;
        }
        else
        {
            y = 0;
        }
    }
    else
    {
        y = 0.0;
    }
    return make_tuple(y, z);
}