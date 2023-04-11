/*
 * 		PSR.cpp
 *
 *  	Created on: Mar. 11, 2023
 *      Author: Liam
 *
 *		File Description:
 *
 *      This file serves as the implementation for the PSR (Primary Surveilance Radar)
 *      The PSR will scan the airspace and send an array of illuminated objects to the
 *      SSR.
 *
 */

#include "PSR.h"
#include "SSR.h"
#include <iostream>
#include <math.h>



PSR::PSR(vector<Aircraft> *AircraftSchedule) {

	range = MAX_RANGE;
	reference_angle = REFERENCE_ANGLE;
	scans_per_minute = SCANS_PER_MINUTE;
	pulses_per_degree = PULSES_PER_DEGREE;
	current_angle = CURRENT_ANGLE;
	pulse_speed = PULSE_SPEED;

	this->aircraftList=AircraftSchedule;
}

PSR::~PSR() {
	// TODO Auto-generated destructor stub
}

void PSR::scan(){

    //cout << "Scanning..." << endl;
	while(current_angle < DEGREES_IN_CIRCLE){

	detectAircraft(current_angle);
	// Rotate the radar 1 degree
	rotateRadar();
	}
	// reset the radar
	current_angle = 0;
}

void PSR::detectAircraft(int angle){

	int aircraftDistance; 			// Distance of the detected aircraft
	double aircraftAngleRads; 		// Angle of the detected aircraft

	for (Aircraft& aircraft : *aircraftList){

		// Get the aircraft angle in radians
		aircraftAngleRads = (atan2(aircraft.getPosY(), aircraft.getPosX()));

		   // Adjust the aircraft angle to be between 0 and 2*pi
		   if (aircraftAngleRads < 0)
			   aircraftAngleRads += 2 * M_PI;

		   // Adjust the input angle to be between 0 and 2*pi
		   if (angle  < 0)
			   angle += 2 * M_PI;

		// convert to degrees
		int aircraftAngleDegrees = (int) (aircraftAngleRads * 180)/ M_PI;

		   // Check if the aircraft is at the current radar angle
     		   if (aircraftAngleDegrees == angle){
			   // Get the aircraft distance
			   aircraftDistance = (int) (sqrt(pow(aircraft.getPosX(), 2) + pow(aircraft.getPosY(), 2)));
			   // Add the aircraft object to the array if it is within range
			   if(aircraftDistance < range){
				   illuminatedObjects.push_back(&aircraft);
			   }
		   }
	}

}

void PSR::rotateRadar(){

	current_angle++;
}


vector<Aircraft> PSR::sendAircraftPositionsToSSR(){

//	cout << "Sending illuminated objects" << endl;
//
//	for (Aircraft& aircraft : illuminatedObjects){
//
//		cout << "Aircraft: " << aircraft.getFlightID() << endl;
//
//	}


	//return illuminatedObjects;
}


void PSR::execute(){

    cout << endl<< "Executing PSR..." << endl;
//while(true)
//{

    while (true) {

	pthread_mutex_lock(&psr_mutex);
	scan();

	SSR ssr(illuminatedObjects);
	illuminatedObjects.clear();
	textfileCounter++;
	ssr.execute();

	pthread_mutex_unlock(&psr_mutex);
    // Sleep for 5 seconds before executing again
    sleep(5);
          }


//}


}

void PSR::test(){}



