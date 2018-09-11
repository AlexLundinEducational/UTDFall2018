//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef dash_H_INCLUDED
#define dash_H_INCLUDED
char **parseCommandLine(char *line);
char **parsePathArguements(char *line);
int processControl(char **args);
void commandLineLoop(void);
int executeCommandLine(char **args);
char *scanCommandLine(void);
extern int (*builtin_func[]) (char **);
extern char *builtin_str[];
extern char *dash_paths[];
extern int dash_paths_elements;
#endif
