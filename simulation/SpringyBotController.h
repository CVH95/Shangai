/* 
	CREATED on Dec 7th, 2018 by cavie17@student.sdu.dk
	from SpringyBotWmptyController.h:

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

		// Save motor data
		void store(double posFL, double posFR, double posBL, double posBR);
	
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
		ofstream output;
		double pwm_period;

		string getGaitType(int type);
};


#endif /* ODE_ROBOTS_ROBOTS_LOCOKIT_SPRINGYBOTPHASECONTROLLER_H_ */
