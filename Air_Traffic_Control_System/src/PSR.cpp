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


/* -----------------------------------------------------------------------------
 * Name:        PSR
 * Input:       Pointer to a vector of Aircraft objects
 * Output:      None
 * Description: Initializes the PSR object with default values and stores the
 *              pointer to the vector of Aircraft objects..
 * -----------------------------------------------------------------------------
 */
PSR::PSR(vector<Aircraft> *AircraftSchedule) {

	range = MAX_RANGE;
	reference_angle = REFERENCE_ANGLE;
	scans_per_minute = SCANS_PER_MINUTE;
	pulses_per_degree = PULSES_PER_DEGREE;
	current_angle = CURRENT_ANGLE;
	pulse_speed = PULSE_SPEED;

	this->aircraftList=AircraftSchedule;
	cout << "PSR Aircraft list address: " << aircraftList << endl;
}


/* -----------------------------------------------------------------------------
 * Name:        PSR Destructor
 * Input:       None
 * Output:      None
 * Description: Destructor of PSR object.
 * -----------------------------------------------------------------------------
 */
PSR::~PSR() {
	// TODO Auto-generated destructor stub
}



/* -----------------------------------------------------------------------------
 * Name:        scan
 * Input:       None
 * Output:      None
 * Description: Scans for aircraft by rotating the radar 360 degrees and
 *              calling detectAircraft at each degree.
 * -----------------------------------------------------------------------------
 */
void PSR::scan(){

    cout << "Scanning..." << endl;
	while(current_angle <= DEGREES_IN_CIRCLE){

		detectAircraft(current_angle);

		if (current_angle >= DEGREES_IN_CIRCLE){

			// reset the radar
			current_angle = 0;
			break;
		}

		// Rotate the radar 1 degree
		rotateRadar();
	}
}



/* -----------------------------------------------------------------------------
 * Name:        detectAircraft
 * Input:       int angle
 * Output:      None
 * Description: Detects if an aircraft is present at the given angle and if so,
 *              adds it to the illuminatedObjects vector if it is within range.
 * -----------------------------------------------------------------------------
 */
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

				   cout << "Pushing back with address: " << &aircraft  << endl;
				   illuminatedObjects.push_back(&aircraft);
			   	   cout << illuminatedObjects.size() << endl;
			   }
		   }
	}

}


/* -----------------------------------------------------------------------------
 * Name:        rotateRadar
 * Input:       None
 * Output:      None
 * Description: Rotates the radar by one degree.
 * -----------------------------------------------------------------------------
 */
void PSR::rotateRadar(){

	current_angle++;
}

/* -----------------------------------------------------------------------------
 * Name:        sendAircraftPositionsToSSR
 * Input:       None
 * Output:      A vector of Aircraft objects
 * Description: Sends the list of illuminated Aircraft objects to the
 *              SSR object.
 * -----------------------------------------------------------------------------
 */
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




/* -----------------------------------------------------------------------------
 * Name:        execute
 * Input:       None
 * Output:      None
 * Description: Executes the PSR object by calling scan,
 *              sendAircraftPositionsToSSR, and executing the SSR object.
 * -----------------------------------------------------------------------------
 */
void PSR::execute(){

    cout << "Executing PSR..." << endl;

	scan();
	sendAircraftPositionsToSSR();
	SSR ssr(illuminatedObjects);
	ssr.execute();

	//return illuminatedObjects;

}

void PSR::test(){}



