/*
 * CommunicationSystem.h
 *
 *  Created on: Apr 8, 2023
 *      Author: Argi
 */

#ifndef SRC_COMMUNICATIONSYSTEM_H_
#define SRC_COMMUNICATIONSYSTEM_H_
#include "ComputerSystem.h"
#include "Console.h"
#include "ResourceManager.h"

class CommunicationSystem {
public:
    CommunicationSystem();
    virtual ~CommunicationSystem();

    void requestAircraftInfo(int aircraftID);



};

#endif /* SRC_COMMUNICATIONSYSTEM_H_ */
