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
#include "Aircraft.h"

class CommunicationSystem {
public:
    CommunicationSystem();
    CommunicationSystem(Aircraft& flight_id);

    virtual ~CommunicationSystem();

    void requestAircraftInfo(int aircraftID);

    int msgPassingChannel();
    void fwdConsoleRequest(Aircraft &flight_id);
    static void* fwdServiceInterrogationSignalID(void *flight_id_ptr);


    void interrogateAircraftConsole(Aircraft *targetAircraft);


    void receiveTransponderDataConsole(sTransponderData illuminatedObject);
    vector<sTransponderData> transponderDataList;



private:
    int cID;
    Aircraft flight_id;
    vector<Aircraft* > illuminatedObjects;

};

#endif /* SRC_COMMUNICATIONSYSTEM_H_ */
