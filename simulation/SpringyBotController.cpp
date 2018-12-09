/*

 	Created on: Dec 7th, 2018
    Author: cavie17@student.sdu.dk
 
*/

#include <assert.h>

#include "SpringyBotController.h"

using namespace std;
using namespace matrix;


//=====================================================================================================================================================

// SPRINGYBTCONTROLLER CLASS 

// The constructor implements the AbstractController interface. A trial number can be
// passed to the constuctor in order to automate variations in the controller setup
// over different trials.
SpringyBotController::SpringyBotController(const std::string& name)
: AbstractController(name, "1.0") {
	initialised=false;

	cout << "---- Simulation of different gaits with SpringyBot: ----" << endl;
	cout << "0: Nothing." << endl;
	cout << "1: Forward walking at constant speed." << endl;
	cout << "1: Forward bounding." << endl;
	cout << "1: Forward trotting." << endl;
	cout << "4: Forward pace gait." << endl;
	cout << "Enter Gait Type:  ";
	//cin >> setGait;
	setGait = 1;

	ticks_since_init = 0.0;
	itime = 0.0;
	itime_step = 0.01;
  
	speedSetpoint = 8.0;
	phaseSetpoint = 4.0;

	// String Streams to output the files
	string _path = "../genfiles/simulation/motorValues_";
	string _format = ".csv";
	stringstream ss;
	ss << _path << setGait << _format;
	string motorsFile = ss.str(); 

	string path = "../genfiles/simulation/sensoredValues_";
	stringstream sss;
	sss << path << setGait << _format;
	string sensorFile = sss.str(); 

	string i_path = "../genfiles/simulation/controlValues_";
	stringstream pp;
	pp << i_path << setGait << _format;
	string controlFile = pp.str(); 

	string f_path = "../genfiles/simulation/footprints_";
	stringstream tt;
	tt << f_path << setGait << _format;
	string footprintFile = tt.str(); 

	output.open(motorsFile);
	sensored.open(sensorFile);
	controlled.open(controlFile);
	feet.open(footprintFile);

}

SpringyBotController::~SpringyBotController() 
{
	output.close();
	sensored.close();
	controlled.close();
	feet.close();

	cout << "Simulation Finished." << endl;
	cout << "Stopped recording output motor values: Saved to ../genfiles/simulation/motorValues_(int gaitType).csv." << endl;
	cout << "Stopped recording sensored motor values: Saved to ../genfiles/simulation/sensoredValues_(int gaitType).csv." << endl;
	cout << "Stopped recording controlled motor values: Saved to ../genfiles/simulation/controlValues_(int gaitType).csv." << endl;
	cout << "Stopped recording footprints: Saved to ../genfiles/simulation/footprints_(int gaitType).csv." << endl;
	cout << "NOTE: Stored as ticks, FrontLeft, FrontRight, BackLeft, BackRight." << endl << endl;
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

// Actuation function: Controlling the walking pattern
void SpringyBotController::step(const sensor* sensors, int sensornumber, motor* motors, int motornumber)
{

	// Setting up parameters

	// Update internal time
	ticks_since_init++;
	itime = itime + itime_step;

	// Motor Commands
	double posFL;
	double posFR;
	double posBL;
	double posBR;

	// Feedback Commands
	double errorFL = 0;
	double errorFR = 0;
	double errorBL = 0;
	double errorBR = 0;

	// Control Commands
	double controlFL = 0;
	double controlFR = 0;
	double controlBL = 0;
	double controlBR = 0;

//-------------------------------------------------------------------------------------------------

	// Read sensors
	double leftFrontPosition = sensors[SIdx("left front motor")];
	double leftRearPosition = sensors[SIdx("left rear motor")];
	double rightFrontPosition = sensors[SIdx("right front motor")];
	double rightRearPosition = sensors[SIdx("right rear motor")];


//-------------------------------------------------------------------------------------------------

	/**********************************************/

				 /* WALKING PATTERNS */

	/**********************************************/

	// Default: Nothing happens
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
		speedSetpoint = 8.0;

		// Calculate Motor Positions 
		posFL = SpringyBotController::sine(speedSetpoint, pwm_period, 270, itime); // Front Left +
		posFR = SpringyBotController::sine(speedSetpoint, pwm_period, 90, itime); // Front Right -
		posBL = SpringyBotController::sine(speedSetpoint, pwm_period, 0, itime); // Back Left +
		posBR = SpringyBotController::sine(speedSetpoint, pwm_period, 180, itime); // Back Right -

		// Feedback line
		errorFL = SpringyBotController::phase_controller(posFL, leftFrontPosition);
		errorFR = SpringyBotController::phase_controller(posFR, rightFrontPosition);
		errorBL = SpringyBotController::phase_controller(posBL, leftRearPosition);
		errorBR = SpringyBotController::phase_controller(posBR, rightRearPosition);

		// Control line
		controlFL = SpringyBotController::phase_controller(posFL, errorFL);
		controlFR = SpringyBotController::phase_controller(posFR, errorFR);
		controlBL = SpringyBotController::phase_controller(posBL, errorBL);
		controlBR = SpringyBotController::phase_controller(posBR, errorBR);

		// Set motor speeds
		motors[MIdx("left front motor")] = controlFL;
		motors[MIdx("right front motor")] = -controlFR;
		motors[MIdx("left rear motor")] = controlBL;
		motors[MIdx("right rear motor")] = -controlBR;
	}

	// Forward Bound Gait
	else if (setGait == 2)
	{
		// Set signal parameters
		pwm_period = 0.35; 
		speedSetpoint = 10.0;

		// Calculate Motor Positions 
		posFL = SpringyBotController::sine(speedSetpoint, pwm_period, 185, itime); // Front Left -
		posFR = SpringyBotController::sine(speedSetpoint, pwm_period, 5, itime); // Front Right +
		posBL = SpringyBotController::sine(speedSetpoint, pwm_period, 0, itime); // Back Left -
		posBR = SpringyBotController::sine(speedSetpoint, pwm_period, 180, itime); // Back Right +

		// Set motor speeds
		motors[MIdx("left front motor")] = posFL;
		motors[MIdx("right front motor")] = posFR;
		motors[MIdx("left rear motor")] = posBL;
		motors[MIdx("right rear motor")] = posBR;
	}

	// Forward Trot Gait
	else if (setGait == 3)
	{
		// Set signal parameters
		pwm_period = 0.75; 
		speedSetpoint = 12.0;

		// Calculate Motor Positions 
		posFL = SpringyBotController::sine(speedSetpoint, pwm_period, 180, itime); // Front Left +
		posFR = SpringyBotController::sine(speedSetpoint, pwm_period, 180, itime); // Front Right -
		posBL = SpringyBotController::sine(speedSetpoint, pwm_period, 0, itime); // Back Left +
		posBR = SpringyBotController::sine(speedSetpoint, pwm_period, 0, itime); // Back Right -

		// Set motor speeds
		motors[MIdx("left front motor")] = posFL;
		motors[MIdx("right front motor")] = -posFR;
		motors[MIdx("left rear motor")] = posBL;
		motors[MIdx("right rear motor")] = -posBR;
	}

	// Pace Gait
	else if (setGait == 4)
	{
		// Set signal parameters
		pwm_period = 0.75; 

		// Calculate Motor Positions 
		posFL = SpringyBotController::sine(speedSetpoint, pwm_period, 90, itime); // Front Left -
		posFR = SpringyBotController::sine(speedSetpoint, pwm_period, 90, itime); // Front Right +
		posBL = SpringyBotController::sine(speedSetpoint, pwm_period, 270, itime); // Back Left -
		posBR = SpringyBotController::sine(speedSetpoint, pwm_period, 270, itime); // Back Right +

		// Set motor speeds
		motors[MIdx("left front motor")] = -posFL;
		motors[MIdx("right front motor")] = posFR;
		motors[MIdx("left rear motor")] = -posBL;
		motors[MIdx("right rear motor")] = posBR;
	}

	// Wrong case
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

//----------------------------------------------------------------------------------------------------------------

	/**********************************************/

			  /* OMNIDIRECTIONAL WALKING */

	/**********************************************/




//----------------------------------------------------------------------------------------------------------------

	// Save data
	SpringyBotController::store_motor_values(posFL, posFR, posBL, posBR);
	SpringyBotController::store_sensor_values(leftFrontPosition, rightFrontPosition, leftRearPosition, rightRearPosition);
	SpringyBotController::store_controller_values(controlFL, controlFR, controlBL, controlBR);
	SpringyBotController::store_gait_footprints(controlFL, controlFR, controlBL, controlBR);

}


// Controller to correct the phase of the motor positions
double SpringyBotController::phase_controller(double desired, double error)
{
	return desired + error;
}


// Get error after receving feedback from motor sensors
double SpringyBotController::getFeedbackError(double position1, double position2) 
{
	Vector measured(position1);
	Vector expected(position2);
	return measured.smallestAngle(expected);
}


// Initiate controller
void SpringyBotController::init(int sensornumber, int motornumber, RandGen* randGen) {
	nSensors = sensornumber;
	nMotors  = motornumber;
	initialised=true;
}


// Return number of sensors
int SpringyBotController::getSensorNumber() const {
	return nSensors;
}


// Return number of motors
int SpringyBotController::getMotorNumber() const {
	return nMotors;
}

//---------------------------------------------------------------

// Used by the simulation

bool SpringyBotController::store(FILE* f) const {
	Configurable::print(f,0);
	return true;
}


bool SpringyBotController::restore(FILE* f) {
	Configurable::parse(f);
	return true;
}

//---------------------------------------------------------------


// Save Motor Data
void SpringyBotController::store_motor_values(double posFL, double posFR, double posBL, double posBR) 
{
	output << itime << "," << posFL << "," << posFR << "," << posBL << "," << posBR << endl;
}


// Save sensor data
void SpringyBotController::store_sensor_values(double FL, double FR, double BL, double BR)
{
	sensored << itime << "," << FL << "," << FR << "," << BL << "," << BR << endl;
}

// Save sensor data
void SpringyBotController::store_controller_values(double FL, double FR, double BL, double BR)
{
	controlled << itime << "," << FL << "," << FR << "," << BL << "," << BR << endl;
}

void SpringyBotController::store_gait_footprints(double FL, double FR, double BL, double BR)
{
	// Store values
	double feetFL = 0;
	double feetFR = 0;
	double feetBL = 0;
	double feetBR = 0;
	
	// Front Left footprint
	if (FL > 0)
	{
		feetFL = 3.4;
	}
	else
	{
		feetFL = 2.4;
	}

	// Front Right footprint
	if (FR > 0)
	{
		feetFR = 1;
	}
	else
	{
		feetFR = 0;
	}

	// Back Left footprint
	if (BL > 0)
	{
		feetBL = 4.6;
	}
	else
	{
		feetBL = 3.6;
	}

	// Back Right footprint
	if (BR > 0)
	{
		feetBR = 2.2;
	}
	else
	{
		feetBR = 1.2;
	}

	// Collect footprints
	feet << itime << "," << feetBL << "," << feetFL << "," << feetBR << "," << feetFR << endl;
}

// Get Gait name
string SpringyBotController::getGaitType(int type)
{
	string gaitType;
	if(type == 1)
	{
		gaitType = "Forward walking at constant speed"; 
	}
	else if(type == 2)
	{
		gaitType = "Forward bound gait"; 
	}
	else if(type == 3)
	{
		gaitType = "Fordward trot gait";
	}
	else if(type == 4)
	{
		gaitType = "Forward pace gait";
	}
	else
	{
		gaitType = "Dummy input";
	}

	return gaitType;
}



//=====================================================================================================================================================

// VECTOR CLASS 

Vector::Vector(double angle) {
	_x = cos(angle);
	_y = sin(angle);
}

Vector::Vector(double x, double y) {
	_x = x;
	_y = y;
}

double Vector::angle(Vector vector) {
	double out = 0;
    if (length() && vector.length())
    {
        double tmp = dot(vector) / ( length() * vector.length() );
        if (tmp > 1)
            out = acos(1);
        else if  (tmp < -1)
        	out = acos(-1);
        else
            out = acos(tmp);
    }
    else
        out = 0.0;

    return out;
}

double Vector::length() {
	return sqrt( pow(_x,2) + pow(_y,2) );
}

double Vector::dot(Vector vector) {
	return _x*vector._x + _y*vector._y;
}

double Vector::smallestAngle(Vector vector) {
	double lead = vector.angle( Vector(_x,_y) );
	double lag = angle(vector);
	if(abs(lead) < abs(lag))
		return lead;
	else
		return lag;
}

Vector Vector::rotate(double angle) {
    double new_x = cos(angle)*_x - sin(angle)*_y;
    double new_y = sin(angle)*_x + cos(angle)*_y;
    return Vector(new_x,new_y);

}