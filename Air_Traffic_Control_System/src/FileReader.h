/*
 * FileReader.h
 *
 *  Reads input file
 *
 *  Created on: March 15, 2023
 *      Author: Fahim
 */

#ifndef SRC_FILEREADER_H_
#define SRC_FILEREADER_H_

#include "Types.h"

/*
takes a filename as an argument and opens the file for reading, 
extracts the information about the scheduled flights and stores them in the schedule vector
*/
class FileReader {
	std::string fileName;
	std::vector<Aircraft> schedule;

public:
	// read file
	FileReader(std::string fileName);

/*
a long integer representing a time value as an argument, iterates over the schedule vector, 
and returns a vectorof Aircraft objects representing the scheduled flights that are 
expected to enter at the specified time.
*/
	// iterate over the schedule file, returns aircraft entering at time time
	std::vector<Aircraft> getScheduledAircraftsForTime(long time);

};

#endif /* SRC_FILEREADER_H_ */
