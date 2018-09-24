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
#include <deque>

using namespace std;

// Prototyping statements

// Set global constants
#define INPUT_SIZE 256
#define SPACE " "

int main() {
	// Create variables
	char *buffer;
	char **args = (char**)malloc(sizeof(args[0]) * 1);
	char input[INPUT_SIZE+1] = "y";
	// Disable cout buffer
	cout << unitbuf;
	// while (strcmp(input, "q") && strcmp(input, "quit") && strcmp(input, "exit"))
	// {
		// Ask user for input
		cout << "480shell> ";
		fgets(input, INPUT_SIZE, stdin);
		int i = 0;
		buffer = strtok(input, " ");
		while(buffer != NULL){
			args[i++] = buffer;
			buffer = strtok(NULL, " ");
			if(buffer != NULL){
				args = (char**)realloc(args, (i+1)*sizeof(args[0]));
			}
		}
		i = 0;
		while(args[i] != NULL)
		{
			cout << args[i++] << '\n';
		}
	// }
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
