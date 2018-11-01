
// includes for project p4a
#include "globals.h"

// declarations of any globals that are used for the first time
int helpAccumulator;

void * tutor (void * tId )
{

   int rHtime; 	// random amount of time tutor will assist student
   
   while(studentsDone < argNumStudents ) // If student not done continue to assistance. Tutors work till all students done
   {
      if(DEBUG)
      {
         printf("Tutor %d is signalling to the coordinator that it is ready to assist students\n", tId);
      }
	  // tell coorindator that this tutor is ready
      sem_post(&tutorReady);
	  
	  // continue to try to get semaphore, until try returns a value greater than 0
	  // value greater than or equal to 0 means
	  // coodinator signaled by unlocking coordinatorToTutor semaphore
      // meaning that the coordinator has found a student ready for this tutor
      while((sem_trywait(&coordinatorToTutor)) < 0)
       {
		  // do a thread exit check while trying to get the semaphore 
          if(studentsDone >= argNumStudents)
          {
            if(DEBUG)
            {
               printf("The tutors have finished assisting the students\n");
               printf("Tutor %d is done assisting\n", tId);
            }   
            
            pthread_exit(0);
            
          }
       }
      
	  // once control reaches here, then that means the sem_try returned value >= 0
	  
      rHtime = ( rand() % 3 ) + 1;
      printf("Tutor %d helping student for %d seconds. Waiting students = %d\n", tId, rHtime, studentsWaiting);
	  
      sleep(rHtime);  

      // wait on mutex lock for shared variable editing
      sem_wait(&mutex);
      helpAccumulator++; // accumulates total times any tutor assists any student
      if(DEBUG)
      {
         printf("Tutors assisted %d times\n", helpAccumulator); 
      } 
      sem_post(&mutex);   
   }
   
   if(DEBUG)
   {
      printf("Tutor %d is done assisting\n", tId);
   }  
   pthread_exit(0);
   
}