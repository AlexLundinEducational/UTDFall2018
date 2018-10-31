// includes for project p4a
#include "globals.h"

// declarations of any globals that are used for the first time
int helpAccumulator;

void * tutor (void * tId )
{
   // Signal(tutorReady) // signal tutor is ready
//    Wait(CoordReady) // wait for coord to give them a student
//    // argNumSeekHelp student

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
      while((sem_trywait(&coordToTutor)) < 0)
       {
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
      // wait on mutex lock for shared variable editing
      sem_wait(&mutex);
      rHtime = ( rand() % 3 ) + 1;
      sem_post(&mutex);
      printf("Tutor %d assisting student for %d miliseconds\nCurrently waiting students: %d\n", tId, rHtime, studentsWaiting);
      sem_wait(&mutex);
      sleep(rHtime);  
      sem_post(&mutex);
      
      sem_wait(&mutex);
      helpAccumulator++;
      if(DEBUG)
      {
         printf("Tutors assisted %d times\n", helpAccumulator); // accumulates total times any tutor assists any student
      } 
      sem_post(&mutex);   
   }
   
   if(DEBUG)
   {
      printf("Tutor %d is done assisting\n", tId);
   }  
   pthread_exit(0);
   
}