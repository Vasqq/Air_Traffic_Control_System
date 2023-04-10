/*
 * DataDisplay.cpp
 *
 *  Created on: Apr 7, 2023
 *      Author: Argi
 */

#include "DataDisplay.h"

DataDisplay::DataDisplay(vector<sTransponderData> *transponderDataARR, vector<int> *closeAircraftsARR)
{

	this->transponderDataARR = transponderDataARR;
	this->closeAircraftsARR = closeAircraftsARR;

	displayVisual();
	displayTransponderData();
}

DataDisplay::~DataDisplay()
{
	// TODO Auto-generated destructor stub

}

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

void DataDisplay::displayVisual()
{

	// Define the dimensions of the full airspace
	const int AIRSPACE_WIDTH = 100000;
	const int AIRSPACE_HEIGHT = 100000;

	// Define the dimensions of the reduced airspace (box)
	const int BOX_WIDTH = 70;
	const int BOX_HEIGHT = 40;

	// Compute the maximum distance between any two aircrafts
	double maxDistance = 0;
	for (int i = 0; i < transponderDataARR->size(); i++)
	{
		for (int j = i + 1; j < transponderDataARR->size(); j++)
		{
			double distance = sqrt(pow(transponderDataARR->at(i).positionX - transponderDataARR->at(j).positionX, 2) +
								   pow(transponderDataARR->at(i).positionY - transponderDataARR->at(j).positionY, 2));
			if (distance > maxDistance)
			{
				maxDistance = distance;
			}
		}
	}

	// Compute the scaling factors for both dimensions based on the maximum distance
	double widthFactor = AIRSPACE_WIDTH / (maxDistance/10);
	double heightFactor = AIRSPACE_HEIGHT / (maxDistance/10);

	// If the scaling factors are too small, round them up to 1
	if (widthFactor < 1)
		widthFactor = 1;
	if (heightFactor < 1)
		heightFactor = 1;

	// Compute the dimensions of the reduced airspace including the border
	const int BORDER_WIDTH = BOX_WIDTH + 4;
	const int BORDER_HEIGHT = BOX_HEIGHT + 2;

	// Create a 2D vector to represent the reduced airspace and initialize it with empty cells
	vector<vector<string>> reducedAirspace(BORDER_HEIGHT, vector<string>(BORDER_WIDTH, " "));

	// Iterate over the transponder data and update the corresponding cell in the reduced airspace
	for (sTransponderData &data : *transponderDataARR)
	{
		// Scale the coordinates down to the reduced airspace
		int x = static_cast<int>(data.positionX / widthFactor);
		int y = static_cast<int>(data.positionY / heightFactor);

		// Check if the scaled coordinates are within the reduced airspace
		if (x >= 0 && x < BOX_WIDTH && y >= 0 && y < BOX_HEIGHT)
		{
			// Mark the cell with the aircraft ID
			string cellContent = "A" + to_string(data.flightId);
			if (cellContent.length() > 2)
			{
				cellContent = cellContent.substr(0, 2);
			}
			if (reducedAirspace[y + 1][x + 1] == " ")
			{
				reducedAirspace[y + 1][x + 1] = cellContent;
			}
			else
			{
				// If the cell is already occupied, shift the new cell over by 1
				for (int i = 1; i <= BOX_WIDTH; i++)
				{
					if (x + i < BOX_WIDTH && reducedAirspace[y + 1][x + i + 1] == " ")
					{
						reducedAirspace[y + 1][x + i + 1] = cellContent;
						break;
					}
				}
			}
		}
	}

	// Display the reduced airspace with the aircraft IDs and the border
	cout << "+" << string(BOX_WIDTH - 2, '-') << "+" << endl;
	for (int y = 0; y < BOX_HEIGHT; y++)
	{
		cout << "|";
		for (int x = 0; x < BOX_WIDTH; x++)
		{
			if (reducedAirspace[y][x] == " ")
			{
				cout << " ";
			}
			else
			{
				cout << reducedAirspace[y][x];
			}
		}
		cout << "|" << endl;
	}
	cout << "+" << string(BOX_WIDTH - 2, '-') << "+" << endl;
}
