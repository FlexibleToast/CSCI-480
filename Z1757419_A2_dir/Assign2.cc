/*********************************************************************
   PROGRAM:			CSCI 480 Assignment 2
   PROGRAMMER:	Joseph McDade
   LOGON ID:		z1757419
   DUE DATE:		09/18/2018
	 Note:				Uses hard tabs set to display as 2 spaces

   FUNCTION:		This program adds practice of using pipe() to relay
	 							information between processes. It uses three pipes:
								-> parent -pipeA-> child -pipeB-> grandchild -
								|                                            |
								--------------------pipeC--------------------
								Each process reads a number and performs a calculation
								on that number. The program is terminated after the
								number reaches the target value.
*********************************************************************/

#include <iostream>
#include <iomanip>			// setw
#include <unistd.h>     // fork,pipe
#include <wait.h>       // wait
#include <stdlib.h>     // system, itoa, atoi

using namespace std;

// Prototyping statements
void printValue(const char proc[], char value[]);
void performMaths(char value[]);
void parentWork(int write_fd[], int read_fd[], const char name[]);
void childrenWork(int write_fd[], int read_fd[], const char name[]);

// Set global constants
const int READ_FD = 0;
const int WRITE_FD = 1;
const int SIZE = 15;
const int TARGET = 999999999;

int main() {
	// Disable cout buffer
	cout << unitbuf;
  // Create file descriptors
  int par_fd[2];
  int child_fd[2];
	int grand_fd[2];
  // Create and check pipes for errors
  if(pipe(par_fd) == -1){
		std::cout << "First pipe failed" << '\n';
		exit(-5);}
	if(pipe(child_fd) == -1){
		std::cout << "Second pipe failed" << '\n';
		exit(-5);}
	if(pipe(grand_fd) == -1){
		std::cout << "Third pipe failed" << '\n';
		exit(-5);}
  // Create child processes
  pid_t childPID = fork();
  // Check if error creating fork
  if(childPID == -1){
    std::cout << "Child process failed to start" << '\n';
    exit(-5);
  }	else if(childPID > 0)
  { /********* Parent process *********/
    close(par_fd[READ_FD]); 		// Close pipeA read end
    close(grand_fd[WRITE_FD]);	// Close pipeC write end
		const char *par = "Parent:";
		parentWork(par_fd, grand_fd, par);
		exit(0);
  }	else { // Child process
    // Create grandchild process
    pid_t grandPID = fork();
    //Check if error creating fork
    if(grandPID == -1){
      std::cout << "Grandchild process failed to start" << '\n';
      exit(-5);
    }	else if(grandPID > 0)
    { /********* Child process *********/
      close(par_fd[WRITE_FD]);	// Close pipeA write end
			close(child_fd[READ_FD]);	// Close pipeB read end
			const char *child = "Child:";
			childrenWork(child_fd, par_fd, child);
			wait(0);
			exit(0);
    }	else { /********* Grandchild process *********/
			close(child_fd[WRITE_FD]);	// Close pipeB write end
			close(grand_fd[READ_FD]);		// Close pipeC read end
			const char *grand = "Grandchild:";
			childrenWork(grand_fd, child_fd, grand);
			exit(0);
    }
  }
  return 0;
}
/////////////////////////////////  Functions  //////////////////////////////////
/*******************************************************************************
Function:		void parentWork(int write_fd[], int read_fd[], const char name[])
Use:				Performs the work of the parent. Initializes value and sending
						through the pipes. As long as the value is less than TARGET,
						it continues to process the value and send through pipe.
Arguments:	write_fd	- File descriptor of pipe to write to
						read_fd		- File descriptor of pipe to read from
						name 			- Name of process calling function
Returns:		Nothing
*******************************************************************************/
void parentWork(int write_fd[], int read_fd[], const char name[]) {
	close(write_fd[READ_FD]);	// Close pipeA read end
	close(read_fd[WRITE_FD]);	// Close pipeC write end
	char value[SIZE] = "1";		// Prime read
	printValue(name, value);
	while (atoi(value) < TARGET)
	{	//While value is still less than TARGET
		performMaths(value);
		write(write_fd[WRITE_FD], value, SIZE);
		read(read_fd[READ_FD], value, SIZE);
		printValue(name, value);
	} // Write large value to pipe so child processes can exit
	write(write_fd[WRITE_FD], value, SIZE);
	// Close pipes
	close(read_fd[READ_FD]);
	close(write_fd[WRITE_FD]);
}

/*******************************************************************************
Function:		void childrenWork(int write_fd[], int read_fd[], const char name[])
Use:				Performs the work of the child. Receives value from a pipe. As long
						as the value is less than TARGET,it continues to process the value
						and send through pipe.
Arguments:	write_fd	- File descriptor of pipe to write to
						read_fd		- File descriptor of pipe to read from
						name 			- Name of process calling function
Returns:		Nothing
*******************************************************************************/
void childrenWork(int write_fd[], int read_fd[], const char name[]) {
	close(write_fd[READ_FD]);	// Close pipeA read end
	close(read_fd[WRITE_FD]);	// Close pipeC write end
	char value[SIZE];
	read(read_fd[READ_FD], value, SIZE);	// Prime read
	while (atoi(value) < TARGET)
	{	// While value is still less than TARGET
		printValue(name, value);
		performMaths(value);
		write(write_fd[WRITE_FD], value, SIZE);
		read(read_fd[READ_FD], value, SIZE);
	} // Write large value to pipe so child processes can exit
	write(write_fd[WRITE_FD], value, SIZE);
	// Close pipes
	close(read_fd[READ_FD]);
	close(write_fd[WRITE_FD]);
}

/*******************************************************************************
Function:		void printValue(const char proc[], char value[])
Use:				Prints the calling process and the current value
Arguments:	proc	- Calling process
						value	- Current value
Returns:		Nothing
*******************************************************************************/
void printValue(const char proc[], char value[]) {
	std::cout << setw(14) << left << proc << "Value: " << value << '\n';
}

/*******************************************************************************
Function:		void	performMaths(char value[])
Use:				Performs 4 * current value + 3
Arguments:	value	- Current value
Returns:		Nothing
*******************************************************************************/
void	performMaths(char value[]){
	int newValue = atoi(value);
	newValue = 4 * newValue + 3;
	sprintf(value, "%d", newValue);
}
