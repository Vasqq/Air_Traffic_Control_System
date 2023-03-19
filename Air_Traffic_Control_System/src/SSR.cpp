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


SSR::SSR() {
	// TODO Auto-generated constructor stub

};

/*
 * Function Name: interrogateAircraft
 * Input: Aircraft targetAircraft
 * Output: Aircraft targetAircraft
 * Description:This method will request the aircraft thread for transponder data
 */
void SSR::interrogateAircraft(Aircraft targetAircraft){
	Aircraft A;
};

/*
 * Function Name: receiveTransponderData
 * Input: Aircraft targetAircraft
 * Output: Aircraft targetAircraft
 * Description:This method will receive transponder data between Aircraft Thread and SSR.
 */
SSR::transponderData SSR::receiveTransponderData(Aircraft targetAircraft){

	/*
	Aircraft A;
	//Aircraft Flight ID and Flight Level
	TD.flightID=A.getFlightId(targetAircraft);//after we have successfully interrogated the Aircrafts in illuminatedObjects, we can go ahead and grab the required info
	TD.flightLevel= A.getFlightLevel(targetAircraft);

	//Aircraft Positions X,Y,Z
	TD.positionX=A.getPositionX(targetAircraft);
	TD.positionY=A.getPositionY(targetAircraft);
	TD.positionZ=A.getPositionZ(targetAircraft);

	//Aircraft Speeds X,Y,Z
	TD.speedX=A.getSpeedX(targetAircraft);
	TD.speedY=A.getSpeedY(targetAircraft);
	TD.speedZ=A.getSpeedZ(targetAircraft);
	return TD;
	*/
};

 SSR::transponderData* SSR::Interrogate(Aircraft illuminatedObjects[])		//first we receive an array of illuminated Objects (assume we push them from back to front)
{
	int i;
	int s= (sizeof(illuminatedObjects) / sizeof((illuminatedObjects[0])));		//because I refuse to run a for loop for this, I'm using this to get the length
	for (i=0;i<=s;i++){
		//interrogate the aircraft and receive the transponder data
		interrogateAircraft(illuminatedObjects[i]);		//goes into array and grabs ith object and passes it to function
				//if we successfully ask for the
		//Store this inside an Aircraft object array called transponderData to use for the senTransponderData function

	transponderDataArr[i]=receiveTransponderData(illuminatedObjects[i]);		//doing this will also dynamically increase the size of the array

	}
	return transponderDataArr;
}


 SSR::transponderData* SSR::sendTransponderData(transponderData transponderDataArr[])
{

	 return transponderDataArr;
}
SSR::~SSR() {
	// TODO Auto-generated destructor stub
};

