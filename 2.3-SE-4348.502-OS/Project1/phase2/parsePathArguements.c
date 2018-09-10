//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS

#include "dash.h"

#define PARSE_PATH_TOK_BUFSIZE 64
#define PARSE_PATH_TOK_DELIM " \t\r\n\a"

char **parsePathArguements(char *line)
{
  int bufsize = PARSE_PATH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "parsePathArguements: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, PARSE_PATH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += PARSE_PATH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "parsePathArguements: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, PARSE_PATH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}