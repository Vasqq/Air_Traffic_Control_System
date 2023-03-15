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
public:
	SSR();

	Aircraft* Interrogate(Aircraft illuminatedObjects[]);
	Aircraft* sendTransponderData(Aircraft transponderData[]);

	void interrogateAircraft(Aircraft targetAircraft);
	void receiveTransponderData(Aircraft targetAircraft);

	virtual ~SSR();
};

#endif /* SSR_H_ */
