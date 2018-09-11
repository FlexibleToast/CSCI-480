/*********************************************************************
   PROGRAM:			CSCI 480 Assignment 2
   PROGRAMMER:	Joseph McDade
   LOGON ID:		z1757419
   DUE DATE:		09/18/2018

   FUNCTION:		This program adds practice of using pipe() to relay
	 							information between processes
*********************************************************************/

#include <iostream>
#include <unistd.h>     // fork,pipe
#include <wait.h>       // wait
#include <stdlib.h>     // system
#include <string>				// string

using namespace std;

// Prototyping statements

int main() {
	// Disable cout buffer
	cout << unitbuf;
  // Create file descriptors
  int par_fd[2];
  int child_fd[2];
	string buffer;
	// int grand_fd[2];
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

  // Create child processes
  pid_t childPID = fork();
  // Check if error
  if(childPID == -1){
    std::cout << "Child process failed to start" << '\n';
    exit(-5);
  } else if(childPID > 0)
  { ////////// Parent process //////////
    close(par_fd[0]); 	// Close pipeA read end
    // close(grand_fd[1]);	// Close pipeC write end
    // Call parent process
		std::cout << "Test of the pipeA" << '\n';
		string answer = "42 is the answer";
		std::cout << answer << '\n';
		write(par_fd[1], answer.c_str(), answer.length()+1);
    wait(0);
		exit(0);
  } else { // Child process
    // Create grand child process
    pid_t grandPID = fork();
    //Check if error
    if(grandPID == -1){
      std::cout << "Grand child process failed to start" << '\n';
      exit(-5);
    } else if(grandPID > 0)
    { ////////// Child process //////////
      close(par_fd[1]);		// Close pipeA write end
			close(child_fd[0]);	// Close pipeB read end
      // Call child function
      // Write pipeB
			std::cout << "This is the child" << '\n';
			string ultimateAnswer = read(par_fd[0], answer, strlen(answer)+1);
			std::cout << "The ultinate answer is: " << ultimateAnswer << '\n';
      wait(0);
    } else { ////////// Grand child process //////////
			std::cout << "This is the grandChild" << '\n';
      // Close pipeB write
      // Close pipeC read
      // Read pipeB
      // Call grand child function
      // Write pipeC
    }
  }
  return 0;
}

/* Parent process
Create char array value and buffer
create int M
while M is less than 99999999
  cout value
  perform maths()
  write to pipeA
  read pipeC
  convert to M */

/* Child function
cout value
perform maths()
return value */

/* Grand child function
cout value
perform maths()
return value */

/* Perform maths
convert string to int
M = 4 * M + 3;
convert to string
return string */
