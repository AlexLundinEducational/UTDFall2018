// includes for project p4a
#include "globals.h"



void * tutor (void * tId )
{
   // Signal(tutorReady) // signal tutor is ready
//    Wait(CoordReady) // wait for coord to give them a student
//    // Help student

   while(studDone < NumStudents ) // If student not done continue to help. Tutors work till all students done
   {
      if(DEBUG)
      {
         printf("Tutor %d is signalling to the coordinator that it is ready to help students\n", tId);
      }
      sem_post(&tutorReady); // says to coord it is ready.
      while((sem_trywait(&coordTut)) < 0) // continue to happen in till does get semaphore
       // Wait until student finsished 
       {
          if(studDone >= NumStudents)
          {
            if(DEBUG)
            {
               printf("The tutors have finished helping the students\n");
               printf("Tutor %d is done helping\n", tId);
            }   
            
            pthread_exit(0);
            
          }
       }

      
      //sem_wait(&coordTut); // Wait for coordinator when coordinator is ready
      sem_wait(&mutex);
      r = ( rand() % 3 ) + 1;
      sem_post(&mutex);
      printf("Tutor %d helping student for %d miliseconds\nCurrently waiting students: %d\n", tId, r, stuWaiting);
      sem_wait(&mutex);
      sleep(r);  
      sem_post(&mutex);
      
      sem_wait(&mutex);
      numHelp++;
      if(DEBUG)
      {
         printf("tutors helped %d times\n", numHelp); // Tells how many times the tutors in total helped.
      } 
      sem_post(&mutex);   
   }
   
   if(DEBUG)
   {
      printf("tutor %d is done helping\n", tId);
   }  
   pthread_exit(0);
   
}