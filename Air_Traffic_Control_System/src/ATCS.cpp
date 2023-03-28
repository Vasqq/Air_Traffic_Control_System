#include <iostream>
using namespace std;

#include "Aircraft.h"
#include "PSR.h"
#include "SSR.h"
#include "ResourceManager.h"
#include "IPC.cpp"

<<<<<<< HEAD

=======
void* server_start_routine(void*);
>>>>>>> 2a45a1ac1238570823d4779b605b170c9c10d2c6

int main() {

	Aircraft a1(10,20000,1,30,60,0,1000,1000,1000);
	Aircraft a2(11,20000,2,40,70,0,1000,1000,1000);

	vector<Aircraft> testAircraftArr;
	testAircraftArr.push_back(a1);
	testAircraftArr.push_back(a2);

	cout << "Address of testAircraftArr" << &testAircraftArr << endl;



	ResourceManager RM(testAircraftArr);
	RM.execute();


	return 0;
}
