/*
 * SSR.cpp
 *
 *  Created on: Mar. 11, 2023
 *      Author: Liam
 *
 *      FILE DESCRIPTION GOES HERE
 */

#include "SSR.h"
#include "Aircraft.h"
#include <iostream>
#include <array>
#include <sys/neutrino.h>


using namespace std;

/* -----------------------------------------------------------------------------
 * Name:        SSR
 * Input:       vector<Aircraft> illuminatedObjects
 * Output:      None
 * Description:  This is a constructor of the SSR class that  initializes the
 *               illuminatedObjects vector.
 * -----------------------------------------------------------------------------
 */
SSR::SSR(vector<Aircraft>illuminatedObjects) {
	// TODO Auto-generated constructor stub
	this->illuminatedObjects=illuminatedObjects;




};




/* -----------------------------------------------------------------------------
 * Name:        ~SSR
 * Input:       None
 * Output:      None
 * Description: Destructor for the SSR class.
 * -----------------------------------------------------------------------------
 */
SSR::~SSR() {


};





/* -----------------------------------------------------------------------------
 * Name:        interrogateAircraft
 * Input:       Aircraft targetAircraft
 * Output:      Aircraft targetAircraft
 * Description: This method will request the aircraft thread for transponder
 *              data
 * -----------------------------------------------------------------------------
 */
void SSR::interrogateAircraft(Aircraft targetAircraft){

	//implement message passing for thread
    // Send interrogation signal to the Aircraft thread


        // Create message passing channel

                int chid = ChannelCreate(0);
                if (chid == -1) {
                    cerr << "Error: ChannelCreate failed." << endl;
                    return;
                }


                cout << "Aircraft thread waiting for Interrogation signal..." << endl;

                // Receive message
                struct {
                    int code;
                    int flight_id;
                    int flight_lvl;
                    int posx;
                    int posy;
                    int posz;
                    int speedX,speedY,speedZ;

                } msg;
                //we are requesting the following from Aircraft
                msg.code = INTERROGATION_SIGNAL;


                // Send the message to the Aircraft thread

                int rc = MsgSend(chid, &msg, sizeof(msg), NULL, 0);

                if (rc == -1) {
                    perror("Failed to send message to Aircraft");
                    exit(EXIT_FAILURE);
                }

                //after msg is sent, we pass channel ID to function to run it
                targetAircraft.ServiceInterrogationSignal(chid);
                //if we dont send the channel id, we cannot receive and send a reply
                //the only other alternative is to do a get and set but that means
                //creating a private member called chid in the Aircraft class

                // Wait for a reply message from the Aircraft thread
                struct {
                    int type;
                    int status;
                } reply_msg;

                rc = MsgReceive(chid, &reply_msg, sizeof(reply_msg), NULL);
                if (rc == -1) {
                    perror("Failed to receive reply message from Aircraft");
                    exit(EXIT_FAILURE);
                }



                // Process the reply message
                if (reply_msg.type == INTERROGATION_REPLY) {
                    int status_data = reply_msg.status;
                    cout<<"Need to integrate this but it works"<<endl;
                    // Do something with the status data...//HERE IS WHERE WE RUN RECEIVETRANSPONDERDATA
                } else {
                    cerr << "Error: Received unexpected message type from Aircraft." << endl;
                }

                	// Close the message passing channel
                    ChannelDestroy(chid);
};

/* -----------------------------------------------------------------------------
 * Name:        receiveTransponderData
 * Input:       Aircraft targetAircraft
 * Output:      Aircraft targetAircraft
 * Description: This method will receive transponder data between the Aircraft
 *              thread and SSR.
 * -----------------------------------------------------------------------------
 */
void SSR::receiveTransponderData(Aircraft targetAircraft){

    // Receive message from the aircraft thread containing transponder data

    //targetAircraft.receiveInterrogationSignal();

    transponderData TD;

    //targetAircraft.ServiceInterrogationSignal();

    TD.flightId=targetAircraft.getFlightID();
    TD.flightLevel= targetAircraft.getFlightLevel();

    //Aircraft Positions X,Y,Z
    TD.positionX=targetAircraft.getPosX();
    TD.positionY=targetAircraft.getPosY();
    TD.positionZ=targetAircraft.getPosZ();

    //Aircraft Speeds X,Y,Z
    TD.speedX=targetAircraft.getSpeedX();
    TD.speedY=targetAircraft.getSpeedY();
    TD.speedZ=targetAircraft.getSpeedZ();


    transponderDataList.push_back(TD);


};

/* -----------------------------------------------------------------------------
 * Name:        interrogate
 * Input:       vector<Aircraft> illuminatedObjects
 * Output:      transponderDataList
 * Description: This method will interrogate each Aircraft and Illuminated Obj
 *              vector and return the transponder Data for each Aircraft.
 * -----------------------------------------------------------------------------
 */

void SSR::interrogate(vector<Aircraft> illuminatedObjects)
{

    transponderData receivedReply;

for(Aircraft& illuminatedObject: illuminatedObjects){
    //interrogate the aircraft and receive transponder data
    interrogateAircraft(illuminatedObject);
    receiveTransponderData(illuminatedObject);
}

}

/* -----------------------------------------------------------------------------
 * Name:        sendTransponderData
 * Input:       None
 * Output:      transponderDataList
 * Description: This method will return the transponderDataList vector that was
 *              filled with the push_back values of the transponderData struct
 *              from receiveTransponderData().
 * -----------------------------------------------------------------------------
 */
vector<transponderData> SSR::sendTransponderData()
{
    //send transponderDataList to computer system
    return transponderDataList;
}

/* -----------------------------------------------------------------------------
 * Name:        execute
 * Input:       None
 * Output:      None
 * Description: This method will run interrogate and senTransponderData,
 *              executing all functions within the SSR.
 * -----------------------------------------------------------------------------
 */
 void SSR::execute(){


     interrogate(illuminatedObjects);
     sendTransponderData();
 }

 long SSR::MsgSend(int chid,const void* smsg,size_t sbytes,void* rmsg,size_t rbytes ) {
     return (chid, smsg, sbytes, rmsg,rbytes);
 }

 int SSR::ConnectAttach(uint32_t nd,pid_t pid,int chid,unsigned index,int flags ){
     return (nd,pid,chid,index,flags);
 }

