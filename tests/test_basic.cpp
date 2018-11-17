// TEST 1.0 - VELOCITY REDUCTION NETWORK

#include "transfer_function.h"
#include "neuron.h"
#include "so2_cpg.h"

using namespace std;

float y;

int main()
{
    cout << "Hello world" << endl;
    transfer_function G;

    y = G.linear_biased(0.5, 2.3, 0.015);

    cout << "y = " << y << endl;

    neuron n;

    n.set_activity(0.67);

    float a = n.get_activity();

    cout << "activity = " << a << endl;

    so2 cpg;

    /*vector<float> opts;
    opts.push_back(0.25);
    opts.push_back(0.75);*/

    cpg.udpate_output(0.25, 0.75);
    vector<float> up_opts = cpg.get_output();

    cout << "CPG output = (" << up_opts[0] << ", " << up_opts[1] << ")" << endl;

    return 0;
}