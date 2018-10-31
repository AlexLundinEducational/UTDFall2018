#ifndef _GLOBALS_H_
#define _GLOBALS_H_

// all files
#include <semaphore.h>
#define DEBUG 1 // Debug flag. If this equals 1, debug statements will appear in program
#include <errno.h>

// coordinator.c
void * 				coordinator(void * cId );

// helloworld.c
int 				hello(void);

// student.c
void *				student(void * sId );

// tutor.c
void *				tutor(void * tId );



// global variables
extern sem_t coordStu; // coordinator to talk to student
extern sem_t tutorReady;
extern sem_t studReady;
extern sem_t coordTut;
extern sem_t mutex; // mutex
// cond variables seem like semaphores that automatically unlock mutexes when waiting and used to control exe of prog when specfic conditions are met?

extern int numChairs; // has to be acceble to all functions hence global
extern int numAval; // number of chairs available
extern int help;
extern int studDone;
extern int NumTutors;
extern int NumStudents;
extern int numHelp; // Count amount of times all the students helped. If 2 students need help 3 times. this = 6. Only for debugging purposes
extern int stuWaiting; // Number of students waiting. Increments when a student takes a seat and decrements ehen a student is finished asking for help
extern int r; // Generate random number to find time tutor will help student or time student will program



#endif // _DEFS_H_
