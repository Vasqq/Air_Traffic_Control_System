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
	ComputerSystem();
	virtual ~ComputerSystem();



	void checkAircraftProximity(vector<sTransponderData> transponderDataList);
	void displayAlert();
	vector<int> closeAircrafts; // a vector to store flight IDs of aircrafts in close proximity



private:
	bool collisionDetection  = false;

};

#endif /* SRC_COMPUTERSYSTEM_H_ */
