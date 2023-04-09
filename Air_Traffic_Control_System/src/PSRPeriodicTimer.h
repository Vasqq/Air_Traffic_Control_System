/*
 * PSRPeriodicTimer.h
 *
 *  Created on: Apr. 9, 2023
 *      Author: Liam
 */
#include "PSR.h"

#ifndef SRC_PSRPERIODICTIMER_H_
#define SRC_PSRPERIODICTIMER_H_

class PSRPeriodicTimer {
public:
    PSRPeriodicTimer();
    PSRPeriodicTimer(PSR *psr);
    virtual ~PSRPeriodicTimer();

    void    startTimer(const timespec& period);
    void    stopTimer();

private:

    static void   fwdExecutionToPSR(sigval signalValue);

    timer_t     timerID_;
    sigevent    signalEvent_;
    itimerspec  timerInterval_;
    PSR*        psr;
};

#endif /* SRC_PSRPERIODICTIMER_H_ */
