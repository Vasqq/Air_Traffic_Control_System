/*
 * SSR.cpp
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 *
 *      FILE DESCRIPTION GOES HERE
 */

#include "SSR.h"
#include "Aircraft.h"
#include <iostream>
#include <array>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/types.h>

using namespace std;

/* -----------------------------------------------------------------------------
 * Name:        SSR
 * Input:       vector<Aircraft> illuminatedObjects
 * Output:      None
 * Description:  This is a constructor of the SSR class that  initializes the
 *               illuminatedObjects vector.
 * -----------------------------------------------------------------------------
 */
SSR::SSR(vector<Aircraft *> illuminatedObjects)
{
    // TODO Auto-generated constructor stub
    this->illuminatedObjects = illuminatedObjects;
};

/* -----------------------------------------------------------------------------
 * Name:        ~SSR
 * Input:       None
 * Output:      None
 * Description: Destructor for the SSR class.
 * -----------------------------------------------------------------------------
 */
SSR::~SSR(){

};

/* -----------------------------------------------------------------------------
 * Name:        interrogateAircraft
 * Input:       Aircraft targetAircraft
 * Output:      Aircraft targetAircraft
 * Description: This method will request the aircraft thread for transponder
 *              data
 * -----------------------------------------------------------------------------
 */
void SSR::interrogateAircraft(Aircraft *targetAircraft)
{

    cout << targetAircraft << endl;
    int chid = targetAircraft->getTransponderDataChannel();

    // Connecting the SSR to channel
    int coid = ConnectAttach(ND_LOCAL_NODE, 0, chid, _NTO_SIDE_CHANNEL, 0);
    if (coid == -1)
    {
        perror("Failed to connect to Aircraft");
        ChannelDestroy(chid);
        exit(EXIT_FAILURE);
    }

    cout << "Aircraft thread waiting for Interrogation signal..." << endl;
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
        cout << "Aircraft reply\n";
    }
    else
    {
        cout << "MsgSend failed. Error Code: " << strerror(errno) << endl;
        return;
    }

    ConnectDetach(coid);

    //cout << "Aircraft flightID is: " << aircraftTransponderData.flightId << endl;

    receiveTransponderData(aircraftTransponderData);
};

/* -----------------------------------------------------------------------------
 * Name:        receiveTransponderData
 * Input:       Aircraft targetAircraft
 * Output:      Aircraft targetAircraft
 * Description: This method will receive transponder data between the Aircraft
 *              thread and SSR.
 * -----------------------------------------------------------------------------
 */
void SSR::receiveTransponderData(sTransponderData aircraftTransponderData)
{

    // Receive message from the aircraft thread containing transponder data

    transponderDataList.push_back(aircraftTransponderData);
};

/* -----------------------------------------------------------------------------
 * Name:        interrogate
 * Input:       vector<Aircraft> illuminatedObjects
 * Output:      transponderDataList
 * Description: This method will interrogate each Aircraft and Illuminated Obj
 *              vector and return the transponder Data for each Aircraft.
 * -----------------------------------------------------------------------------
 */

void SSR::interrogate(vector<Aircraft *> illuminatedObjects)
{

    for (Aircraft *illuminatedObject : illuminatedObjects)
    {
        // interrogate the aircraft and receive transponder data
        interrogateAircraft(illuminatedObject);
        // receiveTransponderData(illuminatedObject);
    }
}

/* -----------------------------------------------------------------------------
 * Name:        sendTransponderData
 * Input:       None
 * Output:      transponderDataList
 * Description: This method will return the transponderDataList vector that was
 *              filled with the push_back values of the transponderData struct
 *              from receiveTransponderData().
 * -----------------------------------------------------------------------------
 */
vector<sTransponderData> SSR::sendTransponderData()
{
    // send transponderDataList to computer system

    // this just tests that all values passed over are correct so we can move on to send the Transponder data
//    for (const auto &td : transponderDataList)
//    {
//        cout << "Flight ID: " << td.flightId << endl;
//        cout << "Position (x, y, z): (" << td.positionX << ", " << td.positionY << ", " << td.positionZ << ")" << endl;
//        cout << "Speed (x, y, z): (" << td.speedX << ", " << td.speedY << ", " << td.speedZ << ")" << endl;
//        cout << endl;
//    }


    return transponderDataList;
}

/* -----------------------------------------------------------------------------
 * Name:        execute
 * Input:       None
 * Output:      None
 * Description: This method will run interrogate and senTransponderData,
 *              executing all functions within the SSR.
 * -----------------------------------------------------------------------------
 */
void SSR::execute()
{

    interrogate(illuminatedObjects);
    //cout << &transponderDataList << endl;
    ComputerSystem cs(&transponderDataList);
    //cs.checkAircraftProximity(sendTransponderData());
}
