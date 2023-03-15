/*
 * Aircraft.cpp
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 */

#include "Aircraft.h"

Aircraft::Aircraft(int time,int flightId, int positionX, int positionY, int positionZ,int speedX,int speedY,int speedZ) {
	// TODO Auto-generated constructor stub
		this->time=time;
		this->flightId=flightId;
		this->positionX=positionX;
		this->positionY=positionY;
		this->positionZ=positionZ;
		this->speedX=speedX;
		this->speedY=speedY;
		this->speedZ=speedZ;
}

void Aircraft::updatePosition(int flightId){		//updates the position of the the aircraft by passing it's identifier

	getPositionX(flightId)+=((this->speedX)*diff_in_time);		//need to define how to do diff in time
	getPositionY(flightId)+=((this->speedY)*diff_in_time);
	getPositionZ(flightId)+=((this->speedZ)*diff_in_time);
}

int Aircraft::getPositionX(int flightId){

	return this->positionX;

}

int Aircraft::getPositionY(int flightId){

	return this->positionY;

}

int Aircraft::getPositionZ(int flightId){

	return this->positionZ;

}
Aircraft::~Aircraft() {
	// TODO Auto-generated destructor stub
}




