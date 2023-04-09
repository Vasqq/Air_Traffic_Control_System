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
#include "TransponderData.h"
#include "DataDisplay.h"
using namespace std;

class ComputerSystem
{
public:
	// ComputerSystem();
	ComputerSystem(vector<sTransponderData> *transponderDataList);
	void ComputeAirTrafficFlow();
	void SetN(int new_n);
	virtual ~ComputerSystem();

	std::vector<sTransponderData> receiveIlluminatedObjects();
	void forwardIlluminatedObjectsToDataDisplay();
	void checkAircraftSeperationConstraints();
	void notifySafetyViolation();
	vector<int> closeAircrafts; // a vector to store flight IDs of aircrafts in close proximity
	void runCS();

private:
	int n;

	bool collisionDetection = false;
	vector<vector<bool>> pushback; // declaration of pushback as a private member variable
	vector<sTransponderData> *transponderDataList;
};

#endif /* SRC_COMPUTERSYSTEM_H_ */
