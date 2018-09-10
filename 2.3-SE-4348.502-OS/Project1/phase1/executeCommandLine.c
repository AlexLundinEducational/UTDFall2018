//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS

#include "project1.h"

int executeCommandLine(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < DASH_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return processControl(args);
}