/*
 * ComputerSystem.cpp
 *
 *  Created on: Apr 2, 2023
 *      Author: argi1
 */

#include "ComputerSystem.h"
#include "ResourceManager.h"
#include <set>

//ComputerSystem::ComputerSystem() {
//	// TODO Auto-generated constructor stub
//	//pushback = std::vector<std::vector<bool>>();
//
//
//}

ComputerSystem::ComputerSystem(vector<sTransponderData> *transponderDataList) {
    //	this->n=n;

	//option 1: receive new n through interprocess communication
	//todo:implement

	//option2: n is defined in shared memory
	//todo:implement

	//option3: operation console has a reference to the computer system object
	//todo:implement

	//option4: operator console requests setting n through the resource manager

    this->transponderDataList = transponderDataList;
    pushback = vector<vector<bool>>();

    checkAircraftSeperationConstraints();
}

void ComputerSystem::SetN(int new_n){
	this->n=new_n;
}

void ComputerSystem::ComputeAirTrafficFlow(){
	std::vector<sTransponderData> illuminatedObjects = receiveIlluminatedObjects();
	forwardIlluminatedObjectsToDataDisplay(illuminatedObjects);
	//checkAircraftSeperationConstraints(illuminatedObjects);
}

std::vector<sTransponderData> ComputerSystem::receiveIlluminatedObjects() {
	std::vector<sTransponderData> transponderDataList;

	//Generate simulated transponder data for n aircrafts
	for(int i=0; i<n ; i++){
		sTransponderData td;
		//todo

		transponderDataList.push_back(td);
	}

	return transponderDataList;
}

ComputerSystem::~ComputerSystem() {
}

void ComputerSystem::forwardIlluminatedObjectsToDataDisplay(std::vector<sTransponderData> illuminatedObjects) {
	//ResourceManager::GetInstance().AddDataToQueue(illuminatedObjects);
}



void ComputerSystem::checkAircraftSeperationConstraints() {

	 //this dynamically resizes the 2d boolean vector based on the number of structs in the list.
		    int max_flight_id = 0;
		    for (sTransponderData& td : *transponderDataList) {
		        if (td.flightId > max_flight_id) {
		            max_flight_id = td.flightId;
		        }
		    }
		    pushback.resize(max_flight_id + 1, vector<bool>(max_flight_id + 1, false));



		for (sTransponderData& td1 : *transponderDataList) {

		    for (sTransponderData& td2 : *transponderDataList) {

		        if (td1.flightId != td2.flightId) {

	                int distance = sqrt( pow((td1.positionX - td2.positionX),2) +
	                                     pow((td1.positionY - td2.positionY),2));
	                int altitude = abs(td1.positionZ - td2.positionZ);

	                if (distance <= 3000 && altitude <= 1000) {
	                    collisionDetection  = true;


	                    if (!pushback[td1.flightId][td2.flightId] && !pushback[td2.flightId][td1.flightId] && collisionDetection == true){       //stops looping the pushbacks more than once
	                        closeAircrafts.push_back(td1.flightId);
	                        closeAircrafts.push_back(td2.flightId);

	                        pushback[td1.flightId][td2.flightId] = true; // Mark this pair of flight IDs as pushed back
	                        pushback[td2.flightId][td1.flightId] = true; // Mark this pair of flight IDs as pushed back
	                        //this above 2d boolean is done so that you dont have the reverse order of aircrafts being checked as well.
	                        collisionDetection  = false;	//reset collisionDetection back to false to check again

	                    }

	                }

	            }
	        }
	             }
		notifySafetyViolation();


	}


void ComputerSystem::notifySafetyViolation() {

	// Remove duplicates from closeAircrafts and sort them in numerical order
		    sort(closeAircrafts.begin(), closeAircrafts.end());
		    closeAircrafts.erase(unique(closeAircrafts.begin(), closeAircrafts.end()), closeAircrafts.end());

		    // Loop through each unique flight ID
		    cout<<endl;
		    for (int flightId : closeAircrafts) {
		        cout << "Aircraft " << flightId << " is in close proximity to ";

		        // Loop through the closeAircrafts vector to find all the aircrafts close to the current flight ID
		        bool firstAircraft = true;
		        for (int closeFlightId : closeAircrafts) {
		            if (closeFlightId != flightId) {
		                if (!firstAircraft) {
		                    cout << ", ";
		                }
		                cout << "Aircraft: " <<closeFlightId;
		                firstAircraft = false;
		            }
		        }
		        cout << endl;
		    }
}
