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
#include <stdlib.h>		// malloc, realloc, free, exit

// Prototyping statements
bool find_pipe(char *input, char **output);
void tokenize(char *input, char **args);
void single_command(char **args);
void piped_command(char **args1, char **args2);

// Set global constants
#define INPUT_SIZE 256
#define READ 0
#define WRITE 1

int main() {
	// Create variables
	char *command[2];
	char input[INPUT_SIZE];
	bool pipe_found = false;
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
		tokenize(command[0], child1_args);
		if(pipe_found)
		{
			char **child2_args = malloc(1 * sizeof(child2_args[0]));
			tokenize(command[1], child2_args);
			piped_command(child1_args, child2_args);
			free(child2_args);
		} else {
			single_command(child1_args);
		}
		command[0] = command[1] = NULL;
		free(child1_args);
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
Function:		void tokenize(char *input, char **args, size_t *new_size)
Use:				Used to tokenize a string on spaces to prepare for use with execvp()
Arguments:	input    - string to tokenize
						args     - array of character pointers to place arguments in
						new_size - size of args array
Returns:		void
*******************************************************************************/
void tokenize(char *input, char **args){
	int size = 0;
	args[size] = strtok(input, " ");
	while(args[size++] != NULL)
	{
		args = realloc(args, (size + 1) * sizeof(args[0]));
		args[size] = strtok(NULL, " ");
	}
	return;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void single_command(char **args){
	pid_t child = fork();
	if(child < 0){
		fprintf(stderr, "Process failed to fork\n");
		exit(-1);
	}
	if(child == 0)
	{	// Child Process
		if(execvp(args[0], args) < 0)
		{
			fprintf(stderr, "Command failed to run with execvp\n");
			exit(-1);
		}
		exit(0);
	}
	wait(0);
	return;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void piped_command(char **args1, char **args2){
	int pipe_ends[2];
	if(pipe(pipe_ends) < 0){
		fprintf(stderr, "Failed to pipe\n");
		exit(-1);
	}
	pid_t child1 = fork();
	pid_t child2 = fork();
	if(child1 < 0){
		fprintf(stderr, "Child 1 failed to fork\n");
		exit(-1);
	}
	if(child2 < 0){
		fprintf(stderr, "Child 2 failed to fork\n");
		exit(-1);
	}
	if(child1 == 0)
	{	// Child 1 Process
		close(WRITE);
		dup(pipe_ends[WRITE]);
		close(pipe_ends[READ]);
		close(pipe_ends[WRITE]);
		if(execvp(args1[0], args1) < 0)
		{
			fprintf(stderr, "Command failed to run with execvp\n");
			exit(-1);
		}
		exit(0);
	}
	if(child2 == 0)
	{	// Child 2 Process
		close(READ);
		dup(pipe_ends[READ]);
		close(pipe_ends[WRITE]);
		close(pipe_ends[READ]);
		if(execvp(args2[0], args2) < 0)
		{
			fprintf(stderr, "Command failed to run with execvp\n");
			exit(-1);
		}
		exit(0);
	}
	// Parent Process
	close(pipe_ends[READ]);
	close(pipe_ends[WRITE]);
	wait(0);
	wait(0);
	return;
}
