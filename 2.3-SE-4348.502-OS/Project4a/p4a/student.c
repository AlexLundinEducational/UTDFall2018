// includes for project p4a
#include "globals.h"



void * student (void * sId )
{

//   If(help > 0)
// Mutex
// mutex
// While  numberOfFreeWRSeats > 0: # If there are any free seats:
// mutex
//       numberOfFreeWRSeats -= 1  #   sit down in a chair
// signal(mutex)     #   don't need to lock the chairs anymore mutex
//       signal(studReady)         #   notify the coord, who's waiting until there is a student
//       wait(CoordReady)         #   wait until theCoordinator is ready
//       # (Have hair cut here.)
//     else:                       # otherwise, there are no free seats; tough luck --
//       signal(mutex)
   int helpNum = help; // Each students needs a copy of help that they modify
   
   while(helpNum > 0) // Help is the amount of times each student needs help. Each student needs help
   {
                     // not changing value of helo here
         sem_wait(&mutex);
         r = ( rand() % 3 ) + 1;
         sem_post(&mutex);
         if(DEBUG)
         {
            printf("Student %d programming\n", (int)sId); // Students programming which takes time
         }
         sleep(r);                   
      
      if(numAval > 0) 
      {
         sem_wait(&mutex);
         numAval--; // sit on chair
         stuWaiting++;
         sem_post(&mutex); // Protect numAval, stuWaiting, r
         
         printf("Student %d takes a seat, notifying coordinator its ready and waiting for help\nCurrently waiting students: %d\n", (int)sId, stuWaiting);
         sem_post(&studReady); // notify the coord, who's waiting until there is a student
        
        // put student in an array. Space to save what students are want help and are waiting for help or not.
         sem_wait(&coordStu); // wait until theCoordinator is ready
         if(DEBUG)
         {
            printf("Student %d got help\n", (int)sId);
         }   
         
         sem_wait(&mutex);
         helpNum--;
         if(DEBUG)
         {
            printf("Student will wait for help %d more times.\n", helpNum); // This is debug statement
         }    
         sem_post(&mutex);
          
      }
     else
         //sem_post(&mutex);
         printf("No chairs are currently available for student %d. Student will program and ask for help later.\n", (int)sId);
         sem_wait(&mutex);
         r = ( rand() % 3 ) + 1;
         sem_post(&mutex);
         sleep(r);
         
      
   }
   if(DEBUG)
   {
      printf("Student %d is done\n", sId);
   }   
   sem_wait(&mutex);
   studDone++;
   sem_post(&mutex);
   //printf("StudDone %d is done\n", studDone); // Was a debug statement
 
   pthread_exit(0);
}