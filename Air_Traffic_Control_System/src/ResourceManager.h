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
    // Constructors and destructor
    ResourceManager();
    ResourceManager(vector<Aircraft>& AircraftSchedule);
    virtual ~ResourceManager();

    // Initialization functions
    void initializeDataDisplay();
    void initializeComputerSystem();
    void initializeCommunicationSystem();
    void initializeOperatorConsole();
    void initializeRadar();
    void initializePSR();
    void initializeSSR();

    // Process management functions
    void createAircraftThreads();
    void createATCSSubsystems();
    void storeAircraftProcessId(int pid);
    void storeATCSProcessId(int pid);

    // Thread execution functions
    static void * fwdExecutionToAircraft(void * aircraft);
    static void * fwdExecutionToPSR(void * psr);
    static void * fwdExecutionToSSR(void * ssr);

    // Simulation functions
    void execute();
    void configureSimulation();
    void runSimulation();
    void spawnNewAircraftThread(Aircraft& nextAircraft);

private:
    vector<int> aircraft_pids;
    vector<int> ATCS_pids;
    vector<Aircraft> AircraftSchedule;

};

#endif /* SRC_RESOURCEMANAGER_H_ */
