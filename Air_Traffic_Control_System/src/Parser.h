/*
 * Parser.h
 *
 *  Created on: Apr. 3, 2023
 *      Author: Liam
 */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "Aircraft.h"

#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#define AIRCRAFT_UPDATE_POSITION_SIGNAL_BASE 41

class Parser {
public:
    Parser(const char* AIRCRAFT_DATA_FILE);
    vector<Aircraft> getAircraftSchedule();
    int parse();
    virtual ~Parser();

private:

    const char * AIRCRAFT_DATA_FILE;
    vector<Aircraft> aircraftSchedule;
};

#endif /* SRC_PARSER_H_ */
