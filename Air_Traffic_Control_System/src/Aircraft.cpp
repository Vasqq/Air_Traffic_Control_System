/*
 * Aircraft.cpp
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 */

#include "Aircraft.h"
using namespace std;




/* -----------------------------------------------------------------------------
 * Name:        Aircraft
 * Input:       None
 * Output:      None
 * Description: This is the constructor of the Aircraft class.
 * -----------------------------------------------------------------------------
 */
Aircraft::Aircraft()
{

}


/* -----------------------------------------------------------------------------
 * Name:        ~Aircraft
 * Input:       None
 * Output:      None
 * Description: This is the destructor of the Aircraft class.
 * -----------------------------------------------------------------------------
 */
Aircraft::~Aircraft()
{
}

/* -----------------------------------------------------------------------------
 * Name:        Aircraft
 * Input:       None
 * Output:      None
 * Description: This is the constructor of the Aircraft class. This defines all
 * 				private members to be used in later functions.
 * -----------------------------------------------------------------------------
 */
Aircraft::Aircraft(int time_at_boundary,int flight_level, int flight_id, int posX, int posY, int posZ,int speedX,int speedY,int speedZ)
{
    this->time_at_boundary=time_at_boundary;
	this->flight_level=flight_level;
	this->flight_id=flight_id;
	this->posX=posX;
	this->posY=posY;
	this->posZ=posZ;
	this->speedX=speedX;
	this->speedY=speedY;
	this->speedZ=speedZ;





}



/* -----------------------------------------------------------------------------
 * Name:        updateAircraftPositionX
 * Input:       None
 * Output:      None
 * Description: This grabs the value of positionX and adds the speed to it.
 * 				Now posX will be its previous value with added speed.
 * -----------------------------------------------------------------------------
 */
void Aircraft::updatePositionX()
{
    posX += speedX;
}


/* -----------------------------------------------------------------------------
 * Name:        updateAircraftPositionY
 * Input:       None
 * Output:      None
 * Description: This grabs the value of positionY and adds the speed to it.
 * 				Now posY will be its previous value with added speed.
 * -----------------------------------------------------------------------------
 */
void Aircraft::updatePositionY()
{
    posY += speedY;
}



/* -----------------------------------------------------------------------------
 * Name:        updateAircraftPositionZ
 * Input:       None
 * Output:      None
 * Description: This grabs the value of positionZ and adds the speed to it.
 * 				Now posZ will be its previous value with added speed.
 * -----------------------------------------------------------------------------
 */
void Aircraft::updatePositionZ()
{
    posZ += speedZ;
}



/* -----------------------------------------------------------------------------
 * Name:        updateFlightLevel
 * Input:       None
 * Output:      None
 * Description: This grabs the value of the flightLevel and updates it.
 * -----------------------------------------------------------------------------
 */
void Aircraft::updateFlightLevel()
{
}



/* -----------------------------------------------------------------------------
 * Name:        updateAircraftPosition
 * Input:       None
 * Output:      None
 * Description: This calls the updatePosition functions for the X, Y and Z
 * 				coordinates.
 * -----------------------------------------------------------------------------
 */
void Aircraft::updateAircraftPosition()
{
    cout<<"Executing aircraft thread..."<<endl;

    updatePositionX();
    updatePositionY();
    updatePositionZ();
}



/* -----------------------------------------------------------------------------
 * Name:        ServiceInterrogationSignal
 * Input:       None
 * Output:      None
 * Description: This will call the IPC to check for messages.
 * -----------------------------------------------------------------------------
 */
void Aircraft::ServiceInterrogationSignal()
{


    // Create message passing channel
        int chid = ChannelCreate(0);
        if (chid == -1) {
            cerr << "Error: ChannelCreate failed." << endl;
            return;
        }

        cout << "Aircraft thread waiting for interrogation signal..." << endl;

        // Receive message
        struct {
            int code;
            int data;
        } msg;

        int rcvid = MsgReceive(chid, &msg, sizeof(msg), NULL);
        if (rcvid == -1) {
            cerr << "Error: MsgReceive failed." << endl;
            return;
        }

        cout << "Interrogation signal received from ground station. Code = " << msg.code << ", data = " << msg.data << endl;

        // Reply to message
        MsgReply(rcvid, EOK, NULL, 0);

        // Destroy message passing channel
        ChannelDestroy(chid);



}


/* -----------------------------------------------------------------------------
 * Name:        receiveInterrogationSignal
 * Input:       None
 * Output:      None
 * Description: This will receiver the message from the IPC. If IPC has an error
 * 				the code is blocked until the error is resolved.
 * -----------------------------------------------------------------------------
 */
void Aircraft::receiveInterrogationSignal()
{

    // Connect to message passing channel
        int chid = ConnectAttach(0,0,0,0,0);
        if (chid == -1) {
            cerr << "Error: ChannelConnect failed." << endl;
            return;
        }

        // Send message
        struct {
            int code;
            int data;
        } msg = { 1, 42 };

        int status = MsgSend(chid, &msg, sizeof(msg), NULL, 0);
        if (status == -1) {
            cerr << "Error: MsgSend failed." << endl;
            return;
        }

        cout << "Interrogation signal sent to aircraft. Code = " << msg.code << ", data = " << msg.data << endl;

        // Receive reply to message
        status = MsgReceive(chid, &msg, sizeof(msg), NULL);
        if (status == -1) {
            cerr << "Error: MsgReceive failed." << endl;
            return;
        }

        cout << "Reply received from aircraft." << endl;

        // Disconnect from message passing channel
        ConnectDetach(chid);

}



/* -----------------------------------------------------------------------------
 * Name:        getFlightID
 * Input:       None
 * Output:      flight_id
 * Description: This will return the newly updated flight_id.
 * -----------------------------------------------------------------------------
 */
int Aircraft::getFlightID(){

	return this->flight_id;
}


/* -----------------------------------------------------------------------------
 * Name:        getFlightLevel
 * Input:       None
 * Output:      flight_level
 * Description: This will return the newly updated flight_level.
 * -----------------------------------------------------------------------------
 */
int Aircraft::getFlightLevel(){

	return this->flight_level;
}






/* -----------------------------------------------------------------------------
 * Name:        getPosX
 * Input:       None
 * Output:      posX
 * Description: This will return the newly updated posX.
 * -----------------------------------------------------------------------------
 */
int Aircraft::getPosX(){

	return this->posX;
}




/* -----------------------------------------------------------------------------
 * Name:        getPosY
 * Input:       None
 * Output:      posY
 * Description: This will return the newly updated posY.
 * -----------------------------------------------------------------------------
 */
int Aircraft::getPosY(){

	return this->posY;
}




/* -----------------------------------------------------------------------------
 * Name:        getPosZ
 * Input:       None
 * Output:      posZ
 * Description: This will return the newly updated posZ.
 * -----------------------------------------------------------------------------
 */
int Aircraft::getPosZ(){

	return this->posZ;
}




/* -----------------------------------------------------------------------------
 * Name:        getSpeedX
 * Input:       None
 * Output:      speedX
 * Description: This will return the newly updated speedX.
 * -----------------------------------------------------------------------------
 */
int Aircraft::getSpeedX(){

	return this->speedX;
}


/* -----------------------------------------------------------------------------
 * Name:        getSpeedY
 * Input:       None
 * Output:      speedY
 * Description: This will return the newly updated speedY.
 * -----------------------------------------------------------------------------
 */
int Aircraft::getSpeedY(){

	return this->speedY;
}


/* -----------------------------------------------------------------------------
 * Name:        getSpeedZ
 * Input:       None
 * Output:      speedZ
 * Description: This will return the newly updated speedZ.
 * -----------------------------------------------------------------------------
 */
int Aircraft::getSpeedZ(){

	return this->speedZ;
}










/* -----------------------------------------------------------------------------
 * Name:        collectTransponderData
 * Input:       None
 * Output:      0
 * Description: This will collect all Transponder Data and return 0 when
 * 				completed.
 * -----------------------------------------------------------------------------
 */
char* Aircraft::collectTransponderData()
{
	return 0;
}



/* -----------------------------------------------------------------------------
 * Name:        sendTransponderData
 * Input:       None
 * Output:      None
 * Description: This will send a vector of transponder data to be sent to the
 * 				system.
 * -----------------------------------------------------------------------------
 */
void Aircraft::sendTransponderData(char transponderData[])
{
}

int Aircraft::MsgReceive(int chid, void *msg, size_t bytes, struct _msg_info *info) {
    return ::MsgReceive(chid, msg, bytes, info);
}

int Aircraft::MsgReply(int rcvid, long status,const void* msg, size_t bytes ){
    return ::MsgReply(rcvid,status,msg, bytes);
}
