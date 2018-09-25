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
	char *buffer, *command, *child_command;
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
		char **child_args = malloc(sizeof(child_args[0]) * 1);
		size_t argSize = 0;
		size_t childArgSize = 0;
		buffer = strtok(input, " ");
		command = buffer;
		buffer = strtok(NULL, " ");
		while(buffer != NULL){
			args[argSize++] = buffer;
			buffer = strtok(NULL, " ");
			if(buffer != NULL)
			{
				if(strcmp(buffer, "||") == 0)
				{
					child_command = buffer = strtok(NULL, " ");
					buffer = strtok(NULL, " ");
					while(buffer != NULL)
					{
						child_args[childArgSize++] = buffer;
						buffer = strtok(NULL, " ");
						if(buffer != NULL)
						{
							child_args = realloc(child_args,
								(childArgSize+1)*sizeof(child_args[0]));
						}
					}
					break;
				}
				args = realloc(args, (argSize+1)*sizeof(args[0]));
			}
		}
		pid_t child = fork();
		if(child < 0)
		{
			fprintf(stderr, "Child failed to fork\n");
		} else if(child > 0)
		{
			// Parent
			// Test area

			printf("%s\n", command);
			if(argSize > 0)
			{
				for(size_t i = 0; i < argSize; i++)
				{
					printf("%s\n", args[i]);
				}
			}
			wait(0);
			if(child_command != NULL)
			{
				child_command = NULL;
			}
			if(childArgSize > 0)
			{
				free(child_args);
				childArgSize = 0;
			}
		} else {
			if(child_command != NULL)
			{
				printf("%s\n", child_command);
				child_command = NULL;
			}
			if(childArgSize > 0)
			{
				for(size_t i = 0; i < childArgSize; i++)
				{
					printf("%s\n", child_args[i]);
				}
				free(child_args);
				childArgSize = 0;
			}
			exit(0);
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
