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

using namespace std;


SSR::SSR(vector<Aircraft>illuminatedObjects) {
	// TODO Auto-generated constructor stub
	this->illuminatedObjects=illuminatedObjects;


};



/*
 * Function Name: interrogateAircraft
 * Input: Aircraft targetAircraft
 * Output: Aircraft targetAircraft
 * Description:This method will request the aircraft thread for transponder data
 */
void SSR::interrogateAircraft(Aircraft targetAircraft){

		//implement message passing for thread

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


vector<transponderData> SSR::sendTransponderData()
{
    //send transponderDataList to computer system
    return transponderDataList;
}

 void SSR::execute(){

     interrogate(illuminatedObjects);
     sendTransponderData();
 }

SSR::~SSR() {
	// TODO Auto-generated destructor stub
};

