/*******************************************************************************
   PROGRAM:			CSCI 480 Assignment 4
   PROGRAMMER:	Joseph McDade
   LOGON ID:		z1757419
   DUE DATE:		10/12/2018
	 Note:				Uses hard tabs set to display as 2 spaces

   FUNCTION:		Simulate a single processor and dealing with multiprocessing.
*******************************************************************************/

#include <iostream>
#include <queue>
#include "Process.h"

// Prototyping statements

// Set global constants
#define MAX_TIME 500
#define AT_ONCE 5
#define QUEUE_SIZE 20
#define ARRAY_SIZE 10
#define HOW_OFTEN 25

int main() {
	priority_queue<Process> Q;
	Process x, y, z;
	x.setPriority((unsigned)20);
	y.setPriority((unsigned)30);
	z.setPriority((unsigned)1000);
	if(x > y)
		cout << "x is larger than y" << endl;
	else
		cout << "y is larger than x" << endl;
	Q.push(x);
	Q.push(y);
	Q.push(z);
	while(!Q.empty()){
		Process I = Q.top();
		cout << I.getPriority() << endl;
		Q.pop();
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
