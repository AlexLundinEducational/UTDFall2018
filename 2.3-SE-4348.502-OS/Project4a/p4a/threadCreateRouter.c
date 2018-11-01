
// includes for project p4a
#include "globals.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// all threads are routed through here for creation
// this allows one function to do the error reporting for all thread creations
// error reporting happens even outside of debug mode
void threadCreateRouter(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{

	int threadCreateSuccess = 0;
	
	threadCreateSuccess =  pthread_create(thread, attr, start_routine, arg);
   				
	// if thread fails to create
    // print error message and exit
    // because this thread can not be joined later
	if (threadCreateSuccess != 0){
       fprintf(stderr, "pthread_create failed to create with argument = %d. errno = %d, %s\n",
                arg, errno, strerror(errno));
		exit(0);
	}
	return;
}