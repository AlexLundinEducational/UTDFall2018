//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS

#include "dash.h"


char *dash_paths[];
int dash_paths_elements;

// main method for dash
// distributes the work to the other methods  
int main(int argc, char **argv)
{

  // Run command loop.
  commandLineLoop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}