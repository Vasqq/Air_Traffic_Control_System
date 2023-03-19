#include <iostream>
using namespace std;

#include "Aircraft.h"
#include "PSR.h"

int main() {
	cout << "Hello World!!!" << endl; // prints Hello World!!!

	Aircraft a1(10,20000,1,30,60,0,1000,1000,1000);
	Aircraft a2(11,20000,2,40,70,0,1000,1000,1000);

	vector<Aircraft> testAircraftArr;
	testAircraftArr.push_back(a1);
	testAircraftArr.push_back(a2);

	PSR psr(testAircraftArr);
	psr.execute();



	return 0;
}
