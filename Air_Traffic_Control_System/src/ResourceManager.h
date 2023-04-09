/*
 * ResourceManager.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Argi
 */

#ifndef SRC_RESOURCEMANAGER_H_
#define SRC_RESOURCEMANAGER_H_
#include "Aircraft.h"
#include "PSR.h"
#include "SSR.h"
#include "AircraftPeriodicTimer.h"
#include "PSRPeriodicTimer.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class ResourceManager {
public:
    // Constructors and destructor
    ResourceManager();
    ResourceManager(vector<Aircraft> *AircraftArr);
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
    int createAircraftTransponderDataChannel();

    // Thread execution functions
    static void * fwdServiceInterrogationSignal(void * aircraft);

    // Simulation functions
    void execute();
    void configureSimulation();
    void runSimulation();
    void spawnNewAircraftThreads(Aircraft& nextAircraft);

private:
    vector<int> aircraft_pids;
    vector<int> ATCS_pids;
    vector<Aircraft> *AircraftSchedule;
    vector<AircraftPeriodicTimer> AircraftPeriodicTimers;
    PSRPeriodicTimer *PSRPeriodicTimer_;

    const timespec AIRCRAFT_UPDATE_POSITION_PERIOD{1,0};
    const timespec PSR_SCAN_PERIOD{1,0};

};

#endif /* SRC_RESOURCEMANAGER_H_ */
