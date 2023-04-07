/*
 * DataDisplay.cpp
 *
 *  Created on: Apr 7, 2023
 *      Author: Argi
 */

#include "DataDisplay.h"


DataDisplay::DataDisplay(vector<sTransponderData> *transponderDataARR,vector<int> *closeAircraftsARR) {
    this->transponderDataARR = transponderDataARR;
    this->closeAircraftsARR = closeAircraftsARR;

    displayVisual();
    displayTransponderData();

}

DataDisplay::~DataDisplay() {
    // TODO Auto-generated destructor stub
}

void DataDisplay::displayTransponderData() {

    cout<<endl;
    cout<<"-----------------------------<Flight Data>---------------------------"
            <<endl;
    for (sTransponderData& td : *transponderDataARR)
        {
            cout<<"------------------------------------------------------------"
                    "---------"<<endl;
            cout << "Aircraft Flight ID: " << td.flightId << endl;
            cout << "Position (x, y, z): (" << td.positionX << ", " << td.positionY << ", " << td.positionZ << ")" << endl;
            cout << "Speed (x, y, z): (" << td.speedX << ", " << td.speedY << ", " << td.speedZ << ")" << endl;
            cout<<"------------------------------------------------------------"
                    "---------"<<endl;
        }
    cout<<"-----------------------------<Flight Data>---------------------------"
            <<endl;
}

void DataDisplay::displayVisual() {
    // Define the dimensions of the rectangle
       const int width = 100000;
       const int height = 100000;

       // Define the scaling factor
       const int scale = 100;

       // Define the characters for the borders and the empty space
       const char border_char = '-';
       const char empty_char = ' ';
       const char vertical_char = '|';

       // Create a string to hold the entire rectangle
       string rectangle((height/scale) * (width/scale), empty_char);

       // Add Xs to the rectangle at the positions of the aircraft
       for (const sTransponderData& td : *transponderDataARR) {
           // Calculate the scaled coordinates of the aircraft on the screen
           int x = static_cast<int>(td.positionX / scale);
           int y = static_cast<int>(td.positionY / scale);

           // If the aircraft is within the rectangle, add its X to the rectangle
           if (x >= 0 && x < width/scale && y >= 0 && y < height/scale) {
               rectangle[y * (width/scale) + x] = 'X';
           }
       }

       // Print the scaled-down rectangle to the console
       for (int y = 0; y < height/scale; y++) {
           // Print the left border
           cout << vertical_char;
           for (int x = 0; x < width/scale; x++) {
               if (y == 0 || y == height/scale - 1) {
                   // Print the top or bottom border
                   cout << border_char;
               } else {
                   // Print the X or empty space
                   cout << rectangle[y * (width/scale) + x];
               }
           }
           // Print the right border
           cout << vertical_char << endl;
       }

       // Print the bottom border
       cout << string(width/scale + 2, border_char) << endl;
   }
