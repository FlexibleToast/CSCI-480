/*********************************************************************
   PROGRAM:			CSCI 480 Assignment 2
   PROGRAMMER:	Joseph McDade
   LOGON ID:		z1757419
   DUE DATE:		09/18/2018
	 Note:				Uses hard tabs set to display as 2 spaces

   FUNCTION:		This program adds practice of using pipe() to relay
	 							information between processes.
*********************************************************************/

#include <iostream>
#include <iomanip>			// setw
#include <unistd.h>     // fork,pipe
#include <wait.h>       // wait
#include <stdlib.h>     // system, itoa, atoi
#include <string.h>			//

using namespace std;

// Prototyping statements
void printValue(const char proc[], char value[]);
void performMaths(char value[]);

// Set global constants
const int READ_FD = 0;
const int WRITE_FD = 1;
const int SIZE = 90;

int main() {
	// Disable cout buffer
	cout << unitbuf;
  // Create file descriptors
  int par_fd[2];
  int child_fd[2];
	int grand_fd[2];
  // pipeC = pipe(grand_fd);
  // Check if any pipe has an error
  if(pipe(par_fd) == -1){
		std::cout << "First pipe failed" << '\n';
		exit(-5);
  }
	if(pipe(child_fd) == -1){
		std::cout << "Second pip failed" << '\n';
		exit(-5);
	}
	if(pipe(grand_fd) == -1){
		std::cout << "Third pip failed" << '\n';
		exit(-5);
	}

  // Create child processes
  pid_t childPID = fork();
  // Check if error
  if(childPID == -1){
    std::cout << "Child process failed to start" << '\n';
    exit(-5);
  }
	else if(childPID > 0)
  { /********* Parent process *********/
    close(par_fd[READ_FD]); 		// Close pipeA read end
    close(grand_fd[WRITE_FD]);	// Close pipeC write end

		// Initialize values
		const char *par = "Parent:";
		char value[SIZE] = "1";
		while (atoi(value) < 99999999)
		{	//While value is still less than 99999999
			printValue(par, value);
			performMaths(value);
			write(par_fd[WRITE_FD], value, strlen(value)+1);
			read(grand_fd[READ_FD], value, SIZE);
		}
		write(par_fd[WRITE_FD], value, strlen(value)+1);
    wait(0);
		close(par_fd[WRITE_FD]);
		close(grand_fd[READ_FD]);
		exit(0);
  }
	else { // Child process
    // Create grand child process
    pid_t grandPID = fork();
    //Check if error
    if(grandPID == -1){
      std::cout << "Grand child process failed to start" << '\n';
      exit(-5);
    }
		else if(grandPID > 0)
    { /********* Child process *********/
      close(par_fd[WRITE_FD]);	// Close pipeA write end
			close(child_fd[READ_FD]);	// Close pipeB read end
			const char *child = "Child:";
			char buffer[SIZE] = "1";	// Prime the read
			while (atoi(buffer) < 99999999)
			{	//While buffer is still less than 99999999
				read(par_fd[READ_FD], buffer, SIZE);
				printValue(child, buffer);
				performMaths(buffer);
				write(child_fd[WRITE_FD], buffer, strlen(buffer)+1);
			}
			write(child_fd[WRITE_FD], buffer, strlen(buffer)+1);
      wait(0);
			close(par_fd[READ_FD]);
			close(child_fd[WRITE_FD]);
			exit(0);
    }
		else { /********* Grand child process *********/
			close(child_fd[WRITE_FD]);	// Close pipeB write end
			close(grand_fd[READ_FD]);		// Close pipeC read end
			const char *grand = "Grandchild:";
			char buffer[SIZE] = "1";	// Prime the read
			while (atoi(buffer) < 99999999)
			{	//While buffer is still less than 99999999
				read(child_fd[READ_FD], buffer, SIZE);
				printValue(grand, buffer);
				performMaths(buffer);
				write(grand_fd[WRITE_FD], buffer, strlen(buffer)+1);
			}
			write(grand_fd[WRITE_FD], buffer, strlen(buffer)+1);
      wait(0);
			close(child_fd[READ_FD]);
			close(grand_fd[WRITE_FD]);
			exit(0);
    }
  }
  return 0;
}
/////////////////////////////////  Functions  //////////////////////////////////
/*******************************************************************************
Function: void printValue(const *char proc, const *char value)
Use: Prints the calling process and the current value
Arguments:	proc	- Calling process
						value	- Current value
Returns: Nothing
*******************************************************************************/
void printValue(const char proc[], char value[]) {
	std::cout << setw(14) << left << proc << "Value: " << value << '\n';
}

/*******************************************************************************
Function: const *char	performMaths(const *char value)
Use: Performs 4 * current value + 3
Arguments:	value	- Current value
Returns: value after maths performed
*******************************************************************************/
void	performMaths(char value[]){
	int newValue = atoi(value);
	newValue = 4 * newValue + 3;
	sprintf(value, "%d", newValue);
}
