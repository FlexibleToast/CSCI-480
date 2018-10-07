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
	while((Timer < MAX_TIME) || (entry.empty() && ready.empty() && input.empty()
		&& output.empty() && Active == nullptr && IActive == nullptr
		&& OActive == nullptr))
	{
		// Initialize Ready Queue
		if(!entry.empty())
		{	// If the entry queue isn't empty, check if need to add to ready queue
			while(entry.front().getArrivalTime() <= Timer && process_amount < AT_ONCE
				&& !entry.empty())
			{	// Add procs to ready if arrived and less than AT_ONCE
				process_amount++;
				Process x = entry.front();
				x.setTimestamp(Timer);
				ready.push(x);
				entry.pop();
				if(!entry.empty())
					x = entry.front();
			}
		}
		// Active process management
		if(Active == nullptr && !ready.empty())
		{	// Get process from ready queue if no active process
			Process x = ready.top();
			ready.pop();
			Active = new Process;
			*Active = x;
			Active->incrementCPUCount();
		} else if(Active == nullptr && ready.empty())
		{	// No active and no ready processes, CPU is idle
			cpu_idle++;
		}
		if(Active)
		{
			Active->incrementCPUTotal();
			if(Active->iterateCPUTimer() == Active->getValue())
			{
				moveQueue(Active);
				delete Active;
				Active = nullptr;
			}
		}

		// Prepare next cycle
		cout << Timer << endl;
		if(Active)
			cout << Active->getName() << endl;
		Timer++;
	}
	cout << "ready Queue contents:" << endl;
	while(!ready.empty()){
		Process X = ready.top();
		ready.pop();
		cout << "That was Process: " << X.getName() << " and Priority: "
			<< X.getPriority() << " with ArrivalTime: " << X.getArrivalTime()	<< endl;
	}

	// Print left overs
	cout << "input Queue contents:" << endl;
	while(!input.empty()){
		Process X = input.top();
		input.pop();
		cout << "That was Process: " << X.getName() << " and Priority: "
			<< X.getPriority() << " with ArrivalTime: " << X.getArrivalTime()	<< endl;
	}
	cout << "output Queue contents:" << endl;
	while(!output.empty()){
		Process X = output.top();
		output.pop();
		cout << "That was Process: " << X.getName() << " and Priority: "
			<< X.getPriority() << " with ArrivalTime: " << X.getArrivalTime()	<< endl;
	}
	cout << "entry Queue contents:" << endl;
	while(!entry.empty()){
		Process X = entry.front();
		entry.pop();
		cout << "That was Process: " << X.getName() << " and Priority: "
			<< X.getPriority() << " with ArrivalTime: " << X.getArrivalTime()	<< endl;
	}
	cout << "terminated Queue contents:" << endl;
	while(!terminated.empty()){
		Process X = terminated.front();
		terminated.pop();
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
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void terminate_proc(){
	cout << "Terminating " << Active->getName() << ", spent total of "
		<< Active->getCPUTotal() << " cycles in CPU" << endl;
	terminated.push(*Active);
	process_amount--;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void moveQueue(Process *X)
{
	char nextEvent = X->getNextEvent();
	if(nextEvent == 'I'){
		input.push(*X);
	} else if(nextEvent == 'O'){
		output.push(*X);
	} else if(nextEvent == 'C'){
		ready.push(*X);
	} else {
		terminate_proc();
	}
}
