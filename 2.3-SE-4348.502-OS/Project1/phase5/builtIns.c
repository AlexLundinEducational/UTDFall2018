//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS

#include "dash.h"

// forward declarations for this file
int dash_exit(char **args);
int dash_cd(char **args);
int dash_path(char **args);
int dash_help(char **args);
char *dash_paths[];
int dash_paths_elements; 

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

  // initialize global dash_paths character array
  dash_paths_elements = sizeof(args) / sizeof(args[0]);
  dash_paths_elements--;
  //*dash_paths[dash_paths_elements];
  
  // initialize loop variables
  int i=1;   
  int j=0;
  char *arg;
  // loop through all arguements
  printf("The tokenized dash_paths are:\n");
  do {
	dash_paths[j] = args[i];
	printf("	%s\n", dash_paths[j]);
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

