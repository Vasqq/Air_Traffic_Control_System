/*
 * PSR.h
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 */

#ifndef PSR_H_
#define PSR_H_

#define MAX_RANGE 100000
#define REFERENCE_ANGLE 0
#define SCANS_PER_MINUTE 12
#define PULSES_PER_DEGREE 1
#define CURRENT_ANGLE 0
#define PULSE_SPEED 1
#define DEGREES_IN_CIRCLE 360

#include "Aircraft.h"
#include <vector>

using namespace std;

class PSR {
public:
    //Constructor and Destructor of class PSR
	PSR(vector<Aircraft> *aircraftSchedule);
	virtual ~PSR();

	//Main functions of the PSR to scan and detect Aircrafts
	//and rotate the radar
	void scan();
	void detectAircraft(int angle);
	void rotateRadar();
	vector<Aircraft> sendAircraftPositionsToSSR();
	void execute();
	void test();



	bool receiveEchoes(int echoes[]);
	Aircraft* determineDistances(int echoes[]);







private:

	int range;
	int reference_angle;
	int scans_per_minute;
	int pulses_per_degree;
	int current_angle;
	int pulse_speed;

	vector<Aircraft> *aircraftList;
	vector<Aircraft*> illuminatedObjects;
};

#endif /* PSR_H_ */
