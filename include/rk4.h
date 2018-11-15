// Runge-Kutta ODE Solver for online muscle control
//  - Inputs:
//          + x == initial possition
//          + v == initial velocity
//          + a == acceleration
//          + dt == time step (for differential approximation)
//          + f == force function 
// VAAM Muscle Dynamics: (ddx/ddt) + (2*(dx/t) + 2*x(t)) = cos(2(t))
// VAAM Muscle Dynamics: a(t) + (2*v(t) + 2*x(t)) = cos(2(t))

#ifndef RK4_H_
#define RK4_H_

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

class rk4{

    public:

        // Functions
        float acceleration(float x, float v, float dt, float f);
        vector<float> compute_rk4(float x, float v, float dt, float f);
        vector<float> diff(vector<float> X, float t);
};

#endif /* RK4_H_ */