/*
 * ResourceManager.cpp
 *
 *  Created on: Mar 14, 2023
 *      Author: Argi
 */

#include "ResourceManager.h"



ResourceManager::ResourceManager() {

}

ResourceManager::ResourceManager(vector<Aircraft> AircraftSchedule) {

    this->AircraftSchedule=AircraftSchedule;

}

void * ResourceManager:: ThreadAircraft(void * aircraft)
{

    cout<<"Test"<<endl;
}

void ResourceManager::createAircraftThreads(){

for(Aircraft& aircraft: AircraftSchedule){
    spawnNewAircraftThread(aircraft);




    }
}
void ResourceManager::spawnNewAircraftThread(Aircraft AircraftObj){

    int err_no;
    pthread_t   our_thread_id;

    err_no= pthread_create(&our_thread_id,
                                  NULL,
                                  &ThreadAircraft,
                                  NULL);
            if(err_no!=0){
                cout<<"ERROR when creating thread"<< err_no <<endl;
            }
            else{
                cout<<" Thread "<<our_thread_id<<" created"<<endl;
            }

}


ResourceManager::~ResourceManager() {
	// TODO Auto-generated destructor stub
}
