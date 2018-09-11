//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS

#include "dash.h"

// forward declarations for this file
int dash_exit(char **args);
int dash_cd(char **args);
int dash_path(char **args);
int dash_help(char **args);


// custom variable declarations
char *builtin_str[] = {
  "exit",
  "cd",
  "path",
  "help"
  
};

int (*builtin_func[]) (char **) = {
  &dash_exit,
  &dash_cd,
  &dash_path,
  &dash_help
  
};

int dash_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

// builtin functions for dash
int dash_exit(char **args)
{
  return 0;
}

int dash_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "dash: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("dash");
    }
  }
  return 1;
}

int dash_path(char **args)
{

  // create global paths character array
  int elements_in_args = sizeof(args) / sizeof(args[0]);
  char *paths[elements_in_args];
  
  // initialize loop variables
  int i=1;   
  int j=0;
  char *arg;
  // loop through all arguements
  // skip index 0, because this is the path command
  printf("The tokenized paths are:\n");
  do {
	paths[j] = args[i];
	printf("	%s\n", paths[j]);
	i++;
	j++;
  } while (args[i]);
  return 1;
}

int dash_help(char **args)
{
  int i;
  printf("Alex Lundin's dash\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < dash_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("The linux man pages will give more information on other programs.\n");
  return 1;
}

