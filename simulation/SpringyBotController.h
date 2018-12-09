/* 
	CREATED on Dec 7th, 2018 by cavie17@student.sdu.dk
	from SpringyBotPhaseController.h:

*/

/*****************************************************************************
* "THE BEER-WARE LICENSE" (Revision 43):
* This software was written by Leon Bonde Larsen <leon@bondelarsen.dk> 
* As long as you retain this notice you can do whatever you want with it. 
* If we meet some day, and you think this stuff is worth it, you can buy me 
* a beer in return.
* 
* Should this software ever become self-aware, remember: I am your master
*****************************************************************************/

#ifndef ODE_ROBOTS_ROBOTS_LOCOKIT_SPRINGYBOTPHASECONTROLLER_H_
#define ODE_ROBOTS_ROBOTS_LOCOKIT_SPRINGYBOTPHASECONTROLLER_H_

#include <selforg/abstractcontroller.h>
#include <ode_robots/joint.h>
#include <ode_robots/contactsensor.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream> 
#include <math.h>

using namespace std;

//#define PI 3.14159265359

class SpringyBotController : public AbstractController 
{

	public:

		SpringyBotController(const std::string& name);
		virtual ~SpringyBotController();

		double sine(double amp, double period, double phase, double x);

		virtual void init(int sensornumber, int motornumber, RandGen* randGen = 0)  override;
		virtual int getSensorNumber() const override;
		virtual int getMotorNumber() const override;

		virtual void step(const sensor* sensors, int sensornumber, motor* motors, int motornumber) override;
		virtual void stepNoLearning(const sensor* , int number_sensors, motor* , int number_motors) override;

		virtual bool store(FILE* f) const override;
		virtual bool restore(FILE* f) override;
	
	protected:

		// Parameters
		double nSensors;
		double nMotors;
		bool initialised;
		int setGait;
		double ticks_since_init;
		double itime;
		double itime_step;
		double speedSetpoint;
		double phaseSetpoint;

		// Output files and vars
		ofstream output, sensored, controlled, feet;
		double pwm_period;

		// Save data
		void store_motor_values(double posFL, double posFR, double posBL, double posBR);
		void store_sensor_values(double FL, double FR, double BL, double BR);
		void store_controller_values(double FL, double FR, double BL, double BR);
		void store_gait_footprints(double FL, double FR, double BL, double BR);
		string getGaitType(int type);

	private:

		// Closed-loop controller implementation
		double add_positions(double p1, double p2);
		double phase_controller(double desired, double error);
		double getFeedbackError(double, double);
};

// Simple 2D vector utility class for phase calculations
class Vector 
{
	public:
		double _x,_y;

		Vector(double);
		Vector(double,double);

		double angle(Vector);
		double smallestAngle(Vector);
		double length();
		double dot(Vector);
		Vector rotate(double);
};


#endif /* ODE_ROBOTS_ROBOTS_LOCOKIT_SPRINGYBOTPHASECONTROLLER_H_ */
