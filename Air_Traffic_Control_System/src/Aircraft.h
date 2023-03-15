/*
 * Aircraft.h
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 */

#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_
#include <pthread.h>
class Aircraft {
public:
	Aircraft(int angle, int distance, int flightId, int flightLevel, int speed, int position);
	void updatePosition(int flightId);
	virtual ~Aircraft();

private:
	int angle;
	int distance;
	int flightId;
	int flightLevel;
	int speed;
	int position;
};

#endif /* AIRCRAFT_H_ */
