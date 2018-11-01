// includes for project p4a
#include "globals.h"


void * coordinator (void * cId )
{
   
   while(studentsDone < argNumStudents) 
   {
      if(DEBUG)
      {   
         printf("Coordinator is waiting for a student to assign a tutor to\n");
      }   
      
	  // continue to try to get semaphore, until try returns a value greater than 0
      while((sem_trywait(&studentReady)) < 0)
      {
		 // if all students are done, tell coordinator thread it's time to exit
         if(studentsDone >= argNumStudents)
         {
            if(DEBUG)
            {
               printf("All students are finished and received assistance\n");
               printf("Coordinator is done helping\n");
            }   
            pthread_exit(0);
            
         }
      }
      
	  // control flow made it to here, so two things about students are true
      // 1] students are ready because studentReady is locked
	  // 2] some are not done yet because studentsDone < argNumStudents
      if(DEBUG)
      {
         printf("Coordinator is waiting for a tutor to be available\n");
      }   

	  // wait until a tutor becomes available
      sem_wait(&tutorReady);
	  
      // once tutor is ready
	  // unlocking the coordinator to tutor and student semaphores
	  // *** seems like it makes sense to signal tutor first, then student
	  sem_post(&coordinatorToTutor);
	  sem_post(&coordinatorToStudent);
      

      if(DEBUG)
      {
         printf("Coordinator has found and assigned an available tutor to a student\n"); 
      }    
   
      // wait on mutex lock for shared variable editing
      sem_wait(&mutex);
      chairsAvailable++; // free a chair
      studentsWaiting--; // remove student from queue
      sem_post(&mutex);
     
   }
	  
   if(DEBUG)
   {
      printf("Coordinator %d is done directing\n", cId);
   }   
   
   pthread_exit(0);
}