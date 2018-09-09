//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS

#include "project1.h"


using namespace std;
void open_log();
void close_log();
void close_pid();
void signalRegister();
void signal_HUP_Handler( int signum );
void signal_INT_Handler( int signum );
void signal_TERM_Handler( int signum );


// this is the SIGHUP handler for program5
// signum is the signal received, and this function decides what to do, depending on the signal
void signal_HUP_Handler( int signum ) {
	

	// SIGHUP
	// re-read config file and store values in map
	// open log will decide to append to the log file or create a new one based on the map
	if	( signum == 1 ){
		
		// write to log and close
		printf("\nInterrupt signal SIGHUP received.");
		printf("\nClosing log.");
		close_log();
		// open log	
		open_log();
	}
   

	return;
}


// this is the SIGINT handler for program5
// signum is the signal received, and this function decides what to do, depending on the signal and verbosity level
void signal_INT_Handler( int signum ) {


   
	// terminate on SIGINT
	if	( signum == 2 ){
		// write to log
		printf("\nInterrupt signal SIGINT received.");
		printf("\nGracefully exiting program.");
		printf("\nPid file deleted.");

		// cleanup and close files
		close_pid();
		close_log();

		// terminate program  
		exit(signum);  

	}	   
	
	return;
}


// this is the SIGTERM handler for program5
// signum is the signal received, and this function decides what to do, depending on the signal and verbosity level
void signal_TERM_Handler( int signum ) {

	// terminate on SIGTERM
	if	( signum == 15 ){
		// write to log
		printf("\nInterrupt signal SIGTERM received.");
		printf("\nGracefully exiting program.");
		printf("\nPid file deleted.");
		printf("\nLog file closing.");
		// cleanup and close files
		close_pid();
		close_log();

		
		// terminate program  
		exit(signum);  

	}	   
	
	return;

}

// registers each value to the correct handler
void signalRegister(){
	
	// register signal SIGINT and signal handler  
	signal(SIGINT, signal_INT_Handler); 	
	signal(SIGTERM, signal_TERM_Handler); 	
	signal(SIGHUP, signal_HUP_Handler); 	
	
}