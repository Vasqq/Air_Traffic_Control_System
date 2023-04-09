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
#include <errno.h>
#include <sys/neutrino.h> // For QNX message passing API
#include <stdint.h> // For data type uint64_t
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <unistd.h>
#include <sys/netmgr.h>
#include <sys/types.h>

#include "TransponderData.h"

using namespace std;



class Aircraft {
public:
	//Constructors and Destructor

    Aircraft();
	virtual ~Aircraft();
	Aircraft(int time_at_boundary, int flight_id, int posX, int posY, int posZ,int speedX,int speedY,int speedZ);

	//Functions that update position and flight level
	void updatePositionX();
	void updatePositionY();
	void updatePositionZ();
	void updateFlightLevel();
	void updateAircraftPosition();
	void setTransponderDataChannel(int chid);

	//Communication with the IPC
	void ServiceInterrogationSignal();
	int connectToChannel();


	void receiveInterrogationSignal();		//this blocks until interrogation signal arrives
	void setTimerID(timer_t timerID);

	//This section will return the new values after they are updated.
	int getFlightID();
	int getFlightLevel();

	int getPosX();
	int getPosY();
	int getPosZ();

	int getSpeedX();
	int getSpeedY();
	int getSpeedZ();

	int getTransponderDataChannel();
	timer_t getTimerID();


	//This will collect all the new values returned and then send the new data.
	char* collectTransponderData();
	void sendTransponderData(char transponderData[]);

	timer_t     aircraftTimerID;

	pid_t get_pid() {
	        return getpid();
	    }

private:
	int time_at_boundary;
	int flight_id;
	int posX, posY, posZ;
	int speedX,speedY,speedZ;
	int transponderDataChannel;

};

#endif /* AIRCRAFT_H_ */
