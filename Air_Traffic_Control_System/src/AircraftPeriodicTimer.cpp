/*
 * AircraftPeriodicTimer.cpp
 *
 *  Created on: Apr. 7, 2023
 *      Author: Liam
 */

#include "AircraftPeriodicTimer.h"

AircraftPeriodicTimer::~AircraftPeriodicTimer() {
    // TODO Auto-generated destructor stub
}

AircraftPeriodicTimer::AircraftPeriodicTimer(Aircraft* aircraft) {

    this->aircraft = aircraft;
    SIGEV_THREAD_INIT(&signalEvent_, &fwdUpdateAircraftPosition, aircraft, 0);
    this->timerID_ = -1;
}


void AircraftPeriodicTimer::startTimer(const timespec& period) {

    // Create the timer
    int result = timer_create(CLOCK_REALTIME, &signalEvent_, &timerID_);
    aircraft->setTimerID(timerID_);

    // Make the timer periodic
    timerInterval_.it_interval = period;
    timerInterval_.it_value = period;
    // Start the timer, flag 0 means relative time
    result = timer_settime(timerID_, 0, &timerInterval_, nullptr);


}
/* -----------------------------------------------------------------------------
 * Name:        fwdExecutionToAircraft
 * Input:       void pointer to an Aircraft object
 * Output:      void pointer
 * Description: This function forwards execution to an Aircraft object to update
 *              its position.
 * -----------------------------------------------------------------------------
 */
void AircraftPeriodicTimer::fwdUpdateAircraftPosition(sigval signalValue) {

    Aircraft* aircraft = static_cast<Aircraft*>(signalValue.sival_ptr);
    aircraft->updateAircraftPosition();

    printf("Aircraft ID: %d with position X:%d, Y:%d, Z:%d\n",aircraft->getFlightID(),aircraft->getPosX(), aircraft->getPosY(), aircraft->getPosZ());

    //Check if aircraft is out of bounds, if it is then stop the timer
    //stopTimer(aircraft->getTimerID());
}

void AircraftPeriodicTimer::stopTimer(timer_t timerID) {

    timer_delete(timerID);
}

AircraftPeriodicTimer::AircraftPeriodicTimer() {
}
