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
#include <vector>

using namespace std;

// Prototyping statements

// Set global constants
#define INPUT_SIZE 256
#define SPACE " "

int main() {
	// Create variables
	char *arg;//, *child_command, *child_args;
	char input[INPUT_SIZE+1] = "y";
	vector<char*> argv;
	// Disable cout buffer
	cout << unitbuf;
	while (strcmp(input, "q") && strcmp(input, "quit") && strcmp(input, "exit"))
	{
		char input[INPUT_SIZE+1] = "y";
		argv.empty();
		// Ask user for input
		std::cout << "480shell> ";
		cin.getline(input, INPUT_SIZE);
		arg = strtok(input, " ");
		argv.push_back(arg);
		while(arg != NULL){
			arg = strtok(NULL, " ");
			argv.push_back(arg);
		}
		argv.pop_back();
		cout << argv.size() << '\n';
		for(unsigned i = 0; i < argv.size(); i++){
			cout << argv[i] << '\n';
		}
		pid_t PID = fork();
		if(PID < 0){
			std::cerr << "Failed to fork" << '\n';
		} else if (PID > 0){
			// Parent process
			wait(0);
		} else {
			// Child process
			cout << "hello world" << '\n';
			//std::cout << "Child command:" << '\n' << child_command << '\n';
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
