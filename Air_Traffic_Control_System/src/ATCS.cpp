
#include "Aircraft.h"
#include "Parser.h"
#include "PSR.h"
#include "SSR.h"
#include "ResourceManager.h"
#include "ComputerSystem.h"
#include "Console.h"

using namespace std;

int main() {

    FILE *fp;
    char filename[] = "/data/home/qnxuser/flight_data.txt";
    fp = fopen(filename, "w");
    fclose(fp);


   const char* input_file = "/data/home/qnxuser/input_flyby.txt";
   vector<Aircraft> aircraftSchedule;

   Parser parser(input_file);
   aircraftSchedule = parser.getAircraftSchedule();

   ResourceManager RM(&aircraftSchedule);
   RM.execute();




	return 0;

}
