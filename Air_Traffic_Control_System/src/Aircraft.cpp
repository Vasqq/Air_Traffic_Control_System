/*
 * Aircraft.cpp
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 */

#include "Aircraft.h"
using namespace std;

Aircraft::Aircraft()
{
}

Aircraft::Aircraft(int time_at_boundary, int flight_level, int flight_id, int posX, int posY, int posZ,int speedX,int speedY,int speedZ)
{
	this->time_at_boundary=time_at_boundary;
	this->flight_level=flight_level;
	this->flight_id=flight_id;
	this->posX=posX;
	this->posY=posY;
	this->posZ=posZ;
	this->speedX=speedX;
	this->speedY=speedY;
	this->speedZ=speedZ;

}


void Aircraft::UpdateAircraftPosition()
{
}

void Aircraft::updatePositionX()
{
}

void Aircraft::updatePositionY()
{
}

void Aircraft::updatePositionZ()
{
}

void Aircraft::updateFlightLevel()
{
}

void Aircraft::ServiceInterrogationSignal()
{
}

void Aircraft::receiveInterrogationSignal()
{
}

char* Aircraft::collectTransponderData()
{
	return 0;
}

void Aircraft::senTransponderData(char transponderData[])
{
}

int Aircraft::getPosX(){

	return this->posX;
}

int Aircraft::getPosY(){

	return this->posY;
}

int Aircraft::getFlightID(){

	return this->flight_id;
}

Aircraft::~Aircraft()
{
}


