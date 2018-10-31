
// includes for project p4a
#include "globals.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// all threads are routed through here for joining
// this allows one function to do the error reporting for all thread joins
// error reporting happens even outside of debug mode
void threadJoinRouter(pthread_t thread, void **retval)
{

	int threadJoinSuccess = 0;
	
	threadJoinSuccess =  pthread_join(thread, retval);
   				
	// if thread fails to join
    // print error message and exit
	if (threadJoinSuccess != 0){
       fprintf(stderr, "pthread_join failed to join. errno = %d, %s\n",
                errno, strerror(errno));
		exit(0);
	}
	return;
}