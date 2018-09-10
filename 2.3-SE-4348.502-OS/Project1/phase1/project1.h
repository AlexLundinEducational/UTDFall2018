//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef PROJECT1_H_INCLUDED
#define PROJECT1_H_INCLUDED
//char **parseCommandLine(char *line);
//int processControl(char **args);
//void commandLineLoop(void);
//int executeCommandLine(char **args);
//char *scanCommandLine(void);
char **parseCommandLine(char *line);
int processControl(char **args);
void commandLineLoop(void);
int executeCommandLine(char **args);
char *scanCommandLine(void);
int (*builtin_func[]) (char **);
char *builtin_str[];
#endif
