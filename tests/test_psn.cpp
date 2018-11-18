#include "so2_cpg.h"
#include "psn.h"


using namespace std;

int main()
{
    cout << "------------------------------------" << endl;
    cout << "    PHASE SITHCHING NETWORK TEST" << endl;
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
    float i3;
    float i4;

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


    cout << "Initialized PSN network with the following parameters:" << endl;
    cout << "   >> Sensor inputs: {CPG_out1, CPG_out2, " << 0.0 << ", " << 0.0 << "}" << endl;
    
    cout << "   >> Weights: {" << wp[0];
    for(size_t a=1; a<wp.size(); a++)
    {
        cout << ", " << wp[a];
    }
    cout << "}" << endl;
    cout << "   >> Biases: {" << b5 << ", " << b9 << ", " << b10 << ", " << b11 << ", " << b12 << ", " << b13 << ", " << b14 << "}" << endl << endl; 



//----------------------------------------------------------------------------------------------------

    ofstream fs2;
    //fs2.open("../genfiles/PSN_full_network_outputs.csv");
    fs2.open("../genfiles/PSN_progressive_full_network_outputs.csv");

    // Compute Network
    vector<tuple<float, float, float> > cpg_out;
    vector<float> ntw_out;
    vector<tuple<float, float> > psn_outputs;
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

        // Progressive
        if ((ti >= 0.0) < (ti < 5.0))
        {
            i4 = 0.0;
            i3 = - i4;
            psn_inputs.push_back(i3);
            psn_inputs.push_back(i4);
        }
        else if((ti >= 5.0) && (ti < 10.0))
        {
            i4 = 0.25;
            i3 = - i4;
            psn_inputs.push_back(i3);
            psn_inputs.push_back(i4);
        }
        else if((ti >= 10.0) && (ti < 15.0))
        {
            i4 = 0.50;
            i3 = - i4;
            psn_inputs.push_back(i3);
            psn_inputs.push_back(i4);
        }
        else if(ti >= 15.0)
        {
            i4 = 0.75;
            i3 = - i4;
            psn_inputs.push_back(i3);
            psn_inputs.push_back(i4);
        }
        else
        {
            float i4 = 0.0;
            float i3 = - i4;
            psn_inputs.push_back(i3);
            psn_inputs.push_back(i4);
        }

        

        // Compute PSN network
        ntw_out = P.compute_psn_network(psn_inputs, wp, bp);

        // Store Network outputs
        fs2 << ti << "," << ntw_out[0]; 
        for(int v=1; v<ntw_out.size(); v++)
        {
            fs2 << "," << ntw_out[v];
        }
        fs2 << endl;

        // PSN outputs
        float _o11 = ntw_out[10];
        float _o12 = ntw_out[11];
        P.update_network_output(_o11, _o12);
        psn_outputs.push_back(make_tuple(_o11, _o12));

        // Clear vectors for next iteration PSN values
        psn_inputs.clear();
        ntw_out.clear(); 
   
    }

    fs2.close();

    // Storing data to later plots:
    ofstream fs1;
    //fs1.open("../genfiles/PSN_test.csv");
    fs1.open("../genfiles/PSN_progressive_test.csv");
    int st = psn_outputs.size();
    for (int i; i<st; i++)
    {
        fs1 << get<0>(cpg_out[i]) << "," << get<1>(cpg_out[i]) << "," << get<2>(cpg_out[i]) << "," << get<0>(psn_outputs[i]) << "," << get<0>(psn_outputs[i]) << endl;
    }
    fs1.close();

    cout << "Network values stored as <time, output_CPG1, output_CPG2, output_PSN1, output_PSN2>" << endl;
    cout << "PSN internal values stored as <time, o1, o2, ... , o12>" << endl;
    cout << "Test Finished. Results saved to $ROOT/genfiles/PSN_full_network_outputs.csv and $ROOT/genfiles/PSN_test.csv" << endl;

    return 0;
}