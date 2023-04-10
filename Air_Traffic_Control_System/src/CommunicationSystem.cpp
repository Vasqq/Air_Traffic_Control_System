/*
 * CommunicationSystem.cpp
 *
 *  Created on: Apr 8, 2023
 *      Author: Argi
 */

#include "CommunicationSystem.h"
/* -----------------------------------------------------------------------------
 * Name:		CommunicationSystem
 * Input:		None
 * Output:		None
 * Description:	Constructor for CommunicationSystem class
 * -----------------------------------------------------------------------------
 */
CommunicationSystem::CommunicationSystem() {
    // TODO Auto-generated constructor stub

}
/* -----------------------------------------------------------------------------
 * Name:		CommunicationSystem
 * Input:		Aircraft object
 * Output:		None
 * Description:	Constructor for CommunicationSystem class taking an Aircraft
 * 				object
 * -----------------------------------------------------------------------------
 */
CommunicationSystem::CommunicationSystem(Aircraft& flight_id) {
    this->flight_id=flight_id;
}
/* -----------------------------------------------------------------------------
 * Name:		~CommunicationSystem
 * Input:		None
 * Output:		None
 * Description:	Destructor for CommunicationSystem class
 * -----------------------------------------------------------------------------
 */
CommunicationSystem::~CommunicationSystem() {
    // TODO Auto-generated destructor stub
}


/* -----------------------------------------------------------------------------
 * Name:		msgPassingChannel
 * Input:		None
 * Output:		Integer representing the created message passing channel ID
 * Description:	Creates a message passing channel and returns the channel ID
 * -----------------------------------------------------------------------------
 */
int CommunicationSystem::msgPassingChannel(){

int chid = ChannelCreate(0);
if (chid == -1) {
    printf("Error: ChannelCreate failed. Error ID: %s\n",strerror(errno));
    exit(EXIT_FAILURE);
}

return chid;
}
/* -----------------------------------------------------------------------------
 * Name:		fwdConsoleRequest
 * Input:		Aircraft object
 * Output:		None
 * Description:	Forwards a service interrogation signal to an Aircraft object
 * 				in a new thread
 * -----------------------------------------------------------------------------
 */
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
/* -----------------------------------------------------------------------------
 * Name:		fwdServiceInterrogationSignalID
 * Input:		Void pointer to an Aircraft object
 * Output:		Void pointer
 * Description:	Forwards execution to an Aircraft object to send a service
 * 				interrogation signal
 * -----------------------------------------------------------------------------
 */
void* CommunicationSystem::fwdServiceInterrogationSignalID(void *flight_id_ptr) {

    static_cast<Aircraft*>(flight_id_ptr)->ServiceInterrogationSignalConsole();
        return NULL;
}

/* -----------------------------------------------------------------------------
 * Name:		interrogateAircraftConsole
 * Input:		Pointer to an Aircraft object
 * Output:		None
 * Description:	Sends a message to an Aircraft object to request transponder data and receives the response
 * -----------------------------------------------------------------------------
 */

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

/* -----------------------------------------------------------------------------
 * Name:		receiveTransponderDataConsole
 * Input:		sTransponderData structure
 * Output:		None
 * Description:	Receives transponder data from an Aircraft object and stores it
 * 				in a list
 * -----------------------------------------------------------------------------
 */
void CommunicationSystem::receiveTransponderDataConsole(sTransponderData aircraftTransponderData)
{

    // Receive message from the aircraft thread containing transponder data

    transponderDataList.push_back(aircraftTransponderData);
};

