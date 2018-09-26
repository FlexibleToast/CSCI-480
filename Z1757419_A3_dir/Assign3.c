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
#include <stdbool.h>	// bool
#include <string.h>		// strtok
#include <unistd.h>		// fork, pipe
#include <wait.h>			// wait
#include <stdlib.h>		// system

// Prototyping statements
bool find_pipe(char *input, char **output);
char *tokenize(char *input, char **args, size_t *new_size);

// Set global constants
#define INPUT_SIZE 256
#define SPACE " "

int main() {
	// Create variables
	char *buffer, *command[2];
	char input[INPUT_SIZE];
	bool pipe_found = false;
	pid_t child1, child2;
	// Disable stdout buffer
	setbuf(stdout, NULL);
	// Ask user for input
	printf("480shell> ");
	fgets(input, INPUT_SIZE, stdin);
	input[strlen(input)-1] = 0;
	while (strcmp(input, "q") != 0 && strcmp(input, "quit") != 0
	 	&& strcmp(input, "exit") != 0)
	{
		pipe_found = find_pipe(input, command);
		char **child1_args = malloc(1 * sizeof(child1_args[0]));
		size_t arg1_size = 0;
		command[0] = tokenize(command[0], child1_args, &arg1_size);
		char **child2_args = malloc(1 * sizeof(child2_args[0]));
		size_t arg2_size = 0;
		if(pipe_found)
		{
			command[1] = tokenize(command[1], child2_args, &arg2_size);
		}
		// Parent

		// Test area
		printf("%s\n", command[0]);
		printf("%d\n", (int)arg1_size);
		if(arg1_size > 0)
		{
			for(size_t i = 0; i < arg1_size; i++)
			{
				printf("%s\n", child1_args[i]);
			}
			free(child1_args);
			arg1_size = 0;
		}
		if(pipe_found){
			printf("%s\n", command[1]);
			if(arg2_size > 0)
			{
				for(size_t i = 0; i < arg2_size; i++)
				{
					printf("%s\n", child2_args[i]);
				}
			}
		}else{
			printf("Pipe not found\n");
		}
		command[0] = NULL;
		// Ask user for input
		printf("480shell> ");
		fgets(input, INPUT_SIZE, stdin);
		input[strlen(input)-1] = 0;
	}
  return 0;
}
/////////////////////////////////  Functions  //////////////////////////////////
/*******************************************************************************
Function:		bool find_pipe(char *input, char **output)
Use:				Splits the input text on the "|" or "||" special character
Arguments:	input  - string to parse
						output - Array of two character pointer. First half of input is set
						to output[0] and if there is a second half it is set to output[1]
Returns:		Boolean value of true if a pipe was found and input was split
*******************************************************************************/
bool find_pipe(char *input, char **output){
	char *buffer = strtok(input, "|");
	output[0] = buffer;
	buffer = strtok(NULL, "|");
	if(buffer != NULL)
	{	// If there is a pipe save second command
		if(buffer[0] == '|') // If double pipe, remove second pipe
			buffer++;
		output[1] = buffer;
		return (true); // Return true, pipe found
	}
	return (false); // Return false, pipe not found
}
/*******************************************************************************
Function:		char *tokenize(char *input, char **args, size_t *new_size)
Use:				Used to tokenize a string on spaces to prepare for use with execvp()
Arguments:	input    - string to tokenize
						args     - array of character pointers to place arguments in
						new_size - size of args array
Returns:		The command to be used with execvp
*******************************************************************************/
char *tokenize(char *input, char **args, size_t *new_size){
	char *buffer = strtok(input, " ");
	char *command = buffer;
	int size = (int) *new_size;
	buffer = strtok(NULL, " ");
	while(buffer != NULL)
	{
		args[size++] = buffer;
		args = realloc(args, (size + 1) * sizeof(args[0]));
		buffer = strtok(NULL, " ");
	}
	*new_size = (size_t) size;
	return(command);
}
