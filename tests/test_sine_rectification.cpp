// Sine rectification function

#include "transfer_function.h"

using namespace std;

int main()
{
    transfer_function G;
    float amp = 2.0;
    float t, y;
    tuple<float, float> h; // tuple == (y; z_to_set_as_z_prev)
    float z_prev = 0.0;

    // Data storing
    ofstream fs;
    fs.open("../genfiles/test_sine_rectification.csv");

    for(t = 0.0; t<4.0; t = t+0.05)
    {
        y = G.sine(amp, 1.0, t);
        //z = G.sine(amp, 0.1, t);
        h = G.thresholded_sine(amp, 1.0, t, z_prev);

        fs << t << "," << y << "," << get<0>(h) << endl;

        // Update z_prev
        z_prev = get<1>(h);
    }

    fs.close();
    cout << "Program done. Data saved to ../genfiles/test_sine_rectification.csv in fomrat <t, y, z>" << endl;

    return 0;
}