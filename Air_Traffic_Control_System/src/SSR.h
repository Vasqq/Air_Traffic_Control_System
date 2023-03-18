/*
 * SSR.h
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 */

#ifndef SSR_H_
#define SSR_H_
#include "Aircraft.h"

class SSR {

private:
	struct transponderData
{
			int flightId;
			int flightLevel;
			int positionX;
			int positionY;
			int positionZ;
			int speedX;
			int speedY;
			int speedZ;

 };


 transponderData TD;

public:
	SSR();

		transponderData transponderDataArr[5];


		transponderData* Interrogate(Aircraft illuminatedObjects[]);
		transponderData* sendTransponderData(transponderData transponderData[]);
		transponderData receiveTransponderData(Aircraft targetAircraft);
	void interrogateAircraft(Aircraft targetAircraft);


	virtual ~SSR();



};

#endif /* SSR_H_ */
