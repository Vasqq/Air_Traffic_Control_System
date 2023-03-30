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
#include <sys/neutrino.h> // For QNX message passing API
#include <stdint.h> // For data type uint64_t
#include <sys/iofunc.h>
#include <sys/dispatch.h>
using namespace std;


class Aircraft {
public:
	//Constructors and Destructor
	Aircraft();
	virtual ~Aircraft();
	Aircraft(int time_at_boundary,int flight_level, int flight_id, int posX, int posY, int posZ,int speedX,int speedY,int speedZ);
	int INTERROGATION_REPLY = 2;
	 int INTERROGATION_SIGNAL = 1;

	//Functions that update position and flight level
	void updatePositionX();
	void updatePositionY();
	void updatePositionZ();
	void updateFlightLevel();
	void updateAircraftPosition();

	//Communication with the IPC
	void ServiceInterrogationSignal(int chid);
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

	int MsgReceive( int chid,
	                void * msg,
	                size_t bytes,
	                struct _msg_info * info );
	int MsgReply( int rcvid,
	              long status,
	              const void* msg,
	              size_t bytes );



private:
	int time_at_boundary;
	int flight_level;
	int flight_id;
	int posX, posY, posZ;
	int speedX,speedY,speedZ;


};

#endif /* AIRCRAFT_H_ */
