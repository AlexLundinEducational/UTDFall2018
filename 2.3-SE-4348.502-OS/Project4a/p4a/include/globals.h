#ifndef _GLOBALS_H_
#define _GLOBALS_H_

// all files
#include <semaphore.h>
#include <errno.h>
#define DEBUG 1 									// Debug flag. If this equals 1, debug statements will appear in program

// p4a.c
extern sem_t 		coordToStudent; 						// coordinator to talk to student
extern sem_t 		tutorReady;
extern sem_t 		studReady;
extern sem_t 		coordToTutor;
extern sem_t 		mutex; 
extern int 			argNumStudents;
extern int 			argNumTutors;
extern int 			argNumChairs;
extern int 			argNumSeekHelp;
extern int 			chairsAvailable;


// coordinator.c
void * 				coordinator(void * cId );

// student.c
void *				student(void * sId );
extern int 			studentsDone;
extern int 			studentsWaiting; 				// Number of students waiting. Increments when a student takes a seat and decrements ehen a student is finished asking for argNumSeekHelp

// tutor.c
void *				tutor(void * tId );
extern int 			helpAccumulator; 				// Accumulator for each time a tutor assists a student. For debugging purposes only


#endif // _DEFS_H_
