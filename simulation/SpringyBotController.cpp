/*

 	Created on: Dec 7th, 2018
    Author: cavie17@student.sdu.dk
 
*/

#include <assert.h>

#include "SpringyBotController.h"

using namespace std;
using namespace matrix;

// The constructor implements the AbstractController interface. A trial number can be
// passed to the constuctor in order to automate variations in the controller setup
// over different trials.
SpringyBotController::SpringyBotController(const std::string& name)
: AbstractController(name, "1.0") {
	initialised=false;

	cout << "---- Simulation of different gaits with SpringyBot: ----" << endl;
	cout << "0: Nothing." << endl;
	cout << "1: Forward walking at constant speed" << endl;
	cout << "Enter Gait Type:  ";
	cin >> setGait;

	ticks_since_init = 0.0;
	itime = 0.0;
	itime_step = 0.01;
  
	speedSetpoint = 8.0;
	phaseSetpoint = 4.0;
	
	output.open("output.csv");
	//gaitf.open("gait.csv");
}

SpringyBotController::~SpringyBotController() 
{
	output.close();
	cout << "Simulation Finished." << endl;
	cout << "Stopped recording output motor values: Saved to output.csv." << endl;
	cout << "Stored as ticks, FrontLeft, FrontRight, BackLeft, BackRight." << endl << endl;
	cout << "-------------SUMARY----------------" << endl << endl;
	cout << "Ticks accounted: " << ticks_since_init << endl;
	cout << "Actual runtime: " << itime  << " seconds." << endl;
	cout << "Gait: " << SpringyBotController::getGaitType(setGait) << endl;
	cout << "PWM Signal max amplitude: " << speedSetpoint << " radians." << endl;
	cout << "PWM Signal period: " << pwm_period << " seconds." << endl << endl;
	cout << "-----------------------------------" << endl << endl;
}

// Sine function (Phase in deg)
double SpringyBotController::sine(double amp, double period, double phase, double x)
{
	double f = 1/period;
	double rad = phase * (2*M_PI/360);
    double w = 2*M_PI*f;
    double y = amp*sin(w*x + rad);
    return y;
}

void SpringyBotController::stepNoLearning(const sensor* sensors, int number_sensors, motor* motors, int number_motors)
{

}

void SpringyBotController::step(const sensor* sensors, int sensornumber, motor* motors, int motornumber)
{

	// Update internal time
	ticks_since_init++;
	itime = itime + itime_step;

	// Read sensors
	double leftFrontPosition = sensors[SIdx("left front motor")];
	double leftRearPosition = sensors[SIdx("left rear motor")];
	double rightFrontPosition = sensors[SIdx("right front motor")];
	double rightRearPosition = sensors[SIdx("right rear motor")];

	// Motor Commands
	double posFL;
	double posFR;
	double posBL;
	double posBR;

	if(setGait == 0)
	{
		pwm_period = 0;

		posFL = speedSetpoint;
		posFR = -speedSetpoint;
		posBL = speedSetpoint;
		posBR = -speedSetpoint;

		// Set motor speeds
		motors[MIdx("left front motor")] = posFL;
		motors[MIdx("right front motor")] = posFR;
		motors[MIdx("left rear motor")] = posBL;
		motors[MIdx("right rear motor")] = posBR;	
	}

	// Forward walking constant speed
	else if(setGait == 1)
	{	
		// Set signal parameters
		pwm_period = 0.75; 

		// Calculate Motor Positions 
		posFL = SpringyBotController::sine(speedSetpoint, pwm_period, 270, itime); // Front Left +
		posFR = SpringyBotController::sine(speedSetpoint, pwm_period, 90, itime); // Front Right -
		posBL = SpringyBotController::sine(speedSetpoint, pwm_period, 0, itime); // Back Left +
		posBR = SpringyBotController::sine(speedSetpoint, pwm_period, 180, itime); // Back Right -

		// Set motor speeds
		motors[MIdx("left front motor")] = posFL;
		motors[MIdx("right front motor")] = -posFR;
		motors[MIdx("left rear motor")] = posBL;
		motors[MIdx("right rear motor")] = -posBR;
	}
	else
	{
		cout << "Problem setting the Gait, please restart simulation and enter a valid Gait type ID" << endl;
		
		pwm_period = 0;

		posFL = speedSetpoint;
		posFR = speedSetpoint;
		posBL = speedSetpoint;
		posBR = speedSetpoint;

		// Set motor speeds
		motors[MIdx("left front motor")] = posFL;
		motors[MIdx("right front motor")] = posFR;
		motors[MIdx("left rear motor")] = posBL;
		motors[MIdx("right rear motor")] = posBR;	
	}

	// Save data
	SpringyBotController::store(posFL, posFR, posBL, posBR);

}

void SpringyBotController::init(int sensornumber, int motornumber, RandGen* randGen) {
	nSensors = sensornumber;
	nMotors  = motornumber;
	initialised=true;
}

int SpringyBotController::getSensorNumber() const {
	return nSensors;
}

int SpringyBotController::getMotorNumber() const {
	return nMotors;
}

bool SpringyBotController::store(FILE* f) const {
	Configurable::print(f,0);
	return true;
}

bool SpringyBotController::restore(FILE* f) {
	Configurable::parse(f);
	return true;
}


void SpringyBotController::store(double posFL, double posFR, double posBL, double posBR) 
{
		output << ticks_since_init << "," << posFL << "," << posFR << "," << posBL << "," << posBR << endl;
}

string SpringyBotController::getGaitType(int type)
{
	string gaitType;
	if(type == 1)
	{
		gaitType = "Forward walking at constant speed"; 
	}
	else
	{
		gaitType = "Dummy input";
	}

	return gaitType;
}
