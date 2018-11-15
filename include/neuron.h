// Creating a neuron class.

#ifndef NEURON_H_
#define NEURON_H_

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
#include <map>
#include <vector>
#include <transfer_function.h>

class neuron{

    public:

        // Constructor
        neuron();

        // Functions
        void tanh_output();
        float get_activity();
        float get_output();
        void set_activity(float a);

    private:

        float activity;
        float output;
};

#endif /* NEURON_H_ */