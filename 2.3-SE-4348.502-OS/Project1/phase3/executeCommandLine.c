//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS

#include "dash.h"
char *dash_paths[];
int dash_paths_elements;

int executeCommandLine(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }
  
  // loop through all built in commands first
  for (i = 0; i < dash_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
  
  
  
  printf("\nPath loop:");
  // loop through all search paths second
  for (i = 0; i < dash_paths_elements; i++) {
	  
    // create string from path and command name
	char commandBuffer[1024];
	strcpy(commandBuffer, dash_paths[i]);
	strcpy(commandBuffer, args[0]);
	
	if( access(commandBuffer, F_OK ) != -1 ) {
    // file exists
	   printf("\nThe command was found in the path:");
    } else {
    // file doesn't exist
	   printf("\nThe command was NOT found in the path:");
    }
    printf("	%s\n", dash_paths[i]);
  }  
  return processControl(args);
}