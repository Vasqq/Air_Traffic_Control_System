/*
 * Aircraft.h
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 */

#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

class Aircraft {
public:
	Aircraft();
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
