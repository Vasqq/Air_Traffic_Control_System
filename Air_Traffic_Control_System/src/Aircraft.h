/*
 * Aircraft.h
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 */

#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_
#include <pthread.h>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;


class Aircraft {
public:
	Aircraft();
	Aircraft(int time_at_boundary, int flight_level, int flight_id, int posX, int posY, int posZ,int speedX,int speedY,int speedZ);
	void updateAircraftPosition();
	void updatePositionX();
	void updatePositionY();
	void updatePositionZ();
	void updateFlightLevel();
	void ServiceInterrogationSignal();
	void receiveInterrogationSignal();		//this blocks until interrogation signal arrives
	char* collectTransponderData();
	void sendTransponderData(char transponderData[]);

	int getFlightID();
	int getFlightLevel();

	int getPosX();
	int getPosY();
	int getPosZ();

	int getSpeedX();
	int getSpeedY();
	int getSpeedZ();

	virtual ~Aircraft();

private:
	int time_at_boundary;
	int flight_level;
	int flight_id;
	int posX, posY, posZ;
	int speedX,speedY,speedZ;

};

#endif /* AIRCRAFT_H_ */
