/*
 * CommunicationSystem.cpp
 *
 *  Created on: Apr 8, 2023
 *      Author: Argi
 */

#include "CommunicationSystem.h"

CommunicationSystem::CommunicationSystem() {
    // TODO Auto-generated constructor stub

}

CommunicationSystem::CommunicationSystem(Aircraft& flight_id) {
    this->flight_id=flight_id;
}

CommunicationSystem::~CommunicationSystem() {
    // TODO Auto-generated destructor stub
}



int CommunicationSystem::msgPassingChannel(){

int chid = ChannelCreate(0);
if (chid == -1) {
    printf("Error: ChannelCreate failed. Error ID: %s\n",strerror(errno));
    exit(EXIT_FAILURE);
}

return chid;
}

void CommunicationSystem::fwdConsoleRequest(Aircraft &flight_id){
        int err_no;
       pthread_t thread_id;
       pthread_attr_t attr;
       pthread_attr_init( &attr );


       err_no = pthread_create(&thread_id,
               &attr, &fwdServiceInterrogationSignalID, &flight_id);
          if (err_no != 0) {
              printf("ERROR when creating thread:\n");
          } else {
              printf("\tfwdServiceInterrogationSignal thread created with ID: %d\n", thread_id);
          }

}



void* CommunicationSystem::fwdServiceInterrogationSignalID(void *flight_id_ptr) {

    static_cast<Aircraft*>(flight_id_ptr)->ServiceInterrogationSignalConsole();
        return NULL;
}

void CommunicationSystem::interrogateAircraftConsole(Aircraft *targetAircraft)
{


    int chid = targetAircraft->getTransponderDataChannel();

    // Connecting the SSR to channel
    int coid = ConnectAttach(ND_LOCAL_NODE, 0, chid, _NTO_SIDE_CHANNEL, 0);
    if (coid == -1)
    {
        perror("Failed to connect to Aircraft");
        ChannelDestroy(chid);
        exit(EXIT_FAILURE);
    }

    //cout << "Aircraft thread waiting for Interrogation signal..." << endl;
    // targetAircraft.ServiceInterrogationSignal();
    //  Receive message
    sInterrogationSignal is;
    sTransponderData aircraftTransponderData;
    // we are requesting the following from Aircraft

    // Send the message to the Aircraft thread
    // targetAircraft.ServiceInterrogationSignal(chid, pid);

    int returnCode = MsgSend(coid, &is, sizeof(is), &aircraftTransponderData, sizeof(aircraftTransponderData));

    if (returnCode != -1)
    {
        //cout << "Aircraft reply\n";
    }
    else
    {
        cout << "MsgSend failed. Error Code: " << strerror(errno) << endl;
        return;
    }

    ConnectDetach(coid);

    //cout << "Aircraft flightID is: " << aircraftTransponderData.flightId << endl;

    receiveTransponderDataConsole(aircraftTransponderData);
};


void CommunicationSystem::receiveTransponderDataConsole(sTransponderData aircraftTransponderData)
{

    // Receive message from the aircraft thread containing transponder data

    transponderDataList.push_back(aircraftTransponderData);
};

