/*
 * Parser.cpp
 *
 *  Created on: Apr. 3, 2023
 *      Author: Liam
 */

#include "Parser.h"
/* -----------------------------------------------------------------------------
 * Name:        Parser
 * Input:       const char* AIRCRAFT_DATA_FILE
 * Output:      None.
 * Description: The Parser constructor which takes in the path of the aircraft
 *              data file and then begins parsing the data.
 * -----------------------------------------------------------------------------
 */
Parser::Parser(const char* AIRCRAFT_DATA_FILE) {
    // TODO Auto-generated constructor stub

    this->AIRCRAFT_DATA_FILE = AIRCRAFT_DATA_FILE;

    parse();
}
/* -----------------------------------------------------------------------------
 * Name:        parse
 * Input:       None.
 * Output:      None.
 * Description: This functions reads aircraft data from a file with a specific
 *              format,where each line represents data for an aircraft,
 *              and creates an Aircraft object for each line. Each object is
 *              added to a vector of Aircraft objects called aircraftSchedule.
 * -----------------------------------------------------------------------------
 */
int Parser::parse() {

    int flight_id, time_at_boundary, pos_x, pos_y, pos_z, speed_x, speed_y, speed_z;

    FILE *input_file = fopen(AIRCRAFT_DATA_FILE, "r");
    if (input_file == NULL) {
        printf("Failed to open input file!\n");
        return 1;
    }

    // Read each line of the input file until the end of file
        int base_timer_signal = AIRCRAFT_UPDATE_POSITION_SIGNAL_BASE;
    while (fscanf(input_file, "%d,%d,%d,%d,%d,%d,%d,%d\n", &time_at_boundary, &flight_id, &pos_x, &pos_y,&pos_z, &speed_x, &speed_y, &speed_z) == 8) {

           // Create an Aircraft object with the extracted data and add it to the aircraftSchedule vector
           Aircraft aircraft(time_at_boundary, flight_id, pos_x, pos_y, pos_z, speed_x, speed_y, speed_z, base_timer_signal++);
           aircraftSchedule.push_back(aircraft);
       }

    /* Close the file */
    fclose(input_file);

    return EXIT_SUCCESS;
}
/* -----------------------------------------------------------------------------
 * Name:        getAircraftSchedule
 * Input:       None.
 * Output:      None.
 * Description: This functions returns the aircraftSchedule vector.
 * -----------------------------------------------------------------------------
 */
vector<Aircraft> Parser::getAircraftSchedule() {

    return aircraftSchedule;
}

Parser::~Parser() {
    // TODO Auto-generated destructor stub
}

