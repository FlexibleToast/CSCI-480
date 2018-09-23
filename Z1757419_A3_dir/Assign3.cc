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
	char *arg, *command;
	char input[INPUT_SIZE+1] = "y";
	deque<char*> argq;

	// Disable cout buffer
	cout << unitbuf;
	while (strcmp(input, "q") && strcmp(input, "quit") && strcmp(input, "exit"))
	{
		// Ask user for input
		std::cout << "480shell> ";
		cin.getline(input, INPUT_SIZE);
		arg = strtok(input, " ");
		argq.push_back(arg);
		while(arg != NULL){
			arg = strtok(NULL, " ");
			argq.push_back(arg);
		}
		argq.pop_back();
		command = argq[0];
		argq.pop_front();
		char *args[argq.size()];
		int i = 0;
		while(!argq.empty())
		{
			args[i++] = argq[0];
			argq.pop_front();
		}
		cout << command << '\n';
		pid_t PID = fork();
		if(PID < 0){
			std::cerr << "Failed to fork" << '\n';
		} else if (PID > 0){
			// Parent process
			wait(0);
		} else {
			// Child process
			//std::cout << "Child command:" << '\n' << child_command << '\n';
			for(unsigned i = 0; i < sizeof(args)/sizeof(args[0]); i++)
			{
				cout << args[i] << '\n';
			}
			exit(0);
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
// void growArray(char *array, int size){
// 	char *temp = new char[size];
// 	for(unsigned i = 0; i < sizeof(array)/sizeof(array[0]); i++){
// 		temp[i] = array[i];
// 	}
// 	delete [] array;
// 	array = temp;
// }
