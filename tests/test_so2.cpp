#include "so2_cpg.h"


using namespace std;

int main()
{
    cout << "------------------------------------" << endl;
    cout << "           SO2 CPG TEST" << endl;
    cout << "------------------------------------" << endl << endl;

    
    // WHY THE HELL IS IT NOT WORKING WITHOUT THIS PART??
    //------------------------------------------------------------
    transfer_function G;
    float y = G.tanh(1.5);

    cout << "y = " << y << endl;

    neuron n;

    //n.set_activity(0.67);

    //float a = n.get_activity();

    //cout << "activity = " << a << endl;
    //-----------------------------------------------------------

    // Creating SO2 object.
    so2 C;

    // Time initialization:
    float t0 = 0.0;
    float tf = 10.0;
    float f = 10*10;
    int sample = (tf-t0)*f +1;
    vector<float> tsp = C.timeSpace(t0, tf, sample);

    // Network Parameters initialization
    
    // Initialize outputs
    float o1 = 0.0;
    float o2 = 0.0;

    // Weights:
    vector<float> ws;
    float w11 = 1.4;
    float w22 = 1.4;
    float w12 = 0.18;
    float w21 = 0.18;
    ws.push_back(w11);
    ws.push_back(w22);
    ws.push_back(w12);
    ws.push_back(w21);

    // Biases:
    vector<float> bs;
    float b1 = 0.01;
    float b2 = 0.01;
    bs.push_back(b1);
    bs.push_back(b2);

    // Frequency
    float hz = 0.0; // Uses value by default


    cout << "Initialized with the following parameters:" << endl;
    cout << "   >> Time: " << tf << " secs" << endl;
    cout << "   >> Sample: " << sample << endl;
    cout << "   >> Wave frequency: ";
    if(hz == 0.0)
    {
        cout << " Default value of 0.02 hz" << endl;
    }
    else
    {
        cout << hz << " Hz." << endl;
    }
    cout << "   >> Weights: {" << w11 << ", " << w22 << ", " << w12 << ", " << w21 << "}" << endl;
    cout << "   >> Biases: {" << b1 << ", " << b2 << "}" << endl << endl;

    // Compute SO2 Network
    vector<tuple<float, float, float> > ntw_out;
    for(size_t j; j<tsp.size(); j++)
    {
        float ti = tsp[j];
        tuple<float, float, float> O = C.intraLegCoordination(ti, ws, bs, hz, o1, o2);
        ntw_out.push_back(O);
        
        // Updates for next iteration
        o1 = get<1>(ntw_out[j]);
        o2 = get<2>(ntw_out[j]);
        C.udpate_output(o1, o2);
        //vector<float> oss = C.get_output();
        //cout << "Output (ti, o1, o2) = (" << get<0>(ntw_out[j]) << ", " << oss[0] << ", " << oss[1] << ")" << endl;
   
    }

    // Storing data to later plots:
    ofstream fs1;
    fs1.open("../genfiles/CPG_test.csv");
    int st = ntw_out.size();
    for (int i; i<st; i++)
    {
        fs1 << get<0>(ntw_out[i]) << "," << get<1>(ntw_out[i]) << "," << get<2>(ntw_out[i]) << endl;
    }
    fs1.close();

    cout << "CPG values stored as <time, output_C1, output_C2>" << endl;
    cout << "Test Finished. Results saved to $ROOT/genfiles/CPG_test.csv" << endl;

    return 0;
}
