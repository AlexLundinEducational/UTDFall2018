//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS

#include "dash.h"

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
  
  // loop through all search paths second
  
  return processControl(args);
}