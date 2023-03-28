/*
 * Timer.h
 *
 *  Created on: Mar 28, 2023
 *      Author: Argi
 */


#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

<<<<<<< HEAD

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
=======
#include <stdio.h>
#include <iostream>
#include <time.h>

>>>>>>> 2a45a1ac1238570823d4779b605b170c9c10d2c6
#include <sync.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/syspage.h>
#include <inttypes.h>
#include <stdint.h>

class Timer {
<<<<<<< HEAD
    int channel_id;
    int connection_id;

    struct sigevent sig_event;
    struct itimerspec timer_spec;
    timer_t timer_id;

    char msg_buffer[100];

    uint64_t cycles_per_sec;
    uint64_t tick_cycles, tock_cycles;
public:
    Timer(uint32_t,uint32_t);

    void setTimerSpec(uint32_t,uint32_t);
    void waitTimer();
    void startTimer();
    void tick();
    double tock();
    virtual ~Timer();
=======
	timer_t timer_id;
	struct sigevent sig_event;
	sigset_t sig_set;
	struct itimerspec timer_spec;
	struct timespec tv;

public:
	Timer(uint32_t,uint32_t,uint32_t,uint32_t);
	~Timer();
	void set_timer(uint32_t,uint32_t,uint32_t,uint32_t);
	void wait_next_activation();


>>>>>>> 2a45a1ac1238570823d4779b605b170c9c10d2c6
};



<<<<<<< HEAD


=======
>>>>>>> 2a45a1ac1238570823d4779b605b170c9c10d2c6
#endif /* SRC_TIMER_H_ */
