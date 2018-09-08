/*********************************************************************
   PROGRAM:    CSCI 480 Assignment 2
   PROGRAMMER: Joseph McDade
   LOGON ID:   z1757419
   DUE DATE:   09/18/2018

   FUNCTION:   This program adds practice of using pipe()
*********************************************************************/

#include <iostream>
#include <unistd.h>     // fork,pipe
#include <wait.h>       // wait
#include <stdlib.h>     // system

using namespace std;

// Prototyping statements

int main() {
  // Create file descriptors
  int par_fd[2];
  int child_fd[2];
	int grand_fd[2];

  // Create pipes
  pipeA = pipe(par_fd);
  pipeB = pipe(child_fd);
  pipeC = pipe(grand_fd);
  // Check if any pipe has an error
  if(pipeA == -1){
    exit(-5);
  } // etc...

  // Create child processes
  childPID = fork();
  // Check if error
  if(childPID == -1){
    std::cerr << "Child process failed to start" << '\n';
    exit();
  } else if(childPID > 0)
  { ////////// Parent process //////////
    // Close pipeA read
    // Close pipeC write
    // Call parent process
    wait(childPID);
  } else { // Child process
    // Create grand child process
    grandPID = fork();
    //Check if error
    if(grandPID == -1){
      std::cerr << "Grand child process failed to start" << '\n';
      exit();
    } else if(grandPID > 0)
    { ////////// Child process //////////
      // Close pipeA write
      // Close pipeB read
      // Read pipeA
      // Call child function
      // Write pipeB
      wait(grandPID);
    } else { ////////// Grand child process //////////
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
  cerr value
  perform maths()
  write to pipeA
  read pipeC
  convert to M */

/* Child function
cerr value
perform maths()
return value */

/* Grand child function
cerr value
perform maths()
return value */

/* Perform maths
convert string to int
M = 4 * M + 3;
convert to string
return string */
