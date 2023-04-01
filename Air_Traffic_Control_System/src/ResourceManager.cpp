/*
 * ResourceManager.cpp
 *
 *  Created on: Mar 14, 2023
 *      Author: Argi
 */

#include "ResourceManager.h"


/* -----------------------------------------------------------------------------
 * Name:        ResourceManager()
 * Input:       None
 * Output:      None
 * Description: This is the constructor of the ResourceManager class, which
 *              initializes the object.
 * -----------------------------------------------------------------------------
 */
ResourceManager::ResourceManager() {

}

/* -----------------------------------------------------------------------------
 * Name:        ResourceManager
 * Input:       vector of Aircraft objects
 * Output:      None
 * Description: This is a constructor of the ResourceManager class that
 *              initializes the AircraftSchedule vector.
 * -----------------------------------------------------------------------------
 */
ResourceManager::ResourceManager(vector<Aircraft> *AircraftArr) {

    this->AircraftSchedule = AircraftArr;

    cout << "Aircraft schedule: " << AircraftSchedule << endl;

    cout << "Aircraft a1: " << &AircraftSchedule[0] << endl;
    cout << "Aircraft a2: " << &AircraftSchedule[1] << endl;

}

/* -----------------------------------------------------------------------------
 * Name:        ~ResourceManager
 * Input:       None
 * Output:      None
 * Description: Destructor for the ResourceManager class.
 * -----------------------------------------------------------------------------
 */
ResourceManager::~ResourceManager() {
    // TODO Auto-generated destructor stub
}





/* -----------------------------------------------------------------------------
 * Name:        initializeDataDisplay
 * Input:       None
 * Output:      None
 * Description: This function initializes the Data Display subsystem.
 * -----------------------------------------------------------------------------
 */
void ResourceManager::initializeDataDisplay() {

    cout << "Initializing Data Display..." << endl;
}

/* -----------------------------------------------------------------------------
 * Name:        initializeComputerSystem
 * Input:       None
 * Output:      None
 * Description: This function initializes the Computer System subsystem.
 * -----------------------------------------------------------------------------
 */
void ResourceManager::initializeComputerSystem() {

    cout << "Initializing Computer System..." << endl;
}

/* -----------------------------------------------------------------------------
 * Name:        initializeCommunicationSystem
 * Input:       None
 * Output:      None
 * Description: This function initializes the Communication System subsystem.
 * -----------------------------------------------------------------------------
 */
void ResourceManager::initializeCommunicationSystem() {

    cout << "Initializing Communication System..." << endl;
}

/* -----------------------------------------------------------------------------
 * Name:        initializeOperatorConsole
 * Input:       None
 * Output:      None
 * Description: This function initializes the Operator Console subsystem.
 * -----------------------------------------------------------------------------
 */
void ResourceManager::initializeOperatorConsole() {

    cout << "Initializing Operator Console..." << endl;
}

/* -----------------------------------------------------------------------------
 * Name:        initializeRadar
 * Input:       None
 * Output:      None
 * Description: This function initializes the Radar subsystem and calls the
 *              initializePSR() function.
 *
 * -----------------------------------------------------------------------------
 */
void ResourceManager::initializeRadar() {

    cout << "Initializing Radar..." << endl;

    initializePSR();

}

/* -----------------------------------------------------------------------------
 * Name:        initializePSR
 * Input:       None
 * Output:      None
 * Description: This function creates a dynamic instance of the PSR class and
 *              creates a new thread to execute it using the fwdExecutionToPSR()
 *              function.
 * -----------------------------------------------------------------------------
 */
void ResourceManager::initializePSR() {

    int err_no;
    pthread_t PSR_thread_id;

    // Create a dynamic instance of the PSR class
    PSR *psr = new PSR(AircraftSchedule);

	    // Set the scheduling policy and priority of the PSR thread
	    struct sched_param param;
	    param.sched_priority = 4;  // set the priority to 10
	    pthread_setschedparam(pthread_self(), SCHED_RR, &param);

	    // Create a new thread for the PSR object
	    err_no = pthread_create(&PSR_thread_id,
	                            NULL,
	                            &fwdExecutionToPSR,
	                            psr);
	    if (err_no != 0) {
	        cout << "ERROR when creating PSR thread: " << err_no << endl;
	    } else {
	        cout << " PSR with thread ID: " << PSR_thread_id << " created" << endl;
	    }
	    psrThreadID=PSR_thread_id;
	    // Set the scheduling policy and priority of the PSR thread



}

/* -----------------------------------------------------------------------------
 * Name:
 * Input:
 * Output:
 * Description:
 * -----------------------------------------------------------------------------
 */
void ResourceManager::initializeSSR() {

}
/* -----------------------------------------------------------------------------
 * Name:        createAircraftThreads
 * Input:       None
 * Output:      None
 * Description: This function creates threads for each Aircraft object in the
 *              AircraftSchedule vector by calling spawnNewAircraftThread().
 * -----------------------------------------------------------------------------
 */
void ResourceManager::createAircraftThreads() {

    cout << "Creating Aircraft threads" << endl;

    for (Aircraft &nextAircraft : *AircraftSchedule) {


        cout << &nextAircraft << endl;
        int chid = createAircraftTransponderDataChannel();
        nextAircraft.setTransponderDataChannel(chid);
        spawnNewAircraftThreads(nextAircraft);
    }
}

/* -----------------------------------------------------------------------------
 * Name:        createATCSSubsystems
 * Input:       None
 * Output:      None
 * Description: This function initializes the ATCS subsystems by calling the
 *              initialize functions for the Data Display, Computer System,
 *              Communication System, Operator Console, and Radar.
 * -----------------------------------------------------------------------------
 */
void ResourceManager::createATCSSubsystems() {

    cout << "Initializing ATCS subsystems..." << endl;
    initializeDataDisplay();
    initializeComputerSystem();
    initializeCommunicationSystem();
    initializeOperatorConsole();
    initializeRadar();
}
/* -----------------------------------------------------------------------------
 * Name:        fwdExecutionToAircraft
 * Input:       void pointer to an Aircraft object
 * Output:      void pointer
 * Description: This function forwards execution to an Aircraft object to update
 *              its position.
 * -----------------------------------------------------------------------------
 */
void* ResourceManager::fwdUpdateAircraftPosition(void *aircraft) {
    static_cast<Aircraft*>(aircraft)->updateAircraftPosition();

    return NULL;
}
/* -----------------------------------------------------------------------------
 * Name:        fwdExecutionToPSR
 * Input:       void pointer to a PSR object
 * Output:      void pointer
 * Description: This function forwards execution to a PSR object to execute.
 * -----------------------------------------------------------------------------
 */
void* ResourceManager::fwdExecutionToPSR(void *psr) {

    static_cast<PSR*>(psr)->execute();

    return NULL;
}

/* -----------------------------------------------------------------------------
 * Name:        fwdExecutionToSSR
 * Input:       void pointer to an SSR object
 * Output:      void pointer
 * Description: This function forwards execution to an SSR object.
 * -----------------------------------------------------------------------------
 */

void* ResourceManager::fwdExecutionToSSR(void *ssr) {

    static_cast<PSR*>(ssr)->execute();
    return NULL;
}
/* -----------------------------------------------------------------------------
 * Name:		execute
 * Input:		None
 * Output:		None
 * Description: This function executes the ATCS simulation by first configuring
 *              the simulation through the configureSimulation() function.
 *              then, the user is prompted to start the simulation by pressing
 *              'R' and the runSimulation() function is executed if the input
 *              is 'R'.
 * -----------------------------------------------------------------------------
 */
void ResourceManager::execute() {

    char input;

    configureSimulation();

    // Execute the ATCS simulation
    cout << "All systems ready, press 'R' to run the simulation." << endl;
    //cin >> input;
    //if (input == 'R')
        runSimulation();

}
/* -----------------------------------------------------------------------------
 * Name:		configureSimulation
 * Input: 		None
 * Output:		None
 * Description: This function is responsible for configuring the simulation by
 *              creating threads for each aircraft in the AircraftSchedule
 	 	 	 	initializing the ATCS subsystems. It calls
 	 	 	 	createAircraftThreads() and createATCSSubsystems() functions.
 * -----------------------------------------------------------------------------
 */
void ResourceManager::configureSimulation() {


    createAircraftThreads();

    createATCSSubsystems();

}

/* -----------------------------------------------------------------------------
 * Name:        runSimulation
 * Input:       None
 * Output:      None
 * Description: This function runs the simulation by printing "Begin of
 *              simulation" to the console.
 * -----------------------------------------------------------------------------
 */
void ResourceManager::runSimulation() {

    cout << "Begin of simulation" << endl;

}

int ResourceManager::createAircraftTransponderDataChannel() {

    // Create message passing channel

        int chid = ChannelCreate(0);
        if (chid == -1) {
            cout << "Error: ChannelCreate failed. Error ID: "<< strerror(errno) << endl;
            exit(EXIT_FAILURE);
        }

    return chid;
}

void* ResourceManager::fwdServiceInterrogationSignal(void *aircraft) {

    static_cast<Aircraft*>(aircraft)->ServiceInterrogationSignal();

        return NULL;
}

/* -----------------------------------------------------------------------------
 * Name:        spawnNewAircraftThread
 * Input:       reference to an Aircraft object
 * Output:      None
 * Description: This function creates a new thread for an Aircraft object passed
 *              in as an argument, using the fwdExecutionToAircraft() function
 *              to forward execution to the object. If there is an error
 *              creating the thread, an error message is printed.
 * -----------------------------------------------------------------------------
 */
void ResourceManager::spawnNewAircraftThreads(Aircraft &nextAircraft) {

    int err_no;
    pthread_t thread_id;

    err_no = pthread_create(&thread_id,
    NULL, &fwdUpdateAircraftPosition, &nextAircraft);
    if (err_no != 0) {
        cout << "ERROR when creating thread: " << err_no << endl;
    } else {
        cout << " Aircraft Update position thread created with ID: " << thread_id << endl;
    }

    err_no = pthread_create(&thread_id,
       NULL, &fwdServiceInterrogationSignal, &nextAircraft);
       if (err_no != 0) {
           cout << "ERROR when creating thread: " << err_no << endl;
       } else {
           cout << " Aircraft service interrogation signal thread created with ID: " << thread_id << endl;
       }

}


