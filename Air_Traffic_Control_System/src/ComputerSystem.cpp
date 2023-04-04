/*
 * ComputerSystem.cpp
 *
 *  Created on: Apr 2, 2023
 *      Author: argi1
 */

#include "ComputerSystem.h"
#include "ResourceManager.h"
#include <set>

ComputerSystem::ComputerSystem() {
	// TODO Auto-generated constructor stub

	pushback = std::vector<std::vector<bool>>();

}

ComputerSystem::~ComputerSystem() {
	// TODO Auto-generated destructor stub
}


void ComputerSystem::checkAircraftProximity(vector<sTransponderData> transponderDataList) {

	 //this dynamically resizes the 2d boolean vector based on the number of structs in the list.
	    int max_flight_id = 0;
	    for (const auto& td : transponderDataList) {
	        if (td.flightId > max_flight_id) {
	            max_flight_id = td.flightId;
	        }
	    }
	    pushback.resize(max_flight_id + 1, std::vector<bool>(max_flight_id + 1, false));



	for (const auto& td1 : transponderDataList) {

        for (const auto& td2 : transponderDataList) {

            if (td1.flightId != td2.flightId) {
                double distance = sqrt(pow((td1.positionX - td2.positionX), 2) + pow((td1.positionY - td2.positionY), 2)
                        + pow((td1.positionZ - td2.positionZ), 2));
                if (distance <= 3000 && abs(td1.positionZ - td2.positionZ) <= 1000) {
                    collisionDetection  = true;
                    if (!pushback[td1.flightId][td2.flightId] && !pushback[td2.flightId][td1.flightId]){       //stops looping the pushbacks more than once
                        closeAircrafts.push_back(td1.flightId);
                        closeAircrafts.push_back(td2.flightId);

                        pushback[td1.flightId][td2.flightId] = true; // Mark this pair of flight IDs as pushed back
                        pushback[td2.flightId][td1.flightId] = true; // Mark this pair of flight IDs as pushed back
                        //this above 2d boolean is done so that you dont have the reverse order of aircrafts being checked as well.
                   }

                }

            }
        }
             }
displayAlert();


}

void ComputerSystem::displayAlert() {


		// Remove duplicates from closeAircrafts
	    sort(closeAircrafts.begin(), closeAircrafts.end());
	    closeAircrafts.erase(unique(closeAircrafts.begin(), closeAircrafts.end()), closeAircrafts.end());

	    // Loop through each unique flight ID
	    for (int flightId : closeAircrafts) {
	        cout << "Aircraft " << flightId << " is in close proximity to: ";

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
