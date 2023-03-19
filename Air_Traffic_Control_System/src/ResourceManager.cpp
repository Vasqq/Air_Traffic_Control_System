/*
 * ResourceManager.cpp
 *
 *  Created on: Mar 14, 2023
 *      Author: Argi
 */

#include "ResourceManager.h"

ResourceManager::ResourceManager() {
	// TODO Auto-generated constructor stub

}

ResourceManager::~ResourceManager() {
	// TODO Auto-generated destructor stub
}


int ResourceManager::spawnNewAircraftThread(Aircraft AircraftObj){

	for (i=1;i<=numOfLines;i++)
	{
		int pid=i;
		pthread_create(NULL, NULL, &functionA ,NULL);

		pthread_create( NULL, NULL, &function, NULL );
	}

}
