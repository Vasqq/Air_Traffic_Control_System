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
    // Struct declaration for transponderData
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
	// Object declaration for Transponder Data object
	transponderData TD;
	// Vector declaration for illuminatedObjects vector of type Aircraft
	vector<Aircraft> illuminatedObjects;

public:
    // Constructors and destructor
    SSR(vector<Aircraft>illuminatedObjects);
    virtual ~SSR();


    // Functions to interact with Aircraft threads and receive their data
    void interrogateAircraft(Aircraft targetAircraft);
    void receiveTransponderData(Aircraft illuminatedObject);

    // Function that will run the two previous functions
    void interrogate(vector<Aircraft> illuminatedObjects);

    // This function will return the result of interrogate
    vector<transponderData> sendTransponderData();

    // This execute will execute all function calls for the SSR
    void execute();


    // Public declaration of transponderDataList vector
    vector<transponderData> transponderDataList;


};

#endif /* SSR_H_ */
