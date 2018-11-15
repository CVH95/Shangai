#include <rk4.h>

using namespace std;

// Acceleration calculus function
float rk4::acceleration(float x, float v, float dt, float f)
{
    float stiffness = 2.0;
    float damping = 2.0;
    float a = (f-stiffness*x) - damping*v;
    return a;
}

// Main calculator
vector<float> rk4::compute_rk4(float x, float v, float dt, float f)
{
    // Constructor
    vector<float> rk;

    float x1 = x;
    float v1 = v;
    float a1 = acceleration(x1, v1, 0, f);

    float x2 = x + 0.5*v1*dt;
    float v2 = v + 0.5*a1*dt;
    float a2 = acceleration(x2, v2, dt/2.0, f);

    float x3 = x + 0.5*v2*dt;
    float v3 = v + 0.5*a2*dt;
    float a3 = acceleration(x3, v3, dt/2.0, f);

    float x4 = x + v3*dt;
    float v4 = v + a3*dt;
    float a4 = acceleration(x4, v4, dt, f);

    float xf = x + (dt/6.0)*(v1 + 2*v2 + 2*v3 + v4);
    float vf = v + (dt/6.0)*(a1 + 2*a2 + 2*a3 + a4);

    rk.push_back(xf);
    rk.push_back(vf);

    return rk;
}

// Derivative function to calculate velocity at a point.
// Given an initial point X=(x1, x2), returns (x1', x2')
vector<float> rk4::diff(vector<float> X, float t)
{
    vector<float> drv;
    drv.push_back(X[1]);
    float x2p = -2*X[1] - 2*X[0] + cos(2*t);
    drv.push_back(x2p);

    return drv;
}