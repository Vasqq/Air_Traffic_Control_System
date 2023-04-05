/*
 * ComputerSystem.h
 *
 *  Created on: Apr 2, 2023
 *      Author: argi1
 */

#ifndef SRC_COMPUTERSYSTEM_H_
#define SRC_COMPUTERSYSTEM_H_

#include "SSR.h"
#include <Math.h>


class ComputerSystem {
public:
	ComputerSystem(int n);
	void ComputeAirTrafficFlow();
	void SetN(int new_n);
	ComputerSystem();
	//virtual ~ComputerSystem();



	void checkAircraftProximity(vector<sTransponderData> transponderDataList);
	void displayAlert();
	vector<int> closeAircrafts; // a vector to store flight IDs of aircrafts in close proximity



private:
	int n;
	std::vector<sTransponderData> receiveIlluminatedObjects();
	void forwardIlluminatedObjectsToDataDisplay(std::vector<sTransponderData> illuminatedObjects);
	void checkAircraftSeperationConstraints(std::vector<sTransponderData>illuminatedObjects);
	void notifySafetyViolation(std::vector<int> violatingAircraft);
	//void displayAlert();

	bool collisionDetection  = false;
	vector<vector<bool>> pushback;  // declaration of pushback as a private member variable
	//std::vector<int>closeAircrafts;

};

#endif /* SRC_COMPUTERSYSTEM_H_ */
