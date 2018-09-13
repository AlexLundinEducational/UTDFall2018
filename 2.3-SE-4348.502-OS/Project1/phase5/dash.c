//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS

// there is an extensive makefile that pairs with this project
// make clean:
// removed all object files
// make:
// builds all object files
// make backup:
// creates a timestamped tarbar backup in my folder, ~/backups 

// I implemented the shell basics, I did not move onto redirection or parallel commands

#include "dash.h"


char *dash_paths[];
int dash_paths_elements;

// main method for dash
// distributes the work to the other methods  
int main(int argc, char **argv)
{

  // Run command loop.
  commandLineLoop();


  return EXIT_SUCCESS;
}