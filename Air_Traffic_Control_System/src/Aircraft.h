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
	Aircraft(int time,int flightId, int positionX, int positionY, int positionZ,int speedX,int speedY,int speedZ);
	void updatePosition(int flightId);
	int getPositionX(int flightId);
	int getPositionY(int flightId);
	int getPositionZ(int flightId);
	virtual ~Aircraft();

private:
	int flightId;
	int speedX,speedY,speedZ;
	int positionX,positionY,positionZ ;
	int time;

};

#endif /* AIRCRAFT_H_ */
