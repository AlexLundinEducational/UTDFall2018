
// includes for project p4a
#include "globals.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void * coodinator (void * cId ); // Why do the data types have to be void * allow pass any data type? what value should pshare be = to
void * tutor (void * tId );
void * student (void * sId );
sem_t coordStu; // coordinator to talk to student
sem_t tutorReady;
sem_t studReady;
sem_t coordTut;
sem_t mutex; // mutex
// cond variables seem like semaphores that automatically unlock mutexes when waiting and used to control exe of prog when specfic conditions are met?

int numChairs; // has to be acceble to all functions hence global
int numAval; // number of chairs available
int help;
int studDone = 0;
int NumTutors;
int NumStudents;
int numHelp; // Count amount of times all the students helped. If 2 students need help 3 times. this = 6. Only for debugging purposes
int stuWaiting = 0; // Number of students waiting. Increments when a student takes a seat and decrements ehen a student is finished asking for help
int r; // Generate random number to find time tutor will help student or time student will program



int main(int argc, char *argv[])
{
	
   srand(time(NULL));
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
   
   sem_init(&coordStu, 0, 0);
   sem_init(&coordTut, 0, 0);
   sem_init(&tutorReady, 0, 0);    // .Declare coordReady semaphore
   sem_init(&studReady, 0, 0);    // Declare coordReady semaphore
   sem_init(&mutex, 0, 1);    // mutex = 1 since it a lock
   // m and n are arguments passed into the program via command line.
   //int NumTutors,NumStudents;
   int i; // Just a counter used to help give the tutors and students an argument to pass into the function
   NumTutors = atoi(argv[2]); // Represent number of tutors
   NumStudents = atoi(argv[1]); // Represent number of students
   help = atoi(argv[4]);
   
   numChairs = atoi(argv[3]); // number of chairs available. Its initial signals that all the chairs are available
                          // No chairs available when numChairs value equals 0
   numAval = numChairs;     
   
   int tutorNum[NumTutors];
   int studentNum[NumStudents];
   
   // Initilizaling Student arguments
   if(DEBUG)
   {
      printf("Initilizaling Student arguments\n");
   }
   for(i = 0; i < NumStudents; i++)
   {
      studentNum[i] = i;
   }
   
   // Initilizaling Student arguments
   if(DEBUG)
   {
      printf("Initilizaling tutor arguments\n");
   }   
   for(i = 0; i < NumTutors; i++)
   {
      tutorNum[i] = i;
   }
   
   pthread_t studentThread[NumStudents]; /* the students identifiers */
   pthread_t tutorThread[NumTutors]; /* the tutors identifiers */
   pthread_t coordinatorThread; /* the coordinator identifiers The coordinator wakes up an idle tutor and assign to a student  */ 
   
   pthread_attr_t attr; /* set of threads attributes. Will equal default value */
                     
   i = 0;
   
  // Creating coordinator thread
  if(DEBUG)
  {
      printf("Coordinator created\n");
  }    
   pthread_create(&coordinatorThread, NULL, coodinator, (void *)i);
   
   // Creating tutor threads
   for (i = 0; i < NumTutors; i++) 
   {
        if(DEBUG)
        {
            printf("tutor %d created\n", tutorNum[i]);
        }    
        pthread_create(&tutorThread[i], NULL, tutor, (void *)tutorNum[i]); 
   } 

   
   for (i = 0; i < NumStudents; i++) 
   {
        if(DEBUG)
        {
            printf("student %d created\n", studentNum[i]);
        }   
        pthread_create(&studentThread[i], NULL, student, (void *)studentNum[i]); 
        // Should you only create student threads that need help. If  n students need help
        // create n students provided that n <= number of students
   } 
   
   
    // Joining the threads
      for(i=0; i < NumStudents; i++)
   {
      pthread_join(studentThread[i],NULL);
   }
   //studDone = 0; // If all students exit true
   
      for(i=0; i < NumTutors; i++)
   {
      pthread_join(tutorThread[i],NULL); // A thread can execute a thread join to wait until the other thread terminates
   }
   
    pthread_join(coordinatorThread,NULL); //  blocks the calling thread until the specified threadid thread terminates.
    
    if(DEBUG)
    {
      printf("The students were helped and program is done \n");
    }  
   
   // What if all the students get help? How will the threads terminate?
   
   
   // student first program, sleep(5) cout << student i programming << endl;
   // if tutor is available get help or sit on a chair. If no chairs available student continues programing
   
   
   // Student threads will alternate between programming for a period of time and seeking help from the tutor
   // If the tutor is available, they will obtain help. Otherwise, they will either sit in a chair in the waiting area
   // or, if no chairs are available, will resume programming and seek help at a later time. 

   // last thing main must do is call pthread_exit to wait for all the threads it created to terminate
   // if main does not do this, main could, and probably will terminate before the threads finish
   // then the threads will attempt to access memory that is no longer protected for them
   // resulting in seg faults
   pthread_exit(NULL);
}



