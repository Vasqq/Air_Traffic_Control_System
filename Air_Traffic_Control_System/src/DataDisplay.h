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



using namespace std;

class DataDisplay {
public:
    DataDisplay(vector<sTransponderData> *transponderDataARR,vector<int> *closeAircraftsARR);
    virtual ~DataDisplay();


    //this function couts the transponder data from the computer system
    void displayTransponderData();

    //this section will create a rectangle of size of 100000x100000 units to
    //display aircrafts as Xs on screen with their X and Y coordinates and X and
    //Y speeds next to them
    void displayVisual();




private:
    vector<sTransponderData> *transponderDataARR;
    vector<int> *closeAircraftsARR;
    bool collisionDetection  = false;

};

#endif /* SRC_DATADISPLAY_H_ */
