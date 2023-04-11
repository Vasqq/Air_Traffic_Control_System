/*
 * DataDisplay.cpp
 *
 *  Created on: Apr 7, 2023
 *      Author: Argi
 */

#include "DataDisplay.h"


/* -----------------------------------------------------------------------------
 * Name:  		DataDisplay
 * Input:		vector<sTransponderData> *transponderDataARR &
 * 				vector<int> *closeAircraftsARR
 * Output:		None
 * Description:	Initializes the DataDisplay object with the provided
 * 				transponder data and close aircrafts, and calls the displayVisual
 * 				and displayTransponderData functions.
 * -----------------------------------------------------------------------------
 */
DataDisplay::DataDisplay(vector<sTransponderData> *transponderDataARR, vector<int> *closeAircraftsARR)
{

	this->transponderDataARR = transponderDataARR;
	this->closeAircraftsARR = closeAircraftsARR;

	displayVisual();
	displayTransponderData();
}

/* -----------------------------------------------------------------------------
 * Name:    	~DataDisplay
 * Input:		None
 * Output:		None
 * Description:	Destructor for the class DataDisplay.
 * -----------------------------------------------------------------------------
 */
DataDisplay::~DataDisplay()
{
	// TODO Auto-generated destructor stub

}

/* -----------------------------------------------------------------------------
 * Name:        displayTransponderData
 * Input:		None
 * Output:		None
 * Description:	Displays the transponder data in a formatted table.
 * -----------------------------------------------------------------------------
 */
void DataDisplay::displayTransponderData()
{

	cout << endl;
	cout << "-----------------------------<Flight Data>---------------------------"
		 << endl;
	for (sTransponderData &td : *transponderDataARR)
	{
		cout << "------------------------------------------------------------"
				"---------"
			 << endl;
		cout << "Aircraft Flight ID: " << td.flightId << endl;
		cout << "Position (x, y, z): (" << td.positionX << ", " << td.positionY << ", " << td.positionZ << ")" << endl;
		cout << "Speed (x, y, z): (" << td.speedX << ", " << td.speedY << ", " << td.speedZ << ")" << endl;
		cout << "------------------------------------------------------------"
				"---------"
			 << endl;
	}
	cout << "-----------------------------<Flight Data>---------------------------"
		 << endl;

}

/* -----------------------------------------------------------------------------
 * Name:        displayVisual
 * Input:		None
 * Output:		None
 * Description:	Displays a visual representation of the airspace with "A"# where
 * 				the # is the aircraft ID in the scaled down airspace.
 * -----------------------------------------------------------------------------
 */
void DataDisplay::displayVisual()
{

     const int width = 301;
     const int height = 201;
     const int originX = width / 2;
     const int originY = height / 2;
     const int minX = -100000 ;
     const int maxX = 100000 ;
     const int minY = -100000 ;
     const int maxY = 100000 ;

     vector<string> plane(height, string(width, ' '));

     // draw x-axis
     for (int x = minX; x <= maxX; x += 1000) {
         int xPos = originX + x / 1000;
         if (xPos >= 0 && xPos < width) {
             if (x % 10000 == 0) {
                 plane[originY][xPos] = '|';
             } else {
                 plane[originY][xPos] = '-';
             }
         }
     }

     // draw y-axis
     for (int y = minY; y <= maxY; y += 1000) {
         int yPos = originY - y / 1000;
         if (yPos >= 0 && yPos < height) {
             if (y % 10000 == 0) { // check if the y-value is a multiple of 10000
                 stringstream ss;
                 ss << y;
                 string yLabel = ss.str();
                 int labelSize = yLabel.size();
                 int labelPos = originX - labelSize - 1;
                 if (labelPos >= 0 && labelPos < width) {
                     plane[yPos].replace(labelPos, labelSize, yLabel);
                 }
             }
             plane[yPos][originX - 1] = '|'; // draw a vertical line at every 1000 units
         }
     }

     // draw negative y-axis
     for (int y = -1000; y >= minY; y -= 1000) {
         int yPos = originY - y / 1000;
             if (yPos >= 0 && yPos < height) {
                     if (y % 10000 == 0) {
                             stringstream ss;
                                 ss << y;
                                 string yLabel = ss.str();
                                 int labelSize = yLabel.size();
                                 int labelPos = originX - labelSize - 1;
                                 if (labelPos >= 0 && labelPos < width) {
                                     plane[yPos].replace(labelPos, labelSize, yLabel);
                                     plane[yPos][originX - 1] = '|';
                                 }
                     } else {
                         plane[yPos][originX - 1] = '|';
                     }
             }
             }
     for (sTransponderData &td : *transponderDataARR) {
          int xPos = round(td.positionX / 1000.0) + originX;
          int yPos = originY - round(td.positionY / 1000.0);
          if (xPos >= 0 && xPos < width && yPos >= 0 && yPos < height) {
              string flightID = to_string(td.flightId);
              string positionStr = "(" + to_string(td.positionX) + "," + to_string(td.positionY) + ")";
              string displayStr = "A" + flightID + positionStr;
              int positionXPos, positionYPos;
              if (td.positionX >= 0) {
                  positionXPos = xPos + 1;
                  positionYPos = xPos - displayStr.size() - 1;
              } else {
                  positionXPos = xPos - displayStr.size() - 2;
                  positionYPos = xPos + 1;
              }
              if (flightID.size() <= 3) {
                  plane[yPos].replace(positionXPos, 3, displayStr);
              } else {
                  plane[yPos].replace(positionXPos, 4, displayStr.substr(0, 4));
              }
          }
      }
     // print the updated plane vector
     for (int i = 0; i < height; i++) {
         cout << plane[i] << endl;
     }

     plane.clear();



 }
