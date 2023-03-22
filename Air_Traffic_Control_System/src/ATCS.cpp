#include <iostream>
using namespace std;

#include "Aircraft.h"
#include "PSR.h"
#include "SSR.h"
#include "ResourceManager.h"

int main() {
	cout << "Hello World!!!" << endl; // prints Hello World!!!

	Aircraft a1(10,20000,1,30,60,0,1000,1000,1000);
	Aircraft a2(11,20000,2,40,70,0,1000,1000,1000);

	vector<Aircraft> testAircraftArr;
	testAircraftArr.push_back(a1);
	testAircraftArr.push_back(a2);


	ResourceManager RM(testAircraftArr);
	RM.createAircraftThreads();


	PSR psr(testAircraftArr);
	vector<Aircraft> illuminatedObjects;


	illuminatedObjects=psr.execute();

	SSR ssr(illuminatedObjects);
	ssr.execute();




	return 0;
}
