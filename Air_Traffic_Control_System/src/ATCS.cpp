#include <iostream>
#include "Aircraft.h"
#include "PSR.h"
#include "SSR.h"
#include "ResourceManager.h"

using namespace std;

int main() {

	Aircraft a1(10,20000,1,30,60,0,1000,1000,1000);
	Aircraft a2(11,20000,2,40,70,0,1000,1000,1000);

	vector<Aircraft> testAircraftArr;
	testAircraftArr.push_back(a1);
	testAircraftArr.push_back(a2);

	cout << "Aircraft a1: " << &testAircraftArr[0] << endl;
    cout << "Aircraft a2: " << &testAircraftArr[1] << endl;

	cout << "Address of testAircraftArr" << &testAircraftArr << endl;



	ResourceManager RM(&testAircraftArr);
	RM.execute();


	return 0;
}
