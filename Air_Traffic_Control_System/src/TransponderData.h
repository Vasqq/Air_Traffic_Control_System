/*
 * TransponderData.h
 *
 *  Created on: Mar. 31, 2023
 *      Author: Liam
 */

#ifndef SRC_TRANSPONDERDATA_H_
#define SRC_TRANSPONDERDATA_H_

typedef struct
{
    int flightId;
    int positionX;
    int positionY;
    int positionZ;
    int speedX;
    int speedY;
    int speedZ;

 } sTransponderData;

 typedef struct
 {
     int code;
 } sInterrogationSignal;


#endif /* SRC_TRANSPONDERDATA_H_ */
