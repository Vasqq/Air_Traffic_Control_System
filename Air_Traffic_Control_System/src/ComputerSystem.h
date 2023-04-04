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




private:
	bool collisionDetection  = false;

};

#endif /* SRC_COMPUTERSYSTEM_H_ */
