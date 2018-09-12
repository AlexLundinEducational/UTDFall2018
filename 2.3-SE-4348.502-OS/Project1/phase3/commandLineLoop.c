//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS

#include "dash.h"

void commandLineLoop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("dash> ");
    line = scanCommandLine();
    args = parseCommandLine(line);
    status = executeCommandLine(args);
	//printf("\nin commandline loop again:");
    //free(line);
    //free(args);
  } while (status);
}