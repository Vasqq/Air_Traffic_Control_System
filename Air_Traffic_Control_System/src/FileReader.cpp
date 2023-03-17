/*
 * FileReader.cpp
 *
 *  Reads input file
 *
 *  Created on: March 15, 2023
 *      Author: Fahim
 */

#include "FileReader.h"
#include <fstream>
using namespace std;

/*
function called tokenize, which takes a string and a delimiter and returns a vector of integers 
by splitting the string on the delimiter and converting each resulting substring to an integer
*/
std::vector<int> tokenize(std::string s, std::string del = " ")
{
	std::vector<int> str;
    int start, end = -1*del.size();
    do {
        start = end + del.size();
        end = s.find(del, start);
        string val = s.substr(start, end - start);
        int v = std::stoi(val);

        str.push_back(v);
        //cout << val << endl;
    } while (end != -1);

    return str;
}

/*
takes a filename as an argument and opens the file for reading using an ifstream. 
It then reads each line of the file and uses tokenize to extract the integer values 
for the aircraft ID, time, position, and velocity. 
It creates an Aircraft object from these values and adds it to the schedule vector.
*/

FileReader::FileReader(std::string fileName) {
	 std::ifstream file1(fileName.c_str());
	 std::string line;

	 while (getline(file1, line, '\n')) {
	      LOG_DEBUG("Aircraft vals: %s\n", line.c_str());
	      std::vector<int> ints = tokenize(line, ",");

	      int id = ints[0];
	      int time = ints[1];
	      Vector position{ints[2], ints[3], ints[4]};
	      Vector velocity{ints[5], ints[6], ints[7]};

	      Aircraft aircraft = Aircraft{id, time, position, velocity};
	      aircraft.timestamp = time;
	      schedule.push_back(aircraft);
	      LOG_DEBUG("Aircraft schedule info for time %d: %s\n", aircraft.timestamp, aircraft.getAircraftInfo().c_str());

	 }

	 if (schedule.size() == 0)
		 LOG_WARN("No aircrafts scheduled\n");

	 file1.close();
}
/*
method takes a timeVal argument and returns a vector of Aircraft objects that are 
scheduled to enter at that time. It iterates over the schedule vector
and adds any Aircraft objects with a timestamp matching timeVal to the ret vector. 
*/
// iterate over the schedule file, returns aircraft entering at time time
std::vector<Aircraft> FileReader::getScheduledAircraftForTime(long timeVal) {
	std::vector<Aircraft> ret;

	for (Aircraft plane : schedule) {
		//LOG_DEBUG("Planes verifyng %d: %d\n", plane.getId(), plane.timestamp);

		if (plane.timestamp == timeVal) {
			ret.push_back(plane);
		}
	}

	//LOG_DEBUG("Planes in cycle %d: %d\n",timeVal, ret.size());

	return ret;
}
