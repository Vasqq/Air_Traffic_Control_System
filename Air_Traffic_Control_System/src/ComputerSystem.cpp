/*
 * ComputerSystem.cpp
 *
 *  Created on: Apr 2, 2023
 *      Author: argi1
 */

#include "ComputerSystem.h"
#include "ResourceManager.h"

ComputerSystem::ComputerSystem() {
	// TODO Auto-generated constructor stub

}

ComputerSystem::~ComputerSystem() {
	// TODO Auto-generated destructor stub
}


void ComputerSystem::checkAircraftProximity(vector<sTransponderData> transponderDataList) {
bool pushback = false;
    for (const auto& td1 : transponderDataList) {
        for (const auto& td2 : transponderDataList) {
            if (td1.flightId != td2.flightId) {
                double distance = sqrt(pow((td1.positionX - td2.positionX), 2) + pow((td1.positionY - td2.positionY), 2)
                        + pow((td1.positionZ - td2.positionZ), 2));
                if (distance <= 3000 && abs(td1.positionZ - td2.positionZ) <= 1000) {
                    collisionDetection  = true;
                    //if (pushback==false){       //stops looping the pushbacks more than once
                      //  closeAircrafts.push_back(td1.flightId);
                      //  closeAircrafts.push_back(td2.flightId);
                      //  pushback=true;
                   // }

                }

            }
        }
    }
displayAlert();


}

void ComputerSystem::displayAlert() {

    if (collisionDetection) {
            cout << "WARNING: Two or more Aircrafts are in close proximity!" << endl;
           // cout << "The following aircrafts are in close proximity: ";
                   // for (int flightId : closeAircrafts) {
                    //    cout << "Aircraft: "<<flightId << " ";
                   // }
                   // cout << endl;
        }
}

