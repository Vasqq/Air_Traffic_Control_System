/*
 * ComputerSystem.cpp
 *
 *  Created on: Apr 2, 2023
 *      Author: argi1
 */

#include "ComputerSystem.h"
#include "ResourceManager.h"
#include <set>

 /* -----------------------------------------------------------------------------
 * Name:		ComputerSystem
 * Input:		vector<sTransponderData>* transponderDataList
 * Output:		None
 * Description:	The constructor of the ComputerSystem class. Initializes the
 * 				transponderDataList and pushback data members and runs the runCS
 * 				method.
 * -----------------------------------------------------------------------------
 */
ComputerSystem::ComputerSystem(vector<sTransponderData> *transponderDataList)
{
    //	this->n=n;

    // option 1: receive new n through interprocess communication
    // todo:implement

    // option2: n is defined in shared memory
    // todo:implement

    // option3: operation console has a reference to the computer system object
    // todo:implement

    // option4: operator console requests setting n through the resource manager

    this->transponderDataList = transponderDataList;
    pushback = vector<vector<bool>>();
    runCS();
}

/* -----------------------------------------------------------------------------
* Name:			SetN
* Input:		int new_n
* Output:		None
* Description:	Setter method for n.
* -----------------------------------------------------------------------------
*/
void ComputerSystem::SetN(int new_n)
{
    this->n = new_n;
}

/* -----------------------------------------------------------------------------
* Name:			ComputeAirTrafficFlow
* Input:		None
* Output:		None
* Description:	Method that receives illuminated objects, forwards them to data
* 				display, and checks safety violations.
* -----------------------------------------------------------------------------
*/
void ComputerSystem::ComputeAirTrafficFlow()
{
    std::vector<sTransponderData> illuminatedObjects = receiveIlluminatedObjects();
    forwardIlluminatedObjectsToDataDisplay();
}



/* -----------------------------------------------------------------------------
* Name:			receiveIlluminatedObjects
* Input:		None
* Output:		vector<sTransponderData>
* Description:	Method that generates simulated transponder data for n
* 				aircrafts and returns a vector of sTransponderData objects.
* -----------------------------------------------------------------------------
*/
std::vector<sTransponderData> ComputerSystem::receiveIlluminatedObjects()
{
    std::vector<sTransponderData> transponderDataList;

    // Generate simulated transponder data for n aircrafts
    for (int i = 0; i < n; i++)
    {
        sTransponderData td;
        // todo

        transponderDataList.push_back(td);
    }

    return transponderDataList;
}

/* -----------------------------------------------------------------------------
* Name:			~ComputerSystem
* Input:		None
* Output:		None
* Description:	Destructor for ComputerSystem class.
* -----------------------------------------------------------------------------
*/
ComputerSystem::~ComputerSystem()
{
}

/* -----------------------------------------------------------------------------
* Name:			forwardIlluminatedObjectsToDataDisplay
* Input:		None
* Output:		None
* Description:	Method that creates a DataDisplay object and passes the
* 				transponderDataList and closeAircrafts vector to it.
* -----------------------------------------------------------------------------
*/
void ComputerSystem::forwardIlluminatedObjectsToDataDisplay()
{

    DataDisplay d(transponderDataList, &closeAircrafts);
}

/* -----------------------------------------------------------------------------
* Name:			checkAircraftSeperationConstraints
* Input:		None
* Output:		None
* Description:	Method that checks for safety violations by looping through
* 				the transponderDataList and adding flight IDs to the
* 				closeAircrafts vector if they are too close.
* -----------------------------------------------------------------------------
*/
void ComputerSystem::checkAircraftSeperationConstraints()
{

    // this dynamically resizes the 2d boolean vector based on the number of structs in the list.
    int max_flight_id = 0;
    for (sTransponderData &td : *transponderDataList)
    {
        if (td.flightId > max_flight_id)
        {
            max_flight_id = td.flightId;
        }
    }
    pushback.resize(max_flight_id + 1, vector<bool>(max_flight_id + 1, false));

    for (sTransponderData &td1 : *transponderDataList)
    {

        for (sTransponderData &td2 : *transponderDataList)
        {

            if (td1.flightId != td2.flightId)
            {

                int distance = sqrt(pow((td1.positionX - td2.positionX), 2) +
                                    pow((td1.positionY - td2.positionY), 2));
                int altitude = abs(td1.positionZ - td2.positionZ);

                if (distance <= 3000 && altitude <= 1000)
                {
                    collisionDetection = true;

                    if (!pushback[td1.flightId][td2.flightId] && !pushback[td2.flightId][td1.flightId] && collisionDetection == true)
                    { // stops looping the pushbacks more than once
                        closeAircrafts.push_back(td1.flightId);
                        closeAircrafts.push_back(td2.flightId);

                        pushback[td1.flightId][td2.flightId] = true; // Mark this pair of flight IDs as pushed back
                        pushback[td2.flightId][td1.flightId] = true; // Mark this pair of flight IDs as pushed back
                        // this above 2d boolean is done so that you dont have the reverse order of aircrafts being checked as well.
                        collisionDetection = false; // reset collisionDetection back to false to check again
                    }
                }
            }
        }
    }

    notifySafetyViolation();
}


/* -----------------------------------------------------------------------------
* Name:			notifySafetyViolation
* Input:		None
* Output:		None
* Description:	Method that removes duplicates from the closeAircrafts vector
* 				and sorts it in numerical order before looping through it to
* 				print safety violation messages.
* -----------------------------------------------------------------------------
*/
void ComputerSystem::notifySafetyViolation()
{

    // Remove duplicates from closeAircrafts and sort them in numerical order
    sort(closeAircrafts.begin(), closeAircrafts.end());
    closeAircrafts.erase(unique(closeAircrafts.begin(), closeAircrafts.end()), closeAircrafts.end());

    // Loop through each unique flight ID
    cout << endl;
    for (int flightId : closeAircrafts)
    {
        cout << "Aircraft " << flightId << " is in close proximity to ";

        // Loop through the closeAircrafts vector to find all the aircrafts close to the current flight ID
        bool firstAircraft = true;
        for (int closeFlightId : closeAircrafts)
        {
            if (closeFlightId != flightId)
            {
                if (!firstAircraft)
                {
                    cout << ", ";
                }
                cout << "Aircraft: " << closeFlightId;
                firstAircraft = false;
            }
        }
        cout << endl;
    }
}


/* -----------------------------------------------------------------------------
* Name:			runCS
* Input:		None
* Output:		None
* Description:	Method that calls the checkAircraftSeperationConstraints() and
* 				forwardIlluminatedObjectsToDataDisplay() methods.
* -----------------------------------------------------------------------------
*/
void ComputerSystem::runCS()
{

    checkAircraftSeperationConstraints();
    forwardIlluminatedObjectsToDataDisplay();
    if (textfileCounter==6){
        sendtoFile();
        textfileCounter=0;
    }

}



/* -----------------------------------------------------------------------------
* Name:			writeToFile
* Input:		const string& filename, const string& data
* Output:		None
* Description:	Method that writes transponder data to a file.
* -----------------------------------------------------------------------------
*/
void ComputerSystem::writeToFile(const string &filename, const string &data) {

        ofstream outfile;
      outfile.open(filename, std::ios_base::app);

      if (!outfile.good()) {
        throw std::runtime_error("Error opening file: " + filename);
      }

      outfile << data << std::endl;
      outfile.close();
    }



/* -----------------------------------------------------------------------------
* Name:			sendtoFile
* Input:		None
* Output:		flight_data.txt
* Description:	Method that generates a string of flight data and calls the
* 				writeToFile() method to write it to a file.
* -----------------------------------------------------------------------------
*/
void ComputerSystem::sendtoFile() {

    string data;
      data += "-----------------------------<Flight Data>---------------------------\n";
      for (sTransponderData &td : *transponderDataList)
      {
        data += "------------------------------------------------------------"
                "---------\n";
        data += "Aircraft Flight ID: " + to_string(td.flightId) + "\n";
        data += "Position (x, y, z): (" + to_string(td.positionX) + ", " +to_string(td.positionY) + ", " +to_string(td.positionZ) + ")\n";
        data += "Speed (x, y, z): (" + to_string(td.speedX) + ", " + to_string(td.speedY) + ", " + to_string(td.speedZ) + ")\n";
        data += "------------------------------------------------------------"
                "---------\n";
      }
      data += "-----------------------------<Flight Data>---------------------------\n";

      writeToFile("/data/home/qnxuser/flight_data.txt", data);
}


/* -----------------------------------------------------------------------------
* Name:			ComputerSystem
* Input:		int flight_id
* Output:		None
* Description:	Initializes a new instance of the ComputerSystem class with
* 				the specified flight_id, and calls forwardIDtoCommSystem to
* 				forward the flight ID to the communication system.
* -----------------------------------------------------------------------------
*/
ComputerSystem::ComputerSystem(int flight_id) {
   this->flight_id=flight_id;
   forwardIDtoCommSystem(flight_id);
}




/* -----------------------------------------------------------------------------
* Name:			forwardIDtoCommSystem
* Input:		int flight_id
* Output:
* Description:	Gets the existing flight ID from an Aircraft object, compares
* 				it to the specified flight_id, and forwards it to the
* 				CommunicationSystem class using fwdConsoleRequest() if it
* 				matches.
* -----------------------------------------------------------------------------
*/
void ComputerSystem::forwardIDtoCommSystem(int flight_id) {
    Aircraft flight;
        int existingFlightID = flight.getFlightID();
        if (existingFlightID == flight_id) {
            this->flight_id = existingFlightID;
            // Forward flight id to communication system
            CommunicationSystem comm;
            comm.fwdConsoleRequest(flight);
        } else {
            printf("Error: Flight id %d does not exist.\n", flight_id);
        }
    }
