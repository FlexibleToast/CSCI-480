/*******************************************************************************
   PROGRAM:			CSCI 480 Assignment 4
   PROGRAMMER:	Joseph McDade
   LOGON ID:		z1757419
   DUE DATE:		10/12/2018
	 Note:				Uses hard tabs set to display as 2 spaces

   FUNCTION:		Simulate a single processor and dealing with multiprocessing.
*******************************************************************************/

#include "Process.h"
#include "Assign4.h"

int main() {
	priority_queue<Process> Q;
	Process x, y, z;
	x.setPriority(20);
	y.setPriority(30);
	z.setPriority(30);
	z.setTimestamp(-3);
	cout << z.getTimestamp() << endl;
	Q.push(x);
	Q.push(y);
	Q.push(z);
	while(!Q.empty()){
		Process I = Q.top();
		cout << I.getPriority() << " with wait time: " << I.getTimestamp() << endl;
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
