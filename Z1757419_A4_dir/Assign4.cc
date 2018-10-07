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
	// Create Queues
	queue<Process> entry = buildEntryQueue();
	priority_queue<Process> ready, input, output;
	Process X;

	while((Timer < MAX_TIME) || (entry.empty() && ready.empty() && input.empty()
		&& output.empty() && Active == nullptr && IActive == nullptr
		&& OActive == nullptr))
	{
		// Initialize Ready Queue
		if(!entry.empty())
			X = entry.front();
		while(X.getArrivalTime() <= Timer && process_amount < AT_ONCE)
		{
			process_amount++;
			X.setTimestamp(Timer);
			ready.push(X);
			entry.pop();
			X = entry.front();
		}
		Timer++;
	}
	while(!ready.empty()){
		X = ready.top();
		ready.pop();
		cout << "That was Process: " << X.getName() << " and Priority: "
			<< X.getPriority() << " with ArrivalTime: " << X.getArrivalTime()	<< endl;
	}
	while(!entry.empty()){
		X = entry.front();
		entry.pop();
		cout << "That was Process: " << X.getName() << " and Priority: "
			<< X.getPriority() << " with ArrivalTime: " << X.getArrivalTime()	<< endl;
	}
	cout << Timer << endl;
  return 0;
}
/////////////////////////////////  Functions  //////////////////////////////////
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
queue<Process> buildEntryQueue(){
	queue<Process> entry;
	ifstream inFile;
	inFile.open("data4.txt");
	if(inFile.fail())
	{
		cerr << "Input file data4.txt failed to open" << endl;
		exit(-1);
	}
	string line;
	char* tokens;
	Process p;
	pid_t PID = 100;
	queue<string> inputQueue;
	while(getline(inFile, line))
	{	// Get first line of parameters for Process
		tokens = strtok((char*)line.c_str(), " ");
		if(strcmp(tokens, "STOPHERE") == 0)
			break;
		while(tokens)
		{
			inputQueue.push(string(tokens));
			tokens = strtok(NULL, " ");
		}
		// Get second line of parameters for Process
		getline(inFile, line);
		tokens = strtok((char*)line.c_str(), " ");
		while(tokens)
		{
			inputQueue.push(string(tokens));
			tokens = strtok(NULL, " ");
		}
		p.importQueue(inputQueue, PID++);
		entry.push(p);
	}
	return entry;
}
