/*
 * Timer.h
 *
 *  Created on: Mar 28, 2023
 *      Author: Argi
 */


#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

#include <stdio.h>
#include <iostream>
#include <time.h>

#include <sync.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/syspage.h>
#include <inttypes.h>
#include <stdint.h>

class Timer {
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


};



#endif /* SRC_TIMER_H_ */
