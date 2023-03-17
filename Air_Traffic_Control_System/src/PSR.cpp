/*
 * PSR.cpp
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 */

#include "PSR.h"

#include <iostream>
#include <math.h>



PSR::PSR(vector<Aircraft> aircraftArr) {

	range = MAX_RANGE;
	reference_angle = REFERENCE_ANGLE;
	scans_per_minute = SCANS_PER_MINUTE;
	pulses_per_degree = PULSES_PER_DEGREE;
	current_angle = CURRENT_ANGLE;
	pulse_speed = PULSE_SPEED;

	aircraftList = aircraftArr;

}

PSR::~PSR() {
	// TODO Auto-generated destructor stub
}

void PSR::scan(){

	cout << "In scan function" << endl;

	while(current_angle <= DEGREES_IN_CIRCLE){

		detectAircraft(current_angle);

		if (current_angle >= DEGREES_IN_CIRCLE){

			// reset the radar
			current_angle = 0;
			break;
		}

		rotateRadar();
	}
}

void PSR::detectAircraft(int angle){

	int aircraftDistance; 	// Distance of the detected aircraft
	int aircraftAngle; 		// Angle of the detected aircraft

	for (Aircraft& aircraft : aircraftList){

		// Get the aircraft angle
		aircraftAngle = (int) (atan2(aircraft.getPosY(), aircraft.getPosX()));

		   // Adjust the aircraft angle to be between 0 and 2*pi
		   if (aircraftAngle < 0)
			   aircraftAngle += 2 * M_PI;

		   // Adjust the input angle to be between 0 and 2*pi
		   if (angle  < 0)
			   angle += 2 * M_PI;

		   // Check if the aircraft is at the current radar angle
		   if (aircraftAngle == angle){
			   // Get the aircraft distance
			   aircraftDistance = (int) (sqrt(pow(aircraft.getPosX(), 2) + pow(aircraft.getPosY(), 2)));

			   if(aircraftDistance < range)
				   illuminatedObjects.push_back(aircraft);
		   }
	}
}

void PSR::rotateRadar(){

	current_angle++;
}

void PSR::execute(){

	while(true){

		scan();
		sendAircraftPositionsToSSR(illuminatedObjects);
	}

}

