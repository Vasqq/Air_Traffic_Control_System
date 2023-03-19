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

using namespace std;


class Aircraft {
public:
	Aircraft();
	Aircraft(int time_at_boundary, int flight_level, int flight_id, int posX, int posY, int posZ,int speedX,int speedY,int speedZ);
	void UpdateAircraftPosition();
	void updatePositionX();
	void updatePositionY();
	void updatePositionZ();
	void updateFlightLevel();
	void ServiceInterrogationSignal();
	void receiveInterrogationSignal();		//this blocks until interrogation signal arrives
	char* collectTransponderData();
	void senTransponderData(char transponderData[]);

	virtual ~Aircraft();

private:
	int time_at_boundary;
	int flight_level;
	int flight_id;
	int posX, posY, posZ;
	int speedX,speedY,speedZ;

};

#endif /* AIRCRAFT_H_ */
