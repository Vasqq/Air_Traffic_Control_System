/*
 * ResourceManager.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Argi
 */

#ifndef SRC_RESOURCEMANAGER_H_
#define SRC_RESOURCEMANAGER_H_
#include "Aircraft.h"
class ResourceManager {
public:
	ResourceManager();
//All the void functions
	void createAircraftProcesses(Aircraft aircraft[]);
	void createATCSSubsystems();
	void storeAircraftProcessId(int pid);
	void initializeDataDisplay();
	void initializeComputerSystem();
	void initializeCommunicationSystem();
	void initializeOperatorConsole();
	void initializeRadar();
	void storeATCSProcessId(int pid);


//Aircraft class function
	Aircraft* TakeNextAircraftProcess(Aircraft aircraft[]);
//int function
	int spawnNewAircraftProcess(Aircraft aircraft);

	virtual ~ResourceManager();
private:
	int aircraft_pids[];		//arrays of type integer to store Aircraft PIDS
	int ATCS_pids[];			//arrays of type integer to store ATCS PIDS
};

#endif /* SRC_RESOURCEMANAGER_H_ */
