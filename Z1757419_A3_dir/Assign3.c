/*******************************************************************************
   PROGRAM:			CSCI 480 Assignment 3
   PROGRAMMER:	Joseph McDade
   LOGON ID:		z1757419
   DUE DATE:		09/29/2018
	 Note:				Uses hard tabs set to display as 2 spaces

   FUNCTION:		Simulate a microshell where a user can input up to two commands
	 							with the output of one piped to the second using the '||' string
*******************************************************************************/

#include <stdio.h>
#include <string.h>		// strtok
#include <unistd.h>		// fork, pipe
#include <wait.h>			// wait
#include <stdlib.h>		// system

// Prototyping statements

// Set global constants
#define INPUT_SIZE 256
#define SPACE " "

int main() {
	// Create variables
	char *buffer;
	char input[INPUT_SIZE];
	// Disable stdout buffer
	setbuf(stdout, NULL);
	// Ask user for input
	printf("480shell> ");
	fgets(input, INPUT_SIZE, stdin);
	input[strlen(input)-1] = 0;
	while (strcmp(input, "q") != 0 && strcmp(input, "quit") != 0
	 	&& strcmp(input, "exit") != 0)
	{
		char **args = malloc(sizeof(args[0]) * 1);
		size_t argSize = 0;
		buffer = strtok(input, " ");
		while(buffer != NULL){
			args[argSize] = buffer;
			buffer = strtok(NULL, " ");
			if(buffer != NULL){
				argSize++;
				args = realloc(args, (argSize+1)*sizeof(args[0]));
			}
		}
		argSize++;
		printf("%d\n", (int)argSize );
		for(size_t i = 0; i < argSize; i++)
		{
			printf("%s\n", args[i]);
		}
		// Ask user for input
		printf("480shell> ");
		fgets(input, INPUT_SIZE, stdin);
		input[strlen(input)-1] = 0;
	}
  return 0;
}
/////////////////////////////////  Functions  //////////////////////////////////
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
// void growArray(char *array, int size){
// 	char *temp = new char[size];
// 	for(unsigned i = 0; i < sizeof(array)/sizeof(array[0]); i++){
// 		temp[i] = array[i];
// 	}
// 	delete [] array;
// 	array = temp;
// }
