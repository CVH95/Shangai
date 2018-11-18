// VRN TEST. MODULAR NEURAL CONTROLLER


// BASIC HEXAPOD ROBOT CONTROL ACTIONS

/*
i1 == All joint inhibition
i2 == FTi inhibition
i3 == PSN inputs -> Sideways motion control
i4, i5 == VRN inputs -> Fordward, backwards and turning motion control

|Action    |i1    |i2    |i3    |i4    |i5    |
|----------|:----:|:----:|:----:|:----:|:----:|
|Forward   |0     |1     |0     |-1    |-1    |
|Backwards |0     |1     |0     |1     |1     |
|Turn right|0     |1     |0     |-1    |1     |
|Turn left |0     |1     |0     |1     |-1    |
*/

#include "so2_cpg.h"
#include "psn.h"
#include "vrn.h"



using namespace std;

int main()
{
    cout << "------------------------------------" << endl;
    cout << "  VELOCITY REDUCTION NETWORK TEST" << endl;
    cout << "------------------------------------" << endl << endl;

    
    // WHY THE HELL IS IT NOT WORKING WITHOUT THIS PART??
    //------------------------------------------------------------
    transfer_function G;
    float y = G.tanh(1.5);

    //cout << "y = " << y << endl;

    neuron n;
    //-----------------------------------------------------------

    // SO2 Initialization
    so2 C;

    // Time initialization:
    float t0 = 0.0;
    float tf = 20.0;
    float f = 20*10;
    int sample = (tf-t0)*f +1;
    vector<float> tsp = C.timeSpace(t0, tf, sample);

    // Network Parameters
    
    // Initialize outputs
    float o1 = 0.0;
    float o2 = 0.0;

    // Weights:
    vector<float> ws;
    float ww11 = 1.4;
    float ww22 = 1.4;
    float ww12 = 0.18;
    float ww21 = 0.18;
    ws.push_back(ww11);
    ws.push_back(ww22);
    ws.push_back(ww12);
    ws.push_back(ww21);

    // Biases:
    vector<float> bs;
    float bb1 = 0.01;
    float bb2 = 0.01;
    bs.push_back(bb1);
    bs.push_back(bb2);

    // Frequency
    float hz = 0.0; // Uses value by default


    cout << "Initialized SO2 CPG with the following parameters:" << endl;
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
    cout << "   >> Weights: {" << ww11 << ", " << ww22 << ", " << ww12 << ", " << ww21 << "}" << endl;
    cout << "   >> Biases: {" << bb1 << ", " << bb2 << "}" << endl << endl;

    // PSN Initialization
    psn P;

    // Network Parameters
    vector<float> psn_inputs;
    float i4 = 0.0;
    float i3 = -i4;

    // Weights (absolute value):
    vector<float> wp;
    float w15 = 0.5;
    float w18 = 0.5;
    float w26 = 0.5;
    float w27 = 0.5;
    float w35 = 5.0;
    float w37 = 5.0;
    float w46 = 5.0;
    float w48 = 5.0;
    float w59 = 0.5;
    float w610 = 0.5;
    float w711 = 0.5;
    float w812 = 0.5;
    float w913 = 3.0;
    float w1013 = 3.0;
    float w1114 = 3.0;
    float w1214 = 3.0;
    wp.push_back(w15);
    wp.push_back(w18);
    wp.push_back(w26);
    wp.push_back(w27);
    wp.push_back(w35);
    wp.push_back(w37);
    wp.push_back(w46);
    wp.push_back(w48);
    wp.push_back(w59);
    wp.push_back(w610);
    wp.push_back(w711);
    wp.push_back(w812);
    wp.push_back(w913);
    wp.push_back(w1013);
    wp.push_back(w1114);
    wp.push_back(w1214);

    // Biases (absolute values):
    vector<float> bp;
    float b5 = 1.0;
    float b9 = 0.5;
    float b10 = 0.5;
    float b11 = 0.5;
    float b12 = 0.5;
    float b13 = 1.35;
    float b14 = 1.35;
    bp.push_back(b5);
    bp.push_back(b9);
    bp.push_back(b10);
    bp.push_back(b11);
    bp.push_back(b12);
    bp.push_back(b13);
    bp.push_back(b14);

    // Outputs
    float _o11;
    float _o12;

    cout << "Initialized PSN network with the following parameters:" << endl;
    cout << "   >> Network inputs: {CPG_out1, CPG_out2, " << i3 << ", " << i4 << "}" << endl;
    
    cout << "   >> Weights: {" << wp[0];
    for(size_t a=1; a<wp.size(); a++)
    {
        cout << ", " << wp[a];
    }
    cout << "}" << endl;
    cout << "   >> Biases: {" << b5 << ", " << b9 << ", " << b10 << ", " << b11 << ", " << b12 << ", " << b13 << ", " << b14 << "}" << endl << endl; 

    // Left VRN initialization
    vrn VLeft;
    float vp;

    // Network parameters
    vector<float> left_vrn_inputs;
    float left_ctrl_i;

    // Weights (absolute value)
    vector<float> wlv;
    float lw13 = 1.7246;
    float lw14 = 1.7246;
    float lw15 = 1.7246;
    float lw16 = 1.7246;
    float lw23 = 1.7246;
    float lw24 = 1.7246;
    float lw25 = 1.7246;
    float lw26 = 1.7246;
    float lw37 = 0.5;
    float lw47 = 0.5;
    float lw57 = 0.5;
    float lw67 = 0.5;
    wlv.push_back(lw13);
    wlv.push_back(lw14);
    wlv.push_back(lw15);
    wlv.push_back(lw16);
    wlv.push_back(lw23);
    wlv.push_back(lw24);
    wlv.push_back(lw25);
    wlv.push_back(lw26);
    wlv.push_back(lw37);
    wlv.push_back(lw47);
    wlv.push_back(lw57);
    wlv.push_back(lw67);

    // Biases (absolute value)
    vector<float> blv;
    float bl3 = 2.48285;
    float bl4 = 2.48285;
    float bl5 = 2.48285;
    float bl6 = 2.48285;
    blv.push_back(bl3);
    blv.push_back(bl4);
    blv.push_back(bl5);
    blv.push_back(bl6);
    
    // Output
    float _o7l;

    // Right VRN initialization
    vrn VRight;

    // Network parameters
    vector<float> right_vrn_inputs;
    float right_ctrl_i;

    // Weights (absolute value)
    vector<float> wrv;
    float rw13 = 1.7246;
    float rw14 = 1.7246;
    float rw15 = 1.7246;
    float rw16 = 1.7246;
    float rw23 = 1.7246;
    float rw24 = 1.7246;
    float rw25 = 1.7246;
    float rw26 = 1.7246;
    float rw37 = 0.5;
    float rw47 = 0.5;
    float rw57 = 0.5;
    float rw67 = 0.5;
    wrv.push_back(rw13);
    wrv.push_back(rw14);
    wrv.push_back(rw15);
    wrv.push_back(rw16);
    wrv.push_back(rw23);
    wrv.push_back(rw24);
    wrv.push_back(rw25);
    wrv.push_back(rw26);
    wrv.push_back(rw37);
    wrv.push_back(rw47);
    wrv.push_back(rw57);
    wrv.push_back(rw67);

    // Biases (absolute value)
    vector<float> brv;
    float br3 = 2.48285;
    float br4 = 2.48285;
    float br5 = 2.48285;
    float br6 = 2.48285;
    brv.push_back(br3);
    brv.push_back(br4);
    brv.push_back(br5);
    brv.push_back(br6);

    // Output
    float _o7r;

    cout << "Initialized left and right VRN networks with the following parameters:" << endl;
    cout << "   >> Network inputs: {PSN_output2, -1.0}" << endl;
    
    cout << "   >> Weights: {" << wrv[0];
    for(size_t a=1; a<wrv.size(); a++)
    {
        cout << ", " << wrv[a];
    }
    cout << "}" << endl;
    cout << "   >> Biases: {" << br3 << ", " << br4 << ", " << br5 << ", " << br6 << "}" << endl << endl;


//----------------------------------------------------------------------------------------------------

   
    // Compute Network
    vector<tuple<float, float, float> > cpg_out;
    vector<float> psn_out;
    vector<tuple<float, float> > psn_outputs;
    vector<float> left_vrn_out;
    vector<float> right_vrn_out;
    vector<tuple<float, float> > vrn_outputs;
    for(size_t j; j<tsp.size(); j++)
    {
        float ti = tsp[j];
     
        // Compute SO2 network
        tuple<float, float, float> O = C.intraLegCoordination(ti, ws, bs, hz, o1, o2);
        cpg_out.push_back(O);
        
        // CPG Updates for next iteration
        o1 = get<1>(cpg_out[j]);
        o2 = get<2>(cpg_out[j]);
        C.udpate_output(o1, o2);
        

        // Set PSN inputs
        psn_inputs.push_back(o1);
        psn_inputs.push_back(o2);
        psn_inputs.push_back(i3);
        psn_inputs.push_back(i4);

        // Compute PSN network
        psn_out = P.compute_psn_network(psn_inputs, wp, bp);

        // PSN outputs
        _o11 = psn_out[10];
        _o12 = psn_out[11];
        P.update_network_output(_o11, _o12);
        psn_outputs.push_back(make_tuple(_o11, _o12));
    

        // Set VRNs' inputs (the connection between PSN_output2 and VRNs is weighted with w = 1.75)
        vp = 1.75 * _o12;
        left_vrn_inputs.push_back(vp);
        right_vrn_inputs.push_back(vp);

        // Changing directions:
        // Move forward 
        if ((ti >= 0.0) < (ti < 5.0))
        {
            left_ctrl_i = -1.0;
            right_ctrl_i = -1.0;
            left_vrn_inputs.push_back(left_ctrl_i);
            right_vrn_inputs.push_back(right_ctrl_i);
        }
        // Move backwards
        else if((ti >= 5.0) && (ti < 10.0))
        {
            left_ctrl_i = 1.0;
            right_ctrl_i = 1.0;
            left_vrn_inputs.push_back(left_ctrl_i);
            right_vrn_inputs.push_back(right_ctrl_i);
        }
        // Turn right
        else if((ti >= 10.0) && (ti < 15.0))
        {
            left_ctrl_i = 1.0;
            right_ctrl_i = -1.0;
            left_vrn_inputs.push_back(left_ctrl_i);
            right_vrn_inputs.push_back(right_ctrl_i);
        }
        // Turn left
        else if(ti >= 15.0)
        {
            left_ctrl_i = -1.0;
            right_ctrl_i = 1.0;
            left_vrn_inputs.push_back(left_ctrl_i);
            right_vrn_inputs.push_back(right_ctrl_i);
        }
        // By default, move forward
        else
        {
            left_ctrl_i = -1.0;
            right_ctrl_i = -1.0;
            left_vrn_inputs.push_back(left_ctrl_i);
            right_vrn_inputs.push_back(right_ctrl_i);
        }

        // Compute VRNs
        left_vrn_out = VLeft.compute_vrn_network(left_vrn_inputs, wlv, blv);
        right_vrn_out = VRight.compute_vrn_network(right_vrn_inputs, wrv, brv);
        
        // VRNs' outputs
        _o7l = left_vrn_out[6];
        _o7r = right_vrn_out[6];
        vrn_outputs.push_back(make_tuple(_o7l, _o7r));
        VLeft.update_network_output(_o7l);
        VRight.update_network_output(_o7r);

        // Clear all vectors for next iteration 
        psn_inputs.clear();
        psn_out.clear(); 
        left_vrn_inputs.clear();
        right_vrn_inputs.clear();
        left_vrn_out.clear();
        right_vrn_out.clear();
   
    }

    // Storing data to later plots:
    ofstream fs1;
    //fs1.open("../genfiles/PSN_test.csv");
    fs1.open("../genfiles/VRN_test.csv");
    int st = psn_outputs.size();
    for (int i; i<st; i++)
    {
        fs1 << get<0>(cpg_out[i]) << "," << get<1>(cpg_out[i]) << "," << get<2>(cpg_out[i]) << "," << get<0>(psn_outputs[i]) << "," << get<1>(psn_outputs[i]) << "," << get<0>(vrn_outputs[i]) << "," << get<1>(psn_outputs[i]) << endl;
    }
    fs1.close();

    cout << "Network values stored as <time, output_CPG1, output_CPG2, output_PSN1, output_PSN2, left_VRN_output, right_VRN_output>" << endl;
    cout << "Test Finished. Results saved to $ROOT/genfiles/VRN_test.csv" << endl;

    return 0;
}