/*
 * ResourceManager.cpp
 *
 *  Created on: Mar 14, 2023
 *      Author: Argi
 */

#include "ResourceManager.h"


 pthread_mutex_t psr_mutex = PTHREAD_MUTEX_INITIALIZER;
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
    cout<<"------------------------------------------"<<endl;

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

    err_no = pthread_create(&PSR_thread_id,
                            NULL,
                            &fwdExecutionToPSR,
                            psr);
    if (err_no != 0) {
        cout << "ERROR when creating PSR thread: " << err_no << endl;
    } else {
        cout <<endl<<"PSR with thread ID: " << PSR_thread_id << " created" << endl;
    }

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

    printf("#################################\n");
    printf("### Creating Aircraft threads ###\n");
    printf("#################################\n\n");



    for (Aircraft &nextAircraft : *AircraftSchedule) {

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
    cout<<"------------------------------------------"<<endl;
    initializeDataDisplay();
    initializeComputerSystem();
    initializeCommunicationSystem();
    initializeOperatorConsole();
    initializeRadar();

}

/* -----------------------------------------------------------------------------
 * Name:        fwdExecutionToPSR
 * Input:       void pointer to a PSR object
 * Output:      void pointer
 * Description: This function forwards execution to a PSR object to execute.
 * -----------------------------------------------------------------------------
 */
void* ResourceManager::fwdExecutionToPSR(void *psr) {

	while (true) {
	        // Lock the mutex to prevent other threads from executing
	        pthread_mutex_lock(&psr_mutex);

	        // Execute the PSR thread
	        static_cast<PSR*>(psr)->execute();

//	        // Unlock the mutex to allow other threads to execute
//	        pthread_mutex_unlock(&psr_mutex);
//
//	        // Sleep for 5 seconds before executing again
//	        sleep(5);
	    }
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

	// Execute the ATCS simulation
	cout << "All systems ready, press 'R' to run the simulation." << endl;
	char input;
	while (cin >> input) {
	    if (input == 'R') {
	        configureSimulation();
	        //runSimulation();
	        //break; // exit the loop if simulation is run
	    } else {
	        cout << "Invalid input, please press 'R' to run the simulation." << endl;
	    }
	}

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
            printf("Error: ChannelCreate failed. Error ID: %s\n",strerror(errno));
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
    pthread_attr_t attr;
    pthread_attr_init( &attr );
    pthread_attr_setschedpolicy(&attr, SCHED_RR);

    AircraftPeriodicTimer aircraftTimer(&nextAircraft);
    aircraftTimer.startTimer(AIRCRAFT_UPDATE_POSITION_PERIOD);

    err_no = pthread_create(&thread_id,
            &attr, &fwdServiceInterrogationSignal, &nextAircraft);
       if (err_no != 0) {
           printf("ERROR when creating thread:\n");
       } else {
           printf("\tfwdServiceInterrogationSignal thread created with ID: %d\n", thread_id);
       }

}
