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
	//Constructors and Destructor
	Aircraft();
	virtual ~Aircraft();
	Aircraft(int time_at_boundary, int flight_level, int flight_id, int posX, int posY, int posZ,int speedX,int speedY,int speedZ);


	//Functions that update position and flight level
	void updatePositionX();
	void updatePositionY();
	void updatePositionZ();
	void updateFlightLevel();
	void updateAircraftPosition();

	//Communication with the IPC
	void ServiceInterrogationSignal();
	void receiveInterrogationSignal();		//this blocks until interrogation signal arrives

	//This section will return the new values after they are updated.
	int getFlightID();
	int getFlightLevel();

	int getPosX();
	int getPosY();
	int getPosZ();

	int getSpeedX();
	int getSpeedY();
	int getSpeedZ();


	//This will collect all the new values returned and then send the new data.
	char* collectTransponderData();
	void sendTransponderData(char transponderData[]);





private:
	int time_at_boundary;
	int flight_level;
	int flight_id;
	int posX, posY, posZ;
	int speedX,speedY,speedZ;

};

#endif /* AIRCRAFT_H_ */
