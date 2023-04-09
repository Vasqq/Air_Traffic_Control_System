/*
 * Console.h
 *
 *  Created on: Apr 8, 2023
 *      Author: Argi
 */

#ifndef SRC_CONSOLE_H_
#define SRC_CONSOLE_H_
#include "ComputerSystem.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <limits>

class Console {
public:
    Console();

    virtual ~Console();

    void* Operator_Commands(void* parameter);




private:
    int command;
    string message = "";
    string temp = "";
};

#endif /* SRC_CONSOLE_H_ */
