// Runge-Kutta 4 ODE method for online control

#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <sstream>

#define PI 3.14159265

using namespace std;


// Acceleration calculus function
float acceleration(float x, float v, float dt, float f)
{
    float stiffness = 2.0;
    float damping = 2.0;
    float a = (f-stiffness*x) - damping*v;
    return a;
}

// Runge-Kutta Solver
//  - Inputs:
//          + x == initial possition
//          + v == initial velocity
//          + a == acceleration
//          + dt == time step (for differential approximation)
//          + f == force function 
// VAAM Muscle Dynamics: (ddx/ddt) + (2*(dx/t) + 2*x(t)) = cos(2(t))
// VAAM Muscle Dynamics: a(t) + (2*v(t) + 2*x(t)) = cos(2(t))
vector<float> rk4(float x, float v, float dt, float f)
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
vector<float> diff(vector<float> X, float t)
{
    vector<float> drv;
    drv.push_back(X[1]);
    float x2p = -2*X[1] - 2*X[0] + cos(2*t);
    drv.push_back(x2p);

    return drv;
}

int main()
{
    // Time Initialization:
    float t0 = 0.0;
    float tf = 10.0;
    float steps = 100.0;
    float dt = (tf-t0)/steps;
    float t = t0;
    float f;

    // Preparing data storage file
    ofstream fdata;
    fdata.open("../genfiles/data.csv");
    cout << "RUNGE-KUTTA 4 ODE NUMERICAL SOLVER" << endl;
    cout << "(ddx/ddt) + (2*(dx/t) + 2*x(t)) = cos(2(t))" << endl;
    cout << "Plotting position x(t) and velocity dx/dt (v(t)) approximated by RK4 method." << endl;
    cout << "Data points are stored in the file such that:" << endl;
    cout << "TIME, POSITION, VELOCITY" << endl;
    cout << "Opening storage file. ChEck data.csv file after program finishes." << endl;
    
    // Initial position:
    /*// Uncomment for if plotting capabilities are added. Use rkpos as a rk position linespace.
    float rkpos[steps];
    for (int i=0; i<steps; i++)
    {
        rkpos[i] = 0.0;
    }
    */
    float rkstate[2] = { 0.0, 0.0};
    int id = 0;

    // Running ODE solver
    while (t < tf)
    {
        // Force function w.r.t. time
        f = cos(2*t);

        // Solving ODE by RK4 approximation
        vector<float> ode_sol = rk4(rkstate[0], rkstate[1], dt, f);
        float xf = ode_sol[0];
        float vf = ode_sol[1];
        
        // Update system state
        rkstate[0] = xf;
        rkstate[1] = vf;

        // Data Storage
        fdata << t << "," << xf << "," << vf << endl;

        // Increment time step
        t = t + dt;

        // flush ode_sol
        ode_sol.clear();
    }

    fdata.close();
    cout << "Program finished." << endl;

    return 0;
}