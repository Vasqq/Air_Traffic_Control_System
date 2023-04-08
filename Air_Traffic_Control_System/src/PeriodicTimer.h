/*
 * PeriodicTimer.h
 *
 *  Created on: Apr. 7, 2023
 *      Author: Liam
 */

#ifndef SRC_PERIODICTIMER_H_
#define SRC_PERIODICTIMER_H_

#define INVALID_SIGNAL -1

#include <iostream>
#include <time.h>
#include <signal.h>
#include <sys/siginfo.h>

struct TimerSignal
{
    int signalNumber{0};
    sigset_t alarmSignalSet{};
};

class PeriodicTimer {
public:
    PeriodicTimer();
    virtual ~PeriodicTimer();

    bool setupTimer(const int sigNo);
    bool startTimer(const timespec& period);
    void waitPeriod();
    int overrunPeriods();
    bool setSignal(const int sigNo);

private:

timer_t timerID_{};
bool isSetup_{false};
bool isStarted_{false};
timespec period_{0,0};
TimerSignal timerSignal_{};
sigevent signalEvent_{};
};

#endif /* SRC_PERIODICTIMER_H_ */
