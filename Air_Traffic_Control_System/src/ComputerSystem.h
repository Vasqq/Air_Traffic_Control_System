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
#include <thread>
#include <fstream>
#include "CommunicationSystem.h"

using namespace std;
extern int textfileCounter;
class ComputerSystem
{
public:
	// ComputerSystem();
	ComputerSystem(vector<sTransponderData> *transponderDataList);
	ComputerSystem(int flight_id);
	void ComputeAirTrafficFlow();
	void SetN(int new_n);
	virtual ~ComputerSystem();

	std::vector<sTransponderData> receiveIlluminatedObjects();
	void forwardIlluminatedObjectsToDataDisplay();
	void checkAircraftSeperationConstraints();
	void notifySafetyViolation();
	vector<int> closeAircrafts; // a vector to store flight IDs of aircrafts in close proximity
	void runCS();

	void writeToFile(const string& filename, const string& data);
	void sendtoFile();

	void forwardIDtoCommSystem(int flight_id);



private:
	int n;
	int cID;
	bool collisionDetection = false;
	vector<vector<bool>> pushback; // declaration of pushback as a private member variable
	vector<sTransponderData> *transponderDataList;
	Aircraft* flight_id_ptr;
	int flight_id;
};

#endif /* SRC_COMPUTERSYSTEM_H_ */
