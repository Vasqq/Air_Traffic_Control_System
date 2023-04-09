/*
 * PSRPeriodicTimer.cpp
 *
 *  Created on: Apr. 9, 2023
 *      Author: Liam
 */

#include "PSRPeriodicTimer.h"

PSRPeriodicTimer::PSRPeriodicTimer() {
    // TODO Auto-generated constructor stub

}

PSRPeriodicTimer::PSRPeriodicTimer(PSR *psr) {

    this->psr = psr;
    SIGEV_THREAD_INIT(&signalEvent_, &fwdExecutionToPSR, psr, 0);
    this->timerID_ = -1;

}

PSRPeriodicTimer::~PSRPeriodicTimer() {
    // TODO Auto-generated destructor stub
}

void PSRPeriodicTimer::startTimer(const timespec &period) {

    // Create the timer
        int result = timer_create(CLOCK_REALTIME, &signalEvent_, &timerID_);

        // Make the timer periodic
        timerInterval_.it_interval = period;
        timerInterval_.it_value = period;
        // Start the timer, flag 0 means relative time
        result = timer_settime(timerID_, 0, &timerInterval_, nullptr);
}
/* -----------------------------------------------------------------------------
 * Name:        fwdExecutionToPSR
 * Input:       void pointer to a PSR object
 * Output:      void pointer
 * Description: This function forwards execution to a PSR object to execute.
 * -----------------------------------------------------------------------------
 */
void PSRPeriodicTimer::fwdExecutionToPSR(sigval signalValue) {

    PSR* psr = static_cast<PSR*>(signalValue.sival_ptr);
    psr->execute();
}

void PSRPeriodicTimer::stopTimer() {

    timer_delete(this->timerID_);
}
