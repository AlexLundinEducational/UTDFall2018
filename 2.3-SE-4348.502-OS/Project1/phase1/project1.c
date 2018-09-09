//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS

#include "project1.h"

void processControl();
void signalRegister();


int main(int argc, char * argv[]);

// main method for project1
// distributes the work to the other methods

int main (int argc, char * argv[]){
	signalRegister ();
	processControl();
	return(0);
}
