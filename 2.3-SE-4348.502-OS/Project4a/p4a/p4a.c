
// includes for project p4a
#include "globals.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// declarations of any globals that are used for the first time
sem_t coordToStudent;
sem_t tutorReady;
sem_t studReady;
sem_t coordToTutor;
sem_t mutex;
int argNumChairs;
int chairsAvailable;
int argNumSeekHelp;
int argNumTutors;
int argNumStudents;

// thread create is done systematically, so there is no livelock
// first coordinator, then all tutors, then all students

// thread join is done systematically, so there is no deadlock
// first all students, then all tutors, then the coordinator


// High level overview of control flow
// 1] validate command line inputs
// 2] initialize simple arrays to indentify student threads and tutor threads 
//			the simple arrarys hold value of counter variable i passed into threadCreateRouter later
// 3] create threads from main
//			call the threadCreateRouter with appropriate arguments
//			this hides error handling details from main
// 4] join threads to main
//			call the threadJoinRouter with appropriate arguments
//			this hides error handling details from main
// 5] tell main to wait until all threads that are joined to main terminate
// 6] allow main to terminate after all joins return

int main(int argc, char *argv[])
{
	
   srand(time(NULL));
   
   // 1] validate command line inputs
   if (argc != 5) 
   {
      fprintf(stderr,"usage: a.out <integer value>\n");
      return -1;
   }
   
   if (atoi(argv[1]) < 0) 
   {
      fprintf(stderr,"%d must be >= 0\n",atoi(argv[1]));
      return -1;
   }
   
   if (atoi(argv[2]) < 0) 
   {
      fprintf(stderr,"%d must be >= 0\n",atoi(argv[2]));
      return -1;
   }
   
      if (atoi(argv[3]) < 0) 
   {
      fprintf(stderr,"%d must be >= 0\n",atoi(argv[3]));
      return -1;
   }
   
         if (atoi(argv[4]) < 0) 
   {
      fprintf(stderr,"%d must be >= 0\n",atoi(argv[4]));
      return -1;
   }
  
   // parse command line
   argNumStudents = atoi(argv[1]);
   argNumTutors = atoi(argv[2]);
   argNumChairs = atoi(argv[3]);
   argNumSeekHelp = atoi(argv[4]);
   
   // initialize number of chairs open to sit on
   chairsAvailable = argNumChairs;
   
   // communication semaphores set to 0 at first
   sem_init(&coordToStudent, 0, 0);
   sem_init(&coordToTutor, 0, 0);
   
   // ready semaphores set to 0 at first
   sem_init(&tutorReady, 0, 0);
   sem_init(&studReady, 0, 0);
   
   // mutual exclusion lock set to 1 at first
   sem_init(&mutex, 0, 1);
   

   // counter used during tutor and student thread creation
   int i;
   
   // 2] initialize simple arrays to indentify student threads and tutor threads
   // integer arrays
   // slot for each student and tutor, respectivley
   // the value at each index, is the index itself, nothing fancy
   int tutorNum[argNumTutors];
   int studentNum[argNumStudents];
   
   // Initilizaling Student array
   if (DEBUG)
   {
      printf("Initilizaling student array\n");
   }
   
   for (i = 0; i < argNumStudents; i++)
   {
      studentNum[i] = i;
   }
   
   // Initilizaling Student array
   if (DEBUG)
   {
      printf("Initilizaling tutor array\n");
   } 
   
   for (i = 0; i < argNumTutors; i++)
   {
      tutorNum[i] = i;
   }
   
   // coordinator thread
   pthread_t coordinatorThread;
   
   // thread arrays
   // slot for each student and tutor, respectivley
   pthread_t studentThreads[argNumStudents];
   pthread_t tutorThreads[argNumTutors];
   
   i = 0;
   
   // 3] create threads from main
   
   // Create coordinator thread
   threadCreateRouter(&coordinatorThread, NULL, coordinator, (void *)i);
   if (DEBUG)
   {
      printf("Coordinator thread created\n");
   }
   
   // Create tutor threads
   for (i = 0; i < argNumTutors; i++) 
   {
	  threadCreateRouter(&tutorThreads[i], NULL, tutor, (void *)tutorNum[i]);
	  if (DEBUG)
      {
      printf("Tutor thread %d created\n", tutorNum[i]);
      }
	  
   } 

   // Create student threads
   for (i = 0; i < argNumStudents; i++) 
   {
      threadCreateRouter(&studentThreads[i], NULL, student, (void *)studentNum[i]); 
      if (DEBUG)
      {
         printf("Student thread %d created\n", studentNum[i]);
      } 	  
	  
   } 
   
   // 4] join threads to main
   
   
   // Join student threads
   for (i = 0; i < argNumStudents; i++)
   {
      threadJoinRouter(studentThreads[i],NULL);
      if (DEBUG)
      {
         printf("Student thread %d joined back to main after completion\n", studentNum[i]);
      } 	
   }
   
   // Join tutor threads
   for (i = 0; i < argNumTutors; i++)
   {
      threadJoinRouter(tutorThreads[i],NULL);
      if (DEBUG)
      {
         printf("Tutor thread %d joined back to main after completion\n", tutorNum[i]);
      } 	
   }  
   
   // Join coordinator thread
   threadJoinRouter(coordinatorThread,NULL);
   if (DEBUG)
   {
      printf("Coordinator thread %d joined back to main after completion\n", tutorNum[i]);
   }    
 
   
   // Student threads will alternate between programming for a period of time and getting assistance from the tutor
   // If the tutor is available, they will obtain assistance. Otherwise, they will either sit in a chair in the waiting area
   // or, if no chairs are available, will resume programming and seek assistance at a later time. 
   
   if (DEBUG)
   {
      printf("The students were helped and program is done \n");
   }  
   
   // last statement main must execute is
   // a call pthread_exit to wait for all the threads it created to terminate
   // if main does not do this, main could, and probably will, terminate before the threads finish
   // then the threads will attempt to access memory that is no longer protected for them
   // resulting in seg faults
   
   // 5] tell main to wait until all threads that are joined to main terminate
   pthread_exit(NULL);
   // 6] allow main to terminate after all joins return
   
}



