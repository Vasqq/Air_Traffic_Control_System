/*
 * AircraftPeriodicTimer.h
 *
 *  Created on: Apr. 7, 2023
 *      Author: Liam
 */

#ifndef SRC_AIRCRAFTPERIODICTIMER_H_
#define SRC_AIRCRAFTPERIODICTIMER_H_

#include <iostream>
#include <time.h>
#include <signal.h>
#include <sys/siginfo.h>

#include "Aircraft.h"

class AircraftPeriodicTimer {
public:
    AircraftPeriodicTimer();
    AircraftPeriodicTimer(Aircraft* aircraft);
    virtual ~AircraftPeriodicTimer();

    void startTimer(const timespec& period);

private:

    static void   fwdUpdateAircraftPosition(sigval aircraft);
    static void   stopTimer(timer_t timerID);

    timer_t     timerID_;
    sigevent    signalEvent_;
    itimerspec  timerInterval_;
    Aircraft*   aircraft;
};

#endif /* SRC_AIRCRAFTPERIODICTIMER_H_ */
