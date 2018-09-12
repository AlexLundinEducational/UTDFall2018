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
  
  // check for redirection
  const char *source = args[0];
  char singleCharacter;
  int c = '>';
  int numberOfRedirects = 0;
  
/*   while((*source) != '\0')
  {
	  printf("%s", *source);
	  if (*source == c){
		  numberOfRedirects++;
	  }
      source++;
  } */
  
   printf("%s",source);
   // loop through the whole command string
   for (i = 0; i < strlen(source); i++){
	   
      singleCharacter = source[i];
      // printf("%c",source[i]);
	  
	  //printf("%c",singleCharacter);
	  //printf("%d",c);
	  
      if ((int)singleCharacter == c){
         numberOfRedirects++;
      }
   }


	
  if (numberOfRedirects > 1){
	  printf("\nToo many redirects");
	  return -1;
  }
  if (numberOfRedirects == 1){
	  printf("\nOne redirect");
	  return 1;
  }  
  
  // first, loop through all built in commands
  for (i = 0; i < dash_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
  
  
  char buffer[1024];

  // second, loop through all search paths
  for (i = 0; dash_paths[i] != NULL; i++) { 
    // create string from path and command name
	char commandBuffer[1024];
	strcpy(commandBuffer, dash_paths[i]);
	strcpy(commandBuffer, args[0]);

	
	if(access(commandBuffer, F_OK ) != -1 ) {
    // file exists
		sprintf(buffer, "\nThe command %s was found in the path: %s", args[0], dash_paths[i]); 
		//printf("\nThe command was found in the path: %s", dash_paths[i]);
    } else {
    // file doesn't exist
		sprintf(buffer, "\nThe command %s was NOT found in the path: %s", args[0], dash_paths[i]); 
		//printf("\nThe command was NOT found in the path: %s", dash_paths[i]);
    }
     // Use sprintf to send the string into buffer 
     // then print with printf
     printf("%s", buffer);
  }
  
  printf("\n");
  return processControl(args);
}