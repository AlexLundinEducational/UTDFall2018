//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS

#include "dash.h"


char *scanCommandLine(void)
{
  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us
  getline(&line, &bufsize, stdin);
  return line;
}