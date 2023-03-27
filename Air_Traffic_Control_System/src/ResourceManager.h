/*
 * ResourceManager.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Argi
 */

#ifndef SRC_RESOURCEMANAGER_H_
#define SRC_RESOURCEMANAGER_H_
#include "Aircraft.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


class ResourceManager {
public:
    ResourceManager();
	ResourceManager(vector<Aircraft>& AircraftSchedule);
//All the void functions
	void createAircraftThreads();
	void createATCSSubsystems();
	void storeAircraftProcessId(int pid);
	void initializeDataDisplay();
	void initializeComputerSystem();
	void initializeCommunicationSystem();
	void initializeOperatorConsole();
	void initializeRadar();
	void initializePSR();
	void initializeSSR();
	void storeATCSProcessId(int pid);
	static void * fwdExecutionToAircraft(void * aircraft);
	static void * fwdExecutionToPSR(void * psr);
	static void * fwdExecutionToSSR(void * ssr);
	void execute();
	void configureSimulation();
	void runSimulation();

	void spawnNewAircraftThread(Aircraft& nextAircraft);

	virtual ~ResourceManager();
private:
	vector<int> aircraft_pids;		//arrays of type integer to store Aircraft PIDS
	vector<int> ATCS_pids;			//arrays of type integer to store ATCS PIDS
	vector<Aircraft> AircraftSchedule;

};

#endif /* SRC_RESOURCEMANAGER_H_ */
