/*
 * SSR.h
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 */

#ifndef SSR_H_
#define SSR_H_
#include "Aircraft.h"
#include "PSR.h"
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


class SSR {

private:



 transponderData TD;

vector<Aircraft> illuminatedObjects;

public:
	SSR(vector<Aircraft>illuminatedObjects);


		 vector<transponderData> transponderDataList;


		 vector<transponderData> Interrogate(vector<Aircraft> illuminatedObjects);
		 vector<transponderData> sendTransponderData();
		transponderData receiveTransponderData(Aircraft illuminatedObject);
	void interrogateAircraft(Aircraft targetAircraft);
	void execute();

	virtual ~SSR();



};

#endif /* SSR_H_ */
