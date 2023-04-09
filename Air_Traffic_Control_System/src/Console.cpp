/*
 * Console.cpp
 *
 *  Created on: Apr 8, 2023
 *      Author: Argi
 */

#include "Console.h"

Console::Console() {
    // TODO Auto-generated constructor stub

}
Console::~Console() {
    // TODO Auto-generated destructor stub
}




void* Console::Operator_Commands(void *parameter) {
    int command;
       //Operator Commands
       cout << "--------------<Operator Console>--------------"
               << "Choose an option by entering one of the numbers below:"<< endl
               << "1. Send a command to an aircraft to change altitude"<< endl
               << "2. Send a command to an aircraft to change X longitude"<< endl
               << "3. Send a command to an aircraft to change Y latitude"<< endl
               //<< "4. Send a command to an aircraft to change altitude speed"<< endl
               //<< "5. Send a command to an aircraft to change X longitude speed"<< endl
              // << "6. Send a command to an aircraft to change Y latitude speed"<< endl
               << "0. Exit the program"<< endl;
       cout << "--------------<Operator Console>--------------"<<endl;
       cin >> command;

       string message = "";
       string temp = "";

       switch(command){
       case 0:
           break;
       case 1:
           message = "1,";
           cout <<"Please enter the ID of the aircraft you wish to communicate to" << endl;
           cin>>temp;
           cout<< temp<<endl;
           static_cast<Aircraft*>(parameter)->getFlightID(); //i want to ask for a specific aircraft number
           //then I want to return its current position Z using getPosZ()
           static_cast<Aircraft*>(parameter)->getPosZ();
           //then I want to update the aircrafts posZ using another cin
           cout <<"Please enter the altitude you wish to set the aircraft to" << endl;
           cin>>temp;
           cout<< temp<<endl;
           static_cast<Aircraft*>(parameter)->updatePositionZ();

           break;
       case 2:
           message = "2,";
           cout <<"Please enter the ID of the aircraft you wish to communicate to" << endl;
           cin>>temp;
           cout<< temp<<endl;
           static_cast<Aircraft*>(parameter)->getFlightID(); //i want to ask for a specific aircraft number

           static_cast<Aircraft*>(parameter)->getPosX();

           cout <<"Please enter the longitude X coordinate you wish to set the aircraft to" << endl;
           cin>>temp;
           cout<< temp<<endl;
           static_cast<Aircraft*>(parameter)->updatePositionX();
           break;

       case 3:
           message = "3,";
           cout <<"Please enter the ID of the aircraft you wish to communicate to" << endl;
           cin>>temp;
           cout<< temp<<endl;
           static_cast<Aircraft*>(parameter)->getFlightID(); //i want to ask for a specific aircraft number

           static_cast<Aircraft*>(parameter)->getPosY();

           cout <<"Please enter the latitude Y coordinate you wish to set the aircraft to" << endl;
           cin>>temp;
           cout<< temp<<endl;
           static_cast<Aircraft*>(parameter)->updatePositionY();
           break;
//       case 4:
//           message = "4,";
//           cout <<"Please enter the ID of the aircraft you wish to communicate to" << endl;
//           cin>>temp;
//           cout<< temp<<endl;
//           static_cast<Aircraft*>(parameter)->getFlightID(); //i want to ask for a specific aircraft number
//
//           static_cast<Aircraft*>(parameter)->getSpeedZ();
//
//           cout <<"Please enter the altitude Speed you wish to set the aircraft to" << endl;
//           cin>>temp;
//           cout<< temp<<endl;
//           static_cast<Aircraft*>(parameter)->;
//           break;
//       case 5:
//            message = "5,";
//             cout <<"Please enter the ID of the aircraft you wish to communicate to" << endl;
//            cin>>temp;
//            cout<< temp<<endl;
//            static_cast<Aircraft*>(parameter)->getFlightID(); //i want to ask for a specific aircraft number
//
//            static_cast<Aircraft*>(parameter)->getSpeedX();
//
//            cout <<"Please enter the X longitude Speed you wish to set the aircraft to" << endl;
//            cin>>temp;
//            cout<< temp<<endl;
//            static_cast<Aircraft*>(parameter)->updateSpeedX();
//            break;
//       case 6:
//            message = "6,";
//            cout <<"Please enter the ID of the aircraft you wish to communicate to" << endl;
//            cin>>temp;
//            cout<< temp<<endl;
//            static_cast<Aircraft*>(parameter)->getFlightID(); //i want to ask for a specific aircraft number
//
//            static_cast<Aircraft*>(parameter)->getSpeedY();
//
//            cout <<"Please enter the Y latitude  Speed you wish to set the aircraft to" << endl;
//            cin>>temp;
//            cout<< temp<<endl;
//            static_cast<Aircraft*>(parameter)->updateSpeedY();
//            break;
       default:
           cout<<"Invalid command.";
       }
}

