// includes for project p4a
#include "globals.h"


void * coodinator (void * cId )
{
   
   while(studDone < NumStudents) // Help is the amount of times each student needs help. Each student needs help
   {
                     // not changing vaalue of helo here
      if(DEBUG)
      {   
         printf("Coordinator is waiting for a student to assign a tutor to\n");
      }   
      
      while((sem_trywait(&studReady)) < 0) // continue to happen in till does hget semaphore
       // Wait for student to be ready and ask for help
       {
          if(studDone >= NumStudents)
          {
            if(DEBUG)
            {
               printf("All students are finished and received help\n");
               printf("Coordinator is done helping\n");
            }   
            pthread_exit(0);
            
          }
       }
      
      if(DEBUG)
      {
         printf("Coordinator is waiting for a tutor to be available\n");
      }   
      //sem_post(&coordReady); // Signal 
      sem_wait(&tutorReady); // signal tutor to be available to help student
      
      sem_post(&coordStu); // Coordinator is ready to asign a tutor to a student
      sem_post(&coordTut);
      if(DEBUG)
      {
         printf("Coordinator has found and assigned an available tutor to a student\n"); 
      }    
   
      sem_wait(&mutex);
      numAval++; // Coordinator setting a chair free for another student to sit on
      stuWaiting--;
      //help--;
      sem_post(&mutex);
     
      }
   if(DEBUG)
   {
      printf("Coordinator %d is done helping\n");
   }   
   
   pthread_exit(0);
}