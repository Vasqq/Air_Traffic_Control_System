/*
 * PeriodicTimer.cpp
 *
 *  Created on: Apr. 7, 2023
 *      Author: Liam
 */

#include "PeriodicTimer.h"

PeriodicTimer::PeriodicTimer() {
    // TODO Auto-generated constructor stub

}

PeriodicTimer::~PeriodicTimer() {
    // TODO Auto-generated destructor stub
}

bool PeriodicTimer::setupTimer(const int sigNo) {

    bool result{false};
        if ((isSetup_ == false) && (setSignal(sigNo) == true))
        {
            // Create a timer that will generate the configured signal
            signalEvent_.sigev_notify = SIGEV_SIGNAL;
            signalEvent_.sigev_signo = timerSignal_.signalNumber;
            signalEvent_.sigev_value.sival_ptr = reinterpret_cast<void*>(&timerID_);
            result = (timer_create(CLOCK_REALTIME, &signalEvent_, &timerID_) == 0);
            isSetup_ = result;
        }
        else
        {
            std::cout << "Timer has been already set up or invalid signal number" << std::endl;
        }

        return result;
}

bool PeriodicTimer::startTimer(const timespec& period) {

    bool result{false};
        if ((isStarted_ == false) && (isSetup_ == true))
        {
            struct itimerspec timerInterval
            {
            };
            period_ = period;
            // Make the timer periodic
            timerInterval.it_interval = period_;
            timerInterval.it_value = period_;
            // Start the timer, flag 0 means relative time
            result = (timer_settime(timerID_, 0, &timerInterval, nullptr) == 0);
            isStarted_ = result;
        }
        else
        {
            std::cout << "Timer has been already started or is not set up" << std::endl;
        }

        return result;
}

void PeriodicTimer::waitPeriod() {

    int receivedSignal{INVALID_SIGNAL};

    int returnCode = sigwait(&(timerSignal_.alarmSignalSet), &receivedSignal);


        if ( returnCode != 0)
        {
            std::cout << "Failed to wait for the next period" << std::endl;
        }
        // Compute the number of timer overrun periods
        auto overruns = overrunPeriods();
        if (overruns > 0)
        {
            std::cout << "Timer overruns " << overruns << " periods" << std::endl;
        }
}

int PeriodicTimer::overrunPeriods() {

    int overruns = timer_getoverrun(timerID_);
        if (overruns == -1)
        {
            std::cout << "Failed to compute the number of overrun periods" << std::endl;
        }

        return overruns;
}

bool PeriodicTimer::setSignal(const int sigNo)
{
    bool result{false};
    timerSignal_.signalNumber = sigNo;

    if (sigemptyset(&timerSignal_.alarmSignalSet) == 0)
    {
        result = (sigaddset(&timerSignal_.alarmSignalSet, sigNo) == 0);
    }

    return result;
}
