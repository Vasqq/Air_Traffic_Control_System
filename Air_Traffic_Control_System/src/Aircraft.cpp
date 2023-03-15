/*
 * Aircraft.cpp
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 */

#include "Aircraft.h"

Aircraft::Aircraft(int angle, int distance, int flightId, int flightLevel, int speed, int position) {
	// TODO Auto-generated constructor stub
		this->angle=angle;
		this->distance=distance;
		this->flightId=flightId;
		this->flightLevel=flightLevel;
		this->speed=speed;
		this->position=position;
}

void Aircraft::updatePosition(int flightId){		//updates the position of the the aircraft by passing it's identifier



}


Aircraft::~Aircraft() {
	// TODO Auto-generated destructor stub
}




