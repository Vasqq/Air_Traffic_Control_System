/*
 * Aircraft.cpp
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 */

#include "Aircraft.h"
int INTERROGATION_REPLY = 2;
int INTERROGATION_SIGNAL=1;
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


/*

           struct {
               int code;

           } msg;


           // Wait for a message on the channel

               if (chid == -1) {
                   perror("Invalid channel ID in ServiceInterrogationSignal");
                   exit(EXIT_FAILURE);
               }
          int rc = MsgReceive(coid, &msg, sizeof(msg), NULL);

           if (rc == -1) {
               perror("Failed to receive message in ServiceInterrogationSignal");
               exit(EXIT_FAILURE);
           }else{cout<<"Message Received."<<endl;}

           // Process the message
           	   	   if(msg.code !=INTERROGATION_SIGNAL){
           	   		perror("Wrong Interrogation signal returned.");
           	   		exit(EXIT_FAILURE);
           	   	   }else
           	   	   {cout<<"Proper Interrogation signal: "<< INTERROGATION_SIGNAL<<" returned."<<endl;}







               // Send a reply message to the calling thread
               struct {
                   int type;
                   int status;
                   int flight_id;
                   int flight_lvl;
                   int posx;
                   int posy;
                   int posz;
                   int speedX;
                   int speedY;
                   int speedZ;
               } reply_msg;

               reply_msg.type = INTERROGATION_REPLY;
               reply_msg.status = 0;  // Set to some status value as needed
               reply_msg.flight_id= this->flight_id;
               reply_msg.flight_lvl= this->flight_level;
               reply_msg.posx= this->posX;
               reply_msg.posy= this->posY;
               reply_msg.posz= this->posZ;
               reply_msg.speedX= this->speedX;
               reply_msg.speedY= this->speedY;
               reply_msg.speedZ= this->speedZ;



               //Here we implement error checks for passed messages

                                  if (reply_msg.flight_id ==-1) {
                                      perror("Failed to retrieve flight Id");
                                      exit(EXIT_FAILURE);}


                                  if (reply_msg.flight_lvl ==-1) {
                                      perror("Failed to retrieve flight_lvl");
                                      exit(EXIT_FAILURE);}

                                  if (reply_msg.posx ==-1) {
                                      perror("Failed to retrieve posX");
                                      exit(EXIT_FAILURE);}

                                  if (reply_msg.posy ==-1) {
                                      perror("Failed to retrieve pos Y");
                                      exit(EXIT_FAILURE);}

                                  if (reply_msg.posz ==-1) {
                                      perror("Failed to retrieve pos Z");
                                      exit(EXIT_FAILURE);}

                                  if (reply_msg.speedX ==-1) {
                                      perror("Failed to retrieve speedX");
                                      exit(EXIT_FAILURE);}

                                  if (reply_msg.speedY ==-1) {
                                       perror("Failed to retrieve speedY");
                                       exit(EXIT_FAILURE);}

                                  if (reply_msg.speedZ ==-1) {
                                       perror("Failed to retrieve speedZ");
                                       exit(EXIT_FAILURE);}






               int rply = MsgReply(rc, EOK, &reply_msg, sizeof(reply_msg));
               if (rply == -1) {
                   perror("Failed to send reply message in ServiceInterrogationSignal");
                   exit(EXIT_FAILURE);
               }else{cout<<"All Test Passed"<<endl;}


*/



    };


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

int Aircraft::connectToChannel(int chid) {

    int coid = ConnectAttach(0,0,chid, _NTO_SIDE_CHANNEL, 0);
      if (coid == -1) {
         perror("Failed to connect to establish connection between SSR and Aircraft");
         ChannelDestroy(chid);
      }else
      {cout<<"Established Connection between SSR and Aircraft"<<endl;}

      return coid;
}
