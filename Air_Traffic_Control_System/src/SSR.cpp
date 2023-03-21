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
	cout<<"Ask Aircraft:"<< targetAircraft.getFlightID()<<endl;
};

/* -----------------------------------------------------------------------------
 * Name:        receiveTransponderData
 * Input:       Aircraft targetAircraft
 * Output:      Aircraft targetAircraft
 * Description: This method will receive transponder data between the Aircraft
 *              thread and SSR.
 * -----------------------------------------------------------------------------
 */
transponderData SSR::receiveTransponderData(Aircraft targetAircraft){

    transponderData TD;

    targetAircraft.ServiceInterrogationSignal();

    TD.flightId=targetAircraft.getFlightID();//after we have successfully interrogated the Aircrafts in illuminatedObjects, we can go ahead and grab the required info
    TD.flightLevel= targetAircraft.getFlightLevel();

    //Aircraft Positions X,Y,Z
    TD.positionX=targetAircraft.getPosX();
    TD.positionY=targetAircraft.getPosY();
    TD.positionZ=targetAircraft.getPosZ();

    //Aircraft Speeds X,Y,Z
    TD.speedX=targetAircraft.getSpeedX();
    TD.speedY=targetAircraft.getSpeedY();
    TD.speedZ=targetAircraft.getSpeedZ();

    return TD;

};

vector<transponderData> SSR::interrogate(vector<Aircraft> illuminatedObjects)		//first we receive an array of illuminated Objects (assume we push them from back to front)
{

    transponderData receivedReply;

for(Aircraft& illuminatedObject: illuminatedObjects){
    //interrogate the aircraft and receive transponder data
    interrogateAircraft(illuminatedObject);

    receivedReply = receiveTransponderData(illuminatedObject);
    transponderDataList.push_back(receivedReply);
}
	return transponderDataList;
}


vector<transponderData> SSR::sendTransponderData()
{
    for (transponderData& transponderData: transponderDataList){

        cout<<transponderData.flightId<<endl;
        cout<<transponderData.flightLevel<<endl;
        cout<<transponderData.positionX<<endl;
        cout<<transponderData.positionY<<endl;
        cout<<transponderData.positionZ<<endl;
        cout<<transponderData.speedX<<endl;
        cout<<transponderData.speedY<<endl;
        cout<<transponderData.speedZ<<endl;
        cout<<endl;
        cout<<endl;
    }

    return transponderDataList;
}

 void SSR::execute(){

     interrogate(illuminatedObjects);
     sendTransponderData();
 }

SSR::~SSR() {
	// TODO Auto-generated destructor stub
};

