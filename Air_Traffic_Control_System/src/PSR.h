/*
 * PSR.h
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 */

#ifndef PSR_H_
#define PSR_H_
#include "Aircraft.h"

class PSR {
public:
	PSR();

	void scan();
	void emitPulses();
	void roateRadar();
	bool receiveEchoes(int echoes[]);
	Aircraft* determineDistances(int echoes[]);

	void sendAircraftPositionsToCS(Aircraft aircraft[]);
	void sendAircraftPositionsToSSR(Aircraft aircraft[]);

	virtual ~PSR();

private:

	int range;
	int refernce_angle;
	int scans_per_minute;
	int pulses_per_degree;
	int current_angle;
	int pulse_speed;
};

#endif /* PSR_H_ */
