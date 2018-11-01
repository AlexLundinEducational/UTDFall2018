#ifndef _GLOBALS_H_
#define _GLOBALS_H_

// all files
#include <semaphore.h>
#include <errno.h>
#define DEBUG 0 									// Debug flag. If this equals 1, debug statements will appear in program

// p4a.c
extern sem_t 		coordinatorToStudent; 			// coordinator to talk to student
extern sem_t 		tutorReady;						// set at top of tutor control loop (loop executes until ALL students are done being helped)
extern sem_t 		studentReady;					// set when student occupies a vacant chair
extern sem_t 		coordinatorToTutor;				// coordinator to talk to tutor
extern sem_t 		mutex; 							// mutual exclusion lock, to lock the following extern globals

extern int 			argNumStudents;					// command line arg total number of students
extern int 			argNumTutors;					// command line arg total number of tutors
extern int 			argNumChairs;					// command line arg total number of chairs (they all start vacant)
extern int 			argNumSeekHelp;					// command line arg number of times each student signals the coordinator before terminating

extern int 			chairsAvailable;				// number of chairs vacant and the given moment


// coordinator.c
void * 				coordinator(void * cId );

// student.c
void *				student(void * sId );
extern int 			studentsDone;					// Increments when student terminates after seeking help required number of times
extern int 			studentsWaiting; 				// Number of students waiting. 
													// Increments when a student takes a seat
													// Decrements when coordinator locks both semaphores after a tutor helps a student

// tutor.c
void *				tutor(void * tId );
extern int 			helpAccumulator; 				// Accumulator for each time a tutor assists a student. For debugging purposes only


#endif // _DEFS_H_
