/*******************************************************************************
   PROGRAM:			CSCI 480 Assignment 3
   PROGRAMMER:	Joseph McDade
   LOGON ID:		z1757419
   DUE DATE:		09/29/2018
	 Note:				Uses hard tabs set to display as 2 spaces

   FUNCTION:		Simulate a microshell where a user can input up to two commands
	 							with the output of one piped to the second using the '||' string
*******************************************************************************/

#include <iostream>
#include <cstring>		// strtok
#include <unistd.h>		// fork, pipe
#include <wait.h>			// wait
#include <stdlib.h>		// system

using namespace std;

// Prototyping statements

// Set global constants
#define INPUT_SIZE 256

int main() {
	// Create variables
	char *command, *args;
	char input[INPUT_SIZE+1] = "y";
	// Disable cout buffer
	cout << unitbuf;
	while (strcmp(input, "q") && strcmp(input, "quit"))
	{
		// Ask user for input
		std::cout << "480shell> ";
		cin.getline(input, INPUT_SIZE);
		args = command = strtok(input, " ");
		while(args != NULL)
		{
			printf("%s\n", args);
			args = strtok(NULL, " ");
		}
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
