
#include "Aircraft.h"
#include "Parser.h"
#include "PSR.h"
#include "SSR.h"
#include "ResourceManager.h"

using namespace std;

int main() {

   const char* input_file = "/data/home/qnxuser/input_flyby.txt";
   vector<Aircraft> aircraftSchedule;

   Parser parser(input_file);
   aircraftSchedule = parser.getAircraftSchedule();

   ResourceManager RM(&aircraftSchedule);
   RM.execute();


    return 0;
}
