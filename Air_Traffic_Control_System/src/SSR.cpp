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


using namespace std;

/* -----------------------------------------------------------------------------
 * Name:        SSR
 * Input:       vector<Aircraft> illuminatedObjects
 * Output:      None
 * Description:  This is a constructor of the SSR class that  initializes the
 *               illuminatedObjects vector.
 * -----------------------------------------------------------------------------
 */
SSR::SSR(vector<Aircraft>illuminatedObjects) {
	// TODO Auto-generated constructor stub
	this->illuminatedObjects=illuminatedObjects;




};




/* -----------------------------------------------------------------------------
 * Name:        ~SSR
 * Input:       None
 * Output:      None
 * Description: Destructor for the SSR class.
 * -----------------------------------------------------------------------------
 */
SSR::~SSR() {


};





/* -----------------------------------------------------------------------------
 * Name:        interrogateAircraft
 * Input:       Aircraft targetAircraft
 * Output:      Aircraft targetAircraft
 * Description: This method will request the aircraft thread for transponder
 *              data
 * -----------------------------------------------------------------------------
 */
void SSR::interrogateAircraft(Aircraft targetAircraft){

	//implement message passing for thread
    // Send interrogation signal to the Aircraft thread
        targetAircraft.ServiceInterrogationSignal();





};

/* -----------------------------------------------------------------------------
 * Name:        receiveTransponderData
 * Input:       Aircraft targetAircraft
 * Output:      Aircraft targetAircraft
 * Description: This method will receive transponder data between the Aircraft
 *              thread and SSR.
 * -----------------------------------------------------------------------------
 */
void SSR::receiveTransponderData(Aircraft targetAircraft){

    // Receive message from the aircraft thread containing transponder data

    targetAircraft.receiveInterrogationSignal();

    transponderData TD;

    targetAircraft.ServiceInterrogationSignal();

    TD.flightId=targetAircraft.getFlightID();
    TD.flightLevel= targetAircraft.getFlightLevel();

    //Aircraft Positions X,Y,Z
    TD.positionX=targetAircraft.getPosX();
    TD.positionY=targetAircraft.getPosY();
    TD.positionZ=targetAircraft.getPosZ();

    //Aircraft Speeds X,Y,Z
    TD.speedX=targetAircraft.getSpeedX();
    TD.speedY=targetAircraft.getSpeedY();
    TD.speedZ=targetAircraft.getSpeedZ();


    transponderDataList.push_back(TD);


};

/* -----------------------------------------------------------------------------
 * Name:        interrogate
 * Input:       vector<Aircraft> illuminatedObjects
 * Output:      transponderDataList
 * Description: This method will interrogate each Aircraft and Illuminated Obj
 *              vector and return the transponder Data for each Aircraft.
 * -----------------------------------------------------------------------------
 */

void SSR::interrogate(vector<Aircraft> illuminatedObjects)
{

    transponderData receivedReply;

for(Aircraft& illuminatedObject: illuminatedObjects){
    //interrogate the aircraft and receive transponder data
    interrogateAircraft(illuminatedObject);
    receiveTransponderData(illuminatedObject);
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
vector<transponderData> SSR::sendTransponderData()
{
    //send transponderDataList to computer system
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
 void SSR::execute(){

     while(true){}
     interrogate(illuminatedObjects);
     sendTransponderData();
 }


