// includes for project p4a
#include "globals.h"

// declarations of any globals that are used for the first time
int studentsDone;
int studentsWaiting;

void * student (void * sId )
{

   // random amount of time student will program
   int rPtime; 	
   
   // Each students needs a copy of argNumSeekHelp that they modify
   int seeksRemaining = argNumSeekHelp; 
   
   // while loop until student reaches number of seeks required
   while(seeksRemaining > 0)
   {

      if(DEBUG)
      {
         printf("Student %d programming\n", (int)sId); // Students programming which takes time
      }
	  // start loop off with student programming for random time
	  rPtime = ( rand() % 3 ) + 1;
      sleep(rPtime);                   
      
	  // if atleast 1 chair is open
	  // then sit on the chair and signal studReady
      if(chairsAvailable > 0) 
      {
		  
		 // wait on mutex lock for shared variable editing
         sem_wait(&mutex);
         chairsAvailable--; // sit on chair
         studentsWaiting++; // add self to queue
         sem_post(&mutex);
		 
         printf("Student %d takes a seat, notifying coordinator its ready and waiting for assistance\nCurrently waiting students: %d\n", (int)sId, studentsWaiting);
		 
		 // signal that a student is ready
         sem_post(&studReady); 
        
         // wait here until coordinator signals by unlocking the coordToStudent semaphore
         sem_wait(&coordToStudent); 
         if(DEBUG)
         {
            printf("Student %d got assistance\n", (int)sId);
         }   
         
         sem_wait(&mutex);
		 // decrement seeksRemaining
         seeksRemaining--;
         if(DEBUG)
         {
            printf("Student will wait for assistance %d more times.\n", seeksRemaining);
         }    
         sem_post(&mutex);
          
      }
	  // else continue programming
      else{
         printf("No chairs are currently available for student %d. Student will program and ask for assistance later.\n", (int)sId);
		 rPtime = ( rand() % 3 ) + 1;
		 sleep(rPtime);
	  }
         
      
   }
   
  
   // wait on mutex lock for shared variable editing   
   sem_wait(&mutex);
   studentsDone++; // increment students
   sem_post(&mutex);
   if(DEBUG)
   {
      printf("Student %d is done\n", sId);
   } 
   pthread_exit(0);
}