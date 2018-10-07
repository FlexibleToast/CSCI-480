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
	// Initialize Ready Queue
	{	// If the entry queue isn't empty, check if need to add to ready queue
		while(entry.front().getArrivalTime() <= Timer && process_amount < AT_ONCE
			&& !entry.empty())
		{	// Add procs to ready if arrived and less than AT_ONCE
			process_amount++;
			Process x = entry.front();
			x.setTimestamp(Timer);
			cout << "Process " << x.getName()
				<< " is moving to ready queue at timer: " << Timer << endl;
			ready.push(x);
			entry.pop();
			if(!entry.empty())
				x = entry.front();
		}
	}
	while((Timer < MAX_TIME) && !(entry.empty() && ready.empty() && input.empty()
		&& output.empty() && Active == nullptr && IActive == nullptr
		&& OActive == nullptr))
	{	// While we haven't reached MAX_TIME and still processes to process
		// Print status of simulation if at multiple of HOW_OFTEN
		if(Timer > 0 && Timer % HOW_OFTEN == 0)
			printStats();
		if(!entry.empty() && process_amount < AT_ONCE)
		{	// If the entry queue isn't empty and we can process more, check next proc
			if(entry.front().getArrivalTime() <= Timer)
			{	// If process has arrived, move to ready queue
				process_amount++;
				Process x = entry.front();
				x.setTimestamp(Timer);
				cout << endl << "Process " << x.getName()
					<< " is moving to ready queue at timer: " << Timer << endl;
				ready.push(x);
				entry.pop();
			}
		}
		// Activate processes from queues
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
		if(IActive == nullptr && !input.empty())
		{	// Get process from input queue if no active process
			Process x = input.top();
			input.pop();
			IActive = new Process;
			*IActive = x;
			IActive->incrementICount();
		}
		if(OActive == nullptr && !output.empty())
		{	// Get process from output queue if no active process
			Process x = output.top();
			output.pop();
			OActive = new Process;
			*OActive = x;
			OActive->incrementOCount();
		}

		// Process the Active processes
		if(Active)
		{
			Active->incrementCPUTotal();
			if(Active->iterateCPUTimer() == Active->getValue())
			{
				Active->addQueuetime(Timer);
				Active->clearCPUTimer();
				moveQueue(Active);
				delete Active;
				Active = nullptr;
			}
		}
		if(IActive)
		{
			IActive->incrementITotal();
			if(IActive->iterateIOTimer() == IActive->getValue())
			{
				IActive->addQueuetime(Timer);
				IActive->clearIOTimer();
				moveQueue(IActive);
				delete IActive;
				IActive = nullptr;
			}
		}
		if(OActive)
		{
			OActive->incrementOTotal();
			if(OActive->iterateIOTimer() == OActive->getValue())
			{
				OActive->addQueuetime(Timer);
				OActive->clearIOTimer();
				moveQueue(OActive);
				delete OActive;
				OActive = nullptr;
			}
		}

		// Prepare next cycle
		Timer++;
	}
	cout << "********************************************************************"
		<< endl << "  Simulation Terminated" << endl << endl
		<< "  Total cycles:" << Timer << endl
		<< "  Total terminated processes:" << terminated_total << endl
		<< "  Total CPU idle time:" << cpu_idle << endl << endl;
	// Print left overs in queues
	if(!entry.empty())
	{	// Print leftovers from entry queue
		cout << "Processes in the entry queue:" << endl;
		while(!entry.empty()){
			Process X = entry.front();
			entry.pop();
			cout << " " << X.getProcessID();
		}
		cout << endl;
	}
	if(!ready.empty())
	{	// Print leftovers from ready queue
		cout << "Processes in the ready queue:" << endl;
		while(!ready.empty()){
			Process X = ready.top();
			ready.pop();
			cout << " " << X.getProcessID();
		}
		cout << endl;
	}
	if(!input.empty())
	{	// Print leftovers from input queue
		cout << "Processes in the input queue:" << endl;
		while(!input.empty()){
			Process X = input.top();
			input.pop();
			cout << " " << X.getProcessID();
		}
		cout << endl;
	}
	if(!output.empty())
	{	// Print leftovers from output queue
		cout << "Processes in the output queue:" << endl;
		while(!output.empty()){
			Process X = output.top();
			output.pop();
			cout << " " << X.getProcessID();
		}
		cout << endl;
	}
	if(!terminated.empty())
	{	// Print leftovers from terminated queue
		cout << "Processes that terminated:" << endl;
		while(!terminated.empty()){
			Process X = terminated.front();
			terminated.pop();
			cout << " " << X.getProcessID();
		}
		cout << endl;
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
	cout << endl
		<< "** Terminating " << Active->getName() << " that had priority: "
		<< Active->getPriority() << " **" << endl
		<< setw(32) << left << "  Number of CPU bursts:"
			<< setw(4) << right << Active->getCPUCount() << endl
		<< setw(32) << left << "  Number of Input bursts:"
			<< setw(4) << right << Active->getICount() << endl
		<< setw(32) << left << "  Number of Output bursts:"
			<< setw(4) << right << Active->getOCount() << endl
		<< setw(32) << left << "  Time spent in CPU:"
			<< setw(4) << right << Active->getCPUTotal() << endl
		<< setw(32) << left << "  Time spent in Input:"
			<< setw(4) << right << Active->getITotal() << endl
		<< setw(32) << left << "  Time spent in Output:"
			<< setw(4) << right << Active->getOTotal() << endl
		<< setw(32) << left << "  Time spent waiting in queues:"
			<< setw(4) << right << Active->getQueuetime() << endl
		<< setw(32) << left << "  Current cycle: "
			<< setw(4) << right << Timer << endl;;
	terminated.push(*Active);
	process_amount--;
	terminated_total++;
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
		X->setTimestamp(Timer);
		input.push(*X);
	} else if(nextEvent == 'O'){
		X->setTimestamp(Timer);
		output.push(*X);
	} else if(nextEvent == 'C'){
		X->setTimestamp(Timer);
		ready.push(*X);
	} else {
		terminate_proc();
	}
}

void printStats(){
	queue<Process> temp_entry, temp_ready, temp_input, temp_output;
	cout << endl
		<< "***** Current Simlation Status as of Timer: "
		<< setw(4) << right << Timer << " *****" << endl;
	if(Active)
			cout << Active->getName() << " is Active process with PID: "
			<< Active->getProcessID() << endl;
	if(IActive)
		cout << IActive->getName() << " is IActive process with PID: "
			<< IActive->getProcessID() << endl;
	if(OActive)
		cout << OActive->getName() << " is OActive process with PID: "
			<< OActive->getProcessID() << endl;
	if(!entry.empty())
	{
		cout << "Current processes in entry queue:";
		while(!entry.empty())
		{
			Process X = entry.front();
			cout << " " << X.getProcessID();
			temp_entry.push(X);
			entry.pop();
		}
		cout << endl;
		// Rebuild entry queue
		while(!temp_entry.empty())
		{
			entry.push(temp_entry.front());
			temp_entry.pop();
		}
	}
	if(!ready.empty())
	{
		cout << "Current processes in ready queue:";
		while(!ready.empty())
		{
			Process X = ready.top();
			cout << " " << X.getProcessID();
			temp_ready.push(X);
			ready.pop();
		}
		cout << endl;
		// Rebuild ready queue
		while(!temp_ready.empty())
		{
			ready.push(temp_ready.front());
			temp_ready.pop();
		}
	}
	if(!output.empty())
	{
		cout << "Current processes in output queue:";
		while(!output.empty())
		{
			Process X = output.top();
			cout << " " << X.getProcessID();
			temp_output.push(X);
			output.pop();
		}
		cout << endl;
		// Rebuild output queue
		while(!temp_output.empty())
		{
			output.push(temp_output.front());
			temp_output.pop();
		}
	}
}
