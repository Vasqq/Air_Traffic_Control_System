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
#include "ResourceManager.h"

using namespace std;

class PSR {
public:
	PSR(vector<Aircraft> *aircraftSchedule);

	void execute();
	void test();
	void scan();
	void detectAircraft(int angle);
	void rotateRadar();
	bool receiveEchoes(int echoes[]);
	Aircraft* determineDistances(int echoes[]);

	vector<Aircraft> sendAircraftPositionsToSSR();

	virtual ~PSR();

	//pthread_mutex_t psr_mutex = PTHREAD_MUTEX_INITIALIZER;

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
