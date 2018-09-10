//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS

#include "project1.h"

/*
  Function Declarations for builtin shell commands:
 */
int DASH_cd(char **args);
int DASH_help(char **args);
int DASH_exit(char **args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &DASH_cd,
  &DASH_help,
  &DASH_exit
};

int DASH_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/
int DASH_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "DASH: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("DASH");
    }
  }
  return 1;
}

int DASH_help(char **args)
{
  int i;
  printf("Alex Lundin's DASH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < DASH_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int DASH_exit(char **args)
{
  return 0;
}