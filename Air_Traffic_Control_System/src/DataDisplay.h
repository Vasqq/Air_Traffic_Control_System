/*
 * DataDisplay.h
 *
 *  Created on: Apr 7, 2023
 *      Author: Argi
 */

#ifndef SRC_DATADISPLAY_H_
#define SRC_DATADISPLAY_H_

#include "ComputerSystem.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <limits>
#include <thread>
#include <cstdlib>

using namespace std;

class DataDisplay
{
public:
    DataDisplay(vector<sTransponderData> *transponderDataARR, vector<int> *closeAircraftsARR);
    virtual ~DataDisplay();

    // this function couts the transponder data from the computer system
    void displayTransponderData();


    // scaled down and should also show the aircrafts relative location within that too
    void displayVisual();

private:
    vector<sTransponderData> *transponderDataARR;
    vector<int> *closeAircraftsARR;
    bool collisionDetection = false;
};

#endif /* SRC_DATADISPLAY_H_ */
