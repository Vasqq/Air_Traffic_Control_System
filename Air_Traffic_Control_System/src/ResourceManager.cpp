/*
 * ResourceManager.cpp
 *
 *  Created on: Mar 14, 2023
 *      Author: Argi
 */

#include "ResourceManager.h"
#include "PSR.h"



ResourceManager::ResourceManager() {

}

ResourceManager::ResourceManager(vector<Aircraft> AircraftSchedule) {

    this->AircraftSchedule=AircraftSchedule;

}

void* ResourceManager:: fwdExecutionToAircraft(void * aircraft)
{
    static_cast <Aircraft*> (aircraft)->updateAircraftPosition();

    return NULL;
}
void* ResourceManager::fwdExecutionToPSR(void * psr) {

    static_cast <PSR*> (psr)->execute();

    return NULL;
}

void* ResourceManager::fwdExecutionToSSR(void *ssr) {
}

void ResourceManager::createAircraftThreads(){

    cout << "Creating Aircraft threads" << endl;

for(Aircraft& nextAircraft: AircraftSchedule){
    spawnNewAircraftThread(nextAircraft);
    }
}
void ResourceManager::spawnNewAircraftThread(Aircraft nextAircraft){

    int err_no;
    pthread_t   thread_id;

    err_no= pthread_create(&thread_id,
                           NULL,
                           &fwdExecutionToAircraft,
                           &nextAircraft);
    if(err_no!=0){
        cout<<"ERROR when creating thread: "<< err_no <<endl;
    }
    else{
        cout<<" Aircraft with thread ID: "<<thread_id<<" created"<<endl;
        }

}

void ResourceManager::createATCSSubsystems(){

    cout << "Initializing ATCS subsystems..." << endl;
    initializeDataDisplay();
    initializeComputerSystem();
    initializeCommunicationSystem();
    initializeOperatorConsole();
    initializeRadar();
}

void ResourceManager::initializeDataDisplay(){

    cout << "Initializing Data Display..." << endl;
}

void ResourceManager::initializeComputerSystem(){

    cout << "Initializing Computer System..." << endl;
}

void ResourceManager::initializeCommunicationSystem(){

    cout << "Initializing Communication System..." << endl;
}

void ResourceManager::initializeOperatorConsole(){

    cout << "Initializing Operator Console..." << endl;
}

void ResourceManager::initializeRadar(){

    cout << "Initializing Radar..." << endl;

    initializePSR();

}

void ResourceManager::initializePSR(){

    int err_no;
    pthread_t   PSR_thread_id;

    vector<Aircraft> aircraftArr = AircraftSchedule;

    PSR psr;

    err_no= pthread_create(&PSR_thread_id,
                           NULL,
                           &fwdExecutionToPSR,
                           &psr);
    if(err_no!=0){
        cout<<"ERROR when creating PSR thread: "<< err_no <<endl;
    }
    else{
        cout<<" PSR with thread ID: "<<PSR_thread_id<<" created"<<endl;
        }

}
void ResourceManager::initializeSSR(){

}

void ResourceManager::configureSimulation(){

    createAircraftThreads();
    createATCSSubsystems();
}

void ResourceManager::runSimulation(){

    cout << "Begin of simulation" << endl;


}

void ResourceManager::execute(){

    char input;

    configureSimulation();

    // Execute the ATCS simulation
    cout << "All systems ready, press 'R' to run the simulation." << endl;
    cin >> input;
    if (input == 'R')
        runSimulation();

}


ResourceManager::~ResourceManager() {
	// TODO Auto-generated destructor stub
}
